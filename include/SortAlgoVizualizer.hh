#pragma once

#include <vector>

#include <SDL2/SDL_render.h>



class SortAlgoVisualizer
{
public:
    static void setView(SDL_Rect view) { m_view = view; }

    static void draw(SDL_Renderer* renderer, const std::vector<int>& data, int max_value);
    static void hightlight(SDL_Renderer* renderer, int value, int index, SDL_Color color);
    static void update(SDL_Renderer* renderer, int value, int index);


private:
    static SDL_Rect m_view;
};