// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// dir.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

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
			cout << path2  << fileinfo->name << "\n";		//������� ��������� ����� � �������� �����
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
				strcpy (path, s.c_str()); //���� ��� �����, �� ������� path = ����+�����
				//cout << path << "\n";
				Find(path, size, maska, path2);
			}
	
		
		//cout << path2  << fileinfo->name << "\n";		//������� ��������� ����� � �������� �����
			CopyHandle = _findnext(handle, fileinfo);
		}
	}



	delete fileinfo;
	return 0;
}