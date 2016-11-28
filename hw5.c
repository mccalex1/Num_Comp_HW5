#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define FUNC .9973
#define LOWER_BOUND -3
#define UPPER_BOUND 3
#define FUNC_MAX .398942
#define RANDOM_MAX 0x7FFFFFFF

double get_eps();
void mathPart(int);
double doFunc(double);
void doMVS(double[], double[]);

int main()
{
  int niter = 0;
  srand(time(NULL));
  srandom(time(NULL));
  

  for(niter = 10; niter <= 100000; niter *= 10){
    mathPart(niter);
  }
}
  

void mathPart(int niter){
  printf("-------------------------------------------------------Iterations = %d------------------------------------------------------------\n", niter);
  double x, x2, x3;
  double y, y2, y3;

  unsigned int seed;

  int i = 0;

  //number of points below graph
  int count = 0;
  int count2 = 0;
  int count3 = 0;

  double func, func2, func3;

  double xList[niter], yList[niter];
  double xList2[niter], yList2[niter];
  double xList3[niter], yList3[niter];

  count=0;

  //run however many times the user specifies
  for ( i=0; i<niter; i++) {
    
    //generate random numbers

    //srand
    x = ((double)rand() / RAND_MAX) * UPPER_BOUND;
    y = ((double)rand() / RAND_MAX) * FUNC_MAX;



    if(y < doFunc(x)){
      count++;
      xList[i] = x;
      yList[i] = y;
    }
    else{
      xList[i] = 1;
      yList[i] = 1;
    }

    //srandom
    x2 = ((double)random() / RAND_MAX) * UPPER_BOUND;
    y2 = ((double)random() / RAND_MAX) * FUNC_MAX;
 
    if(y2 < doFunc(x2)){
      count2++;
      xList2[i] = x2;
      yList2[i] = y2;
    }
    else{
      xList2[i] = 1;
      yList2[i] = 1;
    }


    //rand_r
    x3 = ((double)rand_r(&seed) / RAND_MAX) * UPPER_BOUND;
    y3 = ((double)rand_r(&seed) / RAND_MAX) * FUNC_MAX;

    if(y3 < doFunc(x3)){
      count3++;
      xList3[i] = x3;
      yList3[i] = y3;
    }
    else{
      xList3[i] = 1;
      yList3[i] = 1;
    }

  }

  func=(double)count/niter * ((UPPER_BOUND * 2) * FUNC_MAX);
  func2=(double)count2/niter * ((UPPER_BOUND * 2) * FUNC_MAX);
  func3=(double)count3/niter * ((UPPER_BOUND * 2) * FUNC_MAX);

  printf("Type\tEstimate\tError\t\tMeanX\t\tMeanY\t\tVarianceX\tVarianceY\tDeviationX\tDeviationY\n");
  printf("----------------------------------------------------------------------------------------------------------------------------------\n");

  //srand
  printf("SRAND\t%f\t%f\t", func, func-FUNC);
  doMVS(xList, yList);

  //srandom
  printf("SRANDOM\t%f\t%f\t", func2, func2-FUNC);
  doMVS(xList2, yList2);

  //rand_r
  printf("rand_r\t%f\t%f\t", func3, func3-FUNC);
  doMVS(xList3, yList3);


  printf("\n\n");

}//mathPart

void doMVS(double xList[], double yList[]){
  int i = 0;
  int listSize = sizeof(xList);
  double sumX, sumY = 0;
  double meanX, meanY = 0;

  //calculate sum
  for(i=0; i < listSize; i++){
    sumX += xList[i];
    sumY += yList[i];
  }

  //calculate mean
  meanX = sumX / listSize;
  meanY = sumY / listSize;

  double newSumX, newSumY = 0;
  //calculate variance and standard deviation
  for(i = 0; i < listSize; i++){
    newSumX += pow(xList[i] - meanX, 2);
    newSumY += pow(yList[i] - meanY, 2);
  }

  double varianceX = newSumX / (float)listSize;
  double varianceY = newSumY / (float)listSize;

  double stdX = sqrt(varianceX);
  double stdY = sqrt(varianceY);

  printf("%f\t%f\t", meanX, meanY);
  printf("%f\t%f\t", varianceX, varianceY);
  printf("%f\t%f\n", stdX, stdY);

}

double doFunc(double x){

  double partA = (1 / sqrt(2 * M_PI));
  double partB = pow(x, 2) / 2;
  double partC = pow(M_E, -1 * partB);

  return partA * partC;
}
