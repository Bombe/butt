// aac encoding functions for butt
//
// Copyright 2007-20016 by Daniel Noethen.
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

#ifndef AAC_ENCODE_H
#define AAC_ENCODE_H

#include <fdk-aac/aacenc_lib.h>

struct aac_enc {
	HANDLE_AACENCODER handle;
	AACENC_InfoStruct info;
    int aot;
    int overwrite_aot;
    int bitrate;
    int samplerate;
    int channel;
    volatile int state;
};

enum {
    AAC_READY = 0,
    AAC_BUSY = 1
};

int aac_enc_init(aac_enc *aac);
int aac_enc_encode(aac_enc *aac, short *pcm_buf, char *enc_buf, int samples, int size);
int aac_enc_reinit(aac_enc *aac);
void aac_enc_close(aac_enc *aac);

#endif

