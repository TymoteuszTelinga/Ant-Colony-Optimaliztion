
#include "Benchmark.hpp"
#include <algorithm>
#include <fstream>
#include <iomanip>

Benchmark::~Benchmark()
{
    std::ofstream file("benchmark.txt");
    if (!file.is_open())
    {
        return;
    }

    file<<std::left<<std::setw(13)<<"funcion_name"<<"|"
    <<std::right<<std::setw(5)<<"calls"<<"|"
    <<std::setprecision(2)<<std::fixed<<std::setw(15)<<"total_time(ms)"<<"|"
    <<std::setw(15)<<"min_time(ms)"<<"|"
    <<std::setw(15)<<"max_time(ms)"<<"|"
    <<std::setw(15)<<"avg_time(ms)"<<"|\n";

    for (auto &&i : performance)
    {
        file<<std::left<<std::setw(13)<<i.first<<"|"
        <<std::right<<std::setw(5)<<i.second.funcCalls<<"|"
        <<std::setprecision(2)<<std::fixed<<std::setw(15)<<i.second.totalTime*1000.f<<"|"
        <<std::setw(15)<<i.second.minTime*1000.f<<"|"
        <<std::setw(15)<<i.second.maxTime*1000.f<<"|"
        <<std::setw(15)<<i.second.totalTime/i.second.funcCalls*1000.f<<"|\n";
    }
    
    file.close();
    
}

Benchmark& Benchmark::Get()
{
    static Benchmark instance;
    return instance;
}

void Benchmark::addFuncCall(const std::string& funcName, float time)
{
    auto it = performance.find(funcName);
    if (it == performance.end())
    {
        performance[funcName] = {1,time,time,time};
        return;
    }

    (*it).second.upadte(time);

}

void Benchmark::FuncionData::upadte(float time)
{
    funcCalls++;
    totalTime += time;
    minTime = std::min(minTime, time);
    maxTime = std::max(maxTime, time);
}
