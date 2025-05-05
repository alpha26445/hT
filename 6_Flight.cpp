#include <iostream>
#include <string>
using namespace std;

// Node structure for adjacency list
struct node {
    string vertex;
    int time;
    node *next;
};

// Class to represent graph using matrix and list
class adjmatlist {
    int m[20][20], n;
    string v[20];
    node *head[20];

public:
    adjmatlist() {
        for (int i = 0; i < 20; i++) {
            head[i] = nullptr;
            for (int j = 0; j < 20; j++) {
                m[i][j] = 0;
            }
        }
    }

    void getgraph();
    void adjlist();
    void displaym();
    void displaya();
};

// Function to input graph using adjacency matrix
void adjmatlist::getgraph() {
    char ch;

    cout << "\nEnter number of cities (max 20): ";
    cin >> n;

    cout << "Enter names of cities:\n";
    for (int i = 0; i < n; i++) {
        cout << "City " << i + 1 << ": ";
        cin >> v[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "\nIs there a path from " << v[i] << " to " << v[j] << "? (y/n): ";
            cin >> ch;
            if (ch == 'y' || ch == 'Y') {
                cout << "Enter time (in minutes): ";
                cin >> m[i][j];
            } else {
                m[i][j] = 0;
            }
        }
    }

    adjlist();  // Build adjacency list from matrix
}

// Function to convert matrix to adjacency list
void adjmatlist::adjlist() {
    for (int i = 0; i < n; i++) {
        // Head node (self)
        node *p = new node{v[i], 0, nullptr};
        head[i] = p;

        // Connect adjacent vertices
        for (int j = 0; j < n; j++) {
            if (m[i][j] != 0) {
                node *q = new node{v[j], m[i][j], nullptr};

                // Append to linked list
                node *temp = head[i];
                while (temp->next != nullptr)
                    temp = temp->next;
                temp->next = q;
            }
        }
    }
}

// Function to display adjacency matrix
void adjmatlist::displaym() {
    cout << "\nAdjacency Matrix:\n\t";
    for (int i = 0; i < n; i++) {
        cout << v[i] << "\t";
    }

    for (int i = 0; i < n; i++) {
        cout << "\n" << v[i] << "\t";
        for (int j = 0; j < n; j++) {
            cout << m[i][j] << "\t";
        }
    }
    cout << endl;
}

// Function to display adjacency list
void adjmatlist::displaya() {
    cout << "\nAdjacency List:\n";
    for (int i = 0; i < n; i++) {
        cout << head[i]->vertex;
        node *temp = head[i]->next;
        while (temp != nullptr) {
            cout << " -> " << temp->vertex;
            temp = temp->next;
        }
        cout << endl;
    }

    cout << "\nPaths and Times:\n";
    for (int i = 0; i < n; i++) {
        node *temp = head[i]->next;
        while (temp != nullptr) {
            cout << head[i]->vertex << " -> " << temp->vertex;
            cout << " [Time: " << temp->time << " min]\n";
            temp = temp->next;
        }
    }
}

int main() {
    adjmatlist a;
    int m;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Enter Graph\n";
        cout << "2. Display Adjacency Matrix\n";
        cout << "3. Display Adjacency List\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> m;

        switch (m) {
            case 1:
                a.getgraph();
                break;
            case 2:
                a.displaym();
                break;
            case 3:
                a.displaya();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
