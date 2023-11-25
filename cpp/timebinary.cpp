#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
void writeTime(int h,int m,int s ){
    ofstream writeFile;
    char inputline[20];
    sprintf(inputline,"%02d:%02d:%02d",h,m,s);
    writeFile.open("time.dat",ios::out|ios::binary);
    if(!writeFile.is_open()){
        cout<<"failed to write file" <<endl;
        return;
    }
    writeFile.write((char*) &inputline,sizeof(inputline));
    cout<<"writefile successful ,time :"<<endl<<inputline<<endl;
    writeFile.close();
}
void readTime(int &h,int &m,int &s){
    ifstream readFile;
    char outputline[20];
    readFile.open("time.dat",ios::out|ios::binary);
    if(!readFile.is_open()){
        cout<<"failed to read File" <<endl;
        return;
    }
    while(readFile.read((char*) &outputline,sizeof(outputline))){
        sscanf(outputline,"%02d:%02d:%02d",&h,&m,&s);
    }
    readFile.close();
}
int main(){
    int h,m,s;
    cout <<"Enter the time to write in the file :"<<endl;
    cout<<"hour : ";cin>>h;
    cout<<"min : ";cin>>m;
    cout<<"sec : ";cin>>s;
    writeTime(h,m,s);
    h=m=s=0;
    cout<<"time is before setting :"<<h<<":"<<m<<":"<<s<<":";
    readTime(h,m,s);
    cout<<"time is :"<<setw(2)<<setfill('0')<<h<<":"<<setw(2)<<setfill('0')<<m<<":"<<setw(2)<<setfill('0')<<s<<":";
    return 0;
}