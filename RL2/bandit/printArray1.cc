//#define XERR
#include "bandit.ih"

void Bandit::printArray(size_t *array, size_t size)
{
    for (size_t inc = 0; inc < size; ++inc)
    {
        cout << ' ' << array[inc] << " |";
    }    
    cout << '\n';
}
