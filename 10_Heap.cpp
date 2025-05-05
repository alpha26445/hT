#include <iostream>
using namespace std;

void min_heapify(int *a, int i, int n) {
    int temp = a[i];
    int j = 2 * i;

    while (j <= n) {
        if (j < n && a[j + 1] < a[j])
            j = j + 1;

        if (temp < a[j])
            break;
        else {
            a[j / 2] = a[j];
            j = 2 * j;
        }
    }

    a[j / 2] = temp;
}

void max_heapify(int *a, int i, int n) {
    int temp = a[i];
    int j = 2 * i;

    while (j <= n) {
        if (j < n && a[j + 1] > a[j])
            j = j + 1;

        if (temp > a[j])
            break;
        else {
            a[j / 2] = a[j];
            j = 2 * j;
        }
    }

    a[j / 2] = temp;
}

void build_minheap(int *a, int n) {
    for (int i = n / 2; i >= 1; i--) {
        min_heapify(a, i, n);
    }
}

void build_maxheap(int *a, int n) {
    for (int i = n / 2; i >= 1; i--) {
        max_heapify(a, i, n);
    }
}

int main() {
    int n, choice;
    char cont;
    int a[100];  // increased array size

    cout << "Enter number of elements: ";
    cin >> n;

    if (n >= 100) {
        cout << "Array size too large!" << endl;
        return 1;
    }

    // Taking input from user
    for (int i = 1; i <= n; i++) {
        cout << "Enter element " << i << ": ";
        cin >> a[i];
    }

    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Build Min Heap" << endl;
        cout << "2. Build Max Heap" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                build_minheap(a, n);
                cout << "Min Heap: ";
                for (int i = 1; i <= n; i++) {
                    cout << a[i] << " ";
                }
                cout << endl;
                break;

            case 2:
                build_maxheap(a, n);
                cout << "Max Heap: ";
                for (int i = 1; i <= n; i++) {
                    cout << a[i] << " ";
                }
                cout << endl;
                break;

            default:
                cout << "Invalid choice!" << endl;
                break;
        }

        cout << "Do you want to continue? (Y/N): ";
        cin >> cont;

    } while (cont == 'Y' || cont == 'y');

    return 0;
}
