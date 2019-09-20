/*
 * KNNimplement.c
 *
 *  Created on: Sep 21, 2017
 *      Author: everyday
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "KNNHeader.h"



double **malloc_matrix(int n1, int n2) {

    double **mat = NULL;       // pointer to the matrix

    if (n1 > 0 && n2> 0) {
    	mat = malloc(n1*sizeof(double *)); //allocates memory for matrix of doubles
    	for (int i = 0; i < n1; i++) {
    		mat[i] =malloc(n2*sizeof(double)); //allocates memory in each row for each column entry
    	}
    }
    return mat;//returns the pointer to the location created in memory
}

int **malloc_matrix_int(int n1, int n2) {

    int **mat = NULL;       // pointer to the matrix

    if (n1 > 0 && n2> 0) {
    	mat = malloc(n1*sizeof(int *)); //allocates memory for matrix of doubles
    	for (int i = 0; i < n1; i++) {
    		mat[i] =malloc(n2*sizeof(int)); //allocates memory in each row for each column entry
    	}
    }
    return mat;//returns the pointer to the location created in memory
}

double **find_distance (double **classifyData, int classifyNumData, int classifyDim, double **trainData, int trainNumData) {

	double **distance = malloc_matrix(classifyNumData, trainNumData);
	double sum = 0;
	double dif;

	for (int i = 0; i < classifyNumData; i++) {
		for (int j = 0; j < trainNumData; j++) {
			for (int k = 0; k < classifyDim; k++) {
				dif = classifyData[i][k] - trainData[j][k];
				sum += dif*dif;
			}
			distance[i][j] = sqrt(sum);
			sum = 0;
		}
	}
	return distance;
}

int find_closest_idx(double *distance, int trainNumData) {

	int closest_idx = 0;

	int best_index;
	double closest_distance = 10000000;
//
	for (int i = 0; i < trainNumData; i++) {
		double cur_distance = distance[i];
		if (cur_distance < closest_distance) {
			best_index = i;
			closest_distance = cur_distance;
		}
	}
//
	closest_idx = best_index;
	return closest_idx;

}

int **find_closest(double **distance, int classifyNumData, int trainNumData, int k) {
	int closest_idx;
	int **closest = malloc_matrix_int(classifyNumData, k);
	for (int i = 0; i < classifyNumData; i++) {
		double *distance_row = distance[i];
		for (int j = 0; j < k; j++){
			closest_idx = find_closest_idx(distance_row, trainNumData);
			closest[i][j] = closest_idx;
			distance[i][closest_idx] = 10000000;
		}
	}
//			for (int j = 0; j < k; j++) {
//				printf("%d\n", j);
//				printf("%d\n", closest[j]);
//			}
	return closest;
}

double **all_labels(int trainNumData,double **trainData){
	double **trainLabels = malloc_matrix(1, trainNumData);
		for (int i = 0; i < trainNumData; i++) {
			trainLabels[0][i] = trainData[i][2];
//			printf("%f\n", trainLabels[0][i]);
		}
		return trainLabels;
}


int **find_labels(int **closest,double **trainData, int classifyNumData, int trainNumData, int numClasses, int k){

	int count[numClasses];
	int closest_idx;
	int label;
	int final_label;
	double **trainLabels = all_labels(trainNumData, trainData);
	int **final_labels = malloc_matrix_int(classifyNumData, 1);
	for (int i = 0; i < classifyNumData; i++) {
		for (int i = 0; i < numClasses; i++) {
			count[i] = 0;
		}
		for (int j = 0; j < k; j++) {
			closest_idx = closest[i][j];
			label = (int) trainLabels[0][closest_idx];
			count[label]++;
		}
		final_label = 0;
		for (int j = 0; j< numClasses; j++) {
			printf("%d:  %d\n", j, count[j]);
			if (count[final_label] < count[j]) {
				final_label = j;
			}
		}
		printf("%d\n", final_label);
		final_labels[i][0] = final_label;
	}
//	for (int i = 0; i < classifyNumData; i++) {
//			printf("%d\n", final_labels[i][0]);
//		}
	return final_labels;
}



