#include "bandit/bandit.ih"

int main()
{
    size_t arms, algorithm;
    size_t gaussian = 0;
    size_t bernoulli = 1;
    float algorithmSpecific;   
    cout << "Provide a number of arms" << '\n';
    cin >> arms;
    cout << "The value you entered is: " << arms << '\n';
    cout << "Which algorithm do you want to use?" << '\n' <<
        "Enter 0 for 'epsilon greedy'." << '\n' <<
        "Enter 1 for 'optimistic initial value'." << '\n' <<
        "Enter 2 for 'upper confidence bounds'." << '\n' << 
        "Enter 3 for 'reinforcement comparison'." << '\n';
         
    cin >> algorithm;
    switch (algorithm)
    {
        case 0:
        { 
            cout << "Which value for epsilon do you want to use?" << '\n';
            break;
        }
        case 1:
        { 
            cout << "Which starting Q value do you want to use" << '\n';
            break;
        }
        case 2:
        { 
            cout << "Which value for c do you want to use" << '\n';
            break;
        }
        case 3:
        { 
            cout << "Which starting alpha value do you want to use" << '\n';
            break;
        }
        default:
        {
            cout << "Wrong input" << '\n';
            break;        
        }
    }
    cin >> algorithmSpecific;
    Bandit Gaussian(gaussian, arms, algorithm, algorithmSpecific);
    Bandit Bernoulli(bernoulli, arms, algorithm, algorithmSpecific);
    Gaussian.show();
    Bernoulli.show();
}
