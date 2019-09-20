/*
 * graph.c
 *
 *  Created on: Oct 16, 2017
 *      Author: Erik
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graph.h"


struct List{
	int size;
	listNode *head;
	listNode *tail;

};

struct listNode{
	int vertexNumber;
	struct listNode *nextListNode;
};


struct graph{
	int numVertex;
	List *array;
};
//helper
size_t getNumNeighbors(graph *g, int i){
	return g->array[i].size;
}
//helper
listNode *getListNode(graph *g, int i){
	if(g->array[i].head == NULL)return NULL;
	return g->array[i].head;
}
//helper
int getVertNum(listNode *n){
	return n->vertexNumber;
}
//helper
listNode *getNextListNode(listNode *n){
	return n->nextListNode;
}
//creates list node
listNode *create_listNode(int vertexNumber){
	listNode *l = (listNode*)malloc(sizeof(listNode));
	if(l == NULL){
		printf("Fatal Error out of memory!\n");
		return NULL;
	}
	l->vertexNumber = vertexNumber;
	l->nextListNode = NULL;

	return l;
}
//creates list
List *create_list(){
	List *l = (List*)malloc(sizeof(List));
	if(l == NULL){
		printf("Fatal Error out of memory!\n");
		return NULL;
	}
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;

	return l;
}

//creates graph
graph *create_graph(int numVertex){
	graph *g = (graph*)malloc(sizeof(graph));
	if(g == NULL){
		printf("Fatal Error out of memory!\n");
		return NULL;
	}
	g->numVertex = numVertex;

	g->array = (List*)malloc(numVertex * sizeof(List));
	for(int i = 0; i < numVertex; i++){
		g->array[i].head = NULL;
		g->array[i].tail = NULL;
		g->array[i].size = 0;
	}
	return g;
}
//help function list node to generic list
void addToList(List *l, int edge){
	listNode *newNode = create_listNode(edge);
	if(newNode == NULL){
		printf("Fatal memory out of memory!");
		return;
	}
	if(l->size == 0){
		l->head = newNode;
		l->tail = newNode;
		l->size++;
	}else{
		l->tail->nextListNode = newNode;
		l->tail = newNode;
		l->size++;
	}
}

void removeFromList(List *l){

	l->head = l->head->nextListNode;
	l->size--;

}



//adds edge to graph

void addEdge(graph *g, int src, int dest){
	listNode *source = create_listNode(src);
	listNode *destin = create_listNode(dest);
	if(g->array[src].size ==0){
		g->array[src].head=destin;
		g->array[src].tail=destin;
		g->array[src].tail->nextListNode = NULL;
		g->array[src].size++;
	}else{
		g->array[src].tail->nextListNode = destin;
		g->array[src].tail = destin;

		g->array[src].size++;
	}

	if(g->array[dest].size == 0){
		g->array[dest].head = source;
		g->array[dest].tail = source;
		g->array[dest].tail->nextListNode = NULL;
		g->array[dest].size++;
	}else{
		g->array[dest].tail->nextListNode = source;
		g->array[dest].tail = source;

		g->array[dest].size++;
	}


}
//need global variable for number of nodes currently in graph: numV
//need global variable for number of degrees currently in graph: totalDegrees
//pick node function from assignment documentation
int findProb(graph *g, int numV, int totalDegrees){
	double probArray[numV];
	//printf("pdf matrix\n");
	for(int i = 0; i < numV; i++){
		probArray[i] = ((double)(g->array[i].size)/totalDegrees);
		//printf("%d\n", g->array[i].size);
		//printf("%f\n", probArray[i]);
	}
	double r = (double)rand() / (double)RAND_MAX;
		double cdf[numV];
		//printf("cdf matrix\n");
		for(int i = 0; i < numV; i++){
			if(i==0){
				cdf[i] = probArray[i];
			}else{
				cdf[i]= probArray[i] + cdf[i-1];
			}
			//printf("%f\n", cdf[i]);
		}
		//printf("%f", r);

		for(int i = 0; i < numV; i++){
			if(cdf[i] >= r){
				//printf("%f", cdf[i]);
				return i;
			}
		}
		return 0;


}

//prints graph
void printGraph(graph* graph, int numV){
    int v;
    for (v = 0; v < numV; v++){
       struct listNode* n = graph->array[v].head;

//        printf("\nSize: %d\n", n->);

        printf("List of vertex %d\n head ", v);
        while (n){
            printf("-> %d", n->vertexNumber);

            n = n->nextListNode;
        }
        printf("\n");
    }
}

//remove nodes from graph
void removeNode(graph *g, int node){
	int x = g->array[node].size;
	int *vertNums = malloc(x * sizeof(int));
	listNode *n = g->array[node].head;
	int i = 0;
	int temp;
	while(n){
		vertNums[i] = n->vertexNumber;
		n = n->nextListNode;
		i++;
	}


	for(int i = 0; i < x; i++){
		temp = vertNums[i];
		listNode *m = g->array[temp].head;
		listNode *p = g->array[temp].tail;
		if(g->array[temp].size == 1 && m->vertexNumber == node){
			g->array[temp].head = NULL;
		}else if(m->vertexNumber == node){
			g->array[temp].head = m->nextListNode;

		}else if(p->vertexNumber == node){

		while(m->nextListNode->nextListNode){
				if(m->nextListNode->vertexNumber == node){
					m->nextListNode = m->nextListNode->nextListNode;
				}
				m=m->nextListNode;
			}
		m->nextListNode = NULL;
		}else{
			while(m->nextListNode){
							if(m->nextListNode->vertexNumber == node){
								m->nextListNode = m->nextListNode->nextListNode;
							}
							m=m->nextListNode;
						}
			m->nextListNode = NULL;
		}
	}

	g->array[node].head = NULL;

}

//gets random node for deletion
int getRandNode(graph *g, int N){
	int r = rand()%N;
	if(g->array[r].head ==NULL){
		getRandNode(g, N);
	}
	return r;
}

//bfs search function
int bfs(graph *g, int N){
	int total = 0;
	int *color = malloc(N * sizeof(int));
		for(int i = 0; i < N; i++){
			color[i] = 0;
		}
	List *l = create_list();
	for(int i = 0; i < N; i++){
		listNode *temp = g->array[i].head;
		if(color[i]==0 && temp != NULL){
			addToList(l, i);
			color[i] = 1;
			while(temp->nextListNode){
				int tempVert = temp->nextListNode->vertexNumber;
				if(color[tempVert]==0){
					addToList(l,tempVert);
					color[tempVert] = 1;
				}
				temp = temp->nextListNode;
			}
			removeFromList(l);
		}
		//printf("%d\n",color[i]);
	}
	for(int j = 0; j < N; j++){
		if(color[j]==1){
			total++;
		}
	}
	return total;
}





