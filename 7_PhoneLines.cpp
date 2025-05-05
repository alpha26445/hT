#include <iostream>
#include <climits>
using namespace std;

class Graph {
    int adjMatrix[20][20];   // Adjacency matrix to store connection weights
    int visited[20];         // Array to track visited nodes
    int vertices, edges;     // Number of branches and connections

public:
    void input();
    void display();
    void primMST();
};

void Graph::input() {
    cout << "Enter the number of branches: ";
    cin >> vertices;

    // Initialize adjacency matrix and visited array
    for (int i = 0; i < vertices; ++i) {
        visited[i] = 0;
        for (int j = 0; j < vertices; ++j) {
            adjMatrix[i][j] = INT_MAX;  // INT_MAX represents no direct connection
        }
    }

    cout << "\nEnter the number of connections: ";
    cin >> edges;

    for (int i = 0; i < edges; ++i) {
        int src, dest, weight;
        cout << "Enter the two branches of the connection (1-indexed): ";
        cin >> src >> dest;
        cout << "Enter the phone company charges for this connection: ";
        cin >> weight;

        // Convert to 0-based indexing
        src--; dest--;

        // Set weight in both directions (undirected graph)
        adjMatrix[src][dest] = adjMatrix[dest][src] = weight;
    }
}

void Graph::display() {
    cout << "\nAdjacency Matrix:\n   ";
    for (int i = 0; i < vertices; ++i)
        cout << i + 1 << "\t";
    
    for (int i = 0; i < vertices; ++i) {
        cout << "\n" << i + 1 << " ";
        for (int j = 0; j < vertices; ++j) {
            if (adjMatrix[i][j] == INT_MAX)
                cout << "∞\t";
            else
                cout << adjMatrix[i][j] << "\t";
        }
    }
    cout << endl;
}

void Graph::primMST() {
    int totalCost = 0;
    visited[0] = 1; // Start from the first branch

    cout << "\nMinimum Cost Connections:\n";

    for (int count = 0; count < vertices - 1; ++count) {
        int minCost = INT_MAX, from = -1, to = -1;

        for (int i = 0; i < vertices; ++i) {
            if (visited[i]) {
                for (int j = 0; j < vertices; ++j) {
                    if (!visited[j] && adjMatrix[i][j] < minCost) {
                        minCost = adjMatrix[i][j];
                        from = i;
                        to = j;
                    }
                }
            }
        }

        if (minCost == INT_MAX) {
            cout << "Graph is disconnected. MST not possible.\n";
            return;
        }

        visited[to] = 1;
        totalCost += minCost;

        cout << "Connection: " << from + 1 << " -> " << to + 1 
             << " | Cost: " << minCost << endl;
    }

    cout << "Total Minimum Cost of Connections: " << totalCost << endl;
}

int main() {
    Graph g;
    int choice;

    do {
        cout << "\nPRIM'S ALGORITHM \n";
        cout << "1. Input Graph\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Show Minimum Cost (MST)\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.input();
                break;
            case 2:
                g.display();
                break;
            case 3:
                g.primMST();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
