#include<iostream>
using namespace std;

struct node {
    int data;
    node *L, *R;
};

class bst {
    node *root;
    int count;

public:
    bst() {
        root = NULL;
        count = 0;
    }

    void create();
    void insert(node*, node*);
    void disin(node*);
    void dispre(node*);
    void dispost(node*);
    void search(node*, int);
    int height(node*);
    void mirror(node*);
    void min(node*);
    node* getRoot() { return root; }  // Accessor for root
};

void bst::create() {
    char ans;
    node *temp;
    do {
        temp = new node;
        cout << "Enter the data: ";
        cin >> temp->data;
        temp->L = temp->R = NULL;

        if (root == NULL)
            root = temp;
        else
            insert(root, temp);

        count++;
        cout << "Do you want to insert more values? (y/n): ";
        cin >> ans;
    } while (ans == 'y');

    cout << "Total number of nodes: " << count << endl;
}

void bst::insert(node *root, node *temp) {
    if (temp->data > root->data) {
        if (root->R == NULL)
            root->R = temp;
        else
            insert(root->R, temp);
    } else {
        if (root->L == NULL)
            root->L = temp;
        else
            insert(root->L, temp);
    }
}

void bst::disin(node *root) {
    if (root != NULL) {
        disin(root->L);
        cout << root->data << "\t";
        disin(root->R);
    }
}

void bst::dispre(node *root) {
    if (root != NULL) {
        cout << root->data << "\t";
        dispre(root->L);
        dispre(root->R);
    }
}

void bst::dispost(node *root) {
    if (root != NULL) {
        dispost(root->L);
        dispost(root->R);
        cout << root->data << "\t";
    }
}

void bst::search(node *root, int key) {
    node *temp = root;
    while (temp != NULL) {
        if (key == temp->data) {
            cout << "\nKEY FOUND: " << key << endl;
            return;
        } else if (key > temp->data)
            temp = temp->R;
        else
            temp = temp->L;
    }
    cout << "\nKEY NOT FOUND: " << key << endl;
}

int bst::height(node *root) {
    if (root == NULL)
        return 0;
    int hl = height(root->L);
    int hr = height(root->R);
    return 1 + max(hl, hr);
}

void bst::min(node *root) {
    node *temp = root;
    while (temp->L != NULL)
        temp = temp->L;
    cout << "\nMinimum element is: " << temp->data << endl;
}

void bst::mirror(node *root) {
    if (root != NULL) {
        mirror(root->L);
        mirror(root->R);
        node *temp = root->L;
        root->L = root->R;
        root->R = temp;
    }
}

int main() {
    bst t;
    int ch, key;
    char ans;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1) Insert new node\n2) Height of BST\n3) Minimum element\n";
        cout << "4) Mirror the tree\n5) Search\n6) Inorder\n7) Preorder\n8) Postorder\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                t.create();
                break;
            case 2:
                cout << "\nHeight (longest path): " << t.height(t.getRoot()) << endl;
                break;
            case 3:
                t.min(t.getRoot());
                break;
            case 4:
                t.mirror(t.getRoot());
                cout << "\nMirror (inorder): ";
                t.disin(t.getRoot());
                break;
            case 5:
                cout << "Enter key to search: ";
                cin >> key;
                t.search(t.getRoot(), key);
                break;
            case 6:
                cout << "\nInorder: ";
                t.disin(t.getRoot());
                break;
            case 7:
                cout << "\nPreorder: ";
                t.dispre(t.getRoot());
                break;
            case 8:
                cout << "\nPostorder: ";
                t.dispost(t.getRoot());
                break;
            default:
                cout << "Invalid choice!\n";
        }
        cout << "\nDo you want to continue? (y/n): ";
        cin >> ans;
    } while (ans == 'y');

    return 0;
}
