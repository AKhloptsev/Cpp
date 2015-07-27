// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <tchar.h>
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdlib.h>
#include <ctime>
#include <regex>

LRESULT CALLBACK WFunc (HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK FirstFunc (HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK SecondFunc (HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK ThirdFunc (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK FuncAbout (HWND,UINT,WPARAM,LPARAM);
#include "resource.h"
#include "Heaps.h"
TCHAR str[256] = "";
string strForRE;
int koef = 1;
static int numberOfStones;
static bool bFlag;
static double* stoneArray;
static double* stoneArrayCopy;
using namespace std;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
