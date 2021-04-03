#include "gameObject.hpp"
#include "textureManager.hpp"
#include "main.hpp"

GameObject::GameObject(const char *textureSheet, int x, int y) {
    objTexture = TextureManager::LoadTexture(textureSheet);

    xpos = x;
    ypos = y;
}

GameObject::GameObject(SDL_Texture *texture, int x, int y) {
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

    destRect.h = srcRect.h;
    destRect.w = srcRect.w;
    destRect.x = (xpos + count) % SCREEN_WIDTH;
    destRect.y = (ypos + count) % SCREEN_HEIGHT;

    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject() {
    SDL_DestroyTexture(objTexture);
}
