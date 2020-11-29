//#define XERR
#include "bandit.ih"

int Bandit::e_Greedy(float epsilon)
{
    //printArray(d_Q, d_arms);
    int arm = getHighestValue(d_Q, d_arms);
    double p = (double)rand()/(double)(RAND_MAX/1);
    //Using Mersenne twister PRNG in order to initalize random seed.
    random_device rd;
    mt19937 gen(rd());
	//Exploration.
	if ( epsilon >= p){
        uniform_int_distribution<int> uniformDist(0, d_arms - 1); 
        int random = uniformDist(gen);
		return random;
	}
	//optimal probability
	else
		return arm;
}
