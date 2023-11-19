
#include "Timer.hpp"

#include "Benchmark.hpp"

Timer::Timer()
{
    start = std::chrono::high_resolution_clock::now();
}

Timer::Timer(const std::string& name)
{
    funcName = name;
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;

    Benchmark::Get().addFuncCall(funcName, duration.count());
}
