#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class cTexture
{
    public:

        // Contructor / destructor
        cTexture();
        ~cTexture();
        void free();

        // Methods
        bool loadFromFile(SDL_Window *window, SDL_Renderer *renderer, std::string path, bool alpha = false);
        void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = NULL);

        bool lockTexture();
        bool unlockTexture();

        // Accessors
        int get_width();
        int get_height();

        void *get_Pixels();
        int get_Pitch();

    private:

        // The texture
        SDL_Texture *m_texture;
        void *m_pixels;
        int m_pitch;

        // Dimensins
        int m_width;
        int m_height;
};


#endif