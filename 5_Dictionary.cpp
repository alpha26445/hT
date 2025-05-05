#include <iostream>
#include <cstring>
using namespace std;

// Node structure representing each keyword-meaning pair
struct node {
    char k[20]; // Keyword
    char m[20]; // Meaning
    node *left;
    node *right;
};

// Dictionary class containing BST functions
class dict {
public:
    node *root;

    dict() {
        root = NULL;
    }

    void create();
    void disp(node *);
    void insert(node *, node *);
    int search(node *, char[]);
    int update(node *, char[]);
    node* del(node *, char[]);
    node* min(node *);
};

// Create dictionary by taking user input
void dict::create() {
    node *temp;
    int ch;

    do {
        temp = new node;
        cout << "\nEnter Keyword: ";
        cin >> temp->k;
        cout << "Enter Meaning: ";
        cin >> temp->m;

        temp->left = temp->right = NULL;

        if (root == NULL) {
            root = temp;
        } else {
            insert(root, temp);
        }

        cout << "Do you want to add more? (Yes=1 / No=0): ";
        cin >> ch;
    } while (ch == 1);
}

// Insert node into BST
void dict::insert(node *root, node *temp) {
    if (strcmp(temp->k, root->k) < 0) {
        if (root->left == NULL)
            root->left = temp;
        else
            insert(root->left, temp);
    } else {
        if (root->right == NULL)
            root->right = temp;
        else
            insert(root->right, temp);
    }
}

// Display dictionary in sorted order
void dict::disp(node *root) {
    if (root != NULL) {
        disp(root->left);
        cout << "\nKeyword: " << root->k << " | Meaning: " << root->m;
        disp(root->right);
    }
}

// Search for a keyword in the dictionary
int dict::search(node *root, char k[20]) {
    int comparisons = 0;
    while (root != NULL) {
        comparisons++;
        if (strcmp(k, root->k) == 0) {
            cout << "\nKeyword found after " << comparisons << " comparisons.";
            return 1;
        } else if (strcmp(k, root->k) < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return -1;
}

// Update meaning of a keyword
int dict::update(node *root, char k[20]) {
    while (root != NULL) {
        if (strcmp(k, root->k) == 0) {
            cout << "Enter New Meaning for '" << root->k << "': ";
            cin >> root->m;
            return 1;
        } else if (strcmp(k, root->k) < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return -1;
}

// Delete a keyword from dictionary
node* dict::del(node *root, char k[20]) {
    if (root == NULL) {
        cout << "Keyword not found.\n";
        return NULL;
    }

    if (strcmp(k, root->k) < 0) {
        root->left = del(root->left, k);
    } else if (strcmp(k, root->k) > 0) {
        root->right = del(root->right, k);
    } else {
        // Node found
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        } else if (root->left == NULL) {
            node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            node *temp = root->left;
            delete root;
            return temp;
        } else {
            node *temp = min(root->right);
            strcpy(root->k, temp->k);
            strcpy(root->m, temp->m);
            root->right = del(root->right, temp->k);
        }
    }

    return root;
}

// Find node with minimum key (leftmost)
node* dict::min(node *q) {
    while (q->left != NULL) {
        q = q->left;
    }
    return q;
}

// Main function with menu
int main() {
    int ch;
    dict d;

    do {
        cout << "\n\nDictionary Menu";
        cout << "\n1. Create Dictionary";
        cout << "\n2. Display Dictionary";
        cout << "\n3. Search Keyword";
        cout << "\n4. Update Meaning";
        cout << "\n5. Delete Keyword";
        cout << "\nEnter your choice (1-5): ";
        cin >> ch;

        char key[20];
        switch (ch) {
            case 1:
                d.create();
                break;

            case 2:
                if (d.root == NULL)
                    cout << "Dictionary is empty.\n";
                else
                    d.disp(d.root);
                break;

            case 3:
                if (d.root == NULL)
                    cout << "Dictionary is empty. Add keywords first.\n";
                else {
                    cout << "Enter keyword to search: ";
                    cin >> key;
                    if (d.search(d.root, key) == 1)
                        cout << "\nKeyword Found!";
                    else
                        cout << "\nKeyword Not Found!";
                }
                break;

            case 4:
                if (d.root == NULL)
                    cout << "Dictionary is empty. Add keywords first.\n";
                else {
                    cout << "Enter keyword to update meaning: ";
                    cin >> key;
                    if (d.update(d.root, key) == 1)
                        cout << "\nMeaning Updated Successfully!";
                    else
                        cout << "\nKeyword Not Found!";
                }
                break;

            case 5:
                if (d.root == NULL)
                    cout << "Dictionary is empty. Add keywords first.\n";
                else {
                    cout << "Enter keyword to delete: ";
                    cin >> key;
                    d.root = d.del(d.root, key);
                    cout << "Keyword Deleted (if it existed).\n";
                }
                break;

            default:
                cout << "Invalid Choice!";
        }
    } while (ch >= 1 && ch <= 5);

    return 0;
}
