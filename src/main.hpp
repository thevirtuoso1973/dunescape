#ifndef __MAIN_H_
#define __MAIN_H_

#include <SDL2/SDL.h>
#include <string>

// starts SDL & creates window
bool init();

bool loadMedia();

// frees media and closes SDL
void close();

SDL_Surface *loadSurface(std::string path);

// loads image at path as a texture
SDL_Texture *loadTexture(std::string path);

#endif // __MAIN_H_
