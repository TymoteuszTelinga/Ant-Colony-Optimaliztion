
#pragma once

#include <chrono>
#include <string>

class Timer
{
private:
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<float> duration;
    std::string funcName;

public:
    Timer();
    Timer(const std::string& name);
    ~Timer();
};
