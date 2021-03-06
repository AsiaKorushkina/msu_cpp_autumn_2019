#include <chrono>
#include <iostream>
#include "myfunction.h"

class Timer
{
    using clock_t = std::chrono::high_resolution_clock;
    using microseconds = std::chrono::microseconds;
public:
    Timer()
        : start_(clock_t::now())
    {
    }

    ~Timer()
    {
        const auto finish = clock_t::now();
        const auto us = 
            std::chrono::duration_cast<microseconds>
                (finish - start_).count();
        std::cout << us << " us" << std::endl;
    }

private:
    const clock_t::time_point start_;
};

int main()
{
    int N = 10000;
    int M = 10000;
    int rep = 5;
    int** mas = new int* [N];
    for (int i = 0; i < N; i++){
        mas[i] = new int [M];
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
                mas[i][j] = i + 2 * j;

    for (int i = 0; i < rep; i++){
        Timer t1;
        int sum1 = sum_by_rows(mas, N, M);
    }  

    for (int i = 0; i < rep; i++){
        Timer t2;
        int sum2 = sum_by_col(mas, N, M);
    }

    for (int i = 0; i < N; i++){
        delete [] mas[i];
    }
    delete [] mas;
    return 0;    
}