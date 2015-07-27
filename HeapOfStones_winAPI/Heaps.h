#pragma once
#include "StdAfx.h"
#include <vector>

using namespace std;

class Heaps
{
public:
    Heaps(double *, int);
    ~Heaps();
	Heaps(vector<double> *, vector<double> *, vector<double> *);
	int print(HWND, HDC, int, int, int&, int&, int&);
private:
    static bool goldHit;
    static double bestDiff;
    static double halfWeight;
	static double mas;
    static vector<double> bestFirstHeap;
    static vector<double> bestSecondHeap;
    vector<double> * restHeapPtr;
    vector<double> * firstHeapPtr;
    vector<double> * secondHeapPtr;
    void firstPart();
    void secondPart();
    void initiate();
};
