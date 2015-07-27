// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// test.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

void Find(char dir[256], char mask[256])
{
	_finddata_t* fileinfo = new _finddata_t;
	long handle, cHandle;
	char str[256] = "", path[256] = "";
	strcpy(path, dir);
	strcpy(str,strcat(path, "\\")); //str = D:\\		.
	strcat(path, mask);	//path = D:\\*.*
	handle = cHandle = _findfirst(path, fileinfo);

	while (cHandle != -1)
	{
		if(fileinfo->name[0] != '.')
			cout << dir << "\\" << fileinfo->name << "\n";
		cHandle = _findnext(handle, fileinfo);
	}

	char str2[256] = "", str3[256] = "";
	strcpy(str3,strcpy(str2,str));	// D:\\		.
	strcat(str, "*.*");	// D:\\*.*
	
	
	handle = cHandle = _findfirst(str, fileinfo);

	while(cHandle != -1)
	{
		if(fileinfo->name[0] != '.')
		{
			if(fileinfo->attrib & _A_SUBDIR)
			{
				strcat(str2, fileinfo->name);
				Find(str2, mask);
				strcpy(str2, str3);
			}
		}
		cHandle = _findnext(handle, fileinfo);
	}


	delete fileinfo;
}