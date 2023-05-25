#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <omp.h>

#define MAX_NODES 75888   //Initialize the number of nodes
#define MAX_EDGES 508838  //Initialize the number of edges
#define NUM_THREADS 4     //Initialize the thread count

typedef struct {
   long int node;
   long int cost;
} Edge;

typedef struct {
   long int node;
   long int distance;
} NodeDistance;

long int **graph;
long int *distances;
long int *visited;


void initialize(long int numNodes) {
    distances = (long int*)malloc(numNodes * sizeof(long int));
    visited = (long int *)malloc(numNodes * sizeof(long int));

    if (distances == NULL || visited == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (long int i = 0; i < numNodes; i++) {
        distances[i] = 222;
        visited[i] = 0;
    }
}
long int findMinDistanceNode() {
    long int minDistance = INT_MAX;
    long int minNode = -1;

    #pragma omp parallel for num_threads(NUM_THREADS)
    for (long int i = 0; i < MAX_NODES; i++) {
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

void dijkstra(long int startNode) {   `     //Implement Dijkstra's algorithm to find the shortest path
    distances[startNode] = 0;

    for (long int count = 0; count < MAX_NODES - 1; count++) {
        long int u = findMinDistanceNode();
        visited[u] = 1;

        #pragma omp parallel for num_threads(NUM_THREADS)
        for (long int v = 0; v < MAX_NODES; v++) {
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

    FILE *file = fopen("Large_data.txt", "r");          //Read the file which is placed in the same directory in which the code is present.
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    printf("Hello\n");

    initialize(MAX_NODES);
    printf("This\n");


graph = (long int**)malloc(MAX_NODES * sizeof(long int*));              //Dynamically allocate memory
if (graph == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
}
printf("Check 1\n");

for (long int i = 0; i < MAX_NODES; i++) {
    graph[i] = (long int *)malloc(MAX_NODES * sizeof(long int));
    if (graph[i] == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

printf("Check 2\n");

long int source, destination;
while (fscanf(file, "%ld %ld", &source, &destination) == 2) {
    
    
    
    if (source < 0 || source >= MAX_NODES) {                                //Check whether the source node is valid
        printf("Invalid node index: %ld\n", source);
        continue;                                                           // Skip this iteration and proceed to the next iteration
    }

    
    
    if (destination < 0 || destination >= MAX_NODES) {                       //Check whether the destination node is valid
        printf("Invalid node index: %ld\n", destination);
        continue;                                                           // Skip this iteration and proceed to the next iteration
    }

    
    if (graph[source] == NULL) {
        graph[source] = (long int*)malloc(MAX_NODES * sizeof(long int));
        if (graph[source] == NULL) {
            printf("Memory allocation failed for graph[%ld]\n", source);
            continue;                                                           // Skip this iteration and proceed to the next iteration
        }
        for (long int i = 0; i < MAX_NODES; i++) {
            graph[source][i] = 0;                                               // Initialize the newly allocated row
        }
    }

    graph[source][destination] = 1;
}



    fclose(file);
    printf("Check 3\n");
    double start_time = omp_get_wtime();

    dijkstra(0);

    double end_time = omp_get_wtime();
    printf("Check 4\n");
    printf("Execution time: %f seconds\n", end_time - start_time);                  //Time taken to execute the program.

    return 0;
}
