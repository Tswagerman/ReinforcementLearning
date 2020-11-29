//#define XERR
#include "bandit.ih"

void Bandit::show()
{
    cout << "## show called! ##" << '\n';
    cout << "-- printing distribution -- " << '\n';
    for (size_t inc = 0; inc < d_arms; ++inc)
    {
        cout << ' ' << d_distArr[inc] << " |";
    }    
    cout << '\n';
    cout << "-- printing Q values --" << '\n';
    for (size_t inc = 0; inc < d_arms; ++inc)
    {
        cout << ' ' << d_Q[inc] << " |";
    }    
    cout << '\n';
    cout << "-- printing count values --" << '\n';
    for (size_t inc = 0; inc < d_arms; ++inc)
    {
        cout << ' ' << d_count[inc] << " |";
    }    
    cout << '\n';
    cout << "The max value in the Q array is: " << d_Qmax << '\n';
}
