#pragma once

#include <vector>
#include "Graph.h"

class NearestNeighbor
{
public:
    NearestNeighbor(const Graph& graph);
    ~NearestNeighbor();

    std::vector<int> GetPath() const { return m_Path; };
    float GetPathCost() const { return m_PathCost; };
    void Run();

private:

    void Implementation(int start);

private:
    const Graph& m_Context;

    std::vector<int> m_Path;
    float m_PathCost;
};