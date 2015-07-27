// stdafx.cpp : source file that includes just the standard includes
//	Sceleton.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

extern HINSTANCE hInst;

LRESULT CALLBACK WFunc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
	static HWND hEditRegEx, hStaticRegEx, hListText, hStaticText, hButCheck, hButAdd, hButLoad, hButSave, hEditAddText, hButDel, hButDelAll, hButReplace, hEditReplace;
	HICON hIcon;
	static OPENFILENAME file;
	static TCHAR name[256] = "";
	static HDC hdc;
	static string s;
	static string masSTR[256];
	static int count, curSel;
	static regex re;
	static BOOL bFlag = FALSE;
	ifstream in;
	ofstream out;
	
	switch (message)
	{
	case WM_CREATE:
		file.lStructSize = sizeof(OPENFILENAME);
		file.hInstance = hInst;
		file.lpstrFile = name;
		file.nMaxFile = 256;
		file.lpstrInitialDir = ".\\";
		file.lpstrDefExt = "txt";
		file.lpstrFilter = ".txt\0*.txt";
		hStaticRegEx = CreateWindow("STATIC", "Регулярные выражения:", WS_VISIBLE|WS_CHILD, 10, 10, 220, 20, hwnd, 0, hInst, 0);
		hEditRegEx = CreateWindow("EDIT", "", WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL, 10, 40, 300, 30, hwnd, 0, hInst, 0);
		hStaticText = CreateWindow("STATIC", "Текст", WS_VISIBLE|WS_CHILD, 10, 175, 50, 20, hwnd, 0, hInst, 0);
		hListText = CreateWindow("LISTBOX", "", WS_VISIBLE|WS_CHILD|WS_BORDER|LBS_NOTIFY|WS_HSCROLL|WS_VSCROLL, 10, 200, 350, 400, hwnd, 0, hInst, 0);
		hButCheck = CreateWindow("BUTTON", "Проверить", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 350, 40, 95, 25, hwnd, 0, hInst, 0);
		hButReplace = CreateWindow("BUTTON", "Заменить на", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 350, 88, 112, 25, hwnd, 0, hInst, 0);
		hEditReplace = CreateWindow("EDIT", "", WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL, 10, 88, 300, 30, hwnd, 0, hInst, 0);
		hEditAddText = CreateWindow("EDIT", "Добавить строку в текст", WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL, 10, 135, 300, 25, hwnd, 0, hInst, 0);
		hButAdd = CreateWindow("BUTTON", "Добавить", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 350, 135, 95, 25, hwnd, 0, hInst, 0);
		hButLoad = CreateWindow("BUTTON", "Загрузить", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 370, 200, 95, 25, hwnd, 0, hInst, 0);
		hButSave = CreateWindow("BUTTON", "Сохранить", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 370, 235, 95, 25, hwnd, 0, hInst, 0);
		hButDel = CreateWindow("BUTTON", "Удалить", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 370, 270, 95, 25, hwnd, 0, hInst, 0);
		hButDelAll = CreateWindow("BUTTON", "Удалить всё", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 370, 305, 110, 25, hwnd, 0, hInst, 0);
		SendMessage(hListText, LB_SETHORIZONTALEXTENT, (WPARAM)750, 0);
		hIcon = LoadIcon(hInst, (TCHAR*)IDI_ICON1);
		SendMessage(hwnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIcon);
		SetFocus(hEditRegEx);

		break;


	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_FILE_NEW1: case IDM_FILE_NEW:
			MessageBoxA(hwnd, "NEW", "NEW", MB_OK);
			SendMessage(hEditRegEx, WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(hEditReplace, WM_SETTEXT, (WPARAM)0, (LPARAM)"");
			SendMessage(hEditAddText, WM_SETTEXT, (WPARAM)0, (LPARAM)"Добавить строку в текст");
			SendMessage(hListText, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
			strcpy(str,(strcpy(str2, (strcpy(str3, "")))));
			break;

		case ID_FILE_OPEN1: case IDM_FILE_OPEN:
			file.lpstrTitle = "Открыть файл";
			if (!GetOpenFileName(&file))
				return 1;
			in.open(name);
			while(!in.eof())
			{
				getline(in, s);
				s += "\n";
				SendMessage(hListText, LB_ADDSTRING, 0, (LPARAM)s.c_str());//
			}
			in.close();
			SetFocus(hEditRegEx);
			break;

		case ID_FILE_SAVE1: case IDM_FILE_SAVE:
			file.lpstrTitle = "Сохранить как...";
			file.Flags = OFN_NOTESTFILECREATE;
			if(!GetSaveFileName(&file))
				return 1;
			out.open(name);
			count = SendMessage(hListText, LB_GETCOUNT, 0, 0);
			for (int i = 0; i < count; i++)
			{
				SendMessage(hListText, LB_GETTEXT, (WPARAM)i, (LPARAM)str);
				out << str;
			}
			out.close();
			break;

		case ID_FILE_EXIT1: case IDM_FILE_EXIT:
			DestroyWindow(hwnd);
			break;
		}

		if((HWND)lParam == hButReplace)
		{
			SendMessage(hEditRegEx, WM_GETTEXT, (WPARAM)256, (LPARAM)str2);
			re = str2;
			count = SendMessage(hListText, LB_GETCOUNT, 0, 0);
			for (int i = 0; i < count; i++)
			{
				SendMessage(hListText, LB_GETTEXT, (WPARAM)i, (LPARAM)str);
				if(regex_search(str, re))
				{
					SendMessage(hEditReplace, WM_GETTEXT, (WPARAM)256, (LPARAM)str3);
					s = regex_replace(str, re, str3);
					masSTR[i] = s;
				}
				else
					masSTR[i] = str;
			}
			SendMessage(hListText, LB_RESETCONTENT, 0, 0);
			for (int i = 0; i < count; i++)
			{
				strcpy(str, masSTR[i].c_str());
				SendMessage(hListText, LB_ADDSTRING, (WPARAM)0, (LPARAM)str);
			}
		}

		if((HWND)lParam == hButCheck)
		{
			bFlag = FALSE;
			SendMessage(hEditRegEx, WM_GETTEXT, (WPARAM)256, (LPARAM)str2);
			strcat(str2, "\n");
			re = str2;
			count = SendMessage(hListText, LB_GETCOUNT, 0, 0);
			for (int i = 0; i < count; i++)
			{
				SendMessage(hListText, LB_GETTEXT, (WPARAM)i, (LPARAM)str);
				if(regex_match(str, re))
				{
					MessageBoxA(hwnd, str, "Find", MB_OK);
					bFlag = TRUE;
				}
			}
			if(!bFlag)
				MessageBoxA(hwnd, str2, "Not Found", MB_OK);
		}
		
		if((HWND)lParam == hButAdd)
		{
			SendMessage(hEditAddText, WM_GETTEXT, (WPARAM)256, (LPARAM)str);
			strcat(str, "\n");
			SendMessage(hListText, LB_ADDSTRING, 0, (LPARAM)str);
		}
		
		if((HWND)lParam == hButLoad)
		{
			ifstream fin ("1.txt", ios::in);
			if(!fin)
				MessageBoxA(hwnd, "Error loading 1.txt", "Error loading", MB_OK);
			while(!fin.eof())
			{
				getline(fin, s);
				s += "\n";
				SendMessage(hListText, LB_ADDSTRING, 0, (LPARAM)s.c_str());//
			}
			fin.close();
			SetFocus(hEditRegEx);
		}


		if((HWND)lParam == hButSave)
		{
			ofstream fout("1.txt", ios::out);
			if(!fout)
				MessageBoxA(hwnd, "Error writing to file!", "Error writing", MB_OK);
			count = SendMessage(hListText, LB_GETCOUNT, 0, 0);
			for (int i = 0; i < count; i++)
			{
				SendMessage(hListText, LB_GETTEXT, (WPARAM)i, (LPARAM)str);
				fout << str;
			}
			fout.close();
		}

		if((HWND)lParam == hButDel)
		{
			curSel = SendMessage(hListText, LB_GETCURSEL, 0, 0);
			SendMessage(hListText, LB_DELETESTRING, (WPARAM)curSel, 0);
		}

		if((HWND)lParam == hButDelAll)
		{
			SendMessage(hListText, LB_RESETCONTENT, 0, 0);
		}
		break;


	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); //отправка сообщения в WM_QUIT
		break;

	default:
		return
			DefWindowProc(hwnd,message,wParam,lParam);//возврат неотработанного сообщения
	}
	return 0L;
}



