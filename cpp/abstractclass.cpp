#include<iostream>
#include<string>
using namespace std;
class Shape {
    string color;
    public:
        Shape(string color):color(color){}
        virtual int calcArea() =0;
        void printColor(){
            cout<<"i am a "<< color<<" colored shape "<<endl;
        }
};
class Circle:public Shape {
    int radius ;
    public :
        Circle(int rad, string color):radius(rad),Shape(color){}
        int calcArea() override{
            return 3.1415927*radius*radius ;
        }
};
class Square :public Shape {
    int side ;
    public:
        Square(int side , string color ): side(side),Shape(color){}
        int calcArea() override {
            return side *side ;
        }
};
int main(){
    Circle cir(2, "blue");
    cir.printColor();
    cout<<"My area is "<<cir.calcArea()<<endl;
    Square sqr(2, "red");
    sqr.printColor();
    cout<<"My area is "<<sqr.calcArea()<<endl;
    return 0;
}