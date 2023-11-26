#pragma once

#include "Graph.h"
#include <vector>
#include <mutex>

struct AntColonySpec
{
    float evaporationRate = 0.1f;
    float pheromoneIntesity = 1.f;
    uint32_t NumOfIteration = 100;
    uint32_t GroupSize = 200;
    uint32_t NumOfTest = 1;

    bool LoadFromFile(const std::string& filePath);
    void SaveToFile(const std::string& filePath);
};

class AntColony
{
public:
    AntColony(const Graph& graph, const AntColonySpec& spec);
    ~AntColony();

    std::vector<int> GetPath() const { return m_Path; };
    float GetPathCost() const { return m_PathCost; };
    void Run();

private:
    float& GetPheromone(int x, int y);
    float GetPheromone(int x, int y) const;
    float GetDistanceWeight(int x, int y) const;
    void Evaporate();
    void UpdatePheromones(const std::vector<int> &path, float pathCost);
    void Invalidate();


private:
    const Graph& m_Graph;
    const uint32_t m_Size;
    AntColonySpec m_Spec;

    std::vector<int> m_Path; // all time best
    float m_PathCost;
    uint32_t m_LastImprovement = 0;

    float* m_Pheromone = nullptr;
    float* m_DistancePower = nullptr;

    friend class Ant;
};