//#define XERR
#include "bandit.ih"

size_t Bandit::OIV()
{
    size_t highestValue = getMaxArm(d_Q, d_arms, d_MaxQArm);
    d_Qmax = d_Q[highestValue];
    d_MaxQArm = highestValue;
    return highestValue;
}
