#ifndef INCLUDED_BANDIT_
#define INCLUDED_BANDIT_

#include <cstddef>


class Bandit
{
    //Arrays
    float *d_distArr; //Distribution array filled with all real reward values
    float *d_Q; //Q array filled with the Q reward values
    float *d_P; //P array used for RC
    float *d_reward; //reward per action selection
    float *d_rewardAverage; //average reward  per action selection
    float *d_countMaxAverage; //Average max arm was picked per action selection
    size_t *d_count; //Counting how many times each arm is picked over one run
    size_t *d_overallCount; //Same as d_count but over all runs
    
    //10.000 actions per run for 1000 runs set in runAlgorithm()
    size_t d_actionSelections; //Number of action selections is set at construction
    size_t d_runs; //Number of runs is set at construction
    
    //Declarations general data members
    size_t d_algorithm; //Algorithm that is picked
    size_t d_distribution; //Distribution that is picked
    size_t d_armPicked; //Arm picked during current action
    size_t d_runCount; //counting number of runs
    size_t d_currentAction; //Keeping track of which action we are at currently
    size_t d_arms; //Amount of arms
    size_t d_MaxQArm; //Max rewarding arm according to Q array
    size_t d_realMaxArm; //Max rewarding arm according to distribution
    float d_Qmax; //Max reward value in Q array currently
    //Algorithm specific data members
    float d_epsilon; //Value is set at construction
    int d_oiv;  //Value is set at construction
    float d_ubc; //Value is set at construction
    float d_alpha; //Value is set at construction
    float d_totalRewardRun; //keeping track of the total reward for RC
    float d_averageRewardRun; //Taking the averageReward at that moment for RC
    
    public:
        //Constructors
        Bandit();
        Bandit(size_t distribution, size_t arms, size_t algorithm, float algSp);
        //Destructor
        ~Bandit();
        
        void show();
    private:
        //Algorithm specific member functions
        size_t e_Greedy();
        size_t OIV();
        size_t UCB();
        size_t RC();
        void setQandCount();
        void softMax();
        void reward();
        //General member functions
        void runAlgorithm();
        void updateQvalue();
        void takeAverageRun();//Used to take average of multiple data members
        void printArray(float *array, int size);
        void printArray(size_t *array, size_t size);
        size_t getMaxArm(float *array, int size, size_t currMaxArm);//Highest value of any array
        
};
        
#endif
