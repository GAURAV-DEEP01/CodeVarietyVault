#include<iostream>
using namespace std;
int main (){
    int n = 4;
    for(int i= 1;i<=n;i++){
        for(int j=n-i+1;j>0;j--){
            cout<<"_";
        }
        for(int k=1;k<i*2;k++){
            cout<<"*";
        }
        cout<<endl;
    }
    return 0;
}