#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

/*
 * Random generator with Mersenne twister method
 *
 * Sample usage:
 *
 * RandomGenerator g(10);
 * for (int i = 0; i < 5; i++) cout << g.get() << endl;
 *
 */
class RandomGenerator
{

public:

    RandomGenerator(unsigned int seed)
    {
        idx = 0;
        mt = new unsigned int[length];
        mt[0] = seed;
        for (unsigned int i = 1; i < length; i++)
            mt[i] = (1812433253 * (mt[i-1] ^ (mt[i-1] >> 30)) + i) & bitMask_32;
    }

    unsigned int get()
    {
        if (idx == 0) gen();
        unsigned int y = mt[idx];
        y ^= y >> 11;
        y ^= (y << 7) & 2636928640UL;
        y ^= (y << 15) & 4022730752UL;
        y ^= y >> 18;
        idx = (idx + 1) % length;
        return y;
    }

    void gen()
    {
        for (unsigned int i = 0; i < length; i++)
        {
            unsigned int y = (mt[i] & bitPow_31) + (mt[(i+1) % length] & (bitPow_31 - 1));
            mt[i] = mt[(i + 397) % length] ^ (y >> 1);
            if (y % 2) mt[i] ^= 2567483615UL;
        }
        return;
    }

    ~RandomGenerator()
    {
        delete[] mt;
    }

private:

    static const unsigned int length = 624;
    static const unsigned int bitMask_32 = 0xffffffff;
    static const unsigned int bitPow_31 = (1 << 31);
    unsigned int *mt;
    unsigned int idx;
};

#endif // RANDOMGENERATOR_H
