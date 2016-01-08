/*----------------------------------------------------------------------------------------------------------------------#
#- This file is a part of FIBBAGE3DS by Leif Ericson. ------------------------------------------------------------------#
#- It may or may not compile on its own depending on what other calls/files it relies on. ------------------------------#
#- Plese do not redistribute without permission. -----------------------------------------------------------------------#
#-----------------------------------------------------------------------------------------------------------------------#
#- File that handles the loading of audio. Note that it currently only plays 16-bit PCM RAW @32000.  -------------------#
#-----------------------------------------------------------------------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <3ds.h>
#include "audio.h"

s16 *audiobuf = NULL;
s16 *sfxbuf = NULL;
#define SAMPLERATE 32000

// Loads a RAW 16-bit PCM audio file into the audio buffer, and then plays the sound/music in the local buffer.
void audio_load(const char *audio){
    if (fopen(audio, "rb")) {
        // Clear the buffer if already in use
        linearFree(audiobuf);

        // Open the file requested
        FILE *file = fopen(audio, "rb");
        // seek to end of file
        fseek(file, 0, SEEK_END);
        // file pointer tells us the size
        long int size = ftell(file);
        // seek back to start
        fseek(file, 0, SEEK_SET);
        //allocate the buffer
        audiobuf = linearAlloc(size);
        //read contents !
        fread(audiobuf, 1, size, file);
        u32 audiobuf_size = (u32)size;
        //close the file because we like being nice and tidy
        fclose(file);

        GSPGPU_FlushDataCache(NULL, (u8*)audiobuf, audiobuf_size);

        // Play the loaded audio
        //csndPlaySound(SOUND_CHANNEL(8), SOUND_REPEAT | SOUND_LINEAR_INTERP | SOUND_FORMAT_16BIT, 32000, 1.0, 0.0, (u32*)audiobuf, (u32*)audiobuf, audiobuf_size);
        //csndPlaySound(0x8, SOUND_REPEAT | SOUND_LINEAR_INTERP | SOUND_FORMAT_16BIT, 32000, (u32*)audiobuf, (u32*)audiobuf, audiobuf_size);
    }
}