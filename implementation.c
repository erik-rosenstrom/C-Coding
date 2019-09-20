/*
 * implementation.c
 *
 *  Created on: Sep 18, 2017
 *      Author: Erik
 */

#include "hw2.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/* this print data function prints an array
 * it is the helper function from the slides
 * takes in pointer to 2D array, number of data observations and number of data attributes
 * */

void print_data(double **data, int numData, int dim){
	for(int i = 0; i<numData; i++){
		printf("Distance array %d: ", i);
		for(int j = 0; j < dim; j++){
			printf("%f    ", data[i][j]);
		}
		printf("\n");
	}
}

/*find distance finds the distance between every point and each centroid
 * the distance to each centroid is a column in the matrix
 * takes in a pointer to a data set, dimensions, pointer to matrix of centroids, number of centroids, and number of data items  */

double **find_distance(double **data, int dim, double **centroids, int k, int numData){
	double **distance = malloc_matrix(numData, k);
	double sum = 0;
	double dif;

	for(int a = 0; a < numData; a++){
		for(int i =0; i < k; i++){
				for(int j = 0; j < dim; j++){
				dif = data[a][j] - centroids[i][j];
				sum += (dif) * (dif);
				}
				distance[a][i]=sqrt(sum);
				sum = 0;
			}


	}
	return distance;
}

/*find label is a function that assigns a label to each point in the data set based on which centroid it is closest too
 * takes each point as a 1d array from the whole 2d distance array
 * as well as number of data and number of centroids, returns an int label particular to each point*/
int find_label(double *distance, int numData, int k){

	int label;

	int best_index;
	double closest_distance = 100000000;


	for (int j = 0; j < k; j++){


	    double cur_distance = distance[j];
	    if (cur_distance < closest_distance){
	        best_index = j;
	        closest_distance = cur_distance;
	    }
	}


	        label = best_index;


}
/*repeats find label for the entire distance array and updates the labels matrix
 * takes the full distance matrix, number of data, number of centroids
 * and a pointer to the 2d 1 x numData array of labels */

void clustering(double **distance, int numData, int k, int **labels){
	int label;
	for(int i = 0; i < numData; i++){

       label = find_label(distance[i], numData, k);

		labels[0][i] = label;

	}
}
/* for file output  purposes to get final dataset's labels */
int **final_labels(double **distance, int numData, int k, int **labels){
	int label;
	for(int i = 0; i < numData; i++){

       label = find_label(distance[i], numData, k);

		labels[0][i] = label;

	}
	return labels;
}





/**
 * Allocate memory for a 2D matrix
 * @param n1 the number of rows
 * @param n2 the number of columns
 * @return a pointer to the matrix
*/
double **malloc_matrix(int n1, int n2) {


	    if(n1 >= 0 && n2>=0){
	    	double  **mat = (double **)malloc(n1 * sizeof(double *));
	    	            for (int i=0; i<n1; i++){
	    	                 mat[i] = (double *)malloc(n2 * sizeof(double));
	    	            }
	    	            return mat;
	    }else{
	    	return NULL;
	    }


	}
/*malloc but for ints*/
int **malloc_matrix_int(int n1, int n2){


	    if(n1 >= 0 && n2>=0){
	    	int  **mat = (int **)malloc(n1 * sizeof(int *));
	    	            for (int i=0; i<n1; i++){
	    	                 mat[i] = (int *)malloc(n2 * sizeof(int));
	    	            }
	    	            return mat;
	    }else{
	    	return NULL;
	    }


	}
/* counts how many of each label there are
 * returns a 2d array of ints kx1
 * takes in array of labels, number of data and number of centroids*/
int **increment_count(int **labels, int numData, int k){
	int **counts = malloc_matrix_int(1, k);
	int count = 0;
	int temp;
	for(int i = 0; i < k; i++){

			for(int j = 0; j < numData; j++){

				temp = labels[0][j];
				if(temp == i){

					count++;


				}


			}

			counts[0][i] = count;
			count = 0;

	}
	return counts;

}
/* updates values of centroids by reinitializing them their value and then sums up each dimensional value for a specific label
 * and divides by number of number of data points assigned that label
 * takes in dataset, array of centroids array of labels, number of centroids number of data, and dimension of data*/
void update_centroids(double **data, double **centroids, int **labels, int k, int numData, int dim){


    int **count = increment_count(labels, numData, k);

	for(int i = 0; i < k; i++){
		for(int j =0; j < dim; j++){
			centroids[i][j] = 0.0;
		}
	}
	for(int i = 0; i < numData; i++){
		for(int j = 0; j < dim; j++){
			for(int a = 0; a < k; a++){
				if(labels[0][i] == a){

					centroids[a][j] += data[i][j];


				}
			}
		}
	}

	for(int i = 0; i < k; i++){
		for(int j = 0; j < dim; j++){

			centroids[i][j] = centroids[i][j] / count[0][i];

		}
	}

}


