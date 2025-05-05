#include<iostream>
using namespace std;

void minHeapify(int a[], int i, int n){
    int smallest=i;
    int left=2*i;
    int right=2*i+1;

    if(left<=n && a[left]<a[smallest]){
        smallest=left;

    }

    if(right<=n && a[right]<a[smallest]){
        smallest=right;


    }

    if(smallest!=i){
        swap(a[i],a[smallest]);
        minHeapify(a,smallest,n);
    }




}

void maxHeapify(int a[], int i, int n){
    int largest=i;
    int left=2*i;
    int right=2*i+1;

    if(left<=n && a[left]>a[largest]){
        largest=left;
    }

    if(right<=n && a[right]>a[largest]){
        largest=right;
    }

    if(largest!=i){
        swap(a[largest],a[i]);
        maxHeapify(a,largest,i);
    }
    



}

void buildMinHeap(int a[], int n){
    for(int i=n/2; i>=1; i--){
        minHeapify(a,i,n);
    }
}

void buildMaxHeap(int a[], int n){
    for(int i=n/2; i>=1; i--){
        maxHeapify(a,i,n);
    }
}


int main(){
    int a[101];
    int n;
    cout<<"Enter total number of students: "<<endl;
    cin>>n;

    for(int i=1; i<=n; i++){
        cout<<"Enter marks of Student "<<i<<": ";
        cin>>a[i];
    }

    buildMinHeap(a,n);
    cout<<"Minimum marks is: "<<a[1]<<endl;

    buildMaxHeap(a,n);
    cout<<"Maximum marks is: "<<a[1]<<endl;


    return 0;
}