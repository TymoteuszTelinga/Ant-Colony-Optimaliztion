#pragma once
#include "AntColony.h"

class Ant
{
public:
    Ant(const AntColony& colony);
    ~Ant();

    std::pair<std::vector<int>, float> Run();

private:

    float CalculateWeight(int nextIndex) const;
    int ChoseRandomNeighbor() const;

    void PopIndex(int index);
    

private:
    const AntColony& m_Contex;
    std::vector<int> m_NotVisited;
    int m_NotVisitedSize;

    int m_CurrentIndex;

    const float m_DistancePower = 4;
    const float m_PheromonePower = 1;
};
