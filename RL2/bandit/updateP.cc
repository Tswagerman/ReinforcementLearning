/*//#define XERR
#include "bandit.ih"

void Bandit::updatePvalue()
{
    float prev = d_P[d_armPicked];
    float sum = 0;
    //Softmax function
	for(size_t inc = 0; inc < d_arms; inc++)
		sum += exp(d_P[inc]);
	for(size_t inc = 0; inc < d_arms; inc++)
		d_P[inc] = (exp(d_P[inc])/sum);
    //When the max P value is lowered, but that lowered value is the new highest P.
    if (prev == d_Pmax && d_P[d_armPicked] < prev)
        d_Pmax = d_P[d_armPicked];
}*/
