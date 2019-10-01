#ifndef HEAP_H
#define HEAP_H

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
#include <math.h>
using namespace std;

struct patient{
	string name;
	int priority;
	int treatment;
	string form;
};

class Heap{
    
public:
    Heap();
    ~Heap();
    void printHeap();
    void addNode(string name, int priority, int treatment, string p, string t);
    void dealHeap();
    void printanswer();
    void DeleteAllHeap();
    void DeleteHeap();
    patient Heaparray[881];
    int present;
    void cleananswer();
    
protected:
    
private:
    queue <string> answer;
};

#endif // HEAP_H