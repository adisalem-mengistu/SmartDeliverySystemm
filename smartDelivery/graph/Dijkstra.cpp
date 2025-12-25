#include "../smartDelivery.h"
#include <cstdio>

// ===========================
// Dijkstra Implementation
// ===========================
    // Find unvisited vertex with minimum distance
    int Dijkstra::minDistance(int dist[], bool visited[], int vertices) {
        int min = INF;
        int index = -1;

        for (int i = 0; i < vertices; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                index = i;
            }
        }
        return index;
    }

// ===========================
// Dijkstra Shortest Path
// ===========================
    void Dijkstra::shortestPath(Graph &g, int source) {
        int vertices = g.getVertices();
        int dist[MAX_LOCATIONS];
        bool visited[MAX_LOCATIONS];

        // Initialization
        for (int i = 0; i < vertices; i++) {
            dist[i] = INF;
            visited[i] = false;
        }

        dist[source] = 0;

        // Main Dijkstra Loop
        for (int count = 0; count < vertices - 1; count++) {
            int u = minDistance(dist, visited, vertices);

            if (u == -1)
                break;

            visited[u] = true;

            for (int v = 0; v < vertices; v++) {
                int distanceUV = g.getDistance(u, v);

                if (!visited[v] &&
                    distanceUV != INF &&
                    dist[u] != INF &&
                    dist[u] + distanceUV < dist[v]) {

                    dist[v] = dist[u] + distanceUV;
                }
            }
        }

        // Display result
        cout << "\n🚗 Optimal delivery times from " << g.getLocationName(source) << ":\n";
        cout << "================================================\n";
        for (int i = 0; i < vertices; i++) {
            printf("To %-20s: ", g.getLocationName(i));
            if (i == source) {
                cout << "Current Location\n";
            } else if (dist[i] == INF) {
                cout << "Not reachable\n";
            } else {
                cout << dist[i] << " minutes\n";
            }
        }
        cout << "================================================\n";
    }

    // ===========================
    // Dijkstra Menu
    // ===========================
    void Dijkstra::dijkstraMenu(Graph &g) {
        int source;

        if (g.getVertices() == 0) {
            cout << "No delivery areas set up yet! Please contact your manager.\n";
            return;
        }

        cout << "\n=== Route Optimization for Drivers ===\n";
        cout << "This will help you find the shortest route to your delivery destination.\n";
        cout << "\nAvailable delivery locations:\n";
        for (int i = 0; i < g.getVertices(); i++) {
            cout << i << ". " << g.getLocationName(i) << endl;
        }
        
        cout << "\nEnter your current location number: ";
        cin >> source;

        if (source < 0 || source >= g.getVertices()) {
            cout << "Invalid location number!\n";
            return;
        }

        shortestPath(g, source);
        
        cout << "\n💡 TIP: Use the shortest time routes to optimize your deliveries!\n";
    }
