#include "../smartDelivery.h"
#include <cstdio>

// ===========================
// Graph Implementation
// ===========================
    // ===========================
    // Constructor
    // ===========================
    Graph::Graph() {
        vertices = 0;

        for (int i = 0; i < MAX_LOCATIONS; i++) {
            for (int j = 0; j < MAX_LOCATIONS; j++) {
                if (i == j)
                    adj[i][j] = 0;
                else
                    adj[i][j] = INF;
            }
        }
        
        // Initialize default location names
        strcpy(locationNames[0], "Bole_Area");
        strcpy(locationNames[1], "Merkato");
        strcpy(locationNames[2], "Piassa");
        strcpy(locationNames[3], "CMC");
        strcpy(locationNames[4], "Kazanchis");
        strcpy(locationNames[5], "Addis_Ababa_University");
        strcpy(locationNames[6], "Meskel_Square");
        strcpy(locationNames[7], "Stadium");
        strcpy(locationNames[8], "Arat_Kilo");
        strcpy(locationNames[9], "Sidist_Kilo");
        
        loadFromFile(); // Load existing data on startup
    }

    // ===========================
    // Set number of locations
    // ===========================
    void Graph::setVertices(int v) {
        if (v > MAX_LOCATIONS) {
            cout << "Maximum locations exceeded!\n";
            return;
        }
        vertices = v;
        cout << "Total delivery areas set to " << vertices << endl;
        saveToFile(); // Save after setting vertices
    }

    // ===========================
    // Add Route (Edge)
    // ===========================
    void Graph::addEdge() {
        int src, dest, dist;

        cout << "Available locations:\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << ". " << locationNames[i] << endl;
        }
        
        cout << "Enter starting location number (0 to " << vertices - 1 << "): ";
        cin >> src;
        cout << "Enter destination location number (0 to " << vertices - 1 << "): ";
        cin >> dest;
        cout << "Enter travel time (minutes): ";
        cin >> dist;

        if (src < 0 || dest < 0 || src >= vertices || dest >= vertices) {
            cout << "Invalid location numbers!\n";
            return;
        }

        adj[src][dest] = dist;
        adj[dest][src] = dist; // Undirected graph

        cout << "Route added successfully.\n";
        saveToFile(); // Save after adding route
    }

    // ===========================
    // Display Adjacency Matrix
    // ===========================
    void Graph::displayGraph() {
        if (vertices == 0) {
            cout << "No delivery areas set up yet.\n";
            return;
        }

        cout << "\n=== Delivery Route Network ===\n";
        cout << "📍 Available delivery locations:\n";
        for (int i = 0; i < vertices; i++) {
            cout << i << ". " << locationNames[i] << endl;
        }
        
        cout << "\n🚗 Travel Times Between Locations (minutes):\n";
        
        // Header row with proper spacing
        cout << "From/To          ";
        for (int i = 0; i < vertices; i++) {
            printf("%-12s", locationNames[i]);
        }
        cout << "\n";
        
        // Separator line
        cout << "----------------";
        for (int i = 0; i < vertices; i++) {
            cout << "------------";
        }
        cout << "\n";
        
        // Data rows with proper alignment
        for (int i = 0; i < vertices; i++) {
            printf("%-16s", locationNames[i]);
            for (int j = 0; j < vertices; j++) {
                if (adj[i][j] == INF) {
                    printf("%-12s", "--");
                } else if (adj[i][j] == 0) {
                    printf("%-12s", "Current");
                } else {
                    char timeStr[20];
                    sprintf(timeStr, "%d min", adj[i][j]);
                    printf("%-12s", timeStr);
                }
            }
            cout << "\n";
        }
        
        cout << "\n💡 LEGEND:\n";
        cout << "   '--' = No direct route available\n";
        cout << "   'Current' = Same location\n";
        cout << "   Use 'Find Shortest Route' to get optimal delivery paths!\n";
    }

    // ===========================
    // Getters (Used by Dijkstra)
    // ===========================
    int Graph::getVertices() {
        return vertices;
    }

    int Graph::getDistance(int i, int j) {
        return adj[i][j];
    }

    // ===========================
    // Graph Menu
    // ===========================
    void Graph::graphMenu() {
        int choice;

        do {
            cout << "\n--- Delivery Area Setup ---\n";
            cout << "1. Set Number of Delivery Areas\n";
            cout << "2. Add Route Between Areas\n";
            cout << "3. View Route Network\n";
            cout << "0. Back\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                int v;
                cout << "Enter number of delivery areas: ";
                cin >> v;
                setVertices(v);
                break;
            }
            case 2:
                addEdge();
                break;
            case 3:
                displayGraph();
                break;
            case 0:
                break;
            default:
                cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }
// ===========================
// File Persistence Methods
// ===========================
void Graph::saveToFile() {
    ofstream file("data/graph.dat", ios::binary);
    if (!file) {
        cout << "Error: Could not save routes to file.\n";
        return;
    }
    
    file.write((char*)&vertices, sizeof(vertices));
    file.write((char*)adj, sizeof(adj));
    file.close();
}

void Graph::loadFromFile() {
    ifstream file("data/graph.dat", ios::binary);
    if (!file) {
        // File doesn't exist yet, start with empty data
        vertices = 0;
        return;
    }
    
    file.read((char*)&vertices, sizeof(vertices));
    file.read((char*)adj, sizeof(adj));
    file.close();
}
// ===========================
// Get Location Name
// ===========================
const char* Graph::getLocationName(int index) {
    if (index >= 0 && index < vertices) {
        return locationNames[index];
    }
    return "Unknown";
}