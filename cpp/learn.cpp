#include<iostream>
#include<string>
using namespace std;

class Teacher {
    string teacherName ;
    public:
        Teacher(string techname):teacherName(techname){}
    void teacherIntro(){
        cout<<"Hi im "<<teacherName;
    }
};

class Rollcall{
    Teacher teacher ;
    public:
        Rollcall(string teachername):teacher(teachername){}
    Teacher getTeacher(){
        return teacher;
    }
};

int main (){
    Rollcall rollno23("mathew");
    Teacher teach = rollno23.getTeacher();
    teach.teacherIntro();
    return 0;
}