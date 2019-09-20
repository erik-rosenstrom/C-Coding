/*
 * main.c
 *
 *  Created on: Oct 16, 2017
 *      Author: Erik
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
#include "graph.h"

int main(int argc, char *argv[]){
	srand(time(NULL));
	int totalDegrees = 20;
	int numV = 5;
	int N = atoi(argv[1]);
	int numVertex = N;
	int connectedCount;
	int count=0;

//creates graph
	graph *g = create_graph(N);



	addEdge(g,0,1);
	addEdge(g,0,2);
	addEdge(g,0,3);
	addEdge(g,0,4);
	addEdge(g,1,2);
	addEdge(g,1,3);
	addEdge(g,1,4);
	addEdge(g,2,3);
	addEdge(g,2,4);
	addEdge(g,3,4);



//randomly assigns nodes to create scale free network
	for(int i = 5; i < N; i++){
		int f = findProb(g, numV, totalDegrees);
		//printf("%d", f);
		addEdge(g, i, f);
		numV++;
		totalDegrees = totalDegrees + 2;
	}




	printGraph(g,N);

//main loop
	for(int k = 0; k<N; k++){
		int r = getRandNode(g,N);
		printf("%d\n",r);
		removeNode(g,r);
		//printf("\n");
		//printGraph(g,N);
		//printf("\n");
		numVertex--;
		connectedCount = bfs(g,N);

		//printf("\n %d",connectedCount);
		count++;
		if(connectedCount != numVertex)break;
	}
	printf("\n%d",count);





}
