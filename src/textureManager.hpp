#ifndef __TEXTUREMANAGER_H_
#define __TEXTUREMANAGER_H_

#include "game.hpp"
#include <SDL2/SDL_ttf.h>

class TextureManager {
public:
  static SDL_Texture *LoadTexture(const char *filename);

  //  returns the text as a texture
  static SDL_Texture *LoadTextureText(TTF_Font *font, const char *text,
                                      SDL_Color color);
};

#endif // __TEXTUREMANAGER_H_
