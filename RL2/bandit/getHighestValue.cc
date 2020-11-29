//#define XERR
#include "bandit.ih"

int Bandit::getHighestValue(float *array, int size)
{
    //cout << "highestVallue called" << '\n';
    for (int inc = 0; inc < size; ++inc)
    {
        if (array[inc] > d_Qmax)
        {
            //cout << "**************switcheroo********************" << '\n';
            d_Qmax = d_Q[inc];
            d_highestValue = inc;
        }
    }
    //cout << "Highest value Q = " << d_highestValue << '\n';
    return d_highestValue;
}
