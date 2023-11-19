
#include "Ant.h"
#include "random.h"
#include <math.h>
#include <iostream>
#include <numeric>

Ant::Ant(const AntColony& colony)
    :m_Contex(colony), m_NotVisited(colony.m_Size, 0), m_NotVisitedSize(colony.m_Size)
{

}

Ant::~Ant()
{
    
}

std::pair<std::vector<int>, float> Ant::Run()
{
    std::iota(m_NotVisited.begin(), m_NotVisited.end(), 0);
    m_NotVisitedSize = m_NotVisited.size();

    int index = lehmer32()%m_Contex.m_Size; // chose random start index
    m_CurrentIndex = m_NotVisited[index];
    PopIndex(index);

    float totalCost = 0.0f;
    std::vector<int> path;
    path.push_back(m_CurrentIndex);

    while (path.size() < m_Contex.m_Size)
    {
        int index = ChoseRandomNeighbor();
        int nextIndex = m_NotVisited[index];
        totalCost += m_Contex.m_Graph.GetDistance(m_CurrentIndex, nextIndex);

        m_CurrentIndex = nextIndex;
        path.push_back(m_CurrentIndex);
        PopIndex(index);
    }
    totalCost += m_Contex.m_Graph.GetDistance(path.back(), path.front());

    return std::make_pair(path, totalCost);
}

float Ant::CalculateWeight(int nextIndex) const
{
    float dis = m_Contex.m_Graph.GetDistance(m_CurrentIndex, nextIndex);
    float pheromoneStr = m_Contex.GetPheromone(m_CurrentIndex, nextIndex);
    float desirability = std::pow(1/dis, m_DistancePower) * std::pow(pheromoneStr, m_PheromonePower);
    return desirability;
}

int Ant::ChoseRandomNeighbor() const
{
    std::vector<item> neighbors(m_NotVisitedSize);
    float sumWieght = 0;
    for (int i = 0; i < m_NotVisitedSize; i++)
    {
        int vert = m_NotVisited[i];
        item n = {i, CalculateWeight(vert)};
        neighbors.emplace_back(n);
        sumWieght += n.weight;
    }

    float randomWeight = fRand(0,sumWieght);

    for (size_t i = 0; i < neighbors.size(); i++)
    {
        if (randomWeight <= neighbors[i].weight)
        {
            return neighbors[i].value;
        }
        
        randomWeight -= neighbors[i].weight;
    }
    
    return neighbors.back().value;
}

void Ant::PopIndex(int index)
{
    // std::cout<<m_NotVisited[index]<<" | ";
    m_NotVisited[index] = m_NotVisited[m_NotVisitedSize-1];
    m_NotVisitedSize--;

    // for (size_t i = 0; i < m_NotVisitedSize; i++)
    // {
    //     std::cout<<" "<<m_NotVisited[i];
    // }
    // std::cout<<std::endl;
}
