#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

#define MAX_NODES 8717
#define MAX_EDGES 31525
#define NUM_THREADS 16

typedef struct {
    int node;
    int cost;
} Edge;

typedef struct {
    int node;
    int distance;
} NodeDistance;

int **graph;
int *distances;
int *visited;


void initialize(int numNodes) {
    distances = (int*)malloc(numNodes * sizeof(int));
    visited = (int*)malloc(numNodes * sizeof(int));

    if (distances == NULL || visited == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < numNodes; i++) {
        distances[i] = 222;
        visited[i] = 0;
    }
}
int findMinDistanceNode() {
    int minDistance = INT_MAX;
    int minNode = -1;

    #pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 0; i < MAX_NODES; i++) {
        if (!visited[i] && distances[i] < minDistance) {
            #pragma omp critical
            {
                if (distances[i] < minDistance) {
                    minDistance = distances[i];
                    minNode = i;
                }
            }
        }
    }

    return minNode;
}

void dijkstra(int startNode) {
    distances[startNode] = 0;

    for (int count = 0; count < MAX_NODES - 1; count++) {
        int u = findMinDistanceNode();
        visited[u] = 1;

        #pragma omp parallel for num_threads(NUM_THREADS)
        for (int v = 0; v < MAX_NODES; v++) {
            if (!visited[v] && graph[u][v] && distances[u] != INT_MAX && distances[u] + graph[u][v] < distances[v]) {
                #pragma omp critical
                {
                    if (distances[u] + graph[u][v] < distances[v]) {
                        distances[v] = distances[u] + graph[u][v];
                    }
                }
            }
        }
    }
}

int main() {

    FILE *file = fopen("GUN06.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    printf("Hello\n");

    initialize(MAX_NODES);
printf("This\n");


graph = (int**)malloc(MAX_NODES * sizeof(int*));
if (graph == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
}


for (int i = 0; i < MAX_NODES; i++) {
    graph[i] = (int*)malloc(MAX_NODES * sizeof(int));
    if (graph[i] == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}



int source, destination;
while (fscanf(file, "%d %d", &source, &destination) == 2) {
    graph[source][destination] = 1;
}


    fclose(file);

    double start_time = omp_get_wtime();

    dijkstra(0);

    double end_time = omp_get_wtime();

    printf("Execution time: %f seconds\n", end_time - start_time);

    return 0;
}
