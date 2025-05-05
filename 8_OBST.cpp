#include <iostream>
#include <climits>
using namespace std;

class OBST {
    int keys[10], root[10][10], n;
    float p[10], q[10], weight[10][10], cost[10][10];

public:
    void accept();
    void construct();
    int findMin(int, int);
    void displayTree(int, int, string);
};

void OBST::accept() {
    cout << "Enter the number of keys: ";
    cin >> n;

    cout << "Enter " << n << " keys:\n";
    for (int i = 1; i <= n; i++)
        cin >> keys[i];

    cout << "Enter " << n << " successful search probabilities:\n";
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    cout << "Enter " << n + 1 << " unsuccessful search probabilities:\n";
    for (int i = 0; i <= n; i++)
        cin >> q[i];
}

void OBST::construct() {
    for (int i = 0; i <= n; i++) {
        cost[i][i] = 0;
        weight[i][i] = q[i];
        root[i][i] = 0;

        if (i < n) {
            weight[i][i + 1] = q[i] + p[i + 1] + q[i + 1];
            cost[i][i + 1] = weight[i][i + 1];
            root[i][i + 1] = i + 1;
        }
    }

    for (int m = 2; m <= n; m++) {
        for (int i = 0; i <= n - m; i++) {
            int j = i + m;
            weight[i][j] = weight[i][j - 1] + p[j] + q[j];
            int k = findMin(i, j);
            cost[i][j] = weight[i][j] + cost[i][k - 1] + cost[k][j];
            root[i][j] = k;
        }
    }

    cout << "\nOptimal Binary Search Tree:\n";
    cout << "Root node: " << keys[root[0][n]] << "\n";
    displayTree(0, n, "Root");
}

int OBST::findMin(int i, int j) {
    int minCost = INT_MAX;
    int bestK = -1;

    // Safe loop range: from i+1 to j
    for (int k = i + 1; k <= j; k++) {
        int currCost = cost[i][k - 1] + cost[k][j];
        if (currCost < minCost) {
            minCost = currCost;
            bestK = k;
        }
    }

    return bestK;
}

void OBST::displayTree(int i, int j, string relation) {
    if (root[i][j] == 0) {
        cout << relation << ": NULL\n";
        return;
    }

    int r = root[i][j];
    cout << relation << ": " << keys[r] << "\n";

    displayTree(i, r - 1, "Left child of " + to_string(keys[r]));
    displayTree(r, j, "Right child of " + to_string(keys[r]));
}

int main() {
    OBST obstTree;
    obstTree.accept();
    obstTree.construct();
    return 0;
}
