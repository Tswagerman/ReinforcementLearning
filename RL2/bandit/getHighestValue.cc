//#define XERR
#include "bandit.ih"

int Bandit::getHighestValue(float *array, int size)
{
    //cout << "highestVallue called" << '\n';
    for (int inc = 0; inc < size; ++inc)
    {
        if (array[inc] > d_Qmax)
        {      
            d_Qmax = d_Q[inc];
            d_highestValue = inc;
        }
    }
    return d_highestValue;
}
