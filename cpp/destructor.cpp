#include<iostream>
using namespace std;
class Array{
    int *data,size ;
    public:
        Array(int size);
        void setElement(int index, int value);
        int getElement(int index);
        ~Array(){
            delete[] data;
        }
};

Array ::Array(int size):size(size){
    data = new int[size];
}
void Array:: setElement(int index , int value ){
    data[index]=value ;
}  
int Array :: getElement(int index){
    return data[index];

}
int main (){
    Array newArr(2);
    newArr.setElement(0,10);
    newArr.setElement(1,15);
    cout<<"array element at index 0 is "<<newArr.getElement(0)<<endl;
    cout<<"array element at index 1 is "<<newArr.getElement(1)<<endl;
    return 0;
}