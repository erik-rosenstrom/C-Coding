/*
 * hw2.h
 *
 *  Created on: Sep 18, 2017
 *      Author: Erik
 */

#ifndef HW2_H_
#define HW2_H_



void print_data(double **data, int numData, int dim);
void clustering(double **distance, int numData, int k, int **labels);
int find_label(double *distance, int numData, int k);
double **find_distance(double **data, int dim, double **centroids, int k, int numData);
double **malloc_matrix(int n1, int n2);
int **malloc_matrix_int(int n1, int n2);
int **final_labels(double **distance, int numData, int k, int **labels);
void update_centroids(double **data, double **centroids, int **labels,int k, int numData, int dim);

#endif /* HW2_H_ */
