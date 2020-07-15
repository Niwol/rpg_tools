#ifndef CHARACTER_H
#define CHARAXTER_H

#include <iostream>
#include <SDL2/SDL.h>

#include "texture.h"

enum stats
{
    IDLE,
    WALKING
};

enum faceDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class cCharacter
{
    public:

        cCharacter(SDL_Window *window, SDL_Renderer *renderer);
        ~cCharacter();

        void render(SDL_Renderer *renderer);
        void handleEvent(SDL_Event &e);
        void move();
        void nextFrame();

    private:

    int m_x, m_y;

    int m_currentState;
    int m_currentFrame;
    int m_faceDirection;

    cTexture m_mainSpriteSheet;
};

#endif