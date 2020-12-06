//#define XERR
#include "bandit.ih"

size_t Bandit::e_Greedy()
{
    //printArray(d_Q, d_arms);
    size_t highestValue = getMaxArm(d_Q, d_arms, d_MaxQArm);
    d_Qmax = d_Q[highestValue];
    d_MaxQArm = highestValue;
    double p = (double)rand()/(double)(RAND_MAX/1);
    //Using Mersenne twister PRNG in order to initalize random seed.
    random_device rd;
    mt19937 gen(rd());
	//Exploration.
	if ( d_epsilon >= p){
        uniform_int_distribution<int> uniformDist(0, d_arms - 1); 
        int random = uniformDist(gen);
		return random;
	}
	//Exploitation
	else
		return highestValue;
}
