#include "bandit.ih"

Bandit::~Bandit() // destructor
{
    delete []d_distArr;
    delete []d_Q;
    delete []d_count;
    //delete[] *d_reward;
}
