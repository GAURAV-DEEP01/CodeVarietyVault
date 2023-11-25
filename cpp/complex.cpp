#include<iostream>
using namespace std;
class Complex{
    float x,y;
    public:
        Complex(){}
        Complex(float a,float b):x(a),y(b){}
        Complex(float a):x(a),y(a){}

        friend Complex sum(Complex, Complex);
        friend void display(Complex);
};
void display(Complex a){
        cout <<"complex is = "<<a.x<<"x + "<<a.y<<"y"<<endl;
    }
Complex sum(Complex a , Complex b){
        Complex c;
        c.x=a.x+b.x;
        c.y=a.y+b.y; 
        return c;
    }

int main(){
    Complex compA = Complex(5.5,6.8);
    Complex compB = Complex(5.9);
    Complex compAdd = sum(compA,compB);
    display(compA);
    display(compB);
    display(compAdd);
    return 0;
}