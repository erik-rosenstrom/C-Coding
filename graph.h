/*
 * graph.h
 *
 *  Created on: Oct 16, 2017
 *      Author: Erik
 */

#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct List List;
typedef struct listNode listNode;
typedef struct graph graph;


size_t getNumNeighbors(graph *g, int i);

listNode *getListNode(graph *g, int i);

int getVertNum(listNode *n);

listNode *getNextListNode(listNode *n);

List *getList(graph *g, int index);

listNode *create_listNode(int vertexNumber);

List *create_list();

graph *create_graph(int numVertex);

void addToList(List *l, int edge);

void addEdge(graph *g, int src, int dest);

int findProb(graph *g, int numV, int totalDegrees);

int chooseNode(graph *g, int numV, double *probArray);

void removeNode(graph *g, int node);

void printList(List *l);

void printGraph(graph* graph, int numV);





#endif /* GRAPH_H_ */
