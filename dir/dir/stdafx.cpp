// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// �����_�����.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"


double Find(char path[256], char mask[256])
{
	
	strcat(path,"\\");

	char temp[256] = "";
	char temp2[256] = "";
	char tempOsn[256] = "";

	strcpy(temp,strcpy(temp2,strcpy(tempOsn,path)));                   ////////�����������  ������ ��������

	

	//////////����� ����� � ������� �����/////////
	strcat(path,mask);

	_finddata_t fileinfo ;
	long handl,chandl,count = 0;
	chandl = handl = _findfirst(path,&fileinfo);

	if(chandl != -1)
		cout<<path<<endl;


	////////////������� ���� ��������� � �����//////
	
	strcat(temp,"*.*");
	chandl = handl = _findfirst(temp,&fileinfo);
		
	while(chandl != -1)
		{
			

			if(fileinfo.name[0] != '.')  /////���� ������� ������� �� . � �� .. �� ������� � ���� � �������� ��������
			{
				strcat(temp2,fileinfo.name);
				 Find( temp2,mask);
				 strcpy(temp2,tempOsn); //////��������� ���������� ����������� ������ (� ������ 43)
			}
			
			chandl = _findnext(handl,&fileinfo);
		}
		
			
		return 1;
	}
