//#define XERR
#include "bandit.ih"

void Bandit::takeAverageRun()
{
    d_rewardAverage[d_currentAction] += d_reward[d_armPicked];
    if (d_armPicked == d_realMaxArm && d_armPicked == d_MaxQArm)
    {
        d_countMaxAverage[d_currentAction] += 1;
    }
    //Take average over all runs
    if (d_runCount == d_runs)
    {
        d_rewardAverage[d_currentAction] /= d_runs;
        d_countMaxAverage[d_currentAction] /= (d_runs);
        d_countMaxAverage[d_currentAction] *= 100; 
    }
}
