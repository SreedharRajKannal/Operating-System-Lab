#include <stdio.h>
#include <stdlib.h>  // For malloc() and free()
#include <stdbool.h> // For bool, true, and false
#include <limits.h>  // For INT_MAX, which we use as "Infinity"

/**
 * @brief Finds the unvisited vertex with the minimum distance.
 *
 * @param dist[]    The array holding the current shortest distances
 * @param visited[] The array tracking which nodes are "visited"
 * @param V         The total number of vertices
 * @return The index of the unvisited node with the minimum distance.
 */
int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX;
    int min_index = -1;

    for (int v = 0; v < V; v++) {
        if (visited[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

/**
 * @brief Prints the final distance array.
 *
 * @param dist[] The array of final shortest distances.
 * @param src    The source node (for a clearer title).
 * @param V      The total number of vertices.
 */
void printSolution(int dist[], int src, int V) {
    printf("\n--- Shortest Distances from Source Node %d ---\n", src);
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++) {
        if (dist[i] == INT_MAX) {
            printf("%d \t\t %s\n", i, "INF (No Path)");
        } else {
            printf("%d \t\t %d\n", i, dist[i]);
        }
    }
}

/**
 * @brief Implements Dijkstra's algorithm.
 *
 * @param graph  A 2D pointer to the dynamically allocated adjacency matrix.
 * @param src    The source vertex to start from.
 * @param V      The total number of vertices.
 */
void dijkstra(int **graph, int src, int V) {
    // 1. INITIALIZATION:
    
    // Allocate memory for distance and visited arrays
    int *dist = (int *)malloc(V * sizeof(int));
    bool *visited = (bool *)malloc(V * sizeof(bool));

    if (dist == NULL || visited == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    // Initialize all distances as INFINITE and all visited as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // Distance from the source vertex to itself is always 0
    dist[src] = 0;

    // 2. START THE LOOP:
    for (int count = 0; count < V - 1; count++) {
        
        // 3. GET THE NEXT NODE:
        int u = minDistance(dist, visited, V);

        if (u == -1) {
            break; // No reachable nodes left
        }

        visited[u] = true;

        // 4. LOOK AT NEIGHBORS (The "Relaxation" Step):
        for (int v = 0; v < V; v++) {
            
            // Update dist[v] only if:
            // 1. Node 'v' is NOT visited.
            // 2. There is an edge from 'u' to 'v' (graph[u][v] is not 0).
            // 3. The new path (through 'u') is SHORTER.
            if (!visited[v] &&
                 graph[u][v] != 0 &&
                 dist[u] != INT_MAX &&
                 dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // 5. FINISH:
    printSolution(dist, src, V);

    // 6. CLEANUP:
    // Free the memory allocated inside this function
    free(dist);
    free(visited);
}

// Driver program
int main() {
    int V, E; // V = Vertices, E = Edges
    int **graph; // Graph as an adjacency matrix

    // --- Get Graph Size ---
    printf("Enter the number of nodes (vertices): ");
    scanf("%d", &V);

    printf("Enter the number of connections (edges): ");
    scanf("%d", &E);

    // --- Allocate Memory for the Graph ---
    // Allocate an array of row pointers
    graph = (int **)malloc(V * sizeof(int *));
    if (graph == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    // Allocate memory for each row
    for (int i = 0; i < V; i++) {
        // Use calloc to initialize all values to 0 (no edge)
        graph[i] = (int *)calloc(V, sizeof(int)); 
        if (graph[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
    }

    // --- Get Edge Information ---
    printf("\n--- Enter Edge Details ---\n");
    printf("Enter %d edges as (Source, Destination, Weight).\n", E);
    printf("Note: Node numbering starts from 0 (e.g., 0, 1, 2,...)\n");
    
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);

        // Basic validation
        if (src < 0 || src >= V || dest < 0 || dest >= V) {
            printf("Invalid node number! Must be between 0 and %d.\n", V - 1);
            i--; // Retry this edge
        } else {
            // This creates a directed graph.
            // For an undirected graph, add: graph[dest][src] = weight;
            graph[src][dest] = weight;
        }
    }

    // --- Get Start Node ---
    int startNode;
    printf("\nEnter the start node (0 to %d): ", V - 1);
    scanf("%d", &startNode);

    if (startNode < 0 || startNode >= V) {
        printf("Invalid start node. Exiting.\n");
        return 1;
    }

    // --- Run Dijkstra's Algorithm ---
    dijkstra(graph, startNode, V);

    // --- Free All Dynamically Allocated Memory ---
    for (int i = 0; i < V; i++) {
        free(graph[i]); // Free each row
    }
    free(graph); // Free the array of row pointers

    return 0;
}