#pragma once
#include "game.hpp"

class GameObject {
    public:
        GameObject(const char *textureSheet, SDL_Renderer *ren, int x, int y);
        GameObject(SDL_Texture *texture, SDL_Renderer *ren, int x, int y);
        ~GameObject();

        void Update();
        void Render();

    private:
        int count;

        int xpos;
        int ypos;

        SDL_Texture *objTexture;
        SDL_Rect srcRect, destRect;
        SDL_Renderer *renderer;
};
