#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    string inputstring ,outputstring ;
    ofstream writeFile("textfile.txt");
    if(!writeFile.is_open()){
        cout<<"failed to create file"<<endl;
        return 1;
    }
    while(true){
        getline(cin,inputstring);
        if(inputstring=="end") break;
        writeFile<<inputstring<<endl;
    }
    writeFile.close();
    ifstream readFile("textfile.txt");
    if (!readFile.is_open()){
        cout <<"failed to read file "<<endl;
        return 1;
    }
    while(getline(readFile,outputstring)){
        cout<<outputstring<<endl;
    }
    readFile.close();
    return 0;
}