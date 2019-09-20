/*
 * KNN.c
 *
 *  Created on: Sep 21, 2017
 *      Author: everyday
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "KNNHeader.h"

int main(int argc, char *argv[]) {

	char *trainingFile= argv[1];
	char *classifyFile = argv[2];
	char *outFile = argv[3];
	int k = atoi(argv[4]);


		//load classify data
		FILE *myClassify;
		myClassify = fopen(classifyFile, "r");

		int classifyNumData, classifyDim;

		fscanf(myClassify, "%d", &classifyNumData);
		fscanf(myClassify, "%d", &classifyDim);




		double **classifyData = malloc_matrix(classifyNumData, classifyDim);
				for (int i = 0; i < classifyNumData; i++) {
					for (int j = 0; j < classifyDim; j++) {
						double val;
						fscanf(myClassify, "%lf", &val);
						classifyData[i][j] = val;
					}
				}


	//load training data
	FILE *myTrain;
	myTrain = fopen(trainingFile, "r");

	int trainNumData, trainDim, numClasses;


	fscanf(myTrain, "%d", &trainNumData);
	fscanf(myTrain, "%d", &trainDim);
	fscanf(myTrain, "%d", &numClasses);


	double **trainData = malloc_matrix(trainNumData, trainDim);
		for (int i = 0; i < trainNumData; i++) {
			for (int j = 0; j < trainDim; j++) {
				double val;
				fscanf(myTrain, "%lf", &val);
				trainData[i][j] = val;
			}
		}


	fclose(myTrain);


	double **distance = find_distance (classifyData, classifyNumData, classifyDim, trainData, trainNumData);


	int **closest = find_closest(distance, classifyNumData, trainNumData, k);


	int **labels = find_labels(closest, trainData, classifyNumData, trainNumData, numClasses, k);

	for (int i = 0; i < classifyNumData; i++) {
		printf("%d\n", labels[i][0]);
	}

	FILE *outputFile = fopen(outFile, "w");
	fprintf(outputFile, "%d %d\n", classifyNumData, classifyDim);
	for (int i = 0; i < classifyNumData; i++){
		for (int j = 0; j < classifyDim; j++) {
			fprintf(outputFile, "%f ", classifyData[i][j]);
		}
		fprintf(outputFile, " %d \n", labels[i][0]);
	}
	fclose(outputFile);


}


