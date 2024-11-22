#include <ctime>
#include "RandomNumberGenerator.hpp"

RandomNumberGenerator::RandomNumberGenerator(int seed)
{
    _generator.seed(seed);
}

RandomNumberGenerator::RandomNumberGenerator()
    : RandomNumberGenerator(time(0))
{

}

RandomNumberGenerator::~RandomNumberGenerator()
{

}

int RandomNumberGenerator::getNextNumber(int rangeStart, int rangeEnd)
{
    boost::random::uniform_int_distribution<> distribution(rangeStart, rangeEnd);
    return distribution(_generator);
}

