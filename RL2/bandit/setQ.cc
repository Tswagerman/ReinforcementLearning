//#define XERR
#include "bandit.ih"

void Bandit::setQandCount()
{   
    //cout << "## setQandCount called! ##" << '\n';
    for (size_t arm = 0; arm < d_arms; ++arm)
    {
        (d_algorithm == 1) ? d_Q[arm] = d_oiv : d_Q[arm] = 0;
        (d_algorithm == 1) ? d_count[arm] = 1 : d_count[arm] = 0;
        d_P[arm] = 5;
    }
    d_Qmax = -3;
    //MAking sure not every run starts with a default max arm
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> idist(0,d_arms -1);
    d_MaxQArm = idist(gen); 
}
