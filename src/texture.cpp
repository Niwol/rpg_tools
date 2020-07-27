#include "texture.h"

cTexture::cTexture()
{
    m_texture = NULL;

    m_width = 0;
    m_height = 0;
}

cTexture::~cTexture()
{
    free();
}

void cTexture::free()
{
    if(m_texture)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;

        m_width = 0;
        m_height = 0;
    }
}



bool cTexture::loadFromFile(SDL_Window *window, SDL_Renderer *renderer, std::string path, bool alpha)
{
    free();

    SDL_Texture *newTexture = NULL;
    Uint32 format = alpha ? SDL_PIXELFORMAT_ARGB32 : SDL_GetWindowPixelFormat(window);

    // Load surface
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        printf("Clould not load %s! IMG_ERROR: %s\n", path.c_str(), IMG_GetError());
        return false;
    }


    // Convert to display format
    SDL_Surface *formatedSurface = SDL_ConvertSurfaceFormat(loadedSurface, format, 0);
    if(formatedSurface == NULL)
    {
        printf("Could not convert surface to display format! SDL_ERROR: %s\n", SDL_GetError());

        SDL_FreeSurface(loadedSurface);

        return 0;
    }

    // Create blank texture
    newTexture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, formatedSurface->w, formatedSurface->h);
    if(newTexture == NULL)
    {
        printf("Could not create blank texture! SDL_ERROR: %s\n", SDL_GetError());

        SDL_FreeSurface(loadedSurface);
        SDL_FreeSurface(formatedSurface);

        return false;
    }

    // Fill texture
    SDL_LockTexture(newTexture, NULL, &m_pixels, &m_pitch);
    memcpy(m_pixels, formatedSurface->pixels, formatedSurface->pitch * formatedSurface->h);
    SDL_UnlockTexture(newTexture);
    m_pixels = NULL;

    if(alpha)
        SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

    m_width = formatedSurface->w;
    m_height = formatedSurface->h;
    m_texture = newTexture;

    SDL_FreeSurface(loadedSurface);
    SDL_FreeSurface(formatedSurface);

    return true;
}

void cTexture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad = { x, y, m_width, m_height};

    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    
    SDL_RenderCopy(renderer, m_texture, clip, &renderQuad);
}


bool cTexture::lockTexture()
{
    if(m_pixels != NULL)
    {
        printf("Texture is already locked!\n");
        return false;
    }

    if(SDL_LockTexture(m_texture, NULL, &m_pixels, &m_pitch) != 0)
    {
        printf("Could not lock the texture! SDL_ERROR: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool cTexture::unlockTexture()
{
    if(m_pixels == NULL)
    {
        printf("Texture is not locked!\n");
        return false;
    }

    SDL_UnlockTexture(m_texture);
    m_pixels = NULL;
    m_pitch = 0;

    return true;
}


int cTexture::get_width()    { return m_width;  }
int cTexture::get_height()   { return m_height; }

void *cTexture::get_Pixels() { return m_pixels; }
int cTexture::get_Pitch()    { return m_pitch;  }
