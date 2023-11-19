
#include "AntColony.h"
#include "Ant.h"
#include <limits>
#include <iostream>

AntColony::AntColony(const Graph& graph, const AntColonySpec& spec)
    : m_Graph(graph), m_Size(graph.GetSize()), m_Spec(spec), m_PathCost(std::numeric_limits<float>::infinity())
{
    m_Pheromone = new float[m_Size*m_Size];
    std::fill(m_Pheromone, m_Pheromone+m_Size*m_Size, 1.0f);
}

AntColony::~AntColony()
{
    delete m_Pheromone;
}

void AntColony::Run()
{
    Invalidate();
    Ant ant(*this);
    for (size_t i = 0; i < m_Spec.NumOfIteration; i++)
    {
        //std::cout<<i<<'/'<<m_Spec.NumOfIteration<<'\r';
        std::vector<int> localBestPath;
        float localBestCost = std::numeric_limits<float>::infinity();
        for (size_t j = 0; j < m_Spec.GroupSize; j++)
        {
            auto resoult = ant.Run();
            if (resoult.second < localBestCost)
            {
                localBestPath = resoult.first;
                localBestCost = resoult.second;
            }
        }
        UpdatePheromones(localBestPath, localBestCost);
        
        Evaporate();
    }
    
}

float& AntColony::GetPheromone(int x, int y)
{
    return m_Pheromone[y*m_Size + x];
}

float AntColony::GetPheromone(int x, int y) const
{
    return m_Pheromone[y*m_Size + x];
}

void AntColony::Evaporate()
{
    for (size_t i = 0; i < m_Size*m_Size; i++)
    {
        m_Pheromone[i] *= (1-m_Spec.evaporationRate);
        if (m_Pheromone[i] <= 0.000001f)
        {
            m_Pheromone[i] = 0.f;
        }
    }
    
}

void AntColony::UpdatePheromones(const std::vector<int> &path, float pathCost)
{
    if(pathCost < m_PathCost)
    {
        m_Path = path;
        m_PathCost = pathCost;
    }

    //pathCost = 1;

    for (size_t i = 0; i < path.size()-1; i++)
    {
        GetPheromone(path[i], path[i+1]) = GetPheromone(path[i+1], path[i]) += m_Spec.pheromoneIntesity / pathCost;
    }

    int start = path.front();
    int end = path.back();

    GetPheromone(path[start], path[end]) = GetPheromone(path[end], path[start]) += m_Spec.pheromoneIntesity / pathCost;

}

void AntColony::Invalidate()
{
    m_PathCost = std::numeric_limits<float>::infinity();
    std::fill(m_Pheromone, m_Pheromone+m_Size*m_Size, 1.0f);
}
