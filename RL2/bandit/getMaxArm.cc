//#define XERR
#include "bandit.ih"

size_t Bandit::getMaxArm(float *array, int size, size_t currMaxArm)
{
    cout << "highestVallue called" << '\n';
    size_t maxArm = currMaxArm;    
    for (int inc = 0; inc < size; ++inc)
    {   
        if (array[inc] >= array[maxArm])
            maxArm = inc;
    }
    return maxArm;
}
