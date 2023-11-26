#pragma once
#include "AntColony.h"

struct item;
class Ant
{
public:
    Ant(const AntColony& colony);
    ~Ant();

    void Run();
    inline float GetCost() const { return m_TotalCost; };
    std::vector<int> GetPath() { return m_NotVisited; };

private:
    float CalculateWeight(int nextIndex) const;
    int ChoseRandomNeighbor() const;

    void PopIndex(int index);
    int FindNeighbour(const std::vector<item>& items, float value) const;

private:
    const AntColony& m_Contex;

    std::vector<int> m_NotVisited;
    int m_NotVisitedSize;
    float m_TotalCost;

    int m_CurrentIndex;

    const float m_DistancePower = 4;
    const float m_PheromonePower = 3;
};
