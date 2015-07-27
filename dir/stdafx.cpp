// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// dir.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

double Find(char path[], int size, string maska, char path2[])
{
	
	long handle, CopyHandle;
	_finddata_t* fileinfo = new _finddata_t;
	
	CopyHandle = handle = _findfirst(path, fileinfo);
	

	if(CopyHandle != -1)
	{
		do
		{
			cout << path2  << fileinfo->name << "\n";		//выводит найденные файлы в коренной папке
		}while(_findnext(handle,fileinfo) != -1);
				if(fileinfo->name[0] != '.')
		{

			if(fileinfo->attrib & _A_SUBDIR)
			{
				string s;
				s = (const char*) path;
				int k = strlen(path);
				s.resize(k - size);
				//s += ":\\";
				s += fileinfo->name;
				s += "\\";
				s += maska;
				strcpy (path, s.c_str()); //если это папка, то выводит path = путь+маска
				//cout << path << "\n";
				Find(path, size, maska, path2);
			}
	
		
		//cout << path2  << fileinfo->name << "\n";		//выводит найденные файлы в коренной папке
			CopyHandle = _findnext(handle, fileinfo);
		}
	}



	delete fileinfo;
	return 0;
}