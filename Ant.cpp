
#include "Ant.h"
#include "random.h"
#include <math.h>

#include "Benchmark.hpp"

Ant::Ant(const AntColony& colony)
    :m_Contex(colony), m_Visited(colony.m_Size, false)
{

}

Ant::~Ant()
{
    
}

std::pair<std::vector<int>, float> Ant::Run()
{   
    {
        MEASURE_NAME("Run Init")
        std::fill(m_Visited.begin(), m_Visited.end(), false);
        m_CurrentTndex = lehmer32()%m_Contex.m_Size; // chose random start index
    }

    float totalCost = 0.0f;
    std::vector<int> path;
    path.push_back(m_CurrentTndex);
    m_Visited[m_CurrentTndex] = true;

    while (path.size() < m_Contex.m_Size)
    {
        int nextIndex = ChoseRandomNeighbor();
        totalCost += m_Contex.m_Graph.GetDistance(m_CurrentTndex, nextIndex);

        m_CurrentTndex = nextIndex;
        path.push_back(m_CurrentTndex);
        m_Visited[m_CurrentTndex] = true;
    }
    totalCost += m_Contex.m_Graph.GetDistance(path.back(), path.front());

    return std::make_pair(path, totalCost);
}

float Ant::CalculateWeight(int nextIndex) const
{
    float dis = m_Contex.m_Graph.GetDistance(m_CurrentTndex, nextIndex);
    float pheromoneStr = m_Contex.GetPheromone(m_CurrentTndex, nextIndex);
    float desirability = std::pow(1/dis, m_DistancePower) * std::pow(pheromoneStr, m_PheromonePower);
    return desirability;
}

int Ant::ChoseRandomNeighbor() const
{
    std::vector<item> neighbors;
    float sumWieght = 0;
    for (int i = 0; i < m_Contex.m_Size; i++)
    {
        if (!m_Visited[i] && i != m_CurrentTndex)
        {
            item n = {i, CalculateWeight(i)};
            neighbors.push_back(n);
            sumWieght += n.weight;
        }
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
