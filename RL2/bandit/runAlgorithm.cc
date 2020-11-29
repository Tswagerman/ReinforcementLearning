//#define XERR
#include "bandit.ih"

void Bandit::runAlgorithm()
{
    for (size_t count = 1; count <= d_runs; ++count)
    {
        //Initialization of Q value array and amount of counts per arm.      
        setQandCount(); 
        for (size_t action = 0; action < d_actionSelections; ++action)
        {
            switch (d_algorithm)
            {
                case 0: //epsilon greedy
                {
                    d_armPicked = e_Greedy(d_epsilon);
                    break;
                }
                case 1: //optimistic initial value
                {
                    d_armPicked = OIV();
                    break;
                }
            }
            ++d_count[d_armPicked];
            ++d_overallCount[d_armPicked];
            updateQvalue();
            d_reward[action] += d_distArr[d_armPicked];
            //Take average over all runs
            if (count == d_runs)
                d_reward[action] /= d_runs;
        }
    }
}
