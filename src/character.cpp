#include "character.h"


cCharacter::cCharacter(SDL_Window *window, SDL_Renderer *renderer)
{
    m_x = 380;
    m_y = 280;

    m_currentState = IDLE;
    m_currnetFrame = 0;
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
        switch(m_currnetFrame / 10)
        {
            case 0: renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 0; break;
            case 1: renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 1; break;
            case 2: renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 2; break;
            case 3: renderQuad.x = m_mainSpriteSheet.get_width() / 4 * 3; break;
        }
    }

    m_mainSpriteSheet.render(renderer, m_x, m_y, &renderQuad);
}

void cCharacter::nextFrame()
{
    switch(m_currentState)
    {
        case IDLE:
            m_currnetFrame = 0;
            break;
        
        case WALKING:
            m_currnetFrame++;
            break;
    }
}
