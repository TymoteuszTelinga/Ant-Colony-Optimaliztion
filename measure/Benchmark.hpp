
#pragma once

#include "Timer.hpp"
#include <string>
#include <map>

#define MEASURE Timer timer(__func__);
#define MEASURE_NAME(s) Timer timer(s);

class Benchmark
{
private:

    struct FuncionData
    {
        uint32_t funcCalls = 0;
        float totalTime = 0.0f;
        float maxTime;
        float minTime;

        void upadte(float time);
    };

    std::map<std::string,FuncionData> performance;

    Benchmark() {};

public:

    Benchmark(const Benchmark&) = delete;
    ~Benchmark();

    static Benchmark& Get();
    void addFuncCall(const std::string& funcName, float time);
};