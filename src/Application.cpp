#include "Application.hh"



Application::Application(const WindowProps& props)
:   m_windowProps(props)
{
    SDL_CreateWindowAndRenderer(props.width, props.height, 0, &m_window, &m_renderer);
    SDL_SetWindowTitle(m_window, props.title.c_str());
}

void Application::run()
{
    showMenu();

    while(m_running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
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
                        m_running = false;
                        break;
                    }
                    case SDL_SCANCODE_0:
                    {
                        std::cout << std::endl;
                        std::cout << "Bubble Sort has been selected" << std::endl;
                        std::cout << "Displaying..." << std::endl;
                        bubble_sort();
                        std::cout << "Done!" << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                    case SDL_SCANCODE_1:
                    {
                        break;
                    }
                    case SDL_SCANCODE_2:
                    {
                        break;
                    }
                    case SDL_SCANCODE_3:
                    {
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

void Application::bubble_sort() const
{
    // Values to be sorted
    std::vector<int> data;
    data.reserve(100);

    // Set up random number distribution
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distrib(0, 100);

    // Fill data with random numbers
    for(int i = 0; i < 100; ++i)
    {
        data.push_back(distrib(engine));
    }

    // Launch sorting algorithm
    for(int i = 0; i < data.size(); ++i)
    {
        for(int j = 0; j < data.size() - i - 1; ++j)
        {
            if(data[j] > data[j + 1])
                std::swap(data[j], data[j + 1]);

            SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
            SDL_RenderClear(m_renderer);
            draw(data, j, j + 1);
            SDL_RenderPresent(m_renderer);

            SDL_Delay(10);
        }
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