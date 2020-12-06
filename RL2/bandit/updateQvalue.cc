//#define XERR
#include "bandit.ih"

void Bandit::softMax()
{
    float sum = 0;
	for(size_t inc = 0; inc < d_arms; ++inc)
		sum += exp(d_P[inc]);
    //cout << "sum = " << sum << endl;
    for(size_t inc = 0; inc < d_arms; ++inc)
		d_Q[inc] = (exp(d_P[inc])/sum);
	//printArray(d_Q, d_arms);
    //cout << "d_Q[d_armPicked] = " << d_armPicked << endl;
}

void Bandit::updateQvalue()
{
    //cout << "updateQvalue called" << '\n';
    float prev = d_Q[d_armPicked];
    //cout << "reward = " << d_reward[d_armPicked] << endl;
    if (d_algorithm == 1) 
        d_Q[d_armPicked] = (prev * ((d_count[d_armPicked])) + 
        d_reward[d_armPicked])/(d_count[d_armPicked] + 1);
    else if (d_algorithm == 3)
        softMax();
    else   
        d_Q[d_armPicked] = (prev * ((d_count[d_armPicked])-1) + 
        d_reward[d_armPicked])/(d_count[d_armPicked]);
    //When the max Q value is lowered, but that lowered value is the new highest Q.
    if (prev == d_Qmax && d_Q[d_armPicked] < prev)
        d_Qmax = d_Q[d_armPicked];
}


