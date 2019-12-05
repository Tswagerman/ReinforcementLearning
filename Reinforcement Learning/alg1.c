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

void printArray(double *array){
	int length = len(array);
	printf("[");
	for(int i = 0;i < (length - 1); i++){
		printf("%lf, ", array[i]);
	}
	printf("%lf", array[length - 1]);
	printf("]\n");
}

void printPercentages(double *array){
	int length = len(array);
	printf("[");
	for(int i = 0;i < (length - 1); i++){
		printf("%f, ", 100*array[i]);
	}
	printf("%f", 100*array[length - 1]);
	printf("]\n");
}

int returnMaxArm(double *distribution){
	//printf("test test\n");
	int length = len(distribution);
	double max = 0;
	int maxi = 0;
	for (int i = 0; i < length; i++){
		if(distribution[i] >= max){
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

double *QValue(double *Q, double distribution, int armOption, int k){
	double prev = Q[armOption];
	//printf("prev = %lf\n", prev);
	Q[armOption] = (prev * (k-1) + distribution)/(k);
	//printf("Q[armOption] = %lf\n", Q[armOption]);
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
	//The length is the same every time. This is a bit redundant for this problem.
	int length = len(array);
	double squaredDiff = 0;
    double standardDeviation = 0;
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
    if(p_a > x) {
    	return 1;
    }
    return 0.00000000000000001;
}

//Algorithms

//Epsilon-greedy
int epsilonGreedy(double epsilon, int max, int length){
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

//Optimistic initial value
//Optimistic initial value always goes for the maximum Qvalue. 
//This is done within the main and required an adaptation of my pre-existing function 'QValue'.
double *QValueOptimal(double *Q, double distribution, int armOption, int k){
	double prev = Q[armOption];
	//printf("prev = %lf\n", prev);
	Q[armOption] = (prev * (k) + distribution)/(k+1);
	//printf("Q[armOption] = %lf\n", Q[armOption]);
	return Q;
}


//UCB
int UCB(int arms, double *qValue, int *count, int actionselections, double c){
	//Exploration is dependent on the c value. 
	//The higher this value is, the more the program will explore
	double *A = malloc(10000 * (sizeof(double)));
	int maxi;
	for(int i = 0; i<arms; i++){
		if (count[i] == 0){
			maxi = i;
			return maxi;
		}else{
			A[i] = qValue[i] + c*sqrt(log(actionselections)/count[i]);
		}
	}
	//printArray(A);
	maxi = returnMaxArm(A);
	//optimal probability
	free(A);
	return maxi;
}

//Reinforcement Comparison
void softMaxFunction(int arms, double *pValue, double *softMax){
	double sum = 0;
	for(int j = 0; j<arms; j++){
		sum += exp(pValue[j]);
	}
	for(int i = 0; i<arms; i++){
		softMax[i] = (exp(pValue[i])/sum);
	}
}

int main() {
	clock_t begin = clock();
	srand(time(NULL));
	//Defaults
	int actionSelections = 1000;
	int runs = 2000;
	//double std = 0.0;
	double epsilon = 0;
	double alpha = 0;
	double c = 0;
	int arms = 0;
	int algorithm = 0;
	int optimalArmGaussianCnt = 0;
	int optimalArmBernoulliCnt = 0;
	int maxValueG = 0;
	int maxValueB = 0;
	int maxValueGQ = 0;
	int maxValueBQ = 0;
	double meanGaussianReward = 0;
	double meanBernoulliReward = 0;
	double standardDeviationGaussian = 0;
	double standardDeviationBernoulli = 0;
	double optimalActionG;
	double optimalActionB;
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
	double *gaussianDistribution = malloc (10000 * (sizeof(double)));
	double *gaussianRewardArray = malloc (100000 * (sizeof(double)));
	double *gaussianQ = malloc (10000 * (sizeof(double)));
	int *countArrGaussian =  malloc (10000 * (sizeof(int)));
	double *averageOptimalActionG = malloc (100000 * (sizeof(double)));
	double *countArrOptGaussian = malloc (100000 * (sizeof(double)));
	double *gaussianP = malloc (10000 * (sizeof(double)));
	double *softMaxG = malloc (10000 * (sizeof(double)));
	//
	double *bernoulliDistribution = malloc (10000 * (sizeof(double)));
	double *bernoulliRewardArray = malloc (100000 * (sizeof(double)));
	double *bernoulliQ = malloc (10000 * (sizeof(double)));
	int *countArrBernoulli = malloc (10000 * (sizeof(int)));
	double *averageOptimalActionB = malloc (100000 * (sizeof(double)));
	double *countArrOptBernoulli= malloc (100000 * (sizeof(double)));
	double *bernoulliP = malloc (10000 * (sizeof(double)));
	double *softMaxB = malloc (10000 * (sizeof(double)));
	//initialization of the Gaussian and Bernoulli distributions.
	for(int i = 0; i < arms; i ++){
		//mean = (double)rand()/(double)(RAND_MAX/1);
		gaussianDistribution[i] = gaussian(1, 0);
		bernoulliDistribution[i] = bernoulli();
		//adding just 0 will not fill the array
		gaussianQ[i] = 0.00001;
		bernoulliQ[i] = 0.00001;
		countArrGaussian[i] = 0;
		countArrBernoulli[i] = 0;
	}
	for(int i = 0; i < actionSelections; i ++){
		averageOptimalActionG[i] = 0.0001;
		averageOptimalActionB[i] = 0.0001;
	}
	//printf("\n" );
	printArray(gaussianDistribution);
	printf("\n" );
	printArray(bernoulliDistribution);
	printf("\n" );
	while(algorithm != 1 && algorithm != 2 && algorithm != 3 && algorithm != 4){
		printf("Which algorithm do you wanna use? 1: Epsilon-greedy 2: Optimistic initial value 3: UCB 4: Reinforcement Comparison\n");
		scanf("%d", &algorithm);
	}
	switch (algorithm){
		//Epsilon greedy
		case 1:
			printf("Assign a value to epsilon between 0 and 1.\n");
			scanf("%lf", &epsilon);
			for(int t = 0; t < runs; t ++){
				for(int a = 0; a < actionSelections; a++){
					//Gaussian
					//The element in the array with the highest probability in the distribution.
					//The optimal choice
					maxValueG = returnMaxArm(gaussianDistribution);
					//printf("optimal arm = %d\n", maxValueG);
					//The optimal solution according to the q values.
					maxValueGQ = returnMaxArm(gaussianQ);
					int gaussianArmOption = epsilonGreedy(epsilon, maxValueGQ, arms);
					countArrGaussian[gaussianArmOption] += 1;
					int countG = countArrGaussian[gaussianArmOption];
					//STD of 0.01 for any arm with a mean that varies for every arm.
					double gaussianReward = gaussian(1, gaussianDistribution[gaussianArmOption]);
					gaussianQ = QValue(gaussianQ, gaussianReward, gaussianArmOption, countG);
					//Check whether the arm that was chosen is the arm with the highest probability.
					int optionG = check(maxValueG, gaussianArmOption);
					//If it is the arm with the highest probability the counter goes up.
					if (optionG == 1){
						optimalArmGaussianCnt++;
						countArrOptGaussian[a] = countArrOptGaussian[a] + 1;
					}
					//Adding reward probability to reward array. 
					//This array can be used to compute the average probability.
					double prevG = gaussianRewardArray[a];
					gaussianRewardArray[a] = (double)(prevG*t + gaussianReward)/(double)(t+1);
					//Optimal action caluclations
					//Gaussian
					optimalActionG = (double)countArrOptGaussian[a]/((double)t+1);
					double tempG = averageOptimalActionG[a];
					averageOptimalActionG[a] = (double)(tempG*t + optimalActionG)/(double)(t+1);
					//
					//Bernoulli, same process as gaussian, but different way of computing reward.
					maxValueB = returnMaxArm(bernoulliDistribution);
					maxValueBQ = returnMaxArm(bernoulliQ);
					int bernoulliArmOption = epsilonGreedy(epsilon, maxValueBQ, arms);
					countArrBernoulli[bernoulliArmOption] += 1;
					int countB = countArrBernoulli[bernoulliArmOption];
					double bernoulliProbability = bernoulliDistribution[bernoulliArmOption];
					//To compute the reward of the bernoulli distrubution, one last function
					double bernoulliReward = bernoulliRewardFunction(bernoulliProbability);
					bernoulliQ = QValue(bernoulliQ, bernoulliReward, bernoulliArmOption, countB);
					int optionB = check(maxValueB, bernoulliArmOption);
					if (optionB == 1){
						optimalArmBernoulliCnt++;						
						countArrOptBernoulli[a] = countArrOptBernoulli[a] + 1;
					}
					double prevB = bernoulliRewardArray[a];
					bernoulliRewardArray[a] = (double)(prevB*t + bernoulliReward)/(double)(t+1);
					//Optimal action caluclations
					//Bernoulli
					optimalActionB = (double)countArrOptBernoulli[a]/((double)t+1);
					double tempB = averageOptimalActionB[a];
					averageOptimalActionB[a] = (double)(tempB*t + optimalActionB)/(double)(t+1);
				}
				for(int i = 0; i < arms; i ++){
					//mean = (double)rand()/(double)(RAND_MAX/1);
					gaussianDistribution[i] = gaussian(1, 0);
					bernoulliDistribution[i] = bernoulli();
					gaussianQ[i] = 0.000000001;
					bernoulliQ[i] = 0.000000001;
					countArrGaussian[i] = 0;
					countArrBernoulli[i] = 0;
				}
			}
			break;
		//Optimisitic intital value
		case 2:
			printf("Assign a Q-value preferably from 1 to 5\n");
			scanf("%lf", &alpha);
			for(int i = 0; i < arms; i ++){
				gaussianQ[i] = alpha;
				bernoulliQ[i] = alpha;
			}
			for(int t = 0; t < runs; t ++){
				for(int a = 0; a < actionSelections; a++){
					//Gaussian
					//The element in the array with the highest probability in the distribution.
					//The optimal choice
					maxValueG = returnMaxArm(gaussianDistribution);
					//printf("optimal arm = %d\n", maxValueG);
					//The optimal solution according to the q values.
					maxValueGQ = returnMaxArm(gaussianQ);
					int gaussianArmOption = maxValueGQ;
					countArrGaussian[gaussianArmOption] += 1;
					int countG = countArrGaussian[gaussianArmOption];
					//STD of 0.01 for any arm with a mean that varies for every arm.
					double gaussianReward = gaussian(1, gaussianDistribution[gaussianArmOption]);
					gaussianQ = QValueOptimal(gaussianQ, gaussianReward, gaussianArmOption, countG);
					//Check whether the arm that was chosen is the arm with the highest probability.
					int optionG = check(maxValueG, gaussianArmOption);
					//If it is the arm with the highest probability the counter goes up.
					if (optionG == 1){
						optimalArmGaussianCnt++;
						countArrOptGaussian[a] = countArrOptGaussian[a] + 1;
					}
					//Adding reward probability to reward array. 
					//This array can be used to compute the average probability.
					double prevG = gaussianRewardArray[a];
					gaussianRewardArray[a] = (double)(prevG*t + gaussianReward)/(double)(t+1);
					//Optimal action caluclations
					//Gaussian
					if(countArrGaussian[maxValueG] == 0){
						optimalActionG = 0.000001;
					} else{
						optimalActionG = (double)countArrOptGaussian[a]/((double)t+1);
					}
					double tempG = averageOptimalActionG[a];
					averageOptimalActionG[a] = (double)(tempG*t + optimalActionG)/(double)(t+1);
					//
					//Bernoulli, same process as gaussian, but different way of computing reward.
					maxValueB = returnMaxArm(bernoulliDistribution);
					maxValueBQ = returnMaxArm(bernoulliQ);
					int bernoulliArmOption = maxValueBQ;
					countArrBernoulli[bernoulliArmOption] += 1;
					int countB = countArrBernoulli[bernoulliArmOption];
					double bernoulliProbability = bernoulliDistribution[bernoulliArmOption];
					//To compute the reward of the bernoulli distrubution, one last function
					double bernoulliReward = bernoulliRewardFunction(bernoulliProbability);
					bernoulliQ = QValueOptimal(bernoulliQ, bernoulliReward, bernoulliArmOption, countB);
					int optionB = check(maxValueB, bernoulliArmOption);
					if (optionB == 1){
						optimalArmBernoulliCnt++;						
						countArrOptBernoulli[a] = countArrOptBernoulli[a] + 1;
					}
					double prevB = bernoulliRewardArray[a];
					bernoulliRewardArray[a] = (double)(prevB*t + bernoulliReward)/(double)(t+1);
					//Optimal action caluclations
					//Bernoulli
					if(countArrBernoulli[maxValueB] == 0){
						optimalActionB = 0.000001;
					} else{
						optimalActionB = (double)countArrOptBernoulli[a]/((double)t+1);
					}
					double tempB = averageOptimalActionB[a];
					averageOptimalActionB[a] = (double)(tempB*t + optimalActionB)/(double)(t+1);
				}
				for(int i = 0; i < arms; i ++){
					gaussianQ[i] = alpha;
					bernoulliQ[i] = alpha;
					gaussianDistribution[i] = gaussian(1, 0);
					bernoulliDistribution[i] = bernoulli();
					countArrGaussian[i] = 0;
					countArrBernoulli[i] = 0;
				}
			}
			break;
		//UCB (Upper-Confidence-Bound)
		case 3:
			printf("Assign a c preferably from 0 to 1.\nThe number c > 0 controls the degree of exploration\n");
			scanf("%lf", &c);
			for(int t = 0; t < runs; t ++){
				for(int a = 0; a < actionSelections; a++){
					//Gaussian
					//The element in the array with the highest probability in the distribution.
					//The optimal choice
					maxValueG = returnMaxArm(gaussianDistribution);
					//printf("optimal arm = %d\n", maxValueG);
					//The optimal solution according to the q values.
					maxValueGQ = returnMaxArm(gaussianQ);
					int gaussianArmOption = UCB(arms, gaussianQ, countArrGaussian, actionSelections, c);
					countArrGaussian[gaussianArmOption] += 1;
					int countG = countArrGaussian[gaussianArmOption];
					//STD of 0.01 for any arm with a mean that varies for every arm.
					double gaussianReward = gaussian(1, gaussianDistribution[gaussianArmOption]);
					gaussianQ = QValue(gaussianQ, gaussianReward, gaussianArmOption, countG);
					//Check whether the arm that was chosen is the arm with the highest probability.
					int optionG = check(maxValueG, gaussianArmOption);
					//If it is the arm with the highest probability the counter goes up.
					if (optionG == 1){
						optimalArmGaussianCnt++;
						countArrOptGaussian[a] = countArrOptGaussian[a] + 1;
					}
					//Adding reward probability to reward array. 
					//This array can be used to compute the average probability.
					double prevG = gaussianRewardArray[a];
					gaussianRewardArray[a] = (double)(prevG*t + gaussianReward)/(double)(t+1);
					//Optimal action caluclations
					//Gaussian
					if(countArrGaussian[maxValueG] == 0){
						optimalActionG = 0.000001;
					} else{
						optimalActionG = (double)countArrOptGaussian[a]/((double)t+1);
					}
					double tempG = averageOptimalActionG[a];
					averageOptimalActionG[a] = (double)(tempG*t + optimalActionG)/(double)(t+1);
					//
					//Bernoulli, same process as gaussian, but different way of computing reward.
					maxValueB = returnMaxArm(bernoulliDistribution);
					maxValueBQ = returnMaxArm(bernoulliQ);
					//The armoption is dependent on the UCB function. 
					int bernoulliArmOption = UCB(arms, bernoulliQ, countArrBernoulli, actionSelections, c);
					countArrBernoulli[bernoulliArmOption] += 1;
					int countB = countArrBernoulli[bernoulliArmOption];
					double bernoulliProbability = bernoulliDistribution[bernoulliArmOption];
					//To compute the reward of the bernoulli distrubution, one last function
					double bernoulliReward = bernoulliRewardFunction(bernoulliProbability);
					bernoulliQ = QValue(bernoulliQ, bernoulliReward, bernoulliArmOption, countB);
					int optionB = check(maxValueB, bernoulliArmOption);
					if (optionB == 1){
						optimalArmBernoulliCnt++;						
						countArrOptBernoulli[a] = countArrOptBernoulli[a] + 1;
					}
					double prevB = bernoulliRewardArray[a];
					bernoulliRewardArray[a] = (double)(prevB*t + bernoulliReward)/(double)(t+1);
					//Optimal action caluclations
					//Bernoulli
					if(countArrBernoulli[maxValueB] == 0){
						optimalActionB = 0.000001;
					} else{
						optimalActionB = (double)countArrOptBernoulli[a]/((double)t+1);
					}
					double tempB = averageOptimalActionB[a];
					averageOptimalActionB[a] = (double)(tempB*t + optimalActionB)/(double)(t+1);
				}
				for(int i = 0; i < arms; i ++){
					gaussianQ[i] = 0.00001;
					bernoulliQ[i] = 0.00001;
					gaussianDistribution[i] = gaussian(1, 0);
					bernoulliDistribution[i] = bernoulli();
					countArrGaussian[i] = 0;
					countArrBernoulli[i] = 0;
				}
			}
			break;
		case 4:
			printf("Assign an alpha between 0 and 1.\n");
			scanf("%lf", &alpha);
			for(int i = 0; i < arms; i ++){
				//softMax[i] = 1/(double)arms;
			}
			for(int t = 0; t < runs; t ++){
				double referenceRewardG = 10;
				double referenceRewardB = 10;
				for(int a = 0; a < actionSelections; a++){
					//Gaussian
					maxValueG = returnMaxArm(gaussianDistribution);
					softMaxFunction(arms, gaussianP, softMaxG);
					//printf("softmax v\n");
					//printArray(softMax);
					int gaussianArmOption = returnMaxArm(softMaxG);
					//printf("optimal = %d\n", maxValueG);
					//printf("armoption = %d\n", gaussianArmOption);
					double gaussianReward = gaussian(1, gaussianDistribution[gaussianArmOption]);
					double diffRewardG = gaussianReward - referenceRewardG;
					countArrGaussian[gaussianArmOption] += 1;
					gaussianP[gaussianArmOption] += diffRewardG;
					//printArray(gaussianP);
					referenceRewardG += (alpha*diffRewardG);
					int optionG = check(maxValueG, gaussianArmOption);
					if (optionG == 1){
						optimalArmGaussianCnt++;
						countArrOptGaussian[a] = countArrOptGaussian[a] + 1;
					}
					//Reward
					double prevG = gaussianRewardArray[a];
					gaussianRewardArray[a] = (double)(prevG*t + gaussianReward)/(double)(t+1);
					//Optimal action caluclations
					if(countArrGaussian[maxValueG] == 0){
						optimalActionG = 0.000001;
					} else{
						optimalActionG = (double)countArrOptGaussian[a]/((double)t+1);
					}
					double tempG = averageOptimalActionG[a];
					averageOptimalActionG[a] = (double)(tempG*t + optimalActionG)/(double)(t+1);
					//
					//Bernoulli, same process as gaussian, but different way of computing reward.
					maxValueB = returnMaxArm(bernoulliDistribution);
					softMaxFunction(arms, bernoulliP, softMaxB);
					//printf("softmax v\n");
					//printArray(softMax);
					int bernoulliArmOption = returnMaxArm(softMaxB);
					//printf("optimal = %d\n", maxValueG);
					//printf("armoption = %d\n", gaussianArmOption);
					double bernoulliProbability = bernoulliDistribution[bernoulliArmOption];
					//To compute the reward of the bernoulli distrubution, one last function
					double bernoulliReward = bernoulliRewardFunction(bernoulliProbability);
					double diffRewardB = bernoulliReward - referenceRewardB;
					countArrBernoulli[bernoulliArmOption] += 1;
					bernoulliP[bernoulliArmOption] += diffRewardB;
					//printArray(gaussianP);
					referenceRewardB += (alpha*diffRewardB);
					int optionB = check(maxValueB, bernoulliArmOption);
					if (optionB == 1){
						optimalArmBernoulliCnt++;						
						countArrOptBernoulli[a] = countArrOptBernoulli[a] + 1;
					}
					double prevB = bernoulliRewardArray[a];
					bernoulliRewardArray[a] = (double)(prevB*t + bernoulliReward)/(double)(t+1);
					//Optimal action caluclations
					//Bernoulli
					if(countArrBernoulli[maxValueB] == 0){
						optimalActionB = 0.000001;
					} else{
						optimalActionB = (double)countArrOptBernoulli[a]/((double)t+1);
					}
					double tempB = averageOptimalActionB[a];
					averageOptimalActionB[a] = (double)(tempB*t + optimalActionB)/(double)(t+1);
				}
				for(int i = 0; i < arms; i ++){
					gaussianP[i] = 0.00000000001;
					bernoulliP[i] = 0.00000000001;
					gaussianDistribution[i] = gaussian(1, 0);
					bernoulliDistribution[i] = bernoulli();
					countArrGaussian[i] = 0;
					countArrBernoulli[i] = 0;
				}
			}
			break;
	}
	printf("\ngaussian\n");
	printf("\n#######################################################################\n");
	//Shows average reward for each action over runs.
	printf("Gaussian average reward array\n");
	printArray(gaussianRewardArray);
	printf("\nArray showing percentage for Gaussian optimal arm per action over runs.\n");
	printPercentages(averageOptimalActionG);
	printf("\n");
  	for(int i = 1; i <= actionSelections; i++){
   		if( i == actionSelections){
   			printf("%d", i);
   		} else{
   			printf("%d,", i);
   		}
  	}
  	printf("\n");
	meanGaussianReward = averageReward(gaussianRewardArray);
	standardDeviationGaussian = calculateSD(gaussianRewardArray, meanGaussianReward);
	printf("optArm = %d\n", optimalArmGaussianCnt);
	printf("runs = %d\n", runs);
	printf("actions = %d\n", actionSelections);
	double optimalArmPercentageG = (double)optimalArmGaussianCnt / (double)(runs * actionSelections);
	double optimalArmPercentageB = (double)optimalArmBernoulliCnt / (double)(runs * actionSelections);
	printf("\nmean Gaussian reward= %lf\n", meanGaussianReward);
	printf("\nstandard deviation Gaussian = %lf\n", standardDeviationGaussian);
	printf("\noptimalG = %lf\n",optimalArmPercentageG);
	//
	printf("\nBernoulli\n");
	printf("\n#######################################################################\n");
	printf("Bernoulli average reward array\n");
	printArray(bernoulliRewardArray);
	printf("\nArray showing percentage for Bernoulli optimal arm per action over runs.\n");
	printPercentages(averageOptimalActionB);
  	meanBernoulliReward = averageReward(bernoulliRewardArray);
	standardDeviationBernoulli = calculateSD(bernoulliRewardArray, meanBernoulliReward);
	printf("\nmean Bernoulli reward= %lf\n", meanBernoulliReward);
	printf("\nstandard deviation Bernoulli = %lf\n", standardDeviationBernoulli);
	printf("\noptimalB = %lf\n", optimalArmPercentageB);
	//Free's
	free(gaussianDistribution);
	free(gaussianRewardArray);
	free(countArrGaussian);
	free(gaussianQ);
	free(averageOptimalActionG);
	free(countArrOptGaussian); 
	free(gaussianP);
	free(softMaxG);
	//
	free(bernoulliDistribution);
	free(bernoulliRewardArray);
	free(countArrBernoulli);
	free(bernoulliQ);
	free(averageOptimalActionB);
	free(countArrOptBernoulli); 
	free(bernoulliP);
	free(softMaxB);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time spent = %lf\n", time_spent);
}