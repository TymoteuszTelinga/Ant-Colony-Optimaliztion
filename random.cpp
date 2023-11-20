#include "Random.h"
#include <limits>

uint32_t Random::m_Seed = 0;

uint32_t Random::Rand()
{
    m_Seed += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)m_Seed * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;
}

void Random::SRand(uint32_t seed)
{
    m_Seed = seed;
}

float Random::FRand(double fMin, double fMax)
{
    float random = ((float) Rand()) / (float) std::numeric_limits<uint32_t>::max();
    float diff = fMax - fMin;
    float r = random * diff;
    return fMin + r;
}