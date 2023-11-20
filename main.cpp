
#include <iostream>
#include <algorithm>
#include "Graph.h"
#include "NearestNeighbor.h"
#include "Benchmark.hpp"
#include "AntColony.h"
#include "random.h"

int main()
{
    std::cout<<"Hello\n";

    Graph tsp(R"(Data\uy734.tsp)");

    NearestNeighbor nn(tsp);
    {
        MEASURE_NAME("NN")
        nn.Run();
    }

    std::cout<<"NN:  ";
    // for (auto &&i : nn.GetPath())
    // {
    //     std::cout<< i+1 << ' ';
    // }
    
    std::cout<<" "<<nn.GetPathCost()<<std::endl;

    //--------------------------------
    Slehmer32(time(NULL));
    AntColonySpec spec;
    spec.NumOfIteration = 100;
    spec.GroupSize = 200;
    spec.pheromoneIntesity = 100000;
    AntColony aco(tsp, spec);

    float MaxValue = 0.f;
    float MinValue = std::numeric_limits<float>::infinity();
    float AvgValue = 0.f;
    int tests = 2;
    for (size_t i = 0; i < tests; i++)
    {    
        {
            MEASURE_NAME("ACO")
            aco.Run();
        }

        std::cout<<"ACO: ";

        // auto path = aco.GetPath();
        // std::reverse(path.begin(), path.end());
        // for (auto &&i : path)
        // {
        //     std::cout<< i << ' ';
        // }

        std::cout<<" "<<aco.GetPathCost()<<std::endl;

        AvgValue += aco.GetPathCost();
        MaxValue = std::max(MaxValue, aco.GetPathCost());
        MinValue = std::min(MinValue, aco.GetPathCost());
    }
    AvgValue /= (float)tests;

    std::cout<<"Max: "<<MaxValue<<" Min: "<<MinValue<<" Avg: "<<AvgValue<<std::endl;

    std::cout<<"end\n";
}