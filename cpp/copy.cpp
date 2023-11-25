#include<iostream>
#include<string>
using namespace std;
class GenId{
    string id;
    public :
        GenId(){}
        GenId(string id) {
            this->id=id;
        }
        GenId(GenId& i) {
            id=i.id;
        }
        void displayId(){
            cout<<"id is "<<id;
        }

};
int main (){
    GenId person("bob");
    GenId person2("vance");
    GenId person3;
    person3 = person;
    person.displayId();
    person2.displayId();
    person3.displayId();
    return 0;
}