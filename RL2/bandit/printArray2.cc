//#define XERR
#include "bandit.ih"

void Bandit::printArray(float *array, int size)
{
    for (int inc = 0; inc < size; ++inc)
    {
        cout << ' ' << array[inc] << " |";
    }    
    cout << '\n';
}
