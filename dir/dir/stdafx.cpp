// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// Поиск_маска.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"


double Find(char path[256], char mask[256])
{
	
	strcat(path,"\\");

	char temp[256] = "";
	char temp2[256] = "";
	char tempOsn[256] = "";

	strcpy(temp,strcpy(temp2,strcpy(tempOsn,path)));                   ////////Копиривание  адреса разделов

	

	//////////поиск файла в текущей папке/////////
	strcat(path,mask);

	_finddata_t fileinfo ;
	long handl,chandl,count = 0;
	chandl = handl = _findfirst(path,&fileinfo);

	if(chandl != -1)
		cout<<path<<endl;


	////////////перебор всех элементов в папке//////
	
	strcat(temp,"*.*");
	chandl = handl = _findfirst(temp,&fileinfo);
		
	while(chandl != -1)
		{
			

			if(fileinfo.name[0] != '.')  /////если текущий элемент не . и не .. то заходим в него и вызываем рекурсию
			{
				strcat(temp2,fileinfo.name);
				 Find( temp2,mask);
				 strcpy(temp2,tempOsn); //////отменение последнего сопирования строки (в строке 43)
			}
			
			chandl = _findnext(handl,&fileinfo);
		}
		
			
		return 1;
	}
