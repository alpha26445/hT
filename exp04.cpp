#include<iostream>
using namespace std;

struct Node{
    int data;
    Node*left;
    Node*right;



};


class BST{
    Node*root;

public:

    BST(){
        root=NULL;
    }

    Node*getRoot();
    void setRoot(Node*newRoot);



};

Node*BST::getRoot(){
    return root;
}

void BST::setRoot(Node*newRoot){
    root=newRoot;


}

Node*insert(Node*root, int value){
    if(root==NULL){
        Node*newNode=new Node;
        newNode->data=value;
        newNode->left=newNode->right=NULL;
        return newNode;


    }

    if(value<root->data){
        root->left=insert(root->left,value);
    }
    else{
        root->right=insert(root->right,value);
    }

    return root;

}

void inorder(Node*root){
    if(root!=NULL){
    inorder(root->left);
    cout<<root->data<<endl;
    inorder(root->right);
    }

}

void preorder(Node*root){
    if(root!=NULL){
    cout<<root->data<<endl;
    preorder(root->left);
    preorder(root->right);


    }
}


void postorder(Node*root){
    if(root!=NULL){
        postorder(root->left);
        postorder(root->right);
        cout<<root->data<<endl;


    }
}

void search(Node*root, int key){
    if(root==NULL){
        cout<<"Key not found"<<endl;


    }

    if(key==root->data){
        cout<<"Key found: "<<key<<endl;
    

    }else if(key<root->data){
        search(root->left,key);

    }else{
        search(root->right,key);
    }
}

int height(Node*root){
    if(root==NULL){
        return 0;
    }

    int leftheight=height(root->left);
    int rightheight=height(root->right);

    return 1+max(leftheight,rightheight);

}

void minValue(Node*root){
    if(root==NULL){
        cout<<"Tree is Empty!"<<endl;

    }

    while(root->left!=NULL){
        root=root->left;

    }

    cout<<"Minimum Value is: "<<root->data<<endl;

    

}


void mirror(Node*root){
    if(root!=NULL){
        mirror(root->left);
        mirror(root->right);

        Node*temp=root->left;

        root->left=root->right;
        root->right=root->left;
    }
}


int main()
{

    BST tree;
    int choice,value;
    do{
        cout<<"***** Menu *****"<<endl;
        cout<<"1. Insert Node"<<endl;
        cout<<"2. Inorder Traversal"<<endl;
        cout<<"3. Preorder Traversal"<<endl;
        cout<<"4. Postorder Traversal"<<endl;
        cout<<"5. Search in tree"<<endl;
        cout<<"6. Height of tree"<<endl;
        cout<<"7. Minimum value in tree"<<endl;
        cout<<"8. Mirror "<<endl;
        cout<<"9. Exit"<<endl;

        cout<<"Enter choice :"<<endl;
        cin>>choice;


        switch(choice){
            case 1:
                cout<<"Enter the value to insert: "<<endl;
                cin>>value;
                tree.setRoot(insert(tree.getRoot(),value));
                break;
            case 2:
                cout<<"Inorder"<<endl;
                inorder(tree.getRoot());
                break;

            case 3: 
                cout<<"Preorder"<<endl;
                preorder(tree.getRoot());
                break;


            case 4:
                cout<<"Postorder"<<endl;
                postorder(tree.getRoot());
                break;

            
            case 5:
                cout<<"Enter the key to search :"<<endl;
                cin>>value;
                search(tree.getRoot(),value);

            case 6:

                cout<<"Height is :"<<height(tree.getRoot())<<endl;

            case 7:
            
                minValue(tree.getRoot());
            
            case 8:
                mirror(tree.getRoot());

            
            case 9:
                cout<<"Exiting program"<<endl;
                break;

            
            default:
                cout<<"Invalid choice, Try again"<<endl;

        }



    }while(choice!=5);


    return 0;
}