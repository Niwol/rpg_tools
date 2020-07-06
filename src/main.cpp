#include <iostream>

#include <SDL2/SDL.h>

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

        while(!quit)
        {
            while(SDL_PollEvent(&e))
            {
                if(e.type == SDL_QUIT)
                    quit = true;
            }


            // Rendering

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);



            SDL_RenderPresent(renderer);
        }
    }
    

    // Dealocating memory

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}

bool init(SDL_Window **w, SDL_Renderer **r)
{
    SDL_Init(SDL_INIT_VIDEO);

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