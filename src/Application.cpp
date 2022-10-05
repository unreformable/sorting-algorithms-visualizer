#include "Application.hh"
#include "SortAlgoVizualizer.hh"

#include <algorithm>
#include <iostream>
#include <random>

#define DELAY 1
#define MAX_VAL m_windowProps.height - 1



Application::Application(const WindowProps& props)
:   m_windowProps(props)
{
    // Set up window and renderer
    SDL_CreateWindowAndRenderer(props.width, props.height, 0, &m_window, &m_renderer);
    SDL_SetWindowTitle(m_window, props.title.c_str());

    // Set the part of the screen where algorithm will be displayed
    SortAlgoVisualizer::setView(SDL_Rect{0, 0, m_windowProps.width, m_windowProps.height});
}

void Application::run()
{
    // Set up random number distribution
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> distrib(0, MAX_VAL);

    // Storage for values
    std::vector<int> data;
    data.reserve(MAX_VAL);

    // Fill data with random numbers
    for(int i = 0; i < MAX_VAL; ++i)
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
                        std::vector<int> tmp(data);
                        bubbleSort(tmp);
                        std::cout << "Done!" << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                    case SDL_SCANCODE_1:
                    {
                        std::cout << std::endl;
                        std::cout << "Selection Sort has been selected" << std::endl;
                        std::cout << "Displaying..." << std::endl;
                        std::vector<int> tmp(data);
                        selectionSort(tmp);
                        std::cout << "Done!" << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                    case SDL_SCANCODE_2:
                    {
                        std::cout << std::endl;
                        std::cout << "Insertion Sort has been selected" << std::endl;
                        std::cout << "Displaying..." << std::endl;
                        std::vector<int> tmp(data);
                        insertionSort(tmp);
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
                        std::cout << std::endl;
                        std::cout << "Quickort has been selected" << std::endl;
                        std::cout << "Displaying..." << std::endl;
                        std::vector<int> tmp(data);
                        quicksort(tmp, 0, tmp.size() - 1);
                        std::cout << "Done!" << std::endl;
                        std::cout << std::endl;
                        break;
                    }
                    case SDL_SCANCODE_5:
                    {
                        std::cout << std::endl;
                        std::cout << "Counting Sort has been selected" << std::endl;
                        std::cout << "Displaying..." << std::endl;
                        std::vector<int> tmp(data);
                        countingSort(tmp);
                        std::cout << "Done!" << std::endl;
                        std::cout << std::endl;
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

void Application::bubbleSort(std::vector<int>& data) const
{
    // For each data element
    for(int i = 0; i < data.size(); ++i)
    {
        // From first element to last unsorted element
        for(int j = 0; j < data.size() - i - 1; ++j)
        {
            SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
            SDL_Delay(DELAY);

            // Swap if left element is greater than the right one
            if(data[j] > data[j + 1])
                std::swap(data[j], data[j + 1]);
        }
    }
    SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
}

void Application::selectionSort(std::vector<int>& data) const
{
    // For each data element
    for(int step = 0; step < data.size(); ++step)
    {
        // Lowest element index for actual loop
        int min_index = step;
        // From index of first unsorted element to last element
        for(int i = step + 1; i < data.size(); ++i)
        {
            SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
            SDL_Delay(DELAY);

            // Is new lowest element found?
            if(data[i] < data[min_index])
                min_index = i;
        }
        // Set lowest value element at first unsorted position
        std::swap(data[min_index], data[step]);
    }
    SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
}

void Application::insertionSort(std::vector<int>& data) const
{
    // For (almost) each data element
    for(int step = 1; step < data.size(); ++step)
    {
        // Copy the element value to the right of the first unsorted element
        const int key = data[step];
        // Index of first unsorted element
        int i = step - 1;
        // Untill index isn't negative or elements to the left of key are already sorted
        // keep moving elements to the right
        while(i >= 0 && key < data[i])
        {
            SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
            SDL_Delay(DELAY);

            data[i + 1] = data[i];
            --i;
        }
        // Fix invalid value in (i + 1) position with key value
        data[i + 1] = key;
    }
    SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
}

void Application::mergeSort(std::vector<int>& data, int left, int right) const
{
    // Stop condition - maximum division has already occurred
    if(left == right)
        return;

    // Point where array is divided into two subarrays
    int mid = (left + right)/2;
    // Recursive calls for left and right subarray
    mergeSort(data, left, mid);
    mergeSort(data, mid + 1, right);
    // Division is a thing of the past, now it's time to Conquer!
    merge(data, left, mid, right);
}

void Application::merge(std::vector<int>& data, int left, int mid, int right) const
{
    // Data beetwen left and mid index
    std::vector<int> left_data{data.begin() + left, data.begin() + mid + 1};
    // Data beetwen mid and right index
    std::vector<int> right_data{data.begin() + mid + 1, data.begin() + right + 1};


    int i = 0;          // left_data iterator index
    int j = 0;          // right_data iterator index
    int k = left;       // data iterator index

    // While left_data or right_data iterator index doesn't reach it's data end
    while(i < left_data.size() && j < right_data.size())
    {
        SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
        SDL_Delay(DELAY);

        // Insert the smaller of the values at k position 
        if(left_data[i] <= right_data[j])
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

    // Put remaining elements to data
    while(i < left_data.size())
    {
        SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
        SDL_Delay(DELAY);

        data[k] = left_data[i];
        ++i;
        ++k;
    }
    while(j < right_data.size())
    {
        SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
        SDL_Delay(DELAY);

        data[k] = right_data[j];
        ++j;
        ++k;
    }
    SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
}

void Application::quicksort(std::vector<int>& data, int left, int right) const
{
    // Stop condition - this subarray can't be divided anymore
    if(left >= right)
        return;

    // Point where array is divided into two subarrays
    int pivot = partition(data, left, right);
    // Recursive calls for subarrays
    quicksort(data, left, pivot - 1); 
    quicksort(data, pivot + 1, right);
}

int Application::partition(std::vector<int>& data, int left, int right) const
{
    // Pivot value is value of rightmost element
    int pivot_val = data[right];

    // Pointer is set to left from the leftmost element
    int ptr = left - 1;

    // Until all indexes before the pivot are visited
    for(int i = left; i < right; ++i)
    {
        // Value under index is smaller than pivot value
        if(data[i] <= pivot_val)
        {
            SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
            SDL_Delay(DELAY);

            // Move pointer to the right and swap pointer and index value
            ++ptr;
            // Swap pointer value with index value
            std::swap(data[ptr], data[i]);
        }
    }
    SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);
    SDL_Delay(DELAY);

    // Swap the pivot value with the value on the right from ptr
    std::swap(data[ptr + 1], data[right]);

    SortAlgoVisualizer::draw(m_renderer, data, MAX_VAL);

    // Return the position where partition is done
    return ptr + 1;
}

void Application::countingSort(std::vector<int>& data) const
{
    // Find the greatest value in data
    const int max_value = MAX_VAL;
    
    // Make array for counting values in range (0 - max_value)
    std::vector<int> count(max_value + 1, 0);

    // Count occurrences of values
    for(const int& val : data)
        ++count[val];

    // Make cumulative sum of the elements by adding previous values
    for(int i = 1; i <= max_value; ++i)
        count[i] += count[i - 1];
    
    // Make output array for storing sorted values
    std::vector<int> output(max_value + 1, 0);

    // Main part of counting sort algorithm
    for(const int& val : data)
    {
        // Draw state before step of algorithm
        SortAlgoVisualizer::draw(m_renderer, output, MAX_VAL);
        SDL_Delay(DELAY);

        // Assign value at correct position in output array
        output[count[val] - 1] = val;
        // Decrease count of assigned value
        --count[val];
    }

    // Final draw
    SortAlgoVisualizer::draw(m_renderer, output, MAX_VAL);

    // Assign sorted values to data
    data = output;
}