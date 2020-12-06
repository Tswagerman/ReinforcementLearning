//#define XERR
#include "bandit.ih"

void Bandit::reward()
{
    //Using Mersenne twister PRNG in order to initalize random seed.
    random_device rd;
    mt19937 gen(rd());     
    for (size_t inc = 0; inc < d_arms; ++inc)  
    { 
        if (d_distribution == 0)
        {
            normal_distribution<float> gauDist(d_distArr[inc], 1); 
            //Get the normal distribution using random device.
            d_reward[inc] = gauDist(gen);
        }
        if (d_distribution == 1)
        {
            //Bernouli with p chance of reward 1. And a chance of 1 - p for reward 0 
            bernoulli_distribution berDist(d_distArr[inc]);
            d_reward[inc] = berDist(gen); 
        }
    }
}
