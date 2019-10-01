#include <iostream>
#include "heap.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <istream>
#include <sstream>
#include <stack>
using namespace std;

Heap::Heap(){
	for(int i=0;i<881;i++){
		Heaparray[i].form="";
		Heaparray[i].name="";
		Heaparray[i].priority=0;
		Heaparray[i].treatment=0;
	}
	present=1;
}

Heap::~Heap(){
	for(int i=0;i<881;i++){
		Heaparray[i].form="";
		Heaparray[i].name="";
		Heaparray[i].priority=0;
		Heaparray[i].treatment=0;
	}
	present=1;
}

void Heap::printHeap(){
	if(Heaparray[1].name==""){
		cout<<endl<<"There is no node in the array."<<endl<<endl;
		return;
	}
	int count=1;
	for(int i=1;i<881;i++){
		if(Heaparray[i].name==""){
			return;
		}
		cout<<count<<":\t"<<Heaparray[i].form<<endl;
		count++;
	}
}

void Heap::addNode(string name, int priority, int treatment, string p, string t){
	int i=present;
	string form;
	form=name+",  "+p+",  "+t;
	Heaparray[i].form=form;
	Heaparray[i].name=name;
	Heaparray[i].priority=priority;
	Heaparray[i].treatment=treatment;
	patient a;
	a.form=form;
	a.name=name;
	a.priority=priority;
	if(Heaparray[i/2].priority>=priority){	
		while(Heaparray[i/2].priority>priority){
			a.treatment=treatment;
			Heaparray[i]=Heaparray[i/2];
			Heaparray[i/2]=a;
			i=i/2;
		}
		if(Heaparray[i/2].priority==priority){
			while(Heaparray[i/2].treatment>=treatment&&Heaparray[i/2].priority==priority){//not this one delete &&Heaparray[i/2].priority==priority
				a.treatment=treatment;
				Heaparray[i]=Heaparray[i/2];
				Heaparray[i/2]=a;
				i=i/2;
			}
		}	
	}
	present++;
	return;
}

void Heap::DeleteAllHeap(){
	while(Heaparray[1].name!=""){
		DeleteHeap();
	}
}

void Heap::dealHeap(){
	present=1;
	for(int i=0;i<881;i++){
		Heaparray[i].form="";
		Heaparray[i].name="";
		Heaparray[i].priority=0;
		Heaparray[i].treatment=0;
	}
}

int compare(patient one, patient two){
	// return -1 if two should be before one
	if(one.priority>two.priority){
		return -1;
	}
	// return 1 is one should be before two
	else if(one.priority<two.priority){
		return 1;
	}
	// return 1 is does not matter (both are equal)
	else{
		if(one.treatment>two.treatment){
			return -1;
		}
		else if(one.treatment<=two.treatment){
			return 1;
		}
		else{
			return -1;
		}
	}
}

void Heap::DeleteHeap(){
	if(Heaparray[1].name==""){
		cout<<"Cannot find the array"<<endl;
		return;
	}
	else{
		int i=1;
		answer.push(Heaparray[1].form);
		present--;
		Heaparray[1]=Heaparray[present];
		Heaparray[present].name="";
		Heaparray[present].priority=0;
		Heaparray[present].form="";
		Heaparray[present].treatment=0;
		if(3>=present){
			if(Heaparray[2].name!="")
				if(compare(Heaparray[1],Heaparray[2])==-1){
					patient extra1=Heaparray[1];
					Heaparray[1]=Heaparray[2];
					Heaparray[2]=extra1;
		 		}
		 		return;
		 	}
			while(2*i+1<present){
				if(compare(Heaparray[i],Heaparray[2*i])==-1 || compare(Heaparray[i],Heaparray[2*i+1])==-1){
					if(compare(Heaparray[2*i],Heaparray[2*i+1])==-1){
						patient extra=Heaparray[2*i+1];
						Heaparray[2*i+1]=Heaparray[i];
						Heaparray[i]=extra;
						i=i*2+1;
					}
					else{
						patient extra;
						extra=Heaparray[2*i];
						Heaparray[2*i]=Heaparray[i];
						Heaparray[i]=extra;
						i=i*2;
					}
				}
				else{
					return;
				}
		}
	}
}

void Heap::printanswer(){
	int count=1;
	cout<<"Rank	patient,  Priority,  Treatment"<<endl;
	while(!answer.empty()){
		cout<<count<<":\t"<<answer.front()<<endl;
		answer.pop();
		count++;
	}
}

void Heap::cleananswer(){
	while(!answer.empty()){
		answer.pop();
	}
}