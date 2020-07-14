#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "texture.h"
#include "character.h"

constexpr int SCREEN_W = 800;
constexpr int SCREEN_H = 600;

bool init(SDL_Window **w, SDL_Renderer **r);

int main()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    bool quit = false;

    if(!init(&window, &renderer))
    {
        printf("Exiting...\n");
        exit(1);
    }
    else
    {
        SDL_Event e;

        cTexture texture;
        texture.loadFromFile(window, renderer, "spriteSheet.jpeg");

        SDL_Rect clip = { 0, 0, texture.get_width() / 4, texture.get_height() / 4 };


        cCharacter character(window, renderer);


        int frameCount = 0;

        while(!quit)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_QUIT)
                    quit = true;

                if(e.type == SDL_KEYDOWN)
                {
                    switch(e.key.keysym.sym)
                    {
                        case SDLK_UP: clip.y    =  texture.get_height() / 4 * 3;  break;
                        case SDLK_DOWN: clip.y  =                             0;  break;
                        case SDLK_LEFT: clip.y  =  texture.get_height() / 4    ;  break;
                        case SDLK_RIGHT: clip.y =  texture.get_height() / 4 * 2;  break;
                    }
                }
            }


            // Rendering

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            texture.render(renderer, 10, 10);
            texture.render(renderer, 260, 90, &clip);
            
            character.render(renderer);

            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect rect = {10 + clip.x, 10 + clip.y, clip.w, clip.h};
            SDL_RenderDrawRect(renderer, &rect);

            SDL_RenderPresent(renderer);

            if(frameCount >= 10)
            {
                clip.x += texture.get_width() / 4;
                if(clip.x >= texture.get_width() - texture.get_width() / 4) clip.x = 0;
            }

            frameCount++;
            character.nextFrame();
            if(frameCount > 10) frameCount = 0;
        }
    }
    

    // Dealocating memory

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}

bool init(SDL_Window **w, SDL_Renderer **r)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_ERROR: %s", SDL_GetError());
        return 0;
    }

    int imgFlags = IMG_INIT_JPG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("IMG could not initialize! IMG_ERROR: %s", IMG_GetError());
    }

    *w = SDL_CreateWindow("RPG Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    if(!*w)
    {
        printf("Unable to create window! SDL_ERROR: %s\n", SDL_GetError());
        return false;
    }

    *r = SDL_CreateRenderer(*w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(*r == NULL)
    {
        printf("Unablel to create renderer! SDL_ERROR: %s\n", SDL_GetError());
        return false;
    }

    return true;
}