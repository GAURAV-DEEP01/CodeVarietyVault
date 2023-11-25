#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main(){
    string inputline , outputline;
    ofstream writefile("something.dat");
    cout<<"Input :"<<endl;
    while(true){
        cin >>inputline ;
        if(inputline=="end") break;
        writefile<<inputline<<endl;
    }
    writefile.close();
    cout <<"output :" <<endl;
    ifstream readfile("something.dat");
    while(!readfile.eof()){
        readfile>>outputline;
        cout<<outputline<<endl;
    }
    readfile.close();
    return 0;
}