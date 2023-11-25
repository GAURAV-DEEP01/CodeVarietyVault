#include<iostream>
#include<fstream>
using namespace std;
int main(){
    char ch;
    ofstream writefile("filename.dat");
    cout<<"enter :"<<endl;
    while(true){
        cin.get(ch);
        if(ch=='$') break;
        writefile.put(ch);
    }
    writefile.close();
    cout<<"output :"<<endl;
    ifstream readfile("filename.dat");
    while(!readfile.eof()){
        readfile.unsetf(ios::skipws);
        readfile.get(ch);
        cout.put(ch);
    }
    readfile.close();
    return 0;
}