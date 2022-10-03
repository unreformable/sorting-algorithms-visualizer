#include "Application.hh"

#include <algorithm>
#include <iostream>
#include <random>

#define DELAY 1



Application::Application(const WindowProps& props)
:   m_windowProps(props)
{
    SDL_CreateWindowAndRenderer(props.width, props.height, 0, &m_window, &m_renderer);
    SDL_SetWindowTitle(m_window, props.title.c_str());
}

void Application::run()
{
    // Set up random number distribution
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distrib(0, 100);

    // Values to be sorted
    std::vector<int> data;
    data.reserve(100);

    // Fill data with random numbers
    for(int i = 0; i < 100; ++i)
    {
        data.push_back(distrib(engine));
    }

    showMenu();

    while(m_running)
    {
        SDL_Event event;
        while(SDL_WaitEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                m_running = false;
                break;
            }
            else if(event.type == SDL_KEYUP)
            {
                switch(event.key.keysym.scancode)
                {
                    case SDL_SCANCODE_ESCAPE:
                    {
                        SDL_Event quit_event{SDL_QUIT};
                        SDL_PushEvent(&quit_event);
                        break;
                    }
                    case SDL_SCANCODE_0:
                    {
                        std::cout << std::endl;
                        std::cout << "Bubble Sort has been selected" << std::endl;
                        std::cout << "Displaying..." << std::endl;
                        bubbleSort(data);
                        std::cout << "Done!" << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                    case SDL_SCANCODE_1:
                    {
                        std::cout << std::endl;
                        std::cout << "Selection Sort has been selected" << std::endl;
                        std::cout << "Displaying..." << std::endl;
                        selectionSort(data);
                        std::cout << "Done!" << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                    case SDL_SCANCODE_2:
                    {
                        std::cout << std::endl;
                        std::cout << "Insertion Sort has been selected" << std::endl;
                        std::cout << "Displaying..." << std::endl;
                        insertionSort(data);
                        std::cout << "Done!" << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                    case SDL_SCANCODE_3:
                    {
                        std::cout << std::endl;
                        std::cout << "Merge Sort has been selected" << std::endl;
                        std::cout << "Displaying..." << std::endl;
                        std::vector<int> tmp(data);
                        mergeSort(tmp, 0, tmp.size() - 1);
                        std::cout << "Done!" << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                    case SDL_SCANCODE_4:
                    {
                        break;
                    }
                    case SDL_SCANCODE_5:
                    {
                        break;
                    }
                    case SDL_SCANCODE_6:
                    {
                        break;
                    }
                    case SDL_SCANCODE_7:
                    {
                        break;
                    }
                    case SDL_SCANCODE_8:
                    {
                        break;
                    }
                    case SDL_SCANCODE_9:
                    {
                        break;
                    }
                }
            }
        }
    }
}

void Application::showMenu() const
{
    std::cout << std::endl;
    std::cout << "AVAILABLE OPTIONS:" << std::endl;
    std::cout << "0. Bubble Sort" << std::endl;
    std::cout << "1. Selection Sort" << std::endl;
    std::cout << "2. Insertion Sort" << std::endl;
    std::cout << "3. Merge Sort" << std::endl;
    std::cout << "4. Quicksort" << std::endl;
    std::cout << "5. Counting Sort" << std::endl;
    std::cout << "6. Radix Sort" << std::endl;
    std::cout << "7. Bucket Sort" << std::endl;
    std::cout << "8. Heap Sort" << std::endl;
    std::cout << "9. Shell Sort" << std::endl;
    std::cout << std::endl;
}

void Application::bubbleSort(std::vector<int> data) const
{
    int comparasions = 0;
    int swaps = 0;
    // Launch sorting algorithm
    for(int i = 0; i < data.size(); ++i)
    {
        for(int j = 0; j < data.size() - i - 1; ++j)
        {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            draw(data, j, j + 1);
            SDL_RenderPresent(m_renderer);
            SDL_Delay(DELAY);

            if(data[j] > data[j + 1])
            {
                std::swap(data[j], data[j + 1]);
                ++swaps;
            }
            ++comparasions;
        }
    }
    std::cout << "Total comparasions: " << comparasions << std::endl;
    std::cout << "Total swaps: " << swaps << std::endl;
}

void Application::selectionSort(std::vector<int> data) const
{
    int comparasions = 0;
    int swaps = 0;
    for(int i = 0; i < data.size(); ++i)
    {
        int min_index = i;
        for(int j = i + 1; j < data.size(); ++j)
        {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            draw(data, j, min_index);
            SDL_RenderPresent(m_renderer);
            SDL_Delay(DELAY);

            if(data[j] < data[min_index])
            {
                min_index = j;
            }
            ++comparasions;
        }
        std::swap(data[min_index], data[i]);
        ++swaps;
    }
    std::cout << "Total comparasions: " << comparasions << std::endl;
    std::cout << "Total swaps: " << swaps << std::endl;
}

void Application::insertionSort(std::vector<int> data) const
{
    int comparasions = 0;
    for(int i = 1; i < data.size(); ++i)
    {
        int key = data[i];
        int j = i - 1;
        while(j >= 0 && key < data[j])
        {
            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            draw(data, i, j);
            SDL_RenderPresent(m_renderer);
            SDL_Delay(DELAY);

            data[j + 1] = data[j];
            ++comparasions;
            --j;
        }
        data[j + 1] = key;
    }
    std::cout << "Total comparasions: " << comparasions << std::endl;
}

void Application::mergeSort(std::vector<int>& data, int left, int right) const
{
    if(left == right)
        return;

    int mid = (left + right)/2;
    mergeSort(data, left, mid);
    mergeSort(data, mid + 1, right);
    merge(data, left, mid, right);
}

void Application::merge(std::vector<int>& data, int left, int mid, int right) const
{
    std::vector<int> left_data{data.begin() + left, data.begin() + mid + 1};
    std::vector<int> right_data{data.begin() + mid + 1, data.begin() + right + 1};


    int i = 0;          // left_data iterator index
    int j = 0;          // right_data iterator index
    int k = left;       // data iterator index

    while(i < left_data.size() && j < right_data.size())
    {
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
        draw(data, i, j);
        SDL_RenderPresent(m_renderer);
        SDL_Delay(DELAY);

        if(left_data[i] < right_data[j])
        {
            data[k] = left_data[i];
            ++i;
        }
        else
        {
            data[k] = right_data[j];
            ++j;
        }
        ++k;
    }

    if(i < left_data.size())
    {
        do {
            data[k] = left_data[i];
            ++i;
            ++k;

            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            draw(data, i, j);
            SDL_RenderPresent(m_renderer);
            SDL_Delay(DELAY);
        } while(i < left_data.size());
    }
    else if(j < right_data.size())
    {
        do {
            data[k] = right_data[j];
            ++j;
            ++k;

            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            draw(data, i, j);
            SDL_RenderPresent(m_renderer);
            SDL_Delay(DELAY);
        } while(j < right_data.size());
    }
}

void Application::draw(const std::vector<int>& data, int compared1, int compared2) const
{
    const int elem_count = data.size();
    const int max_value = 100;

    // Smallest part of drawn data
    const int rect_w = m_windowProps.width / elem_count;
    const int rect_h = - m_windowProps.height / max_value;

    // Draw all data values
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    for(int i = 0; i < data.size(); ++i)
    {
        SDL_Rect rect{rect_w * i, m_windowProps.height, rect_w, rect_h * data[i]};
        SDL_RenderFillRect(m_renderer, &rect);
    }
    {   // Highlight in red the first compared value
        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
        SDL_Rect rect{rect_w * compared1, m_windowProps.height, rect_w, rect_h * data[compared1]};
        SDL_RenderFillRect(m_renderer, &rect);
    }
    {   // Highlight in red the second compared value
        SDL_Rect rect{rect_w * compared2, m_windowProps.height, rect_w, rect_h * data[compared2]};
        SDL_RenderFillRect(m_renderer, &rect);
    }
}