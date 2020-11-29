//#define XERR
#include "bandit.ih"

void Bandit::updateQvalue()
{
    //cout << "updateQvalue called" << '\n';
    float prev = d_Q[d_armPicked];
    if (d_algorithm == 1) 
    {
        d_Q[d_armPicked] = (prev * ((d_count[d_armPicked])) + 
        d_distArr[d_armPicked])/(d_count[d_armPicked] + 1);
    }
    else
    {
        d_Q[d_armPicked] = (prev * ((d_count[d_armPicked])-1) + 
        d_distArr[d_armPicked])/(d_count[d_armPicked]);
    }    
    if (prev == d_Qmax && d_Q[d_armPicked] < prev)
    {
        d_Qmax = d_Q[d_armPicked];
    }
}
