
#include "NearestNeighbor.h"
#include <limits>

NearestNeighbor::NearestNeighbor(const Graph& graph)
    : m_Context(graph), m_PathCost(std::numeric_limits<float>::infinity())
{
    
}

NearestNeighbor::~NearestNeighbor()
{
    
}

void NearestNeighbor::Run()
{
    uint32_t numCities = m_Context.GetSize();

    for (size_t i = 0; i < numCities; i++)
    {
        Implementation(i);
    }
    
}

void NearestNeighbor::Implementation(int start)
{
    uint32_t numCities = m_Context.GetSize();

    // Mark all cities as not visited
    std::vector<bool> visited(numCities, false);

    // Start from the first city
    int currentCity = start;
    visited[currentCity] = true;

    // Result vector to store the order of visited cities
    std::vector<int> localPath;
    float totalCost = 0.0f;
    localPath.push_back(currentCity);

    // Continue until all cities are visited
    while (localPath.size() < numCities) 
    {
        double minDistance = std::numeric_limits<float>::infinity(); // Set to positive infinity
        int nearestCity = -1;

        // Find the nearest unvisited city
        for (int i = 0; i < numCities; ++i) 
        {
            if (!visited[i]) 
            {
                double distance = m_Context.GetDistance(currentCity, i);
                if (distance < minDistance) 
                {
                    minDistance = distance;
                    nearestCity = i;
                }
            }
        }

        // Move to the nearest city
        currentCity = nearestCity;
        visited[currentCity] = true;
        localPath.push_back(currentCity);

        // Update the total cost
        totalCost += minDistance;
    }

    // Add the cost of returning to the starting city to complete the tour
    totalCost += m_Context.GetDistance(localPath.back(), localPath.front());

    if (totalCost < m_PathCost)
    {
        m_Path = localPath;
        m_PathCost = totalCost;
    }
}

