#include <iostream>
using namespace std;
class student {
    public:
        int rollno;
        void getrollno(){
            cout<<"enter the no";
            cin>>rollno;
        }
};
class test:public student {
    public:
        int markA,markB;
        void getmark(){
            cout<<"enter the marks";
            cin>>markA>>markB;
        }
};
class result:public test {
    public:
        void calc(){
            cout<<"total of"<<rollno<<"is "<<(markA+markB);
        }
};

int main() {
    result R;
    R.getrollno;
    R.getmark;
    R.calc;
   return 0;
}