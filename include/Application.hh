#pragma once

#include <string>
#include <vector>

#include <SDL2/SDL.h>



struct WindowProps
{
    int width;
    int height;
    std::string title;

    WindowProps(int width, int height, const std::string& title)
    :   width(width), height(height), title(title)
    {

    }
};

class Application
{
public:
    Application(const WindowProps& props);
    void run();
    void showMenu() const;
    void bubbleSort(std::vector<int>& data) const;
    void selectionSort(std::vector<int>& data) const;
    void insertionSort(std::vector<int>& data) const;
    void mergeSort(std::vector<int>& data, int left, int right) const;
    void merge(std::vector<int>& data, int left, int mid, int right) const;
    void quicksort(std::vector<int>& data, int left, int right) const;
    int partition(std::vector<int>& data, int left, int right) const;


private:
    SDL_Renderer* m_renderer = nullptr;
    SDL_Window* m_window = nullptr;

    bool m_running = true;

    WindowProps m_windowProps;
};