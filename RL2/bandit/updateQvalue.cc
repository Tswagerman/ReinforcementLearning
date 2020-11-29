//#define XERR
#include "bandit.ih"

float Bandit::updateQvalue()
{
    //cout << "updateQvalue called" << '\n';
    float prev = d_Q[d_armPicked];
	d_Q[d_armPicked] = (prev * ((d_count[d_armPicked])-1) + 
        d_distArr[d_armPicked])/(d_count[d_armPicked]);
	return d_Q[d_armPicked];
}
