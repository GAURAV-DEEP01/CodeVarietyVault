#include<iostream>
#include<string>
using namespace std; 
class Adhoc {
    int a ,b;
    float x,y;
    public:
        void addnum(int a,int b){
            cout<<"sum int = "<<a+b<<endl;
        }
        void addnum(double x,double y){
            cout<<"sum double = "<<x+y<<endl;
        }
        void addnum(string a, string b){
            cout<<"sum string"<<a+b<<endl;
        }
};
int main(){
    Adhoc sum;
    sum.addnum(5,5);
    sum.addnum(5.1,5.44);
    sum.addnum("4","4");
    return 0;
}
