/*//#define XERR
#include "bandit.ih"

void Bandit::setP()
{
    //cout << "## setP called! ##" << '\n';
    for (size_t arm = 0; arm < d_arms; ++arm)
    {
        d_P[arm] = 10;
    }
    //Making sure not every run starts with a default max arm
    d_Pmax = -3;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> idist(0,d_arms -1);
    d_MaxParm = idist(gen);
}*/
