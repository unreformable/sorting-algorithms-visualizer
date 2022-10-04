#include "SortAlgoVizualizer.hh"



SDL_Rect SortAlgoVisualizer::m_view{0, 0, 900, 900};

void SortAlgoVisualizer::draw(SDL_Renderer* renderer, const std::vector<int>& data, int max_value)
{
    // Change the scales in the x-axis and y-axis so that all elements fit on the screen
    const int x_scale = m_view.w / data.size();
    const int y_scale = m_view.h / max_value;
    SDL_RenderSetScale(renderer, x_scale, y_scale);

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Render data
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    int x_pos = m_view.x - x_scale * 1;
    const int y_bottom = m_view.y + m_view.h;
    for(int i = 0; i < data.size(); ++i)
    {
        x_pos += x_scale * 1;
        SDL_RenderDrawLine(renderer, x_pos, y_bottom, x_pos, y_bottom - y_scale * data[i]);
    }
    
    // Show result
    SDL_RenderPresent(renderer);
}

void update(SDL_Renderer* renderer, int value, int index)
{
    /* const int pixel_w = view.w / data.size();
    const int pixel_h = view.h / max_value; */
}