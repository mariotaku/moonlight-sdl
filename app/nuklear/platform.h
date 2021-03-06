#pragma once

#if NK_SDL_GLES2
#ifdef NK_IMPLEMENTATION
#define NK_SDL_GLES2_IMPLEMENTATION
#endif
#include "nuklear/platform_sdl_gles2.h"
#elif NK_SDL_GL2
#ifdef NK_IMPLEMENTATION
#define NK_SDL_GL2_IMPLEMENTATION
#endif
#include "nuklear/platform_sdl_gl2.h"
#elif NK_LGNC_GLES2
#ifdef NK_IMPLEMENTATION
#define NK_LGNC_GLES2_IMPLEMENTATION
#endif
#include "nuklear/platform_lgnc_gles2.h"
#else
#error "No valid render backend specified"
#endif