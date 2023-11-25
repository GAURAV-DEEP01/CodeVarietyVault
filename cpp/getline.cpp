#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;
int main (){
    char inputline[30],outputline[30];
    ofstream writefile ("newfile.dat");
    cout<<"input :"<<endl;
    while(true){
        cin.getline(inputline,30);
        if(!strcmp(inputline,"end")) break;
        writefile<<inputline<<endl;
    }
    writefile.close();
    cout<<"output :"<<endl;
    ifstream readfile("newfile.dat");
    while(!readfile.eof()){
        readfile.getline(outputline,30);
        cout<<outputline<<endl;
    }
    readfile.close();
    return 0;
}