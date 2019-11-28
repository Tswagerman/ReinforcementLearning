#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h> 
#include <string.h>

int len(double *array){
	for(int i = 1; ;i++){
		if (!array[i]){
			return i;
		}
	}
	return 0;
}

double printArray(double *array){
	double length = len(array);
	for(int i = 0;i < length; i++){
		printf("%lf", array[i]);
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

double *QValue(double *Q, double *distribution, int armOption, int k){
	double prev = Q[armOption];
	printf("prev = %lf\n", prev);
	//Distribution is the same cnstantly.
	printf("distribution[armOption] = %lf\n", gaussian(mean[armOption], std[armOption]));
	printf("k = %d\n", k);
	Q[armOption] = (prev * (k-1) + distribution[armOption])/(k);
	printf("Q[armOption] = %lf\n", Q[armOption]);
	return Q;
}

double averageReward(double *rewardArray){
	double length = len(rewardArray);
	double sum = 0;
	for(int i = 0; i < length; i++){
		sum += rewardArray[i];
	}
	double averageReward = sum / length;
	return averageReward;
}

double calculateSD(double *array, double mean){
	int length = len(array);
	double squaredDiff = 0;
    double standardDeviation = 0;
    //The length is the same every time. This is a bit redundant for this problem.
    for(int i=0; i<length; ++i){
        squaredDiff += pow(array[i] - mean, 2);
    }
    standardDeviation = sqrt(squaredDiff/length);
    return standardDeviation;
}

//Gaussian distribution
double gaussian(double std, double mean){
   double v1=((double)(rand()) + 1. )/( (double)(RAND_MAX) + 1.) ;
   double v2=((double)(rand()) + 1. )/( (double)(RAND_MAX) + 1.) ;
   double x = cos(2*3.14*v2)*sqrt(-2.*log(v1)) * std + mean;
   //printf("double = %f\n", x);
   return x;
}

//Bernoulli distribution in two functions. The first to compute a probability
//and the second function to compute the reward.
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
    return 0.00000000000001;//Need to figure out how to return 0 and still fill distribution array.
}

//Algorithms
//Epsilon-greedy
int epsilonGreedy(double *distribution, double epsilon, int max){
	int length = len(distribution);
	double p = (double)rand()/(double)(RAND_MAX/1);
	//Exploration.
	if ( epsilon >= p){
		int r = rand() % length; 
		return r;
	}
	//optimal probability
	else {
		return max;
	}
}

//Optimisitic intital value
int optimisticInitialValue(double *distribution, double alpha, double a_n, int max){
	int length = len(distribution);
	double random = (double)rand()/(double)(RAND_MAX/(alpha/300));
	double beta = alpha/a_n;
	//Exploration
	if ( beta >= random){
		int r = rand() % length; 
		return r;
	}
	//optimal probability.
	else {
		return max;
	}
}

//


//


int main() {
	clock_t begin = clock();
	srand(time(NULL));
	//Defaults
	int actionSelections = 10000;
	int runs = 1000;
	double std = 0.0;
	double mean = 0.0;
	double epsilon = 0;
	double alpha = 0;
	int arms = 0;
	int algorithm = 0;
	double optimalArmGaussianCnt = 0;
	double optimalArmBernoulliCnt = 0;
	int maxValueG = 0;
	int maxValueB = 0;
	double meanGaussianReward = 0;
	double meanBernoulliReward = 0;
	double standardDeviationGaussian = 0;
	double standardDeviationBernoulli = 0;
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
	double *gaussianDistribution = (double*) malloc (10000 * (sizeof(double)));
	double *gaussianRewardArray = (double*) malloc (100000 * (sizeof(double)));
	double *averageGaussianRewardArray = (double*) malloc (100000 * (sizeof(double)));
	double *gaussianQ = (double*) malloc (10000 * (sizeof(double)));
	double *countArrGaussian = (double*) malloc (10000 * (sizeof(double)));
	//
	double *bernoulliDistribution = (double*) malloc (10000 * (sizeof(double)));
	double *bernoulliRewardArray = (double*) malloc (100000 * (sizeof(double)));
	double *averageBernoulliRewardArray = (double*) malloc (100000 * (sizeof(double)));
	//initialization of the Gaussian and Bernoulli distributions.
	for(int i = 0; i < arms; i ++){
		std = (double)rand()/(double)(RAND_MAX/0.01);
		mean = (double)rand()/(double)(RAND_MAX/1);
		gaussianDistribution[i] = gaussian(std, mean);
		bernoulliDistribution[i] = bernoulli();
		gaussianQ[i] = 0.000000000001;
	}
	int length = len(gaussianQ);
	printf("length = %d\n", length);
	printf("\n" );
	printArray(gaussianDistribution);
	printf("\n" );
	printArray(bernoulliDistribution);
	printf("\n" );
	printf("\nQQQQQQQQQQQQQ\n");
	printArray(gaussianQ);
	printf("\nQQQQQQQQQQQQQ\n");
	while(algorithm != 1 && algorithm != 2 && algorithm != 3 && algorithm != 4){
		printf("Which algorithm do you wanna use? 1: Epsilon-greedy 2: Optimistic initial value 3: 4:\n");
		scanf("%d", &algorithm);
	}
	switch (algorithm){
		case 1:
			printf("Assign a value to epsilon between 0 and 1.\n");
			scanf("%lf", &epsilon);
			for(int t = 0; t < runs; t ++){
				for(int a = 0; a < actionSelections; a++){
					//The element in the array with the highest probability in the distribution.
					maxValueG = returnMaxProb(gaussianQ); //Qvalue 
					maxValueB = returnMaxProb(bernoulliDistribution);
					//Gaussian
					//Picking an arm using the epsilon greedy algorithm.
					int gaussianArmOption = epsilonGreedy(gaussianDistribution, epsilon, maxValueG);
					printf("armoption = %d\n", gaussianArmOption);
					countArrGaussian[gaussianArmOption] += 1;
					int count = countArrGaussian[gaussianArmOption];
					gaussianQ = QValue(gaussianQ, gaussianDistribution, gaussianArmOption, count);
					printf("\nQQQQQQQQQQQQQ\n");
					printArray(gaussianQ);
					printf("\nQQQQQQQQQQQQQ\n");
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
					int bernoulliArmOption = epsilonGreedy(bernoulliDistribution, epsilon, maxValueB);
					int optionB = check(maxValueB, bernoulliArmOption);
					if (optionB == 1){
						optimalArmBernoulliCnt++;
					}
					double bernoulliProbability = bernoulliDistribution[bernoulliArmOption];
					//To compute the reward of the bernoulli distrubution, one last function
					double bernoulliReward = bernoulliRewardFunction(bernoulliProbability);
					bernoulliRewardArray[a] = bernoulliReward;
					
				}
				//Average reward per run. Then added to the reward array, storing the averages per run.
				double averageRewardGaussian = averageReward(gaussianRewardArray);
				averageGaussianRewardArray[t] = averageRewardGaussian;

				double averageRewardBernoulli  = averageReward(bernoulliRewardArray);
				averageBernoulliRewardArray[t] = averageRewardBernoulli;

			}
			meanGaussianReward = averageReward(averageGaussianRewardArray);
			standardDeviationGaussian = calculateSD(averageGaussianRewardArray, meanGaussianReward);

			meanBernoulliReward = averageReward(averageBernoulliRewardArray);
			standardDeviationBernoulli = calculateSD(averageBernoulliRewardArray, meanBernoulliReward);
			break;
		case 2:
			printf("Assign a value to your step function. The higher, the more randomness initially\n");
			scanf("%lf", &alpha);
			for(int t = 0; t < runs; t ++){
				for(int a = 0; a < actionSelections; a++){
					//Gaussian
					//Picking an arm using the epsilon greedy algorithm.
					int gaussianArmOption = optimisticInitialValue(gaussianDistribution, alpha, t, maxValueG);
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
					int bernoulliArmOption = optimisticInitialValue(bernoulliDistribution, alpha, t, maxValueB);
					int optionB = check(maxValueB, bernoulliArmOption);
					if (optionB == 1){
						optimalArmBernoulliCnt++;
					}
					double bernoulliProbability = bernoulliDistribution[bernoulliArmOption];
					//To compute the reward of the bernoulli distrubution, one last function
					double bernoulliReward = bernoulliRewardFunction(bernoulliProbability);
					bernoulliRewardArray[a] = bernoulliReward;
				}
				//Average reward per run. Then added to the reward array, storing the averages per run.
				double averageRewardGaussian = averageReward(gaussianRewardArray);
				averageGaussianRewardArray[t] = averageRewardGaussian;
				

				double averageRewardBernoulli  = averageReward(bernoulliRewardArray);
				averageBernoulliRewardArray[t] = averageRewardBernoulli;
		
			}
			meanGaussianReward = averageReward(averageGaussianRewardArray);
			standardDeviationGaussian = calculateSD(averageGaussianRewardArray, meanGaussianReward);

			meanBernoulliReward = averageReward(averageBernoulliRewardArray);
			standardDeviationBernoulli = calculateSD(averageBernoulliRewardArray, meanBernoulliReward);
			break;
		case 3:

			break;
		case 4:

			break;
	}
	printf("\nQQQQQQQQQQQQQ\n");
	printArray(gaussianQ);
	printf("\nQQQQQQQQQQQQQ\n");
	double optimalArmPercentageG = optimalArmGaussianCnt / (runs * actionSelections);
	double optimalArmPercentageB = optimalArmBernoulliCnt / (runs * actionSelections);
	printf("\ngaussian\n");
	printArray(gaussianDistribution);
	printf("\nstandard deviation Gaussian = %lf\n", standardDeviationGaussian);
	printf("\noptimalG = %f\n", optimalArmPercentageG);
	printf("\nReward Array\n");
	printArray(averageGaussianRewardArray);
	printf("End Reward Array\n");
	printf("\nBernoulli\n");
	printArray(bernoulliDistribution);
	printf("\nstandard deviation Bernoulli = %lf\n", standardDeviationBernoulli);
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