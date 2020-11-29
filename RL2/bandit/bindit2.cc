//#define XERR
#include "bandit.ih"

Bandit::Bandit(size_t distribution, size_t arms, size_t algorithm, float epsilon)
//;
{
    cout << "## constructor2 called! ##" << '\n';
    d_arms = arms;
    d_distArr = new float[d_arms];
    d_Q = new float[d_arms];
    d_count = new int[d_arms];
    d_epsilon = epsilon;
    d_algorithm = algorithm;
    
    //Using Mersenne twister PRNG in order to initalize random seed.
    random_device rd;
    mt19937 gen(rd());
    for (size_t inc = 0; inc < d_arms; ++inc)
    {
        //Initialization of Q value array and amount of counts per arm.        
        d_Q[inc] = 0;
        d_count[inc] = 0;
        switch(distribution)
        {
            case 0:
            {
                //cout << "############### GAUSSIAN ###############" <<'\n';
                normal_distribution<float> gauDist(0, 1); 
                //Get the normal distribution using random device.
                d_distArr[inc] = gauDist(gen);
                break;
            }        
            case 1:
            {        
                //cout << "############### BERNOULI ###############" <<'\n';
                bernoulli_distribution berDist(0.5);
                //Get the bernoulli distribution using random device.
                d_distArr[inc] = berDist(gen);
                break;
            }    
        }
    }
    runAlgorithm(d_algorithm);
}
