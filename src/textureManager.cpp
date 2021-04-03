#include "textureManager.hpp"
#include "SDL_render.h"

SDL_Texture *TextureManager::LoadTexture(const char *filename) {
  SDL_Surface *tempSurface = IMG_Load(filename);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

  SDL_FreeSurface(tempSurface);
  return texture;
}

SDL_Texture *TextureManager::LoadTextureText(const char *text, SDL_Color color) {
  SDL_Surface *tempSurface = TTF_RenderText_Solid(Game::font, text, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

  SDL_FreeSurface(tempSurface);
  return texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dest) {
  SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
