#include<iostream>
#include<string>
using namespace std;
class Teacher {
    string name;
    public :
        Teacher(string name):name(name){}
        void introduce(){
            cout<<"hi im your teacher "<<name<<endl;
        }
};
class Rollno {
    public :
        Teacher teach;
        Rollno(string name):teach(name){}
        Teacher getTeacher(){
            return teach;
        }
};
int main (){
    Rollno roll("mathew");
    Teacher teacher = roll.getTeacher();
    teacher.introduce(); 
    return (0);
}