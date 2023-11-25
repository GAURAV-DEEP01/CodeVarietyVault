#include<iostream>
#include<fstream>
using namespace std;
struct student{
    int rollno;
    char name[10];
    char id[10];
};
void writeStud(student &s){
    cout<<"rollno "<<endl;
    cin>>s.rollno;
    cout<<"name "<<endl;
    cin>>s.name;
    cout<<"id "<<endl;
    cin>>s.id;
}
void readStud(student &s){
    cout<<"rollno "<<endl;
    cout<<s.rollno;
    cout<<"name "<<endl;
    cout<<s.name;
    cout<<"id "<<endl;
    cout<<s.id;
}
int main(){
    struct student studentdata ,readstud;
    char cont;
    ofstream studFile;
    studFile.open("file.dat",ios::out|ios::binary|ios::trunc);
    if(!studFile.is_open())
        cout<<"file opening failed"<<endl;
    writeStud(studentdata);
    do{
       studFile.write((char*) &studentdata,sizeof(struct student));
       if(studFile.fail())
            cout<<"failed to write data"<<endl;
        cout<<"do you want to continue?(y/n)"<<endl;
        cin>>cont;
    }while(cont!='n');
    studFile.close();
    ifstream studfileread;
    studfileread.open("file.dat",ios::in|ios::binary);
    if (!studfileread.is_open()) 
        cout <<"failed to read "<<endl;
    while(!studfileread.eof()){
        studfileread.read((char*) &readstud,sizeof(struct student));
    }  
    readStud(readstud);
    studfileread.close();  
    return 0;
}