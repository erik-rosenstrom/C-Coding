/*
 * KNNHeader.h
 *
 *  Created on: Sep 21, 2017
 *      Author: everyday
 */

#ifndef KNNHEADER_H_
#define KNNHEADER_H_

double**  malloc_matrix (int n1, int n2);
int**  malloc_matrix_int (int n1, int n2);
double **find_distance (double **classifyData, int classifyNumData, int classifyDim, double **trainData, int trainNumData);
int **find_closest(double **distance, int classifyNumData, int trainNumData, int k);
int find_closest_idx(double *distance, int trainNumData);
double **all_labels(int trainNumData, double **trainData);
int **find_labels(int **closest,double **trainData, int classifyNumData, int trainNumData, int numClasses, int k);


#endif /* KNNHEADER_H_ */
