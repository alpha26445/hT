#include<iostream>
#include<cstring>
using namespace std;

struct Node{
    char key[20];
    char meaning[20];
    Node*left;
    Node*right;

};

class Dictionary{
public:

    Node*root;
    Dictionary(){
        root=NULL;
    }


    void insertWord();
    void display(Node*root);
    Node*insert(Node*root, Node*newNode);
    bool search(Node*root, const char key[]);
    bool update(Node*root, const char key[]);

    Node*deleteWord(Node*root, const char key[]);
    Node*findmin(Node*root);

};

void Dictionary::insertWord(){
    Node*newNode=new Node;
    cout<<"Enter keyword: "<<endl;
    cin>>newNode->key;
    cout<<"Enter meaning"<<endl;
    cin>>newNode->meaning;
    newNode->left=newNode->right=NULL;
    


    root=insert(root,newNode);

}

Node*Dictionary::insert(Node*root, Node*newNode){
    if(root==NULL){
        return newNode;
    }

    if(strcmp(newNode->key, root->key)<0){
        root->left=insert(root->left,newNode);
        
    }else{
        root->right=insert(root->right,newNode);
    }

    return root;

}
void Dictionary::display(Node*root){
     if(root==NULL){
        
        return;
     }



        display(root->left);
        cout<<"Keyword: "<<root->key<<" Meaning: "<<root->meaning<<endl;
        display(root->right);

    

}

bool Dictionary::search(Node*root,const char key[]){
    if(root==NULL){
        return false;

    }

    if(strcmp(key,root->key)==0){
        return true;
    }else if(strcmp(key,root->key)<0){
        return search(root->left,key);

    }else{
        return search(root->right, key);
    }
}

bool Dictionary::update(Node*root, const char key[]){

    if(root==NULL){
        return false;

    }

    if(strcmp(key,root->key)==0){
        cout<<"Current Meaning :"<<root->meaning<<endl;

        cout<<"Enter new Meaning"<<endl;
        cin>>root->meaning;
    }else if(strcmp(key,root->key)<0){
         return update(root->left,key);
    }else{
        return update(root->right, key);
    }

    return true;


}


Node*Dictionary::findmin(Node*root){
   

    while(root && root->left!=NULL){
        root=root->left;
    }
    return root;

}

Node*Dictionary::deleteWord(Node*root, const char key[]){
    if(root==NULL){
        return NULL;

    }

    if(strcmp(key,root->key)<0){
        root->left=deleteWord(root->left,key);
         
    }else if(strcmp(key,root->key)>0){
        root->right=deleteWord(root->right,key);
    }
    else{
        if(root->left== NULL && root->right==NULL){
            delete root;
            return NULL;
        }else if(root->right==NULL){
            Node*temp=root->left;
            delete root;
            return temp;
        }else if(root->left==NULL){
            Node*temp=root->right;
            delete root;
            return temp;
        
        
        }else{
            Node*temp=findmin(root->right);
            strcpy(root->key,temp->key);
            strcpy(root->meaning, temp->meaning);

            root->right=deleteWord(root->right, temp->key);
        }


    }

 return root;
}

int main(){
    Dictionary dict;
    char key[20];
    int choice;

    do{ 
        cout<<"***** Menu *****"<<endl;
        cout<<"1. Insert word"<<endl;
        cout<<"2. Display tree"<<endl;
        cout<<"3. Search Word"<<endl;
        cout<<"4. Update Meaning"<<endl;
        cout<<"5. Find minimum value"<<endl;
        cout<<"6. Delete Word"<<endl;

        cout<<"7. Exit"<<endl;
        cout<<"Enter choice"<<endl;
        cin>>choice;

        switch(choice){
            case 1:
                dict.insertWord();
                break;
            case 2:
                dict.display(dict.root);
                break;
            

            case 3:
                cout<<"Enter word to search:"<<endl;
                cin>>key;
                if(dict.search(dict.root,key)){
                    cout<<"Word found"<<endl;
                }else{
                    cout<<"Word not found"<<endl;
                }
                break;

            case 4:
                 cout<<"Enter word to update "<<endl;
                 cin>>key;
                 if(dict.update(dict.root,key)){
                    cout<<"Meaning updated"<<endl;
                 }else{
                    cout<<"Word not found"<<endl;
                 }
                 break;

            case 5:
                 if(dict.findmin(dict.root)!=NULL){
                    cout<<"Minimum Value is : "<<dict.root->key<<endl;

                 }else{
                    cout<<"Tree is Empty! "<<endl;
                 }
                
            case 6:
                cout<<"Enter the key to delete:" <<endl;
                 cin>>key;
                 dict.root=dict.deleteWord(dict.root,key);


            case 7:
                cout<<"Exiting program"<<endl;
                break;
                 


            default:
                cout<<"Invalid choice, try again"<<endl;
        }


    }while(choice!=7);



    return 0;
}