#include "gameObject.hpp"
#include "textureManager.hpp"
#include "main.hpp"

GameObject::GameObject(const char *textureSheet, SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    objTexture = TextureManager::LoadTexture(textureSheet, ren);

    xpos = x;
    ypos = y;
}

GameObject::GameObject(SDL_Texture *texture, SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    objTexture = texture;

    xpos = x;
    ypos = y;
}

void GameObject::Update() {
    ++count;
}

void GameObject::Render() {
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = srcRect.h * 2;
    destRect.w = srcRect.w * 2;
    destRect.x = (xpos + count) % SCREEN_WIDTH;
    destRect.y = (ypos + count) % SCREEN_HEIGHT;

    SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject() {
    SDL_DestroyTexture(objTexture);
}
