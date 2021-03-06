/*
 * This file is part of Moonlight Embedded.
 *
 * Copyright (C) 2015-2017 Iwan Timmer
 *
 * Moonlight is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Moonlight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Moonlight; if not, see <http://www.gnu.org/licenses/>.
 */

#include "stream/module/api.h"
#include "util/logging.h"

#include <stdio.h>

#include <SDL.h>
#include <SDL_audio.h>

#include <Limelight.h>
#include <opus_multistream.h>

#define MAX_CHANNEL_COUNT 6
#define FRAME_SIZE 240

static OpusMSDecoder *decoder;
static short pcmBuffer[FRAME_SIZE * MAX_CHANNEL_COUNT];
static SDL_AudioDeviceID dev;
static int channelCount;

static int sdl_renderer_init(int audioConfiguration, POPUS_MULTISTREAM_CONFIGURATION opusConfig, void *context, int arFlags)
{
  int rc;
  decoder = opus_multistream_decoder_create(opusConfig->sampleRate, opusConfig->channelCount, opusConfig->streams, opusConfig->coupledStreams, opusConfig->mapping, &rc);

  channelCount = opusConfig->channelCount;

  SDL_InitSubSystem(SDL_INIT_AUDIO);

  SDL_AudioSpec want, have;
  SDL_zero(want);
  want.freq = opusConfig->sampleRate;
  want.format = AUDIO_S16LSB;
  want.channels = opusConfig->channelCount;
  want.samples = opusConfig->samplesPerFrame;

  dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
  if (dev == 0)
  {
    applog_e("SDLAud", "Failed to open audio: %s", SDL_GetError());
    return -1;
  }
  else
  {
    if (have.format != want.format) // we let this one thing change.
      applog_w("SDLAud", "We didn't get requested audio format.");
    SDL_PauseAudioDevice(dev, 0); // start audio playing.
  }

  return 0;
}

static void sdl_renderer_cleanup()
{
  if (decoder != NULL)
    opus_multistream_decoder_destroy(decoder);

  SDL_CloseAudioDevice(dev);
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

static void sdl_renderer_decode_and_play_sample(char *data, int length)
{
  int decodeLen = opus_multistream_decode(decoder, (unsigned char *)data, length, pcmBuffer, FRAME_SIZE, 0);
  if (decodeLen > 0)
  {
    SDL_QueueAudio(dev, pcmBuffer, decodeLen * channelCount * sizeof(short));
  }
  else
  {
    applog_e("SDLAud", "Opus error from decode: %d", decodeLen);
  }
}

AUDIO_RENDERER_CALLBACKS audio_callbacks_sdl = {
    .init = sdl_renderer_init,
    .cleanup = sdl_renderer_cleanup,
    .decodeAndPlaySample = sdl_renderer_decode_and_play_sample,
    .capabilities = CAPABILITY_DIRECT_SUBMIT,
};

bool audio_check_sdl(PAUDIO_INFO ainfo)
{
  ainfo->valid = true;
  ainfo->configuration = AUDIO_CONFIGURATION_STEREO;
  return true;
}