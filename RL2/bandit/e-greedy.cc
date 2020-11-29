//#define XERR
#include "bandit.ih"

int Bandit::e_Greedy(float epsilon)
{
    //cout << "e-Greedy called" << '\n';
    int arm = getHighestValue(d_Q, d_arms);
    //cout << "arm = " << arm << '\n';
    double p = (double)rand()/(double)(RAND_MAX/1);
    //cout << "p = " << p << '\n';
    //Using Mersenne twister PRNG in order to initalize random seed.
    random_device rd;
    mt19937 gen(rd());
	//Exploration.
	if ( epsilon >= p){
        //cout << " EXPLORING!!!! " << '\n';
        uniform_int_distribution<int> uniformDist(0, d_arms - 1); 
        int r = uniformDist(gen);
        //cout << "r = " << r << '\n';
        //cout << "arm = " << r << '\n';
		return r;
	}
	//optimal probability
	else {
        //cout << " GREEDY!!!! " << '\n';
        //cout << "arm = " << arm << '\n';
		return arm;
	}
}
