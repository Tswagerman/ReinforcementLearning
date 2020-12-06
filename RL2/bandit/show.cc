//#define XERR
#include "bandit.ih"

void Bandit::show()
{
    cout << "## show called! ##" << '\n';
    switch (d_algorithm)
    {
        case 0:
        { 
            cout << "Using algorithm epsilon greedy" << '\n';
            break;
        }
        case 1:
        { 
            cout << "Using algorithm Optimistic initial values" << '\n';
            break;
        }
    }
    cout << "-- printing average accuracy per actionselection--" << '\n';
    printArray(d_countMaxAverage, d_actionSelections);
    cout << "-- printing distribution -- " << '\n';
    printArray(d_distArr, d_arms);     
    cout << "-- printing Q values --" << '\n';
    printArray(d_Q, d_arms);  
    //cout << "-- printing average reward values--" << '\n';
    //printArray(d_rewardAverage, d_actionSelections);
    cout << "-- printing overall count values --" << '\n';
    printArray(d_overallCount, d_arms);  
    cout << "-- printing last run count values --" << '\n';
    printArray(d_count, d_arms);  
    float div = (d_actionSelections*d_runs);
    cout << '\n';
    float accuracy = ((d_overallCount[d_realMaxArm]) / div) * 100;
    cout << "The arm with the max value in the Q array is: " << d_MaxQArm << '\n'
        << "The max value in the Q array is: " << d_Qmax << '\n'
        << "The arm with the biggest reward has been chosen with " << accuracy << "% accuracy" << '\n' << "The highest rewarding arm = " << d_realMaxArm << '\n';
}
