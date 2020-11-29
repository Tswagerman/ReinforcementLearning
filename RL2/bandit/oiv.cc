//#define XERR
#include "bandit.ih"

int Bandit::OIV()
{
    int arm = getHighestValue(d_Q, d_arms);
    return arm;
}
