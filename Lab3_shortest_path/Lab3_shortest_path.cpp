#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    //TO dO
} Graph;

Graph *initGraph(int vexNumb) {
    //TO DO
    return NULL;
}

void insertEdge(Graph* G, int i, int j, int weight) {
    //TO DO
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
    scanf("%s", &filename);
    FILE* f = fopen(filename, "r");
    if (f == NULL)
        return -1;

    //Create Graph
    Graph* G = NULL;
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
            G = initGraph(numb1);
            printf("%c %d %d\n", 'p', numb1, numb2);
        }
        else if (str[0] == 'a') {
            //numb1 --> vertice i
            //numb2 --> vertice j
            //numb2 --> edge weight
            insertEdge(G, numb1, numb2, numb3);
            printf("%c %d %d %d\n", 'a', numb1, numb2,numb3);
        }
    }
    //find Graph shortest path
    return 0;
}