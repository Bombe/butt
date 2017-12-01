// lame encoding functions for butt
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

#include <stdlib.h>
#include <lame/lame.h>

#include "lame_encode.h"

#include "fl_funcs.h"

int lame_enc_init(lame_enc *lame)
{
    int rc;
    char info_buf[256];

    lame->gfp = lame_init();

    lame_set_num_channels(lame->gfp, lame->channel);
    lame_set_in_samplerate(lame->gfp, lame->samplerate);
    lame_set_out_samplerate(lame->gfp, lame->samplerate);
    lame_set_brate(lame->gfp, lame->bitrate);
    
    if((rc = lame_init_params(lame->gfp)) < 0)
    {
        snprintf(info_buf, sizeof(info_buf),
                "unable to init lame params %d", rc);

        print_info(info_buf, 1);
        return 1;
    }

    lame->state = LAME_READY;
    return 0;
}

int lame_enc_reinit(lame_enc *lame)
{
    if(lame != NULL)
    {
        lame_enc_close(lame);
        return lame_enc_init(lame);
    }
    return 1;
}

void lame_enc_close(lame_enc *lame)
{
    while(lame->state == LAME_BUSY)
       ;

    if (lame->gfp != NULL)
        lame_close(lame->gfp);
    
    lame->gfp = NULL;
}

int lame_enc_encode(lame_enc *lame, short *pcm_buf, char *enc_buf, int samples, int size)
{
    int rc;

    if(samples == 0 || lame->gfp == NULL)
        return 0;

    lame->state = LAME_BUSY;


    if(lame->channel == 2) // stereo
        rc = lame_encode_buffer_interleaved(lame->gfp, pcm_buf, samples, (unsigned char*)enc_buf, size);
    else // mono
        rc = lame_encode_buffer(lame->gfp, pcm_buf, pcm_buf, samples, (unsigned char*)enc_buf, size);


    lame->state = LAME_READY;

    return rc;
}

