#ifndef INCLUDED_BANDIT_
#define INCLUDED_BANDIT_

#include <cstddef>


class Bandit
{
    float *d_distArr;
    float *d_Q;
    int *d_count;
    

    size_t d_arms = 0;
    //10.000 actions per run for 1000 runs
    size_t d_runs = 100;
    size_t d_actionSelections = 1000; 
    //float *d_reward = new float[d_runs * d_actionSelections];
    
    int d_algorithm;
    int d_armPicked;
    float d_epsilon;
    float d_Qmax = -3;
    size_t d_highestValue = 0;
    public:
        Bandit();
        Bandit(size_t distribution, size_t arms, size_t algorithm, float epsilon);
        ~Bandit();
        
        void show();
    private:
        void runAlgorithm(int d_algorithm);
        int e_Greedy(float epsilon);
        int getHighestValue(float *array, int size);
        float updateQvalue();
};
        
#endif
