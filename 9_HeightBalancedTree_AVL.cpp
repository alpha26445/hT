#include<iostream>
#include<cstring>
using namespace std;

class node {
public:
    char keyword[20];
    char meaning[20];
    node *left, *right;
    int ht;

    node() {
        strcpy(keyword, "");
        strcpy(meaning, "");
        left = right = NULL;
        ht = 0;
    }
};

class tree {
    node *root;

    int height(node *T);
    int BF(node *T);
    node* Rotate_Left(node *T);
    node* Rotate_Right(node *T);
    node* insert(node *T, char word[20], char mean[20]);
    node* In_Succ(node *);
    void preorder(node *);
    void inorder(node *);
    void postorder(node *);
    void descending(node *);
    void search1(node *, char []);
    void modify1(node *, char [], char []);
    node* delet(node *, char[]);
    void max_compare(node *, int &);

public:
    tree() { root = NULL; }

    void insert1(char key[20], char mean[20]) {
        root = insert(root, key, mean);
    }

    void display();
};

int tree::height(node *T) {
    if (T == NULL) return 0;
    int l = T->left ? 1 + T->left->ht : 0;
    int r = T->right ? 1 + T->right->ht : 0;
    return max(l, r);
}

int tree::BF(node *T) {
    if (T == NULL) return 0;
    int lh = T->left ? 1 + T->left->ht : 0;
    int rh = T->right ? 1 + T->right->ht : 0;
    return lh - rh;
}

node* tree::Rotate_Left(node *T) {
    node *temp = T->right;
    T->right = temp->left;
    temp->left = T;
    T->ht = height(T);
    temp->ht = height(temp);
    return temp;
}

node* tree::Rotate_Right(node *x) {
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height(x);
    y->ht = height(y);
    return y;
}

node* tree::insert(node *T, char word[20], char mean[20]) {
    if (!T) {
        node *newNode = new node();
        strcpy(newNode->keyword, word);
        strcpy(newNode->meaning, mean);
        return newNode;
    }

    if (strcmp(word, T->keyword) < 0) {
        T->left = insert(T->left, word, mean);
        if (BF(T) == 2) {
            if (strcmp(word, T->left->keyword) < 0)
                T = Rotate_Right(T);
            else {
                T->left = Rotate_Left(T->left);
                T = Rotate_Right(T);
            }
        }
    } else if (strcmp(word, T->keyword) > 0) {
        T->right = insert(T->right, word, mean);
        if (BF(T) == -2) {
            if (strcmp(word, T->right->keyword) > 0)
                T = Rotate_Left(T);
            else {
                T->right = Rotate_Right(T->right);
                T = Rotate_Left(T);
            }
        }
    }

    T->ht = height(T);
    return T;
}

void tree::preorder(node *T) {
    if (T) {
        cout << T->keyword << " : " << T->meaning << endl;
        preorder(T->left);
        preorder(T->right);
    }
}

void tree::inorder(node *T) {
    if (T) {
        inorder(T->left);
        cout << T->keyword << " : " << T->meaning << endl;
        inorder(T->right);
    }
}

void tree::postorder(node *T) {
    if (T) {
        postorder(T->left);
        postorder(T->right);
        cout << T->keyword << " : " << T->meaning << endl;
    }
}

void tree::descending(node *T) {
    if (T) {
        descending(T->right);
        cout << T->keyword << " : " << T->meaning << endl;
        descending(T->left);
    }
}

void tree::search1(node *T, char data[20]) {
    while (T) {
        if (strcmp(T->keyword, data) == 0) {
            cout << "Found: " << T->keyword << " : " << T->meaning << endl;
            return;
        }
        T = strcmp(data, T->keyword) > 0 ? T->right : T->left;
    }
    cout << "Word not found.\n";
}

void tree::modify1(node *T, char data[20], char mean[20]) {
    while (T) {
        if (strcmp(T->keyword, data) == 0) {
            strcpy(T->meaning, mean);
            cout << "Updated meaning.\n";
            return;
        }
        T = strcmp(data, T->keyword) > 0 ? T->right : T->left;
    }
    cout << "Word not found.\n";
}

node* tree::In_Succ(node *T) {
    node *curr = T->right;
    while (curr && curr->left) curr = curr->left;
    return curr;
}

node* tree::delet(node *root, char key[20]) {
    if (!root) return NULL;

    if (strcmp(key, root->keyword) < 0)
        root->left = delet(root->left, key);
    else if (strcmp(key, root->keyword) > 0)
        root->right = delet(root->right, key);
    else {
        if (!root->left || !root->right) {
            node *temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        } else {
            node *succ = In_Succ(root);
            strcpy(root->keyword, succ->keyword);
            strcpy(root->meaning, succ->meaning);
            root->right = delet(root->right, succ->keyword);
        }
    }

    root->ht = height(root);

    int balance = BF(root);
    if (balance > 1 && BF(root->left) >= 0)
        return Rotate_Right(root);
    if (balance > 1 && BF(root->left) < 0) {
        root->left = Rotate_Left(root->left);
        return Rotate_Right(root);
    }
    if (balance < -1 && BF(root->right) <= 0)
        return Rotate_Left(root);
    if (balance < -1 && BF(root->right) > 0) {
        root->right = Rotate_Right(root->right);
        return Rotate_Left(root);
    }

    return root;
}

void tree::max_compare(node *T, int &count) {
    if (T) {
        count++;
        max_compare(T->left, count);
        max_compare(T->right, count);
    }
}

void tree::display() {
    int choice;
    char word[20], mean[20];

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert\n2. Display Inorder\n3. Display Preorder\n4. Display Postorder\n";
        cout << "5. Display Descending\n6. Search\n7. Modify\n8. Delete\n9. Max Comparisons\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;
                cout << "Enter meaning: ";
                cin >> mean;
                insert1(word, mean);
                break;
            case 2:
                inorder(root);
                break;
            case 3:
                preorder(root);
                break;
            case 4:
                postorder(root);
                break;
            case 5:
                descending(root);
                break;
            case 6:
                cout << "Enter word to search: ";
                cin >> word;
                search1(root, word);
                break;
            case 7:
                cout << "Enter word to modify: ";
                cin >> word;
                cout << "Enter new meaning: ";
                cin >> mean;
                modify1(root, word, mean);
                break;
            case 8:
                cout << "Enter word to delete: ";
                cin >> word;
                root = delet(root, word);
                break;
            case 9: {
                int count = 0;
                max_compare(root, count);
                cout << "Max comparisons during traversal: " << count << endl;
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 0);
}

int main() {
    tree dict;
    dict.display();
    return 0;
}
