#ifndef ALGRAPH
#define ALGRAPH

#include <stdlib.h>
#include "priority_queue.h"


#define OK          1
#define ERROR       0
#define OVERFLOW   -2

typedef struct ArcNode {
    int adjvex;
    int weight;
    struct ArcNode* nextarc;
}ArcNode;

typedef struct VNode {
    int index;
    int prev; //verice before reaching current one(use to draw path)
    int dist;
    ArcNode* firstarc;
}VNode, * AdjList;

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;

int comp(VNode* const& v1, VNode* const& v2) {
    return v1->dist - v2->dist;
}

void initGraph(ALGraph* G, int vexnum) {

    G->vertices = (VNode*)malloc(++vexnum * sizeof(VNode));
    if (!G->vertices)
        exit(OVERFLOW);

    for (int i = 0; i < vexnum; i++) {
        G->vertices[i].dist = INT_MAX; //dist = infinite
        G->vertices[i].firstarc = NULL;
        G->vertices[i].prev = -1;
        G->vertices[i].index = i;
    }

    G->vexnum = vexnum;
    G->arcnum = 0;
}//initGraph

void delGraph(ALGraph* G) {
    //free edges
    for (int i = 0; i < G->vexnum; i++) {
        ArcNode* p = G->vertices[i].firstarc;
        while (p != NULL) {
            ArcNode* tmp = p;
            p = p->nextarc;
            free(tmp);
        }
    }
    //
    free(G->vertices);
}

void insertArc(ALGraph* G, int i, int j, int weight) {
    //basic conditions
    if (G == NULL
        || i == j
        || i < 0 || i >= G->vexnum
        || j < 0 || j >= G->vexnum
        ) return;

    //insert i-->j edge
    ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
    if (p == NULL)
        exit(OVERFLOW);

    p->adjvex = j;
    p->nextarc = G->vertices[i].firstarc;
    G->vertices[i].firstarc = p;

    //set edge weight)
    p->weight = weight;

    G->arcnum++;
}//Insert_Arc

// using  dijkstra algorithm and priority queue
void shortestPath(ALGraph *G,int src) {
    // Create a priority queue to store vertices
    Priority_Queue<VNode*> p_queue;
    Priority_Queue<VNode*>::init(p_queue, G->vexnum, comp);

    // Insert source into priority queue and initialize 
    // its distance as 0. 
    G->vertices[src].dist = 0;
    Priority_Queue<VNode*>::enqueue(p_queue, &G->vertices[src]);

    while (!Priority_Queue<VNode*>::empty(p_queue)) {
        VNode* u = NULL;
        Priority_Queue<VNode*>::dequeue(p_queue, u);

        for (ArcNode* e = u->firstarc; e; e = e->nextarc) {
            VNode* v = &G->vertices[e->adjvex];
            //  If there is shorted path to v through u. 
            if (v->dist > u->dist + e->weight) {
                // Updating distance of v 
                v->dist = u->dist + e->weight;
                v->prev = u->index;
                Priority_Queue<VNode*>::enqueue(p_queue, v);
            }
        }
    }
    Priority_Queue<VNode*>::destroy(p_queue);
}

#endif // !ALGRAPH

