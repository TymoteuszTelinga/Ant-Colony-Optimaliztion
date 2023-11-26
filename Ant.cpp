
#include "Ant.h"
#include "random.h"
#include <math.h>
#include <iostream>
#include <numeric>

// #include "Benchmark.hpp"

#include "Benchmark.hpp"

Ant::Ant(const AntColony& colony)
    :m_Contex(colony), m_NotVisited(colony.m_Size, 0), m_NotVisitedSize(colony.m_Size)
{
    std::iota(m_NotVisited.begin(), m_NotVisited.end(), 0);
}

Ant::~Ant()
{
    
}

void Ant::Run()
{
    //MEASURE_NAME("Run Init")
    // std::cout<<"New Path\n";
    std::iota(m_NotVisited.begin(), m_NotVisited.end(), 0);
    m_NotVisitedSize = m_NotVisited.size();

    int index = lehmer32()%m_Contex.m_Size; // chose random start index
    m_CurrentIndex = m_NotVisited[index];
    PopIndex(index);

    m_TotalCost = 0.0f;
    // std::vector<int> path;
    // path.push_back(m_CurrentIndex);

    //while (path.size() < m_Contex.m_Size)
    for(uint32_t i = 1; i < m_Contex.m_Size; i++)
    {
        int index = ChoseRandomNeighbor();
        int nextIndex = m_NotVisited[index];
         m_TotalCost += m_Contex.m_Graph.GetDistance(m_CurrentIndex, nextIndex);

        m_CurrentIndex = nextIndex;
        // path.push_back(m_CurrentIndex);
        PopIndex(index);
    }

    m_TotalCost += m_Contex.m_Graph.GetDistance(m_NotVisited.front(), m_NotVisited.back());
}

float Ant::CalculateWeight(int nextIndex) const
{
    // MEASURE

    // float dis = m_Contex.m_Graph.GetDistance(m_CurrentIndex, nextIndex);
    // float pheromoneStr = m_Contex.GetPheromone(m_CurrentIndex, nextIndex);
    // float desirability = std::pow(1/dis, m_DistancePower) * std::pow(pheromoneStr, m_PheromonePower);
    float dis = m_Contex.GetDistanceWeight(m_CurrentIndex, nextIndex);
    float pheromoneStr = m_Contex.GetPheromone(m_CurrentIndex, nextIndex);
    float desirability = dis * std::pow(pheromoneStr, m_PheromonePower);
    return desirability;
}

int Ant::ChoseRandomNeighbor() const
{
    // MEASURE

    std::vector<item> neighbors(m_NotVisitedSize);
    float sumWieght = 0;
    for (int i = 0; i < m_NotVisitedSize; i++)
    {
        int vert = m_NotVisited[i];
        float weight = CalculateWeight(vert);
        sumWieght += weight;
        neighbors[i] = {i, sumWieght};
    }

    float randomWeight = fRand(0,sumWieght);
    int index = FindNeighbour(neighbors, randomWeight);
    return neighbors[index].value;

    // for (size_t i = 0; i < neighbors.size(); i++)
    // {
    //     if (randomWeight <= neighbors[i].weight)
    //     {
    //         return neighbors[i].value;
    //     }
        
    //     randomWeight -= neighbors[i].weight;
    // }
    
    // return neighbors.back().value;
}

void Ant::PopIndex(int index)
{
    // std::cout<<m_NotVisited[index]<<" | ";
    int tmp = m_NotVisited[index];
    m_NotVisited[index] = m_NotVisited[m_NotVisitedSize-1];
    m_NotVisited[m_NotVisitedSize-1] = tmp;
    m_NotVisitedSize--;

    // for (size_t i = 0; i < m_NotVisitedSize; i++)
    // {
    //     std::cout<<" "<<m_NotVisited[i];
    // }

    // std::cout<<" |";
    // for (size_t i = m_NotVisitedSize; i < m_NotVisited.size(); i++)
    // {
    //     std::cout<<" "<<m_NotVisited[i];
    // }
    
    // std::cout<<std::endl;
}

int Ant::FindNeighbour(const std::vector<item>& items, float value) const
{
    int low = 0;
    int high = items.size()-1;
    float randomWeight = Random::FRand(0,sumWieght);


    int mid;
    while (low < high)
    {
        mid = low + ((high-low) >> 1);
        if (value > items[mid].weight)
        {
            low = mid + 1;
        }
        else
        {
            high = mid;
        }
    }
    
    return low;

    // if (items[low].weight >= value)
    // {
    //     return low;
    // }

    // std::cout<<"find Error\n";
    // return 0;
}
