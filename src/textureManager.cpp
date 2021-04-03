#include "textureManager.hpp"

SDL_Texture *TextureManager::LoadTexture(const char *filename) {
  SDL_Surface *tempSurface = IMG_Load(filename);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

  SDL_FreeSurface(tempSurface);
  return texture;
}

SDL_Texture *TextureManager::LoadTextureText(TTF_Font *font, const char *text,
                                             SDL_Color color) {
  SDL_Surface *tempSurface = TTF_RenderText_Solid(font, text, color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

  SDL_FreeSurface(tempSurface);
  return texture;
}
