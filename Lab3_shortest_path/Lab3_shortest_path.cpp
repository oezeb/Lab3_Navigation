#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct ArcNode {
    int adjvex;
    int weight;
    struct ArcNode* nextarc;
}ArcNode;

typedef struct VNode {
    int dist;
    ArcNode* firstarc;
}VNode, *AdjList;

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
}ALGraph;

void initGraph(ALGraph* G, int vexnum) {
    
    G->vertices = (VNode*)malloc(++vexnum * sizeof(VNode));
    if (!G->vertices)
        exit(0);

    for (int i = 0; i < vexnum; i++) {
        G->vertices[i].dist = INT_MAX; //dist = infinite
        G->vertices[i].firstarc = NULL;
    }

    G->vexnum = vexnum;
    G->arcnum = 0;
}//initGraph

void insertArc(ALGraph* G, int i, int j, int weight) {
    //basic conditions
    if (G == NULL
        || i == j
        || i < 0 || i >= G->vexnum
        || j < 0 || j >= G->vexnum
        ) return;

    //insert i-->j edge
    ArcNode* p = (ArcNode*)malloc(G->vexnum * sizeof(ArcNode));
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


void dijkstra(ALGraph* G, int src, int dest) {

    bool* sptSet = (bool*)malloc(G->vexnum * sizeof(bool)); // sptSet[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 

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

        if (u == dest)
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
}


bool print_shortest_path(ALGraph* G, int src, int dest, int curr_dist, bool* visited) {
    if (!G || !visited)
        return false;

    if (curr_dist > G->vertices[dest].dist)
        return false;

    if (src == dest && curr_dist == G->vertices[dest].dist) {
        printf("%d", dest);
        return true;
    }

    visited[src] = true;
    ArcNode* p = G->vertices[src].firstarc;
    while (p) {
        if (!visited[p->adjvex] && print_shortest_path(G, p->adjvex, dest, curr_dist + p->weight, visited)) {
            printf("<-%d", src);
            return true;
        }
        p = p->nextarc;
    }

    visited[src] = false;
    return false;
}

char* getLine(FILE* f) {
    if (f == NULL)
        return NULL;

    int max_size = SIZE;
    char* str = (char*)malloc(max_size * sizeof(char));
    if (str == NULL)
        return NULL; //overflow

    int  i = 0;
    while (!feof(f)) {
        if (i >= max_size) {
            max_size += SIZE;
            str = (char*)realloc(str, (max_size * sizeof(char)));
            if (!str)
                return NULL; //overflow
        }
        str[i] = fgetc(f);
        if (str[i] == '\n')
            break;
        i++;
    }
    str[i] = '\0';
    return str;
}

int atoi(char* str, int* pos) {
    if (!str)
        return -1;
    int i;
    for (i = 0; str[i] != '\0' && (str[i] < '0' || str[i] > '9'); i++); //skip non integer char

    int result = 0;
    for (; str[i] != '\0' && str[i] >= '0' && str[i] <= '9'; i++)
        result = result * 10 + str[i] - '0';

    if (pos != NULL)
        *pos = i;

    return result;
}

int main(int argc, char* argv[]) {
    //open file
    /*
    if (argv[1] == NULL)
        return -1;
    char* filename = argv[1];
    */
    char filename[SIZE];
    printf("input file name : ");
    scanf("%s", &filename);
    FILE* f = fopen(filename, "r");
    if (f == NULL)
        return -1;

    //Create Graph
    ALGraph* G = (ALGraph*)malloc(sizeof(ALGraph));
    if (!G)
        return -1;
    while (!feof(f)) {
        char* str = getLine(f);
        if (str == NULL)
            return -1;
        if (str[0] != 'a' && str[0] != 'p')
            continue;

        int pos = 0, end;
        int numb1 = atoi(&str[pos], &end); pos += end;
        int numb2 = atoi(&str[pos], &end); pos += end;
        int numb3 = atoi(&str[pos], &end);

        if (str[0] == 'p') {
            //numb1 --> vertices number
            //numb2 --> edges number
            //numb2 --> none
            //init graph with numb1 number of vertices
            initGraph(G, numb1);
            //printf("%c %d %d\n", 'p', numb1, numb2);
        }
        else if (str[0] == 'a') {
            //numb1 --> vertice i
            //numb2 --> vertice j
            //numb2 --> edge weight
            insertArc(G, numb1, numb2, numb3);
            //printf("%c %d %d %d\n", 'a', numb1, numb2,numb3);
        }
    }
    //find Graph shortest path
    int src, dest;
    bool* visited = (bool*)malloc(G->vexnum * sizeof(bool));
    for (int i = 0; i < G->vexnum; i++)
        visited[i] = false;
    if (!visited)
        return -1;
    printf("input source and destination (i.e 1 2) : ");
    scanf("%d%d", &src, &dest);
    dijkstra(G, src, dest);
    printf("%d %d\n\n%d\n\n", src, dest, G->vertices[dest].dist);
    print_shortest_path(G,src, dest, 0, visited);
    return 0;
}
