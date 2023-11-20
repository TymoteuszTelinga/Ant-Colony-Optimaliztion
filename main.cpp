
#include <iostream>
#include "Graph.h"
#include "NearestNeighbor.h"
#include "Benchmark.hpp"
#include "AntColony.h"
#include "random.h"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cerr<<"specify file\n";
        return -1;
    }

    std::string fileName(argv[1]);
    Graph tsp(fileName);
    if (!tsp.IsGood())
    {
        return -1;
    }
    
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
    if(!spec.LoadFromFile("spec.ini"))
    {
        spec.SaveToFile("spec.ini");
    }

    AntColony aco(tsp, spec);

    float MaxValue = 0.f;
    float MinValue = std::numeric_limits<float>::infinity();
    float AvgValue = 0.f;
    for (size_t i = 0; i < 1; i++)
    {    
        {
            MEASURE_NAME("ACO")
            aco.Run();
        }

        std::cout<<"ACO: ";
        // for (auto &&i : aco.GetPath())
        // {
        //     std::cout<< i+1 << ' ';
        // }
        std::cout<<" "<<aco.GetPathCost()<<std::endl;

        AvgValue += aco.GetPathCost();
        MaxValue = std::max(MaxValue, aco.GetPathCost());
        MinValue = std::min(MinValue, aco.GetPathCost());
    }
    AvgValue /= 10.f;

    // std::cout<<"Max: "<<MaxValue<<" Min: "<<MinValue<<" Avg: "<<AvgValue<<std::endl;

    std::cout<<"end\n";
}