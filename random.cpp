#include "random.h"
#include <limits>

uint32_t nLehmer = 0;
const uint32_t lehmerMax = std::numeric_limits<uint32_t>::max();
uint32_t lehmer32()
{
    nLehmer += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)nLehmer * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;
}

void Slehmer32(uint32_t seed) 
{
    nLehmer = seed;
}

float fRand(double fMin, double fMax)
{
    float random = ((float) lehmer32()) / (float) lehmerMax;
    float diff = fMax - fMin;
    float r = random * diff;
    return fMin + r;
}