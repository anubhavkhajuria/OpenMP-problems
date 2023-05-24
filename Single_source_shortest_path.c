#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <omp.h>

#define MAX_NODES 4039
#define MAX_EDGES 88234

void dijkstra(int graph[MAX_NODES][MAX_NODES], int num_nodes, int num_threads, double* elapsed_time) {
    int distances[MAX_NODES];
    int visited[MAX_NODES];

    // Initialize distances and visited arrays
    for (int i = 0; i < MAX_NODES; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
    }

    // Set distance to source node as 0
    distances[0] = 0;

    // Perform Dijkstra's algorithm
    #pragma omp parallel num_threads(num_threads)
    {
        for (int i = 0; i < num_nodes - 1; i++) {
            int min_distance = INT_MAX;
            int min_index = -1;

            // Find the minimum distance vertex
            #pragma omp for
            for (int j = 0; j < num_nodes; j++) {
                if (!visited[j] && distances[j] < min_distance) {
                    min_distance = distances[j];
                    min_index = j;
                }
            }

            // Mark the selected vertex as visited
            #pragma omp single
            visited[min_index] = 1;

            // Update distances of adjacent vertices
            #pragma omp for
            for (int j = 0; j < num_nodes; j++) {
                if (!visited[j] && graph[min_index][j] && distances[min_index] != INT_MAX) {
                    if (distances[min_index] + 1 < distances[j]) {
                        distances[j] = distances[min_index] + 1;
                    }
                }
            }
        }
    }

}

int main() {
    int graph[MAX_NODES][MAX_NODES];
    int num_nodes, num_edges;
    double elapsed_time_seq, elapsed_time_parallel;
    FILE* file;
    FILE* result_file;
    int i, j, num_threads;

    // Read graph information from file
    file = fopen("C:/Users/Anubhav/Desktop/facebook_combined.txt", "r");
    if (file == NULL) {
        printf("Failed to open graph.txt file.\n");
        return 1;
    }

    fscanf(file, "%d %d", &num_nodes, &num_edges);

    for (i = 0; i < MAX_NODES; i++) {
        for (j = 0; j < MAX_NODES; j++) {
            graph[i][j] = 0;
        }
    }

    for (i = 0; i < num_edges; i++) {
        int u, v;
        fscanf(file, "%d %d", &u, &v);
        graph[u][v] = 1;
    }

    fclose(file);

    // Sequential Execution
    dijkstra(graph, num_nodes, 1, &elapsed_time_seq);

    // Parallel Execution with different number of threads
    result_file = fopen("result.txt", "w");
    if (result_file == NULL) {
        printf("Failed to open result.csv file.\n");
        return 1;
    }

    fprintf(result_file, "Graph name,#nodes,#edges,seq time(seconds),parallel times with 1,2,4,8,16 threads\n");
    fprintf(result_file, "Graph1,%d,%d,%f", num_nodes, num_edges, elapsed_time_seq);

    for (num_threads = 1; num_threads <= 16; num_threads *= 2) {
        dijkstra(graph, num_nodes, num_threads, &elapsed_time_parallel);
        fprintf(result_file, ",%f", elapsed_time_parallel);
    }

    fclose(result_file);

    return 0;
}
