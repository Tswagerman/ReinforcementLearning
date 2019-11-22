#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h> 
#include <string.h>

double len(double *array){
	for(int i = 1; ;i++){
		if (!array[i]){
			return i;
		}
	}
	return 0;
}

double printArray(double *array){
	//printf("test test motherfucker\n" );
	double len1 = len(array);
	//printf("len = %f\n", len1);
	for(int i = 0;i < len1; i++){
		//printf("test test motherfucker2\n" );
		printf("%f ", array[i]);
	}
	return 0;
}

int returnMaxProb(double *distribution){
	//printf("test test\n");
	int length = len(distribution);
	double max = 0;
	int maxi = 0;
	for (int i = 0; i < length; i++){
		if(distribution[i] > max){
			max = distribution[i];
			maxi = i;
		}
	}
	return maxi;
}

int check(int maxValue, int x){
	if (maxValue == x){
		return 1;
	}else{
		return 0;
	}
}

double averageReward(double *rewardArray){
	double len2 = len(rewardArray);
	double sum = 0;
	for(int i = 0; i < len2; i++){
		sum += rewardArray[i];
	}
	double averageReward = sum / len2;
	return averageReward;
}

//Gaussian distribution
double gaussian(int NSUM, double std, double mean)
{
   double v1=((double)(rand()) + 1. )/( (double)(RAND_MAX) + 1.) ;
   double v2=((double)(rand()) + 1. )/( (double)(RAND_MAX) + 1.) ;
   double x = cos(2*3.14*v2)*sqrt(-2.*log(v1)) * std + mean;
   //printf("double = %f\n", x);
   return x;
}

//Bernoulli distribution in two functions.
double bernoulli(){
	double p_a = (double)rand()/(double)(RAND_MAX/1);
	return p_a;
}

double bernoulliRewardFunction(double p_a){
	if(p_a < 0 || p_a > 1) {
		return -1;
	}
    double x = (double)rand()/(double)(RAND_MAX/1);
    if(p_a < x) {
    	return 1;
    }
    return 0.00001;//Need to figure out how to return 0 and still fill distribution array.
}

//Algorithms
//Epsilon-greedy
int epsilonGreedy(double *distribution, double epsilon, int max){
	int len3 = len(distribution);
	double p = (double)rand()/(double)(RAND_MAX/1);
	if ( epsilon >= p){
		int r = rand() % len3; 
		return r;
	}
	else {
		return max;
	}
}

//


//


//


int main() {
	clock_t begin = clock();
	srand(time(NULL));
	//Defaults
	int actionSelections = 10000;
	int runs = 1000;
	double std = 0.1;
	double mean = 0.7;
	double epsilon = 0;
	int arms = 0;
	int algorithm = 0;
	double optimalArmGaussianCnt = 0;
	double optimalArmBernoulliCnt = 0;
	int maxValueG = 0;
	int maxValueB = 0;
	//End Defaults
	printf("How many arms? Choose 5 , 10, 20 or 40\n");
	scanf("%d", &arms);
	while (arms != 5 && arms != 10 && arms != 20 && arms != 40){
		printf("%d", arms);
		printf("Error, not a valid amount of arms.\n");
		printf("How many arms? Choose 5 , 10, 20 or 40\n");
		scanf("%d", &arms);
	}
	//All required arrays are initialized here.
	double *gaussianDistribution = (double*) malloc (10000 * (sizeof(int)));
	double *gaussianRewardArray = (double*) malloc (100000 * (sizeof(int)));
	double *averageGaussianRewardArray = (double*) malloc (100000 * (sizeof(int)));
	//
	double *bernoulliDistribution = (double*) malloc (10000 * (sizeof(int)));
	double *bernoulliRewardArray = (double*) malloc (100000 * (sizeof(int)));
	double *averageBernoulliRewardArray = (double*) malloc (100000 * (sizeof(int)));
	//initialization of the Gaussian and Bernoulli distributions.
	for(int i = 0; i < arms; i ++){
		gaussianDistribution[i] = gaussian(arms, std, mean);
		bernoulliDistribution[i] = bernoulli();
	}
	printf("\n" );
	printArray(gaussianDistribution);
	printf("\n" );
	printArray(bernoulliDistribution);
	printf("\n" );
	while(algorithm != 1 && algorithm != 2 && algorithm != 3 && algorithm != 4){
		printf("Which algorithm do you wanna use? 1: Epsilon-greedy 2: 3: 4:\n");
		scanf("%d", &algorithm);
	}
	switch (algorithm){
		case 1:
			printf("Assign a value to epsilon between 0 and 1.\n");
			scanf("%lf", &epsilon);
			for(int t = 0; t < runs; t ++){
				for(int a = 0; a < actionSelections; a++){
					//Gaussian
					//The element in the array with the highest probability in the distribution.
					maxValueG = returnMaxProb(gaussianDistribution);
					//Picking an arm using the epsilon greedy algorithm.
					int gaussianArmOption = epsilonGreedy(gaussianDistribution, epsilon, maxValueG);
					//Check whether the arm that was chosen is the arm with the highest probability.
					int optionG = check(maxValueG, gaussianArmOption);
					//If it is the arm with the highest probability the counter goes up.
					if (optionG == 1){
						optimalArmGaussianCnt++;
					}
					double gaussianReward = gaussianDistribution[gaussianArmOption];
					//Adding reward probability to reward array. 
					//This array can be used to compute the average probability.
					gaussianRewardArray[a] = gaussianReward;
					//Bernoulli, same process as gaussian.
					maxValueB = returnMaxProb(bernoulliDistribution);
					int bernoulliArmOption = epsilonGreedy(bernoulliDistribution, epsilon, maxValueB);
					int optionB = check(maxValueB, bernoulliArmOption);
					if (optionB == 1){
						optimalArmBernoulliCnt++;
					}
					double bernoulliProbability = bernoulliDistribution[bernoulliArmOption];
					double bernoulliReward = bernoulliRewardFunction(bernoulliProbability);
					bernoulliRewardArray[a] = bernoulliReward;
				}
				//Average reward per run. Then added to the reward array, storing the averages per run.
				double averageRewardGaussian = averageReward(gaussianRewardArray);
				averageGaussianRewardArray[t] = averageRewardGaussian;

				double averageRewardBernoulli  = averageReward(bernoulliRewardArray);
				averageBernoulliRewardArray[t] = averageRewardBernoulli;
			}
			break;
		case 2:

			break;
		case 3:

			break;
		case 4:

			break;
	}
	double optimalArmPercentageG = optimalArmGaussianCnt / (runs * actionSelections);
	double optimalArmPercentageB = optimalArmBernoulliCnt / (runs * actionSelections);
	printf("\nGuassian\n");
	printArray(gaussianDistribution);
	printf("\noptimalG = %f\n", optimalArmPercentageG);
	printf("\nReward Array\n");
	printArray(averageGaussianRewardArray);
	printf("End Reward Array\n");
	printf("\nBernoulli\n");
	printArray(bernoulliDistribution);
	printf("\noptimalB = %f\n", optimalArmPercentageB);
	printf("\nReward Array\n");
	printArray(averageBernoulliRewardArray);
	printf("End Reward Array\n");
	//Free's
	free(gaussianDistribution);
	free(bernoulliDistribution);
	free(gaussianRewardArray);
	free(bernoulliRewardArray);
	free(averageGaussianRewardArray);
	free(averageBernoulliRewardArray);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time spent = %lf\n", time_spent);
}