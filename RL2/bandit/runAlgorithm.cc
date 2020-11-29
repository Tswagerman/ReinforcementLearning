//#define XERR
#include "bandit.ih"

void Bandit::runAlgorithm(int algorithm)
{
    for (size_t run = 0; run < d_runs; ++run)
    {
        for (size_t action = 0; action < d_actionSelections; ++action)
        {
            switch (algorithm)
            {
                case 0:
                {
                    d_armPicked = e_Greedy(d_epsilon);
                    break;
                }
            }
            //cout << "d_arm = " << d_armPicked << '\n';
            ++d_count[d_armPicked];
            d_Q[d_armPicked] = updateQvalue();
        }
    }
}
