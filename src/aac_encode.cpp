#include <stdio.h>

#include "fl_funcs.h"
#include "aac_encode.h"
#include "wav_header.h"

FILE *fd;

int aac_enc_init(aac_enc *aac)
{
    int rc;
    char info_buf[256];

    
    if(aac->overwrite_aot == 0)
    {
        if (aac->bitrate < 48)
            aac->aot = 29;            // AAC+v2
        else if (aac->bitrate >= 96)
            aac->aot = 2;             // AAC-LC
        else
            aac->aot = 5;             // AAC+v1
    }

    
    aacEncOpen(&aac->handle, 0, aac->channel);
    aacEncoder_SetParam(aac->handle, AACENC_AOT, aac->aot);
    aacEncoder_SetParam(aac->handle, AACENC_SAMPLERATE, aac->samplerate);
    aacEncoder_SetParam(aac->handle, AACENC_CHANNELMODE, aac->channel);
    aacEncoder_SetParam(aac->handle, AACENC_CHANNELORDER, 1);
    aacEncoder_SetParam(aac->handle, AACENC_BITRATE, aac->bitrate*1000);
    aacEncoder_SetParam(aac->handle, AACENC_TRANSMUX, 2);    // taken from the example aac-enc.c
   // aacEncoder_SetParam(aac->handle, AACENC_AFTERBURNER, 1); // enable after burner


    if ((rc = aacEncEncode(aac->handle, NULL, NULL, NULL, NULL)) != AACENC_OK)
    {
        snprintf(info_buf, sizeof(info_buf), "unable to init aac params %d", rc);
        print_info(info_buf, 1);
        return 1;
    }

    aacEncInfo(aac->handle, &aac->info);

    return 0;

}

int aac_enc_reinit(aac_enc *aac)
{
    if(aac != NULL)
    {
        aac_enc_close(aac);
        return aac_enc_init(aac);
    }
    return 1;
}

void aac_enc_close(aac_enc *aac)
{
    while(aac->state == AAC_BUSY)
       ;

    if (aac->handle != NULL)
        aacEncClose(&aac->handle);
    
    aac->handle = NULL;
}



int aac_enc_encode(aac_enc *aac, short *pcm_buf, char *enc_buf, int samples, int size)
{
    int rc;
    AACENC_BufDesc in_buf = { 0 }, out_buf = { 0 };
    AACENC_InArgs in_args = { 0 };
    AACENC_OutArgs out_args = { 0 };

    int in_identifier = IN_AUDIO_DATA;
    int in_size, in_elem_size;
    int out_identifier = OUT_BITSTREAM_DATA;
    int out_size, out_elem_size;
    void *in_ptr, *out_ptr;


    if(samples == 0 || aac->handle == NULL)
        return 0;

    in_size = samples*sizeof(short)*aac->channel;
    in_elem_size = sizeof(short);
    
    in_ptr = pcm_buf;
    in_args.numInSamples = samples*aac->channel;
    in_buf.numBufs = 1;
    in_buf.bufs = &in_ptr;
    in_buf.bufferIdentifiers = &in_identifier;
    in_buf.bufSizes = &in_size;
    in_buf.bufElSizes = &in_elem_size; 

    out_ptr = enc_buf;
    out_size = size;
    out_elem_size = 1;
    out_buf.numBufs = 1;
    out_buf.bufs = &out_ptr;
    out_buf.bufferIdentifiers = &out_identifier;
    out_buf.bufSizes = &out_size;
    out_buf.bufElSizes = &out_elem_size;


    aac->state = AAC_BUSY;
    
    
    if ((rc = aacEncEncode(aac->handle, &in_buf, &out_buf, &in_args, &out_args)) != AACENC_OK)
    {
        printf("Encoding failed: %d\n", rc);
        return 0;
    }

    aac->state = AAC_READY;

    return out_args.numOutBytes;
}
