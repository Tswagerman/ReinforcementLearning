//#define XERR
#include "bandit.ih"

void Bandit::runAlgorithm()
{
    for (d_runCount = 1; d_runCount <= d_runs; ++d_runCount)
    {
        //Initialization of Q value array and amount of counts per arm.      
        setQandCount(); 
        for (d_currentAction = 0; d_currentAction < d_actionSelections; ++d_currentAction)
        {
            reward();
            switch (d_algorithm)
            {
                case 0: //epsilon greedy
                {
                    d_armPicked = e_Greedy();
                    break;
                }
                case 1: //optimistic initial value
                {
                    d_armPicked = OIV();
                    break;
                }
                case 2: //upper confidence bounds
                {
                    d_armPicked = UCB();
                    break;
                }
                case 3: //reinforcement comparison
                {
                    d_armPicked = RC();
                    break;
                }
            }
            ++d_count[d_armPicked]; //Count per run
            ++d_overallCount[d_armPicked]; //Count over all runs
            updateQvalue();
            takeAverageRun(); //averaging reward and counts
        }
    }
}
