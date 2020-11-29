#include "bandit.ih"

Bandit::~Bandit() // destructor
{
    cout << "## Destructor called! ##" << '\n';
    delete []d_distArr;
    delete []d_Q;
    delete []d_count;
    delete []d_overallCount;
    delete []d_reward;
}
