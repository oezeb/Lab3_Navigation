#ifndef ALGRAPH
#define ALGRAPH

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define OK          1
#define ERROR       0
#define OVERFLOW   -2

typedef struct ArcNode {
    int adjvex;
    int weight;
    struct ArcNode* nextarc;
}ArcNode;

typedef struct VNode {
    int dist;
    ArcNode* firstarc;
}VNode, * AdjList;

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;

void initGraph(ALGraph* G, int vexnum) {

    G->vertices = (VNode*)malloc(++vexnum * sizeof(VNode));
    if (!G->vertices)
        exit(OVERFLOW);

    for (int i = 0; i < vexnum; i++) {
        G->vertices[i].dist = INT_MAX; //dist = infinite
        G->vertices[i].firstarc = NULL;
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


//find the vertex with minimum distance value, from 
// the set of vertices not yet included in shortest path tree 
int minDistance(ALGraph* G, bool* sptSet) {
    // Initialize min value 
    int min = INT_MAX, min_index = -1;

    for (int i = 0; i < G->vexnum; i++)
        if (sptSet[i] == false && G->vertices[i].dist <= min)
            min = G->vertices[i].dist, min_index = i;

    return min_index;
}

//using dijkstra algorithm
void SetDist(ALGraph* G, int src, int dest) {

    // sptSet[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 
    bool* sptSet = (bool*)malloc(G->vexnum * sizeof(bool));
    if (sptSet == NULL)
        exit(OVERFLOW);

    // Initialize all stpSet[] as false
    for (int i = 0; i < G->vexnum; i++)
        sptSet[i] = false;

    // Distance of source vertex from itself is always 0 
    G->vertices[src].dist = 0;

    // Find shortest path for all vertices 
    for (int count = 0; count < G->vexnum - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration. 
        int u = minDistance(G, sptSet);

        if (u == dest) // stop when destination distance is set
            break;

        // Mark the picked vertex as processed 
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex. 
        ArcNode* p = G->vertices[u].firstarc;
        while (p != NULL) {
            int v = p->adjvex;
            // Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to v through u is 
            // smaller than current value of dist[v] 
            if (!sptSet[v] && G->vertices[u].dist != INT_MAX
                && G->vertices[u].dist + p->weight < G->vertices[v].dist)
                G->vertices[v].dist = G->vertices[u].dist + p->weight;
            p = p->nextarc;
        }
    }
    free(sptSet);
}

bool print_shortest_path(ALGraph* G, int src, int dest, int curr_dist, bool* visited, FILE* outputfile) {
    //basic condition
    if (!G || !visited || !outputfile)
        return false;

    // if current dist already bigger than dest dist of course it's not the right path
    if (curr_dist > G->vertices[dest].dist)
        return false;



    //found the right path
    if (src == dest && curr_dist == G->vertices[dest].dist) {
        fprintf(outputfile, "%d", dest);
        return true;
    }

    //check the neighborhood
    visited[src] = true;
    ArcNode* p = G->vertices[src].firstarc;
    while (p) {
        if (!visited[p->adjvex] && print_shortest_path(G, p->adjvex, dest, curr_dist + p->weight, visited, outputfile)) {
            fprintf(outputfile, "<-%d", src);
            return true;
        }
        p = p->nextarc;
    }

    visited[src] = false;
    return false;
}

#endif // !ALGRAPH

