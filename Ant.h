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

private:
    const AntColony& m_Contex;
    std::vector<bool> m_Visited;
    int m_CurrentTndex;

    const float m_DistancePower = 4;
    const float m_PheromonePower = 1;
};
