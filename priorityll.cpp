#include <iostream>
#include "priorityll.hpp"
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

using namespace std;

PriorityLL::PriorityLL(){
	root=NULL;
}

PriorityLL::~PriorityLL(){
    root=NULL;
}

void PriorityLL::printLL(){
	LL *current=root;
	if(root==NULL){
		cout<<endl;
		cout<<endl<<"The current Linked List contains no elements"<<endl;
		cout<<endl;
		return;
	}
	cout<<"Rank	patient,  Priority,  Treatment"<<endl;
	int count=1;
	while(current!=NULL){
		cout<<count<<":\t"<<current->name<<",  "<<current->priority<<",  "<<current->treatment<<endl;
		count++;
		current=current->next;
	}
}

void PriorityLL::deallink(LL *currenthead, LL *now, int treatment,int priority){
	LL *finalhead;
	LL *current=currenthead;
	LL *previous=currenthead;
	while(current!=NULL&&current->priority==priority){
		if(current->treatment>=now->treatment){
			if(current->parent==NULL){
				current->parent=now;
				now->next=current;
				root=now;
				return;
			}
			now->next=current;
			now->parent=current->parent;
			current->parent->next=now;
			current->parent=now;
			return;
		}
		previous=current;
		current=current->next;
	}
	if(current==NULL){
		previous->next=now;
		now->parent=previous;
	}
	else{
		now->next=current;
		now->parent=previous;
		current->parent=now;
		previous->next=now;
	}
}

void PriorityLL::addNode(string name, int priority, int treatment){
	LL* now=new LL;
	now->name=name;
	now->priority=priority;
	now->treatment=treatment;
	now->next=NULL;
	now->parent=NULL;
	//now->link=NULL;
	//now->linkparent=NULL;
	if(root==NULL){
		root=now;
		return;
	}
	else{
		LL *current=root;
		LL *previous=root;
		while(current!=NULL){
			if(current->priority==now->priority){
				deallink(current,now,treatment,priority);
				return;
			}
			else if(current->priority>now->priority){
				if(current->parent==NULL){
					current->parent=now;
					now->next=current;
					root=now;
					return;
				}
				now->next=current;
				now->parent=current->parent;
				current->parent->next=now;
				current->parent=now;
				return;
			}
			previous=current;
			current=current->next;
		}
		previous->next=now;
		now->parent=previous;
	}
}

void PriorityLL::DeleteAllLL(){
	LL *current=root;
	while(current!=NULL){
		LL *previous=current;
		current=current->next;
		delete previous;
	}
	root=NULL;
}

void PriorityLL::DeleteLL(string patientname){
	LL *current=root;
	LL *previous=root;
	if(root==NULL){
		cout<<endl;
		cout<<"No Linked List built already."<<endl;
		cout<<endl;
		return;
	}
	while(current!=NULL){
		if(current->name==patientname){
			if(current->parent==NULL){
				current->next->parent=NULL;
				root=current->next;
				return;
			}
			else if(current->next==NULL){
				current->parent->next=NULL;
				return;
			}
			current->next->parent=current->parent;
			current->parent->next=current->next;
			return;
		}
		previous=current;
		current=current->next;
	}
	cout<<"Target not found."<<endl;
}