//#define XERR
#include "bandit.ih"

Bandit::Bandit(size_t distribution, size_t arms, size_t algorithm, float algSp)
//;
{
    cout << "## constructor2 called! ##" << '\n';
    d_arms = arms;
    d_distArr = new float[d_arms];
    d_Q = new float[d_arms];
    d_count = new int[d_arms];
    d_overallCount = new int[d_arms];
    d_reward = new float[d_actionSelections];
    d_epsilon = algSp;
    d_oiv = algSp;
    d_algorithm = algorithm;
    
    //Using Mersenne twister PRNG in order to initalize random seed.
    random_device rd;
    mt19937 gen(rd());
    for (size_t inc = 0; inc < d_arms; ++inc)
    {
        //Initialization of counts per arm.        
        d_overallCount[inc] = 0;
        switch(distribution)
        {
            case 0:
            {   //Gaussian with mean 0 and std of 1
                normal_distribution<float> gauDist(0, 1); 
                //Get the normal distribution using random device.
                d_distArr[inc] = gauDist(gen);
                break;
            }        
            case 1:
            {   //Bernouli with 0.5 chance of element being 0 or 1.   
                bernoulli_distribution berDist(0.5);
                d_distArr[inc] = berDist(gen);
                break;
            }    
        }
    }
    runAlgorithm();
}
