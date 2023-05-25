#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>                // OpenMp header.

#define MAX_NODES 875713      // Maximum Number of nodes present in the file.
#define NUM_THREADS 8        // initializes number of threads.

typedef struct {
    long int node;
    long int distance;
} NodeDistance;

NodeDistance distances[MAX_NODES];
char visited[MAX_NODES] = {0};

void initialize(long int numNodes) {
    for (long int i = 0; i < numNodes; i++) {
        distances[i].node = i;
        distances[i].distance = (i == 0) ? 0 : INT_MAX;
        visited[i] = 0;
    }
}

long int findMinDistanceNode() {             // Calculate Minimum distance from the start node 
    long int minDistance = INT_MAX;
    long int minNode = -1;

    #pragma omp parallel for num_threads(NUM_THREADS) reduction(min : minDistance)
    for (long int i = 0; i < MAX_NODES; i++) {
        if (!visited[i] && distances[i].distance < minDistance) {
            minDistance = distances[i].distance;
            minNode = i;
        }
    }

    return minNode;
}

void dijkstra(long int startNode) {                    // Implement Djikstra's algorithm
    distances[startNode].distance = 0;

    for (long int count = 0; count < MAX_NODES - 1; count++) {
        long int u = findMinDistanceNode();
        visited[u] = 1;

        #pragma omp parallel for num_threads(NUM_THREADS)
        for (long int v = 0; v < MAX_NODES; v++) {
            if (!visited[v] && distances[u].distance != INT_MAX && distances[u].distance + 1 < distances[v].distance) {
                distances[v].distance = distances[u].distance + 1;
            }
        }
    }
}

int main() {
    FILE *file = fopen("Google.txt", "r");               // Open input file 
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    initialize(MAX_NODES);

    long int source, destination;
    while (fscanf(file, "%ld %ld", &source, &destination) == 2) {
        if (source >= 0 && source < MAX_NODES && destination >= 0 && destination < MAX_NODES) {
            distances[source].node = source;
            distances[destination].node = destination;
        }
    }

    fclose(file);

    double start_time = omp_get_wtime();

    dijkstra(0);

    double end_time = omp_get_wtime();

    printf("Execution time: %f seconds\n", end_time - start_time);         // Time taken to complete the Execution.

    return 0;
}


// The dataset is google web graph from https://snap.stanford.edu/data/ with 875713 nodes and 5105039 edges.
