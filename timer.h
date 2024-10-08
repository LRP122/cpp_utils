#pragma once
#include <iostream>
#include <chrono>

struct Timer
{
     std::chrono::time_point<std::chrono::high_resolution_clock> start , end;
     std::chrono::duration<float> duration;

    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer()
    {
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float duration_ms = duration.count() * 1000.0;
        std::cout << "Runtime : " << duration_ms << "ms\n";
   }
};



