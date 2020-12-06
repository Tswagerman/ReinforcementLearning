//#define XERR
#include "bandit.ih"

Bandit::Bandit(size_t distribution, size_t arms, size_t algorithm, float algSp)
    //definition data members     
    :d_actionSelections(1000), //Number of action selections is set at construction
    d_runs(100),
    d_algorithm(algorithm), //Algorithm that is picked
    d_distribution(distribution), //Distribution that is picked
    d_arms(arms), //Amount of arms
    d_realMaxArm(0), //Max rewarding arm according to distribution
    //Algorithm specific data members
    d_epsilon(algSp), //Value is set at construction
    d_oiv(algSp),
    d_ubc(algSp),
    d_alpha(algSp),
    d_averageRewardRun(0)
{
    cout << "## constructor2 called! ##" << '\n';
    //definition of all the arrays
    d_distArr = new float[d_arms];
    d_Q = new float[d_arms];
    d_P = new float[d_arms];
    d_reward = new float[d_actionSelections];
    d_rewardAverage = new float[d_actionSelections];
    d_countMaxAverage = new float[d_actionSelections];
    d_count = new size_t[d_arms];
    d_overallCount = new size_t[d_arms];   
    
    //Using Mersenne twister PRNG in order to initalize random seed.
    random_device rd;
    mt19937 gen(rd());
    for (size_t inc = 0; inc < d_arms; ++inc)
    {
        //Initialization of overall counts per arm.        
        d_overallCount[inc] = 0;
        switch(d_distribution)
        {
            case 0:
            {   //Gaussian with mean 0 and std of 1
                normal_distribution<float> gauDist(0, 1); 
                //Get the normal distribution using random device.
                d_distArr[inc] = gauDist(gen);
                break;
            }        
            case 1:
            {   //Bernoulli arm reward probability             
                std::uniform_real_distribution<double> unif(0, 1);  
                double p = unif(gen);
                d_distArr[inc] = p;
                break;
            }    
        }
    }
    d_realMaxArm = getMaxArm(d_distArr, d_arms, d_realMaxArm);
    runAlgorithm();
}
