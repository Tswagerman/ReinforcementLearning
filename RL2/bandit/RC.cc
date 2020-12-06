//#define XERR
#include "bandit.ih"

size_t Bandit::RC()
{    
   // cout << "DQ" << endl;    
    //printArray(d_Q, d_arms);    
    size_t highestValue = getMaxArm(d_Q, d_arms, d_MaxQArm);
    d_Qmax = d_Q[highestValue];
    d_MaxQArm = highestValue;
    float& currentReward = d_distArr[highestValue];
    float& referenceReward = d_averageRewardRun;
    float diff = (currentReward - referenceReward);
    //cout << "referenceReward = " << referenceReward << endl;
    //cout << "diff = " << diff << endl;
    //cout << "currentReward = " << currentReward << endl;
    //cout << "#1 d_averageRewardRun = " << d_averageRewardRun << endl;
    //cout << "Arm picked = " << highestValue << endl;
    //printArray(d_P, d_arms);
    d_P[highestValue] = d_Q[highestValue] + diff;
    //cout << "diff reward = " << abs(currentReward - referenceReward) << endl;
    //printArray(d_P, d_arms);
    d_averageRewardRun += d_alpha * diff;
    //cout << "#2 d_averageRewardRun = " << d_averageRewardRun << endl;
    return highestValue;
}
