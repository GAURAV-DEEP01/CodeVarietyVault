#include<iostream>
using namespace std;
int main(){
    int numerator,denominator,arr[4]={0,0,0,0},idx;
    cout<<"enter the index :";
    cin>>idx;
    try{
        if(idx<0  || idx>=4)
            throw "Error array out of bounds";
        cout<<"nume: ";
        cin>>numerator;
        cout<<"denom: ";
        cin>>denominator;
        if(denominator==0)
            throw denominator;
        arr[idx] = numerator/denominator;
        cout<<arr[idx]<<endl;
        
    }catch(const char *msg){
        cout<<msg<<endl;
    }
    catch(int i){
        cout<<"devide by "<<i<<"error";
    }
    catch(...){
        cout<<"unexpected error"<<endl;
    }
}