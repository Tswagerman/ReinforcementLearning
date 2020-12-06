//#define XERR
#include "bandit.ih"

size_t Bandit::UCB()
{    
    size_t highestValue = getMaxArm(d_Q, d_arms, d_MaxQArm);
    //cout << "highest = " << highestValue << endl;
    float *A = new float[d_arms];
    for (size_t inc = 0; inc < d_arms; ++inc)
        A[inc] = d_Q[inc] + (d_ubc * sqrt(log(d_actionSelections)/d_count[inc]));
    highestValue = getMaxArm(A, d_arms, d_MaxQArm);
    d_Qmax = d_Q[highestValue];
    d_MaxQArm = highestValue;
    delete A;
    return highestValue;
}

