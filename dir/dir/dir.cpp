// dir.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char dir[256] = "", mask[256] = "";
	cout << "dir -> ";
	cin.getline(dir,256);
	cout << "mask -> ";
	cin.getline(mask,256);
	Find(dir, mask);

	return 0;
}

