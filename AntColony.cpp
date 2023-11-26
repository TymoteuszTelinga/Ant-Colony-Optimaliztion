
#include "AntColony.h"
#include "Ant.h"
#include <limits>
#include <iostream>
#include <thread>
#include <functional>
#include <math.h>

AntColony::AntColony(const Graph& graph, const AntColonySpec& spec)
    : m_Graph(graph), m_Size(graph.GetSize()), m_Spec(spec), m_PathCost(std::numeric_limits<float>::infinity())
{
    m_Pheromone = new float[m_Size*m_Size];
    std::fill(m_Pheromone, m_Pheromone+m_Size*m_Size, 1.0f);

    m_DistancePower = new float[m_Size*m_Size];
    const float* orginalDistance = graph.GetDistanceRef();
    for (size_t i = 0; i < m_Size*m_Size; i++)
    {
        m_DistancePower[i] = std::pow(1/orginalDistance[i], 4);
    }
    
}

AntColony::~AntColony()
{
    delete m_Pheromone;
}

//hack way
static std::mutex mtx;
void RunSubGroup(const AntColony* Colony, std::vector<int>& BestPath, float& BestCost, uint32_t AntsCount);

void AntColony::Run()
{
    Invalidate();
    // Ant ant(*this);
    for (size_t i = 0; i < m_Spec.NumOfIteration; i++)
    {
        //std::cout<<i<<'/'<<m_Spec.NumOfIteration<<'\r';

        std::vector<int> localBestPath;
        float localBestCost = std::numeric_limits<float>::infinity();
        // for (size_t j = 0; j < m_Spec.GroupSize; j++)
        // {
        //     ant.Run();
        //     if (ant.GetCost() < localBestCost)
        //     {
        //         localBestPath = ant.GetPath();
        //         localBestCost = ant.GetCost();
        //     }
        // }
        std::vector<std::thread> thrpool;
        for (size_t j = 0; j < 4; j++)
        {
            thrpool.push_back(std::thread(RunSubGroup, this,std::ref(localBestPath), std::ref(localBestCost), m_Spec.GroupSize/4));
        }
        
        for (auto &&th : thrpool)
        {
            th.join();
        }

        UpdatePheromones(localBestPath, localBestCost);
        
        Evaporate();

        if (m_LastImprovement >= 80)
        {
            std::cout<<"Early return it: "<<i<<"score :"<<m_PathCost<<std::endl;
            return;
        }
        
    }
    
}

void RunSubGroup(const AntColony* Colony, std::vector<int>& BestPath, float& BestCost, uint32_t AntsCount)
{
    Ant ant(*Colony);
    std::vector<int> localPath;
    float localCost = std::numeric_limits<float>::infinity();

    for (size_t i = 0; i < AntsCount; i++)
    {
        ant.Run();
        if (ant.GetCost() < localCost)
        {
            localPath = ant.GetPath();
            localCost = ant.GetCost();
        }
    }
    
    mtx.lock();
    if (localCost < BestCost)
    {
        BestCost = localCost;
        BestPath = localPath;
    }
    mtx.unlock();

}

float& AntColony::GetPheromone(int x, int y)
{
    return m_Pheromone[y*m_Size + x];
}

float AntColony::GetPheromone(int x, int y) const
{
    return m_Pheromone[y*m_Size + x];
}

float AntColony::GetDistanceWeight(int x, int y) const
{
    return m_DistancePower[y*m_Size + x];
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
        m_LastImprovement = 0;
    }
    else
    {
        m_LastImprovement++;
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


