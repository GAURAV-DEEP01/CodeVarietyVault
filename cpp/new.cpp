#include<iostream>
#include<string>
using namespace std;
class Color{
    string color;
    public : 
        Color (string color);
        void displayColor();
};
Color::Color(string color):color(color){}
void Color :: displayColor(){
    cout<<"I am the color "<<color<<endl;
}
int main (){
    Color col = Color("blue");
    col.displayColor();
    Color col3 = Color("gray");
    col3.displayColor();
    return 0;
}