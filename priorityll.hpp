#ifndef PRIORITYLL_H
#define PRIORITYLL_H

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

struct LL{
	string name;
	int priority;
	int treatment;
	LL *next;
	LL *parent;
};

class PriorityLL{
    
public:
    PriorityLL();
    ~PriorityLL();
    void printLL();
    void addNode(string name, int priority, int treatment);
    void deallink(LL *currenthead, LL *currentnode, int treatment,int priority);
    void DeleteAllLL();
    void DeleteLL(string patientname);
    
protected:
    
private:
    LL* root;
};

#endif // PRIORITYLL_H