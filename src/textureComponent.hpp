#ifndef __TEXTURECOMPONENT_H_
#define __TEXTURECOMPONENT_H_

#include "ecs.hpp"
#include "gridPositionComponent.hpp"
#include "textureManager.hpp"

class TextureComponent : public Component {
private:
  SDL_Rect srcRect, destRect;

  SDL_Texture *texture;

public:
  TextureComponent(const char *text, SDL_Color color) {
    this->texture = TextureManager::LoadTextureText(text, color);

    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;
  }

  void draw() override {
    if (entity->hasComponent<GridPositionComponent>()) {
      auto &gridComponent = entity->getComponent<GridPositionComponent>();

      destRect.h = srcRect.h;
      destRect.w = srcRect.w;
      destRect.x = srcRect.w * gridComponent.col();
      destRect.y = srcRect.h * gridComponent.row();

      SDL_RenderDrawRect(Game::renderer, &destRect);
      SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
    }
  }

  ~TextureComponent() { SDL_DestroyTexture(texture); }
};

#endif // __TEXTURECOMPONENT_H_
