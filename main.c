/*
 * main.c
 *
 *  Created on: Sep 18, 2017
 *      Author: Erik
 */

#include<stdio.h>
#include<stdlib.h>

#include "hw2.h"

int MAX_ITERATIONS = 20;
int DIFFERENCE = 0.01;

int main(int argc, char *argv[]){



    char *filename = argv[1];
	int k =atoi(argv[2]);

    //int k = 5;
	int increment=0;

	FILE *myfile;
    myfile = fopen(filename, "r");



    int numData, dim;

    fscanf(myfile, "%d", &numData);
    fscanf(myfile, "%d", &dim);


    double **data = malloc_matrix(numData, dim);
    		for(int i = 0; i < numData; i++){
    			for(int j = 0; j<dim; j++){
    				double val;
    				fscanf(myfile, "%lf", &val);

    				data[i][j] = val;
    				//printf("%f ", data[i][j]);


    			}


    		}
    		fclose(myfile);

    double **centroids = malloc_matrix(k, dim);

    int **labels = malloc_matrix_int(1,numData);




    for(int i = 0; i < k; i++){
    	printf("Initial centroid %d: ",i);

    	for(int j = 0; j < dim; j++){
    		int temp = i;
    		centroids[i][j] = data[temp][j];
    		printf("%f ",centroids[i][j]);

    	}
    	printf("\n");

    }

    for(increment = 0; increment < MAX_ITERATIONS; increment++){
    	double **distance = find_distance(data, dim, centroids, k, numData);

    	clustering(distance, numData, k, labels);

    	update_centroids(data, centroids, labels, k, numData, dim);

    }

    for(int i = 0; i < k; i++){
            printf("Final centroid %d: ",i);
            	for(int j = 0; j < dim; j++){

            		printf("%f ",centroids[i][j]);


            	}
            	printf("\n");
        }

    double **finalDistance = find_distance(data, dim, centroids, k, numData);
    int **finalLabels = final_labels(finalDistance, numData, k, labels);

    char *output = argv[3] ;
    FILE *outputFile = fopen(output, "w");
    fprintf(outputFile, "%d  %d %d \n", numData, dim+1, k);
    for(int i =0; i < numData; i++){
    	for(int j = 0; j < dim; j++){

    		fprintf(outputFile, "%f ", data[i][j]);

    	}
    	fprintf(outputFile, " %d \n", finalLabels[0][i]);


    }

    fclose(outputFile);






}

