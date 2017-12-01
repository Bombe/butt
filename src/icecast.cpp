// icecast functions for butt
//
// Copyright 2007-2008 by Daniel Noethen.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
 #include <winsock2.h>
 #define usleep(us) Sleep(us/1000)
 #define close(s) closesocket(s)
#else
 #include <sys/types.h>
 #include <sys/socket.h>
 #include <unistd.h>
 #include <netinet/in.h> //defines IPPROTO_TCP on BSD
 #include <netdb.h>
#endif

#include <errno.h>

#include "config.h"
#include "cfg.h"
#include "butt.h"
#include "util.h"
#include "timer.h"
#include "icecast.h"
#include "strfuncs.h"
#include "sockfuncs.h"
#include "parseconfig.h"
#include "fl_funcs.h"
#include "flgui.h"

int ic_connect(void)
{
    int ret;
    int retval;
    int tries = 2;
    int opus_supported = 0;
    char auth[150];
    char b64_auth[200];
    char recv_buf[250];
    char send_buf[250];
    char msg[100];
    char *http_retval;
    static bool error_printed = 0;

    for(int try_cnt = 0; try_cnt < tries; try_cnt++)
    {

        stream_socket = sock_connect(cfg.srv[cfg.selected_srv]->addr,
                cfg.srv[cfg.selected_srv]->port, CONN_TIMEOUT);

        if(stream_socket < 0)
        {
            switch(stream_socket)
            {
                case SOCK_ERR_CREATE:
                    if(!error_printed)
                    {
                        print_info("\nconnect: Could not create network socket", 1);
                        error_printed = 1;
                    }
                    ret = 2;
                    break;
                case SOCK_ERR_RESOLVE:
                    if(!error_printed)
                    {
                        print_info("\nconnect: Error resolving server address", 1);
                        error_printed = 1;
                    }
                    ret = 1;
                    break;
                case SOCK_TIMEOUT:
                case SOCK_INVALID:
                    ret = 1;
                    break;
                default:
                    ret = 2;
            }

            ic_disconnect();
            return ret;
        }



        if (try_cnt == 0)
        {
            // Try PUT method first. Supported since icecast 2.4.0
            if(cfg.srv[cfg.selected_srv]->mount[0] != '/')
                snprintf(send_buf, sizeof(send_buf), "PUT /%s HTTP/1.1\r\n", 
                        cfg.srv[cfg.selected_srv]->mount);
            else
                snprintf(send_buf, sizeof(send_buf), "PUT %s HTTP/1.1\r\n",
                        cfg.srv[cfg.selected_srv]->mount);
            
            opus_supported = 1;
        }
        else
        {

            if(cfg.srv[cfg.selected_srv]->mount[0] != '/')
                snprintf(send_buf, sizeof(send_buf), "SOURCE /%s HTTP/1.0\r\n", 
                        cfg.srv[cfg.selected_srv]->mount);
            else
                snprintf(send_buf, sizeof(send_buf), "SOURCE %s HTTP/1.0\r\n",
                        cfg.srv[cfg.selected_srv]->mount);
        }

        sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);

        snprintf(auth, sizeof(auth), "%s:%s", cfg.srv[cfg.selected_srv]->usr, cfg.srv[cfg.selected_srv]->pwd);
        snprintf(b64_auth, sizeof(b64_auth), "%s", util_base64_enc(auth));
        snprintf(send_buf, sizeof(send_buf), "Authorization: Basic %s\r\n", b64_auth);
        sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);

        // Make butt compatible to proxies/load balancers. Thanks to boyska
        if(cfg.srv[cfg.selected_srv]->port == 80)
            snprintf(send_buf, sizeof(send_buf), "Host: %s\r\n", cfg.srv[cfg.selected_srv]->addr);
        else
            snprintf(send_buf, sizeof(send_buf), "Host: %s:%d\r\n", cfg.srv[cfg.selected_srv]->addr, cfg.srv[cfg.selected_srv]->port);
        sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);

        snprintf(send_buf, sizeof(send_buf), "User-Agent: %s\r\n", PACKAGE_STRING);
        sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);

        if(!strcmp(cfg.audio.codec, "mp3"))
            strcpy(send_buf,  "Content-Type: audio/mpeg\r\n");
        else if(!strcmp(cfg.audio.codec, "aac"))
            strcpy(send_buf,  "Content-Type: audio/aac\r\n");
        else
            strcpy(send_buf,  "Content-Type: audio/ogg\r\n");
        
        
        sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);


        if(cfg.main.num_of_icy > 0)
            snprintf(send_buf, sizeof(send_buf), "ice-name: %s\r\n", cfg.icy[cfg.selected_icy]->name);
        else
            strcpy(send_buf, "ice-name: no name\r\n");
        sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);


        if(cfg.main.num_of_icy > 0)
            snprintf(send_buf, sizeof(send_buf), "ice-public: %s\r\n", cfg.icy[cfg.selected_icy]->pub);
        else
            strcpy(send_buf, "ice-public: 0\r\n");
        sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);

        if(cfg.main.num_of_icy > 0)
        {
            snprintf(send_buf, sizeof(send_buf), "ice-url: %s\r\n", cfg.icy[cfg.selected_icy]->url);
            sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);

            snprintf(send_buf, sizeof(send_buf), "ice-genre: %s\r\n", cfg.icy[cfg.selected_icy]->genre);
            sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);

            snprintf(send_buf, sizeof(send_buf), "ice-description: %s\r\n", cfg.icy[cfg.selected_icy]->desc);
            sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);
        }


        // Send audio settings 
        snprintf(send_buf, sizeof(send_buf), 
                "ice-audio-info: "
                "ice-bitrate=%d;"
                "ice-channels=%d;"
                "ice-samplerate=%d"
                "\r\n",
                cfg.audio.bitrate,
                cfg.audio.channel,
                strcmp(cfg.audio.codec, "opus") == 0 ? 48000 : cfg.audio.samplerate);

        sock_send(&stream_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);

        sock_send(&stream_socket, "\r\n", 2, SEND_TIMEOUT);

        if(sock_recv(&stream_socket, recv_buf, sizeof(recv_buf)-1, RECV_TIMEOUT) == 0)
        {

            if (try_cnt == 0)
            {
                ic_disconnect();
                continue; //try SOURCE method if PUT method did not work
            }
            else
            {
                usleep(100000);
                ic_disconnect();
                return 1;
            }
        }

        //We need to extract the HTTP return value from the HTTP response
        //to see if the login was successfull (HTTP/1.0 200 OK)
        http_retval = strchr(recv_buf, ' ');
        if(http_retval == NULL)
        {
            usleep(100000);
            ic_disconnect();
            return 1;
        }
        //point to the beginning of the HTTP return value
        http_retval++;
        http_retval[3] = '\0';

        if((retval = atoi(http_retval)) != 200)
        {
            switch(retval)
            {
                case 401:
                    print_info("\nconnect: invalid user/password!\n", 1);
                    ic_disconnect();
                    return 2;
                    break;
                case 403:   //mountpoint already in use
                    usleep(100000); 
                    ic_disconnect();
                    return 1;
                    break;
                case 404:
                    if (try_cnt == 0)
                    {
                        ic_disconnect();// This brings compatibility to airtime server. Because they don't understand the PUT method they answer with an 404
                        opus_supported = 1; // Airtimes supports Opus
                        continue;       // Let's try the SOURCE method then...
                    }
                    print_info("\nconnect: server answered with 404!\n", 1);
                    ic_disconnect();
                    return 2;
                    break;
                default:
                    snprintf(msg, sizeof(msg), "\nconnect: server answered with %d!\n", retval);
                    print_info(msg, 1);
                    ic_disconnect();
                    return 2;
            }
        }

        // At this point the connection has been established and encoded data
        // can be send to the server

        // In case Opus is selected we need to verifiy if it is supported by
        // the server
        if(!strcmp(cfg.audio.codec, "opus"))
        {
            if (opus_supported == 1) // The server has at least version 2.4.0 (PUT method worked) or it is an airtime server, thus opus is supported.
            {
                break;
            }
            else
            {
                print_info("\nERROR: Opus is not supported by your\nIcecast server (>=1.4.0 required)!\n", 1);
                ic_disconnect();
                return 2;
            }
        }
            
        
        break;
    }


    connected = 1;

    timer_init(&stream_timer, 1);       //starts the "online" timer

    return 0;
}

int ic_send(char *buf, int buf_len)
{
    int ret;
    ret = sock_send(&stream_socket, buf, buf_len, SEND_TIMEOUT);

    if(ret == SOCK_TIMEOUT)
        ret = -1;

    return ret;
}

int ic_update_song(void)
{
    int ret;
    int web_socket;
    char send_buf[1024];
    char auth[150];
    char *song_buf;
    char *mount;

    web_socket = sock_connect(cfg.srv[cfg.selected_srv]->addr,
            cfg.srv[cfg.selected_srv]->port, CONN_TIMEOUT);

    if(web_socket < 0)
    {
        switch(web_socket)
        {
            case SOCK_ERR_CREATE:
                print_info("\nupdate_song: could not create network socket", 1);
                ret = 2;
                break;
            case SOCK_ERR_RESOLVE:
                print_info("\nupdate_song: error resolving server address", 1);
                ret = 2;
                break;
            case SOCK_TIMEOUT:
            case SOCK_INVALID:
                ret = 1;
                break;
            default:
                ret = 2;
        }

        return ret;
    }

    song_buf = strdup(cfg.main.song);

    strrpl(&song_buf, (char*)" ", (char*)"%20", MODE_ALL);
    strrpl(&song_buf, (char*)"&", (char*)"%26", MODE_ALL);

    mount = (char*)malloc(strlen(cfg.srv[cfg.selected_srv]->mount)+2);

    if(cfg.srv[cfg.selected_srv]->mount[0] != '/')
        sprintf(mount, "/%s", cfg.srv[cfg.selected_srv]->mount);
    else
        strcpy(mount, cfg.srv[cfg.selected_srv]->mount);

    snprintf(auth, sizeof(auth), "%s:%s", cfg.srv[cfg.selected_srv]->usr, cfg.srv[cfg.selected_srv]->pwd);
    
    
    if(cfg.srv[cfg.selected_srv]->port == 80)
        snprintf(send_buf, sizeof(send_buf), "Host: %s\r\n", cfg.srv[cfg.selected_srv]->addr);
    else
        snprintf(send_buf, sizeof(send_buf), "Host: %s:%d\r\n", cfg.srv[cfg.selected_srv]->addr, cfg.srv[cfg.selected_srv]->port);


    snprintf(send_buf, sizeof(send_buf), "GET /admin/metadata?mode=updinfo&mount=%s&song=%s "
                                         "HTTP/1.0\r\n"
                                         "User-Agent: %s\r\n"
                                         "Authorization: Basic %s\r\n",
                                         mount, song_buf, PACKAGE_STRING, util_base64_enc(auth));

    sock_send(&web_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);
    
    
    if(cfg.srv[cfg.selected_srv]->port == 80)
        snprintf(send_buf, sizeof(send_buf), "Host: %s\r\n\r\n", cfg.srv[cfg.selected_srv]->addr);
    else
        snprintf(send_buf, sizeof(send_buf), "Host: %s:%d\r\n\r\n", cfg.srv[cfg.selected_srv]->addr, cfg.srv[cfg.selected_srv]->port);

    sock_send(&web_socket, send_buf, strlen(send_buf), SEND_TIMEOUT);
    
    sock_close(&web_socket);
    free(song_buf);
    free(mount);

    return 0;
}

void ic_disconnect(void)
{
    sock_close(&stream_socket);
}

