#include<iostream>
#include<string>
using namespace std;

struct Node{
    string vertex;
    int time;
    Node*next;

};

class Graph{
    int matrix[20][20];
    int cityCount;
    string cities[20];
    Node*listhead[20];
    public:
    Graph(){
        for(int i=0; i<cityCount; i++){
            listhead[i]=nullptr;

            for(int j=0; j<cityCount; j++){
                matrix[i][j]=0;
            }
        }
    }

    void insertGraph();
    void buildAdjList();
    void showMatrix();
    void showAdjList();


};

void Graph::insertGraph(){
    char ch;
    cout<<"Enter number of  cities: "<<endl;
    cin>>cityCount;
    for(int i=0; i<cityCount; i++){
        cout<<"City: "<<i+1<<": ";
        cin>>cities[i];
    }

    for(int i=0; i<cityCount; i++){
        for(int j=0; j<cityCount; j++){
            cout<<"Is path from: "<<cities[i]<<" to "<<cities[j]<<" (y/n)"<<endl;

            cin>>ch;
            if(ch=='y' || ch== 'Y'){
                cout<<"Enter time"<<endl;
                cin>>matrix[i][j];

            }else{
                matrix[i][j]=0;
            }


        }
    }




}

void Graph::showMatrix(){
    cout<<"\n Adjecency Matrix \n \t \t";
    for(int i=0; i<cityCount; i++){
        cout<<cities[i]<<"\t";

    }
    cout<<endl;
    for(int i=0; i<cityCount; i++){
        cout<<cities[i]<<"\t \t";
        for(int j=0; j<cityCount; j++){
            cout<<matrix[i][j]<<"\t ";
        }
        cout<<endl;
    }


}


int main(){
    Graph g;
    int choice;
    do{
        cout<<"****** Menu ******"<<endl;
        cout<<"1. Insert in graph"<<endl;
        cout<<"2. Display Adjecency matrix"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter choice"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                g.insertGraph();
                break;
            case 2:
                g.showMatrix();
                break;
            default:
                cout<<"Exiting program"<<endl;
                break;
            
        }



    }while(choice!=3);



    return 0;
}