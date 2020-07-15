#include "character.h"


cCharacter::cCharacter(SDL_Window *window, SDL_Renderer *renderer)
{
    m_x = 320;
    m_y = 90;

    m_currentState = IDLE;
    m_currentFrame = 0;
    m_faceDirection = DOWN;

    m_mainSpriteSheet.loadFromFile(window, renderer, "spriteSheet.jpeg");
}

cCharacter::~cCharacter()
{
    m_mainSpriteSheet.free();
}


void cCharacter::render(SDL_Renderer *renderer)
{
    SDL_Rect renderQuad = { 0, 0, m_mainSpriteSheet.get_width() / 4, m_mainSpriteSheet.get_height() / 4 };

    switch(m_faceDirection)
    {
        case UP:    renderQuad.y = m_mainSpriteSheet.get_height() / 4 * 3; break;
        case DOWN:  renderQuad.y = m_mainSpriteSheet.get_height() / 4 * 0; break;
        case LEFT:  renderQuad.y = m_mainSpriteSheet.get_height() / 4 * 1; break;
        case RIGHT: renderQuad.y = m_mainSpriteSheet.get_height() / 4 * 2; break;
    }

    if(m_currentState == WALKING)
    {
        switch(m_currentFrame / 10)
        {
            case 0: renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 0; break;
            case 1: renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 1; break;
            case 2: renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 2; break;
            case 3: renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 3; break;
        }
    }

    m_mainSpriteSheet.render(renderer, m_x, m_y, &renderQuad);
}

void cCharacter::handleEvent(SDL_Event &e)
{
    switch(e.type)
    {
        case SDL_KEYDOWN:
            switch(e.key.keysym.sym)
            {
                case SDLK_UP:    m_faceDirection = UP;    break;
                case SDLK_DOWN:  m_faceDirection = DOWN;  break;
                case SDLK_LEFT:  m_faceDirection = LEFT;  break;
                case SDLK_RIGHT: m_faceDirection = RIGHT; break;
            }

            if(m_currentState != WALKING)
                m_currentFrame = 10;

            m_currentState = WALKING;
            break;

        case SDL_KEYUP:
            m_currentState = IDLE;
            break;
    }
}

void cCharacter::move()
{
    if(m_currentState == WALKING)
    {
        switch(m_faceDirection)
        {
            case UP:    m_y -= 2; break;
            case DOWN:  m_y += 2; break;
            case LEFT:  m_x -= 2; break;
            case RIGHT: m_x += 2; break;
        }
    }
}

void cCharacter::nextFrame()
{
    switch(m_currentState)
    {
        case IDLE:
            m_currentFrame = 0;
            break;
        
        case WALKING:
            m_currentFrame++;

            if(m_currentFrame / 10 > 3)
                m_currentFrame = 0;
            break;
    }
}
