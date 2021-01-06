#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "algraph.h"

#define SIZE 100

//return next line string in the given file
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
            char* tmp = str;
            str = (char*)realloc(str, (max_size * sizeof(char)));
            free(tmp);
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

//convert string into integer
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
    char filename[SIZE];
    printf("input file name : ");
    scanf("%s", &filename);
    FILE* f = fopen(filename, "r");
    if (f == NULL)
        return ERROR;

    //Create Graph
    ALGraph* G = (ALGraph*)malloc(sizeof(ALGraph));
    if (!G)
        exit(OVERFLOW);

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
        free(str);
    }
    fclose(f);
    printf("output file name : ");
    scanf("%s", &filename);
    f = fopen(filename, "w");
    
    //find Graph shortest path
    int src, dest;
    bool* visited = (bool*)malloc(G->vexnum * sizeof(bool)); 
    if (visited == NULL)
        exit(OVERFLOW);
    for (int i = 0; i < G->vexnum; i++)
        visited[i] = false;

    printf("input source and destination (i.e 1 2) : ");
    scanf("%d%d", &src, &dest);
    SetDist(G, src, dest);
    fprintf(f, "%d %d\n\n%d\n\n", src, dest, G->vertices[dest].dist);
    while (dest != src) {
        fprintf(f, "%d<-", dest);
        dest = G->vertices[dest].prev;
    }
    fprintf(f, "%d", dest);

    fclose(f);
    free(visited);
    delGraph(G);
    free(G);

    return OK;
}
