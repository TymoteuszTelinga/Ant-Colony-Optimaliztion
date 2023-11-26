
#include "Graph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

struct City
{
    int id;
    double x;
    double y;
};

float CalculateDistance(const City& A, const City& B)
{
    float dx = A.x - B.x;
    float dy = A.y - B.y;
    return std::sqrt(dx*dx + dy*dy);
}

Graph::Graph(const std::string& filePath)
{
    std::vector<City> cities;
    std::ifstream file(filePath);

    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    std::string line;
    bool readingNodes = false;

    //Read Citis Info
    while (std::getline(file, line)) 
    {
        if (line == "NODE_COORD_SECTION")
        {
            readingNodes = true;
            continue;
        }

        if (readingNodes && line == "TOUR_SECTION") 
        {
            break;
        }

        if (readingNodes) 
        {
            std::istringstream ss(line);
            City city;
            ss >> city.id >> city.x >> city.y;
            cities.emplace_back(city);
        }
    }

    file.close();

    m_Size = cities.size();

    m_Distance = new float [m_Size*m_Size];

    for (size_t x = 0; x < m_Size; x++)
    {
        for (size_t y = 0; y < m_Size; y++)
        {
            m_Distance[y*m_Size + x] = CalculateDistance(cities[x], cities[y]);
        }    
    }

    bIsValid = true;
}

Graph::~Graph()
{
    delete m_Distance;
}

float Graph::GetDistance(uint32_t x, uint32_t y) const
{
    return m_Distance[y*m_Size + x];
}
