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
    NO_DIRECTION = 0,
    UP           = 1,
    DOWN         = 2,
    LEFT         = 3,
    RIGHT        = 4
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

    float m_x, m_y;
    float m_speed;

    int m_currentState;
    int m_currentFrame;
    int m_faceDirection;

    bool m_keyHeld[5];

    cTexture m_mainSpriteSheet;
};

#endif