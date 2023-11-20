#include <cstdint>

struct item
{
    int value;
    float weight;
};

class Random
{
public:
    static uint32_t Rand();
    static void SRand(uint32_t seed);
    static float FRand(double fMin, double fMax);
private:
    static uint32_t m_Seed;
};
