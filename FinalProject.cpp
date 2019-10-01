#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <istream>
#include <sstream>
#include "priorityll.hpp"
#include "heap.hpp"
#include <time.h>
#include <chrono>
#include <ctime>
using namespace std;

struct node{  
    string name;
    int priority;
    int treatment;  
    node(string patientname, int patientpriority, int patienttreatment){
        name=patientname;
        priority=patientpriority;
        treatment=patienttreatment;
    } 
}; 

struct cmp{  
    bool operator()(node a, node b){ 
        if(a.priority == b.priority){
            return a.treatment>=b.treatment;
        }
        return a.priority>b.priority;
    }
};

void split(string str,char a,string words[],int size){
    int count=0;
    int b=str.length();
    string temp="";
    int i=0;
    for(int x=0;x<b;x++){
        if(str[x]!=a){
            temp=temp+str[x];
        }
        if(str[x]==a){
            words[i]=temp;
            temp="";
            i++;
            count++;
        }
    }
    if(str[b-1]!=a){
        words[i]=temp;
    }
    count++;
}

void menu(){
    cout<<"======Main Menu======"<<endl;
    cout<<"1. Build LL priority queue"<<endl;
    cout<<"2. Build Heap priority queue"<<endl;
    cout<<"3. Dequeue LL"<<endl;
    cout<<"4. Dequeue Heap"<<endl;
    cout<<"5. Dequeue all LL"<<endl;
    cout<<"6. Dequeue all Heap"<<endl;
    cout<<"7. Print queue using STL"<<endl;
    cout<<"8. Build LL priority queue 500 times"<<endl;
    cout<<"9. Build and dequeue priority queue 500 times"<<endl;
    cout<<"10. Build STL priority queue 500 times"<<endl;
    cout<<"11. Quit"<<endl;
}

int main(int argc, char *argv[]){
    ifstream a(argv[1]);
    if(!a){
        cout<<"file not found"<<endl;
        return 0;
    }
    else{
        cout<<"Standing By..."<<endl<<"Complete."<<endl;
    }
    PriorityLL b;
    Heap c;
    int press=1;
    menu();
    while(press!=11){
        //let user input number
        cout<<"Press number:";
        cin>>press;
        //1.creat LL
        if(press==1){
            b.DeleteAllLL();
            ifstream a(argv[1]);
            string line;
            int count=0;
            while(!a.eof()){
                string word[3];
                a>>line;
                if(line!="Name,Priority,Treatment"){
                    split(line,',',word,3);
                    b.addNode(word[0],stoi(word[1]),stoi(word[2]));
                }
            }
            b.printLL();
            cout<<endl;
            menu();
        }
        //2.creat Heap
        else if(press==2){
            c.dealHeap();
            ifstream a(argv[1]);
            string line;
            int count=0;
            while(!a.eof()){
                string word[3];
                a>>line;
                if(line!="Name,Priority,Treatment"){
                    split(line,',',word,3);
                    c.addNode(word[0],stoi(word[1]),stoi(word[2]),word[1],word[2]);
                }
            }
            cout<<endl<<"Heap array built"<<endl<<endl;
            menu();
        }
        //3.delete node from LL
        else if(press==3){
            cout<<endl;
            cout<<"type the name you want to delete: ";
            string patientname;
            cin>>patientname;
            cout<<endl;
            b.DeleteLL(patientname);
            b.printLL();
            menu();
        }
        //4.delete node from Heap
        else if(press==4){
            cout<<endl;
            c.DeleteHeap();
            cout<<endl;
            cout<<"Now the deleted heaps are:"<<endl;
            c.printanswer();
            menu();
        }
        //5.clear LL
        else if(press==5){
            b.DeleteAllLL();
            b.printLL();
            cout<<endl;
            menu();
        }
        //6.clear Heap
        else if(press==6){
            c.DeleteAllHeap();
            c.printanswer();
            cout<<endl;
            menu();
        }
        //7.read file using stl
        else if(press==7){
            ifstream a(argv[1]);
            string line;
            int count=1;
            priority_queue<node, vector<node>, cmp>pq1;
            while(!a.eof()){
                string word[3];
                a>>line;
                if(line!="Name,Priority,Treatment"){
                    split(line,',',word,3);
                    pq1.push(node(word[0],stoi(word[1]),stoi(word[2])));
                }
            }
            cout<<"Rank patient,  Priority,  Treatment"<<endl;
            while(!pq1.empty()){  
                cout<<count<<":\t"<<pq1.top().name<<",  "<<pq1.top().priority<<",  "<<pq1.top().treatment<<endl; 
                count++; 
                pq1.pop();  
            }
            cout<<endl;
            menu();
        }
        //8.calculate avg time for ll
        else if(press==8){
            ifstream a;
            string line;
            double count=0;
            clock_t t1, t2;
            int num=0;
            int lines=100;
            while(lines<=880){
                count=0;
                for(int i=0;i<500;i++){
                    b.DeleteAllLL();
                    a.open(argv[1]);
                    num=0;
                    auto start=chrono::system_clock::now();
                    while(num<lines){
                        string word[3];
                        a>>line;
                        if(line!="Name,Priority,Treatment"){
                            num++;
                            split(line,',',word,3);
                            b.addNode(word[0],stoi(word[1]),stoi(word[2]));
                        }
                    }
                    b.DeleteAllLL();
                    auto end =chrono::system_clock::now();
                    chrono::duration<double> elapsed_seconds = end-start;
                    count=count+elapsed_seconds.count();
                    a.close();
                }
                cout << "Run time of reading "<<lines<<" rows: " << count/0.5 << " ms" << endl;
                if(lines!=700){
                    lines=lines+100;
                }
                else{
                    lines=lines+180;
                }   
            }
            menu();
        }
        //9.calculate avg time for heap
        else if(press==9){
            c.DeleteAllHeap();
            ifstream a;
            string line;
            float count=0;
            clock_t t1, t2;
            int num=0;
            int lines=100;
            while(lines<=880){
                count=0;
                for(int i=0;i<50;i++){
                    a.open(argv[1]);
                    num=0;
                    auto start=chrono::system_clock::now();
                    while(num<lines){
                        string word[3];
                        a>>line;
                        if(line!="Name,Priority,Treatment"){
                            num++;
                            split(line,',',word,3);
                            c.addNode(word[0],stoi(word[1]),stoi(word[2]),word[1],word[2]);
                        }
                    }
                    c.DeleteAllHeap();
                    auto end =chrono::system_clock::now();
                    chrono::duration<double> elapsed_seconds = end-start;
                    count=count+elapsed_seconds.count();
                    a.close();
                }
                cout << "Run time of reading "<<lines<<" rows: " << count/0.5 << " ms" << endl;
                if(lines!=700){
                    lines=lines+100;
                }
                else{
                    lines=lines+180;
                }   
                c.cleananswer();
            }
            menu();
        }
        //10.calculate avg time for STL priority queue
        else if(press==10){
            ifstream a;
            string line;
            float count=0;
            int num=0;
            priority_queue<node, vector<node>, cmp>pq1;
            int lines=100;
            while(lines<=880){
                count=0;
                for(int i=0;i<50;i++){
                    num=0;
                    a.open(argv[1]);
                    auto start=chrono::system_clock::now();
                    while(num<lines){
                        string word[3];
                        a>>line;
                        if(line!="Name,Priority,Treatment"){
                            num++;
                            split(line,',',word,3);
                            pq1.push(node(word[0],stoi(word[1]),stoi(word[2])));
                        }
                    }
                    while(!pq1.empty()){   
                        pq1.pop();  
                    }
                    auto end =chrono::system_clock::now();
                    chrono::duration<double> elapsed_seconds = end-start;
                    count=count+elapsed_seconds.count();
                    a.close();
                }
                cout << "Run time of reading "<<lines<<" rows: " << count/0.5 << " ms" << endl;
                if(lines!=700){
                    lines=lines+100;
                }
                else{
                    lines=lines+180;
                }   
            }
            menu();
        }
        //11.end program
        else if(press==11){
            cout<<"3..."<<endl<<"2..."<<endl<<"1..."<<endl<<"Time Out."<<endl<<"Deformation..."<<endl;
            a.close();
            return 0;
        }
        else{
            cout<<endl;
            cout<<"Incorrect command, please re-enter your command."<<endl;
            cout<<endl;
            menu();
        }
    }
    a.close();
    return 0;
}