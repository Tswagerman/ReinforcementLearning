#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h> 
#include <string.h>

double len(double *array){
	for(int i = 1; i <= 100000000; i++){
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

void returnMaxProb(double *distribution, double **maxValues){
	int length = len(distribution);
	int cnt = 0; 
	int max = 0;
	int maxi = 0;
	double *tmp = calloc(length, sizeof(double));
	for (int i = 0; i < length; i++){
		if(distribution[i] == max && max != 0){
			cnt++;
			maxi = i;
			tmp[cnt] = maxi;
		}
		else if(distribution[i] > max){
			cnt = 0;
			max = distribution[i];
			maxi = i;
			tmp[cnt] = maxi;
		}
	}
	free(maxValues);
	*maxValues = tmp;
	printf("tmp=\n");
	printArray(tmp);
	free(tmp);
}

int check(double *maxValues, int x){
	int length2 = len(maxValues);
	for(int j = 0; j < length2; j++){
		if (maxValues[j] == x){
			free(maxValues);
			return 1;
		}
	}
	free(maxValues);
	return 0;
}

double averageReward(double *rewardArray){
	//printf("test");
	double len2 = len(rewardArray);
	//printf("len2 = %f", len2);
	double sum = 0;
	for(int i = 0; i < len2; i++){
		sum += rewardArray[i];
		//printf("%lf", sum);
	}
	double averageReward = sum / len2;
	//printf("%lf", sum);
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

//Bernoulli distribution
double bernoulli(){
	double p_a = (double)rand()/(double)(RAND_MAX/1);
	return p_a;
}

double bernoulliRewardFunction(double p_a){
	//printf("bprob =%f\n", p_a );
	if(p_a < 0 || p_a > 1) {
		return -1;
	}
    double x = (double)rand()/(double)(RAND_MAX/1);
    if(p_a < x) {
    	return 1;
    }
    return 0.00001;
}

//Algorithms
//Epsilon-greedy
int epsilonGreedy(double *distribution, double epsilon){
	int len3 = len(distribution);
	double p = (double)rand()/(double)(RAND_MAX/1);
	if ( epsilon >= p){
		int r = rand() % len3; 
		return r;
	}
	else {
		int max = 0;
		int maxi = 0;
		for (int i = 0; i < len3; i++){
			if(distribution[i] > max){
				max = distribution[i];
				maxi = i;
			}
		}
		return maxi;
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
	double *bernoulliDistribution = (double*) malloc (10000 * (sizeof(int)));
	double *gaussianRewardArray = (double*) malloc (100000 * (sizeof(int)));
	double *averageGaussianRewardArray = (double*) malloc (100000 * (sizeof(int)));
	double *bernoulliRewardArray = (double*) malloc (100000 * (sizeof(int)));
	double *averageBernoulliRewardArray = (double*) malloc (100000 * (sizeof(int)));
	double *maxValuesG = (double*) malloc (10000 * (sizeof(int)));
	double *maxValuesB = (double*) malloc (10000 * (sizeof(int)));
	for(int i = 0; i < arms; i ++){
		gaussianDistribution[i] = gaussian(arms, std, mean);
		printf("hier\n");
		printArray(gaussianDistribution);
		printf("maar 5\n");
		bernoulliDistribution[i] = bernoulli();
	}
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
					printf("check\n");
					//Gaussian
					int gaussianArmOption = epsilonGreedy(gaussianDistribution, epsilon);
					//If gaussianArmOption != bestOption {counter++}
					printf("check2\n");
					returnMaxProb(gaussianDistribution, &maxValuesG);
					printArray(maxValuesG);
					printf("check3\n");
					printArray(maxValuesG);
					int optionG = check(maxValuesG, gaussianArmOption);
					printf("check4\n");
					if (optionG == 1){
						optimalArmGaussianCnt++;
					}
					printf("check5\n");
					double gaussianReward = gaussianDistribution[gaussianArmOption];
					gaussianRewardArray[a] = gaussianReward; //Adding reward probability to reward array
					//Bernoulli
					int bernoulliArmOption = epsilonGreedy(bernoulliDistribution, epsilon);
					//If bernoulliArmOption != bestOption {counter++}
					returnMaxProb(bernoulliDistribution, &maxValuesB);
					int optionB = check(maxValuesB, bernoulliArmOption);
					if (optionB == 1){
						optimalArmBernoulliCnt++;
					}
					double bernoulliProbability = bernoulliDistribution[bernoulliArmOption];
					//printf("bprob =%f\n", bernoulliProbability );
					double bernoulliReward = bernoulliRewardFunction(bernoulliProbability);
					//printf("bprob2=%f\n", bernoulliReward);
					bernoulliRewardArray[a] = bernoulliReward;
					//printf("\nTest bRA\n");
					//printArray(bernoulliRewardArray);
					//printf("\nEnd Test bRA\n");
				}
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