#ifndef RANDOM_NUMBER_GENERATOR_HPP
#define RANDOM_NUMBER_GENERATOR_HPP

#include <boost/random/mersenne_twister.hpp>

namespace LeoEngine
{

    class RandomNumberGenerator
    {
    public:
        RandomNumberGenerator(int seed);
        RandomNumberGenerator();
        ~RandomNumberGenerator();

        int getNextNumber(int rangeStart, int rangeEnd);

    private:
        boost::random::mt19937 _generator;
    };

}

#endif

