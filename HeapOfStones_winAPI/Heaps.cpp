#include "StdAfx.h"

bool Heaps::goldHit = false;	// ����� �� �� ���� ����� ���������� ������
double Heaps::bestDiff = 0.0;	// ������� ����� ������ � ������ �����
double Heaps::halfWeight = 0.0;	// �������� ������ ����
double Heaps::mas = 0.0;
vector<double> Heaps::bestFirstHeap = vector<double>();	// ������� ������ ����
vector<double> Heaps::bestSecondHeap = vector<double>();	// ������� ������ ����
 
Heaps::Heaps(double * stoneArray, int arrSize)
{
    sort(stoneArray, stoneArray + arrSize);	// ��������� ������ � ������� �����������
    halfWeight = accumulate(stoneArray, stoneArray + arrSize, 0.0) / 2.0;	// ����������� ����� ��� � ����� �������
    restHeapPtr = new vector<double>(stoneArray, stoneArray + arrSize);
	mas = accumulate(restHeapPtr->begin(), restHeapPtr->end(), 0.0);	// ����� ����� ����
    firstHeapPtr = new vector<double>();
    secondHeapPtr = new vector<double>();
    secondHeapPtr->push_back(restHeapPtr->back());	// � ������ ������ ���� ��������� ������ � ������������ �����
    restHeapPtr->pop_back();	// �� ����� ���� ������� ��������� ������ (������� ��������� �� ������ ����)
    bestFirstHeap = *restHeapPtr;	// ������� ������ ���� ��������� �� ����� ����
    bestSecondHeap = *secondHeapPtr;	// ������� ������ ���� ��������� �� ������ ����
    if (bestSecondHeap.back() == halfWeight)	// ���� ���� ������ (������������ �� ����) == �������� ������ ����
		goldHit = true;
	else
	{
		// bestDiff = ��� ������ ���� - ��� ������ ����
		bestDiff = fabs(accumulate(bestFirstHeap.begin(), bestFirstHeap.end(), 0.0) - accumulate(bestSecondHeap.begin(), bestSecondHeap.end(), 0.0));
		initiate();
    }
}
 

Heaps::Heaps(vector<double> * rest, vector<double> * first, vector<double> * second)
{
    restHeapPtr = new vector<double>(*rest);
    firstHeapPtr = new vector<double>(*first);
    secondHeapPtr = new vector<double>(*second);
}


Heaps::~Heaps()
{
    delete secondHeapPtr;
    delete firstHeapPtr;
    delete restHeapPtr;
}
 

 
void Heaps::initiate()
{
    if (restHeapPtr->size() > 3)	// ���� ������ ������ ���� ������ ��� 3
        firstPart();
    else
        secondPart();
}


void Heaps::firstPart()
{
    if (goldHit)
        return;
    bool heapsStateChanged = true;	// ����� ���������
    bool firstHeapChanged = false;	// ��������� � ������ ����
    bool secondHeapChanged = false;	// ��������� �� ������ ����
    double weight1 = accumulate(firstHeapPtr->begin(), firstHeapPtr->end(), 0.0);	// ��� ������ ����   
    double weight2 = accumulate(secondHeapPtr->begin(), secondHeapPtr->end(), 0.0);	// ��� ������ ����
    vector<double>::const_iterator pos;	// �������� ��� ������������ �� ����� ����
    do
    {
        for (pos = restHeapPtr->cbegin(); pos != restHeapPtr->cend(); ++pos)
        {
            if (*pos + weight2 == halfWeight)	// ���� ������� ������ �������� �� ������ ���� � ��������� �������� ���� ����� ����
            {
                goldHit = true;
                secondHeapPtr->push_back(*pos);
                restHeapPtr->erase(pos);
                copy(restHeapPtr->cbegin(), restHeapPtr->cend(), back_inserter(*firstHeapPtr));		// �������� � ������ ���� ��� ����� �� ����� ����
                bestFirstHeap = *firstHeapPtr;	// ������� ������ ���� ��������� �� ������ ��� �������������� ������ ����
                bestSecondHeap = *secondHeapPtr;
                bestDiff = 0;
                delete this;
                return;
            }
            else if (*pos + weight2 > halfWeight)	// ���� ������� ������ �������� � ������ ���� � �� ����� ������ �������� ���� ����� ����, �� ������� �� �����
                break;
        }
        if (pos != restHeapPtr->cend() && ++pos != restHeapPtr->cend())	// ���� ���� � ��������� ����� �� ���������
        {
            copy(pos, restHeapPtr->cend(), back_inserter(*secondHeapPtr));	// �� ������� � ����� ����� � �� ���������� ������� �� ������ ����
            restHeapPtr->erase(pos, restHeapPtr->cend());	// ������� ��� ����� �� �������� ����
            firstHeapChanged = true;	// ��������� ���������
            if (restHeapPtr->size() <= 3)	// ���� � ���������� ���� ������ ��� 3 ����� ������������
            {
                while (restHeapPtr->size() != 3)	// ���� � ����� ���� �� ������ ������ ��� 3 �����
                {
                    restHeapPtr->push_back(secondHeapPtr->back());	// � ����� ���� ������ ����� �� ������ ����
                    secondHeapPtr->pop_back(); 
                }
                secondPart();	// �������� ����� ��� 3� ������, ���������� � ����
                return;
            }
        }
        else
            firstHeapChanged = false;
        for (pos = restHeapPtr->cbegin(); pos != restHeapPtr->cend(); ++pos)
        {
            if (*pos + weight1 == halfWeight)	// ���� ������� ������ �������� � ������ ���� � ��� ����� ����� �������� ������ ����
            {
                goldHit = true;
                firstHeapPtr->push_back(*pos);	// ������������ �� ����� ���� ���� ������ � ������ ����
                restHeapPtr->erase(pos);
                copy(restHeapPtr->cbegin(), restHeapPtr->cend(), back_inserter(*secondHeapPtr));	// ��������� ��������� �� ������ ����
                bestFirstHeap = *firstHeapPtr;
                bestSecondHeap = *secondHeapPtr;
                bestDiff = 0.0;
                delete this;
                return;
            }
            else if (*pos + weight1 > halfWeight)	// ���� ���� ������ �������� � ������ ���� � ��� ����� ������ ��� �������� ������ ����
                break;
        }
        if (pos != restHeapPtr->cend() && ++pos != restHeapPtr->cend())	// ���� ���� � ��������� ����� �� ��������� � ����� ����
        {
            copy(pos, restHeapPtr->cend(), back_inserter(*firstHeapPtr));	// ������ ���������� ����� � ������ ����
            restHeapPtr->erase(pos, restHeapPtr->cend());
            secondHeapChanged = true;	// ��������� ���������
            if (restHeapPtr->size() <= 3)	// ���� � ����� ���� �������� ������ ��� 3 �����
            {
                while (restHeapPtr->size() != 3)
                {
                    restHeapPtr->push_back(firstHeapPtr->back());	// ������ �� ������ ���� �� ������� � �����
                    firstHeapPtr->pop_back();
                }
                secondPart();	// �������� ����� ��� 3� ������
                return;
            }
        }
        else
            secondHeapChanged = false;
        heapsStateChanged = firstHeapChanged || secondHeapChanged;
        firstHeapChanged = false;
        secondHeapChanged = false;
    }while (heapsStateChanged);
 
    
    double tempDouble = restHeapPtr->back();	// �������������� ��������� ������ � ����� ����
    restHeapPtr->pop_back();	// ������ ���� ������
    secondHeapPtr->push_back(tempDouble);	// �� ������ ����
    Heaps * tempHeaps1 = new Heaps(restHeapPtr, firstHeapPtr, secondHeapPtr);
    secondHeapPtr->pop_back();	// � ������ � ������ ����
    firstHeapPtr->push_back(tempDouble);
    Heaps * tempHeaps2 = new Heaps(restHeapPtr, firstHeapPtr, secondHeapPtr);
    tempHeaps1->initiate();
    if (goldHit)
        return;
    else
        tempHeaps2->initiate();
    delete this;
}
 
void Heaps::secondPart()
{
    if (goldHit)	// ���� ��� ������ ���� == �������� ������ ����, �� ������� �� ������
        return;
    double thisDiff, tempDiff;	// ��� ������� �������������� �������� ����� �� ����� ���� � ������
    int bestCase;		// ��������� ������ ������� ��� ����, ����� ���������� ������ �� ����� ���� � ������
    double weight1 = accumulate(firstHeapPtr->begin(), firstHeapPtr->end(), 0.0);	// ����� ��� ������ ����
    double weight2 = accumulate(secondHeapPtr->begin(), secondHeapPtr->end(), 0.0);	// ����� ��� ������ ����
    bestCase = 1;	// ������ ������ �� ���������� ���� � ������ ����
	/* ���������, ����� ������ ����� �������� � ������ ����, ����� �� �������� ���� ��� ����� ������: */
    thisDiff = fabs(weight1 + restHeapPtr->at(0) - weight2 - restHeapPtr->at(1) - restHeapPtr->at(2));	// ���� ������ ������ �� ���������� ���� ��������� � ������ ����, � ��������� ����� ��������� �� ������ ����, ��
    if (thisDiff == 0)
    {
        goldHit = true;
        bestFirstHeap = *firstHeapPtr;
        bestFirstHeap.push_back(restHeapPtr->at(0));	// � ������� ������ ���� ��������� ������ ������ �� ����� ����
        bestSecondHeap = *secondHeapPtr;
        bestSecondHeap.push_back(restHeapPtr->at(1));	// � ������� ������ ���� ��������� ������ � ������ ������
        bestSecondHeap.push_back(restHeapPtr->at(2));
        bestDiff = 0.0;		// ������� ����� ������ ����� � ������ == 0
        delete this;
        return;
    }
    tempDiff = fabs(weight1 + restHeapPtr->at(1) - weight2 - restHeapPtr->at(0) - restHeapPtr->at(2));	// ���� � ������ ���� �������� ������ ������ �� ����� ����, � ��������� �� ������
    if (tempDiff == 0)
    {
        goldHit = true;
        bestFirstHeap = *firstHeapPtr;
        bestFirstHeap.push_back(restHeapPtr->at(1));	// � ������� ������ ���� ��������� ������ ������ �� ����� ����
        bestSecondHeap = *secondHeapPtr;
        bestSecondHeap.push_back(restHeapPtr->at(0));	// � ������� ������ ���� ��������� ������ � ������ ������
        bestSecondHeap.push_back(restHeapPtr->at(2));
        bestDiff = 0.0;		// ������� ����� ������ ����� � ������ == 0
        delete this;
        return;
    }
	// ��������� ���������
    else if (tempDiff < thisDiff)
    {
        thisDiff = tempDiff;
        bestCase = 2; //������ ������ �� ���������� ���� � ������ ����
    }
	/* ���� ������, �������� ������ ������ ����� ����� ������ � ������ ���� */
    tempDiff = fabs(weight1 + restHeapPtr->at(2) - weight2 - restHeapPtr->at(0) - restHeapPtr->at(1));	// ���� � ������ ���� �������� ������ ������ �� ����� ����, � ��������� �� ������
    if (tempDiff == 0)
    {
        goldHit = true;
        bestFirstHeap = *firstHeapPtr;
        bestFirstHeap.push_back(restHeapPtr->at(2));	// � ������� ������ ���� ��������� ������ ������
        bestSecondHeap = *secondHeapPtr;
        bestSecondHeap.push_back(restHeapPtr->at(0));	// � ������� ������ ���� ��������� ������ � ������ ������
        bestSecondHeap.push_back(restHeapPtr->at(1));
        bestDiff = 0.0;
        delete this;
        return;
    }
	// ��������� ���������
    else if (tempDiff < thisDiff)
    {
        thisDiff = tempDiff;
        bestCase = 3; //������ ������ �� ���������� ���� � ������ ����
    }

	/* ������ ���������� �������� � ��������� ������ �� ����� ���� �� ������ ������� ����, � ���������� - � ������ */
	// ���� �� ������ ���� ������ ������ ������ �� ����� ����, � ��������� - �� � ������
    tempDiff = fabs(weight2 + restHeapPtr->at(0) - weight1 - restHeapPtr->at(1) - restHeapPtr->at(2));
    if (tempDiff == 0)
    {
        goldHit = true;
        bestFirstHeap = *firstHeapPtr;
        bestFirstHeap.push_back(restHeapPtr->at(1));
        bestFirstHeap.push_back(restHeapPtr->at(2));
        bestSecondHeap = *secondHeapPtr;
        bestSecondHeap.push_back(restHeapPtr->at(0));
        bestDiff = 0.0;
        delete this;
        return;
    }
	// ��������� ���������
    else if (tempDiff < thisDiff)
    {
        thisDiff = tempDiff;
        bestCase = 4; //������ ������ �� ���������� ���� �� ������ ����
    }

	// ���� �� ������ ���� �������� ������ ������ �� ������ ����, � ��������� - � ������
    tempDiff = fabs(weight2 + restHeapPtr->at(1) - weight1 - restHeapPtr->at(0) - restHeapPtr->at(2));
    if (tempDiff == 0)
    {
        goldHit = true;
        bestFirstHeap = *firstHeapPtr;
        bestFirstHeap.push_back(restHeapPtr->at(0));
        bestFirstHeap.push_back(restHeapPtr->at(2));
        bestSecondHeap = *secondHeapPtr;
        bestSecondHeap.push_back(restHeapPtr->at(1));
        bestDiff = 0.0;
        delete this;
        return;
    }
	// ��������� ���������
    else if (tempDiff < thisDiff)
    {
        thisDiff = tempDiff;
        bestCase = 5; //������ ������ �� ���������� ���� �� ������ ����
    }

	// ���� �� ������ ���� �������� ������ ������, � � ������ ���������
    tempDiff = fabs(weight2 + restHeapPtr->at(2) - weight1 - restHeapPtr->at(0) - restHeapPtr->at(1));
    if (tempDiff == 0)
    {
        goldHit = true;
        bestFirstHeap = *firstHeapPtr;
        bestFirstHeap.push_back(restHeapPtr->at(0));
        bestFirstHeap.push_back(restHeapPtr->at(1));
        bestSecondHeap = *secondHeapPtr;
        bestSecondHeap.push_back(restHeapPtr->at(2));
        bestDiff = 0.0;
        delete this;
        return;
    }
	// ��������� ���������
    else if (tempDiff < thisDiff)
    {
        thisDiff = tempDiff;
        bestCase = 6; //������ ������ �� ���������� ���� �� ������ ����
    }

	// ���� � ������ ���� �������� ��� ���������� �����
    tempDiff = fabs(weight1 + restHeapPtr->at(0) + restHeapPtr->at(1) + restHeapPtr->at(2) - weight2);
    if (tempDiff == 0)
    {
        goldHit = true;
        bestFirstHeap = *firstHeapPtr;
        bestFirstHeap.push_back(restHeapPtr->at(0));
        bestFirstHeap.push_back(restHeapPtr->at(1));
        bestFirstHeap.push_back(restHeapPtr->at(2));
        bestSecondHeap = *secondHeapPtr;
        bestDiff = 0.0;
        delete this;
        return;
    }
	// ��������� ���������
    else if (tempDiff < thisDiff)
    {
        thisDiff = tempDiff;
        bestCase = 7; //��� ���������� ����� �������� � ������ ����
    }

	// ���� ��� ����� �� ���������� ���� ���� �� ������ ������� ����
    tempDiff = fabs(weight2 + restHeapPtr->at(0) + restHeapPtr->at(1) + restHeapPtr->at(2) - weight1);
    if (tempDiff == 0)
    {
        goldHit = true;
        bestFirstHeap = *firstHeapPtr;
        bestSecondHeap = *secondHeapPtr;
        bestSecondHeap.push_back(restHeapPtr->at(0));
        bestSecondHeap.push_back(restHeapPtr->at(1));
        bestSecondHeap.push_back(restHeapPtr->at(2));
        bestDiff = 0.0;
        delete this;
        return;
    }
	// ��������� ���������
    else if (tempDiff < thisDiff)
    {
        thisDiff = tempDiff;
        bestCase = 8; //��� ���������� ����� �������� �� ������ ����
    }
	/* � ����������� �� ������������ ���������� ������������ ����� � ��������������� ���� */
    if (thisDiff < bestDiff)
    {
        bestFirstHeap = *firstHeapPtr;
        bestSecondHeap = *secondHeapPtr;
        bestDiff = thisDiff;
        switch (bestCase)
        {
            case 1:
                bestFirstHeap.push_back(restHeapPtr->at(0));
                bestSecondHeap.push_back(restHeapPtr->at(1));
                bestSecondHeap.push_back(restHeapPtr->at(2));
                break;
            case 2:
                bestFirstHeap.push_back(restHeapPtr->at(1));
                bestSecondHeap.push_back(restHeapPtr->at(0));
                bestSecondHeap.push_back(restHeapPtr->at(2));
                break;
            case 3:
                bestFirstHeap.push_back(restHeapPtr->at(2));
                bestSecondHeap.push_back(restHeapPtr->at(0));
                bestSecondHeap.push_back(restHeapPtr->at(1));
                break;
            case 4:
                bestFirstHeap.push_back(restHeapPtr->at(1));
                bestFirstHeap.push_back(restHeapPtr->at(2));
                bestSecondHeap.push_back(restHeapPtr->at(0));
                break;
            case 5:
                bestFirstHeap.push_back(restHeapPtr->at(0));
                bestFirstHeap.push_back(restHeapPtr->at(2));
                bestSecondHeap.push_back(restHeapPtr->at(1));
                break;
            case 6:
                bestFirstHeap.push_back(restHeapPtr->at(0));
                bestFirstHeap.push_back(restHeapPtr->at(1));
                bestSecondHeap.push_back(restHeapPtr->at(2));
                break;
            case 7:
                bestFirstHeap.push_back(restHeapPtr->at(0));
                bestFirstHeap.push_back(restHeapPtr->at(1));
                bestFirstHeap.push_back(restHeapPtr->at(2));
                break;
            case 8:
                bestSecondHeap.push_back(restHeapPtr->at(0));
                bestSecondHeap.push_back(restHeapPtr->at(1));
                bestSecondHeap.push_back(restHeapPtr->at(2));
                break;
        }
    }
    delete this;
}







int Heaps::print(HWND hwnd, HDC hdc, int sx, int sy, int& m, int& m1, int& m2)
{
	int x = sx - 200;
	int y = sy - 200;
    sort(bestFirstHeap.begin(), bestFirstHeap.end());
    sort(bestSecondHeap.begin(), bestSecondHeap.end());
	auto sizeFirst = bestFirstHeap.size();
	auto sizeSecond = bestSecondHeap.size();

	for (int i = 0; i < sizeFirst; i++)
	{
		m1 += bestFirstHeap[i];
		Ellipse(hdc, x - bestFirstHeap[i] / 2, y - 10, x + bestFirstHeap[i] / 2, y + 10);
		y += 30;
	}
	x = sx + 200;
	y = sy - 200;

	for (int i = 0; i < sizeSecond; i++)
	{
		m2 += bestSecondHeap[i];
		Ellipse(hdc, x - bestSecondHeap[i] / 2, y - 10, x + bestSecondHeap[i] / 2, y + 10);
		y += 30;
	}
	m = mas;
    return bestDiff;
}