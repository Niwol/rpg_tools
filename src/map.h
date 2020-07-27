#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <fstream>
#include <ios>
#include <SDL2/SDL.h>

#include "texture.h"

struct sCell
{
    bool solid;

    int tmCol;
    int tmRow;
};


class cMap
{
    public:

        cMap(int cols, int rows);
        ~cMap();

        bool loadTileMap(SDL_Window *window, SDL_Renderer *renderer, std::string path, int cols, int rows, bool alpha);
        bool load(std::string path);
        bool save(std::string path);

        void render(SDL_Renderer *renderer, int x, int y);
        void renderTilemap(SDL_Renderer *renderer, int x, int y);

        void handleEvent(SDL_Event &e);

    private:

        cTexture m_tilemapTexture;

        int m_tileWidth;
        int m_tileHeight;

        int m_tilemapCols;
        int m_tilemapRows;

        int m_cols;
        int m_rows;

        int m_nCells;
        sCell *m_cells;

        int m_selectedTile;

        int m_mouseX;
        int m_mouseY;
        bool m_mouseButton1Hold;

        int m_posX;
        int m_posY;
};

#endif