#ifndef INCLUDED_BANDIT_
#define INCLUDED_BANDIT_

#include <cstddef>


class Bandit
{
    float *d_distArr;
    float *d_Q;
    float *d_reward;
    int *d_count;
    int *d_overallCount;
    
    size_t d_arms = 0;
    //10.000 actions per run for 1000 runs
    size_t d_runs = 1000;
    size_t d_actionSelections = 1000; 
    size_t d_runCount;
    
    int d_algorithm;
    int d_armPicked = 0;
    float d_epsilon;
    int d_oiv;
    float d_Qmax = -3;
    size_t d_highestValue = 0;
    size_t d_realMaxReward;
    public:
        Bandit();
        Bandit(size_t distribution, size_t arms, size_t algorithm, float algSp);
        ~Bandit();
        
        void show();
    private:
        void runAlgorithm();
        void updateQvalue();
        void setQandCount();
        void takeAverageRun();
        int e_Greedy(float epsilon);
        int OIV();
        int getHighestValue(float *array, int size);
        void printArray(float *array, int size);
        void printArray(int *array, int size);
        
};
        
#endif
