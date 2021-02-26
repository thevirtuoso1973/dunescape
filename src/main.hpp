#ifndef __MAIN_H_
#define __MAIN_H_

#include <SDL2/SDL.h>
#include <iostream>

// starts SDL & creates window
bool init();

bool loadMedia();

// frees media and closes SDL
void close();

SDL_Surface *loadSurface(std::string path);

#endif // __MAIN_H_
