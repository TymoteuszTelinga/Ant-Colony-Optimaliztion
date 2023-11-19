#pragma once

#include <string>

class Graph
{
public:
    Graph(const std::string& filePath);
    ~Graph();

    float GetDistance(uint32_t x, uint32_t y) const;
    uint32_t GetSize() const { return m_Size; };

private:
    float* m_Distance = nullptr;
    uint32_t m_Size;

    // friend class NearestNeighbor;
};