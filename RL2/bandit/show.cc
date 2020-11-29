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
    cout << "-- printing distribution -- " << '\n';
    printArray(d_distArr, d_arms);     
    cout << "-- printing Q values --" << '\n';
    printArray(d_Q, d_arms);  
    cout << "-- printing average reward values--" << '\n';
    printArray(d_reward, d_actionSelections);
    cout << "-- printing overall count values --" << '\n';
    printArray(d_overallCount, d_arms);  
    float div = (d_actionSelections*d_runs);
    cout << '\n';
    d_realMaxReward = getHighestValue(d_distArr, d_arms);
    float accuracy = ((d_overallCount[d_realMaxReward]) / div) * 100;
    cout << "The element of the max value in the Q array is: " << d_highestValue << '\n'
        << "The max value in the Q array is: " << d_Qmax << '\n'
        << "The arm with the biggest reward has been chosen with " << accuracy << "% accuracy" << '\n' << "The highest rewarding arm = " << d_realMaxReward << '\n';
}
