// stdafx.cpp : source file that includes just the standard includes
//	Sceleton.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

extern HINSTANCE hInst;

LRESULT CALLBACK WFunc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	srand(time(NULL));
	static HDC hdc;
	static PAINTSTRUCT ps;
	static HWND hButShow, hButSort, hEditDiff, hStaticDiff, hEditM1, hStaticM1, hEditM2, hStaticM2, hEditM, hStaticM;
	static HPEN hPen;
	static int sx, sy;
	switch (message)
	{
	case WM_CREATE:
		hButShow = CreateWindow("BUTTON", "Show total heap", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 270, 10, 120, 20, hwnd, 0, hInst, 0);
		hButSort = CreateWindow("BUTTON", "Sort", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 270, 40, 120, 20, hwnd, 0, hInst, 0);
		hStaticDiff = CreateWindow("STATIC", "Разница масс между первой и второй кучей", WS_CHILD|WS_VISIBLE, 200, 65, 300, 20, hwnd, 0, hInst, 0);
		hEditDiff = CreateWindow("EDIT", "", WS_CHILD|WS_VISIBLE|WS_BORDER, 310, 88, 50, 20, hwnd, 0, hInst, 0);

		hStaticM1 = CreateWindow("STATIC", "Масса первой кучи", WS_CHILD|WS_VISIBLE, 75, 570, 150, 20, hwnd, 0, hInst, 0);
		hEditM1 = CreateWindow("EDIT", "", WS_CHILD|WS_VISIBLE|WS_BORDER, 125, 600, 50, 20, hwnd, 0, hInst, 0);

		hStaticM2 = CreateWindow("STATIC", "Масса второй кучи", WS_CHILD|WS_VISIBLE, 470, 570, 150, 20, hwnd, 0, hInst, 0);
		hEditM2 = CreateWindow("EDIT", "", WS_CHILD|WS_VISIBLE|WS_BORDER, 525, 600, 50, 20, hwnd, 0, hInst, 0);

		hStaticM = CreateWindow("STATIC", "Масса основной кучи", WS_CHILD|WS_VISIBLE, 270, 570, 150, 20, hwnd, 0, hInst, 0);
		hEditM = CreateWindow("EDIT", "", WS_CHILD|WS_VISIBLE|WS_BORDER, 320, 600, 50, 20, hwnd, 0, hInst, 0);

		hPen = CreatePen(PS_SOLID, 2, RGB(200, 200, 200));
		DialogBox(hInst, (TCHAR*)IDD_DIALOG2, hwnd, SecondFunc);
		
		if(!bFlag)
		{
			DialogBox(hInst, (TCHAR*)IDD_DIALOG1, hwnd, FirstFunc);
			stoneArray = new double[numberOfStones];
			for (int i = 0; i < numberOfStones; i++)
			{
				stoneArray[i] = 10 + (rand() % 150);
			}
		}
		else
		{
			DialogBox(hInst, (TCHAR*)IDD_DIALOG3, hwnd, ThirdFunc);
		}
		break;

	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		sx /= 2;
		sy /= 2;
		break;


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		EndPaint(hwnd, &ps);
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case ID_ABOUT_ABOUT:
				DialogBox(hInst, (TCHAR*)IDD_DIALOG4, hwnd, FuncAbout);
				break;

			case ID_MENU_EXIT:
				DestroyWindow(hwnd);
				break;

			case ID_MENU_NEW:
				for (int i = 0; i < numberOfStones; i++)
				{
					stoneArray[i] = 0;
				}
				sprintf(str, "");
				SendMessage(hEditDiff, WM_SETTEXT, (WPARAM)0, (LPARAM)str);
				SendMessage(hEditM, WM_SETTEXT, (WPARAM)0, (LPARAM)str);
				SendMessage(hEditM1, WM_SETTEXT, (WPARAM)0, (LPARAM)str);
				SendMessage(hEditM2, WM_SETTEXT, (WPARAM)0, (LPARAM)str);
				InvalidateRect(hwnd, 0, 1);
				DialogBox(hInst, (TCHAR*)IDD_DIALOG2, hwnd, SecondFunc);
		
				if(!bFlag)
				{
					DialogBox(hInst, (TCHAR*)IDD_DIALOG1, hwnd, FirstFunc);
					stoneArray = new double[numberOfStones];
					for (int i = 0; i < numberOfStones; i++)
					{
						int rm = rand() % 100;
						rm /= 100;
						stoneArray[i] = 10 + (rand() % 150) + rm;
					}
				}
				else
				{
					DialogBox(hInst, (TCHAR*)IDD_DIALOG3, hwnd, ThirdFunc);
				}
		}

		if((HWND)lParam == hButShow)
		{
			hdc = GetDC(hwnd);
			SelectObject(hdc, hPen);
			int y = sy - 200;
			for (int i = 0; i < numberOfStones; i++)
			{
				Ellipse(hdc, sx - stoneArray[i]/2, y - 10, sx + stoneArray[i]/2, y + 10);
				y += 30;
			}
			ReleaseDC(hwnd, hdc);
		}

		if((HWND)lParam == hButSort)
		{
			stoneArrayCopy = new double[numberOfStones];
			int m = 0, m1 = 0, m2 = 0, diff = 0;

			for (int i = 0; i < numberOfStones; i++)
			{
				stoneArrayCopy[i] = stoneArray[i];
			}
			hdc = GetDC(hwnd);
			SelectObject(hdc, hPen);
			int y = sy;
			if(numberOfStones <= 3)
			{
				sort(stoneArrayCopy, stoneArrayCopy + numberOfStones);
				for (int i = 0; i < numberOfStones - 1; i++)
				{
					m1 += stoneArrayCopy[i];
					m += stoneArrayCopy[i];
					Ellipse(hdc, sx - 200, y - 10, sx - 200 + stoneArrayCopy[i], y + 10);
					y += 30;
				}
				Ellipse(hdc, sx + 200, sy - 10, sx + 200 + stoneArrayCopy[numberOfStones - 1], sy + 10);
				m2 = stoneArrayCopy[numberOfStones - 1];
				m += m2;
				diff = m2 - m1;
				sprintf(str, "%d", diff);
				SendMessage(hEditDiff, WM_SETTEXT, (WPARAM)0, (LPARAM)str);

				sprintf(str, "%d", m);
				SendMessage(hEditM, WM_SETTEXT, (WPARAM)0, (LPARAM)str);

				sprintf(str, "%d", m1);
				SendMessage(hEditM1, WM_SETTEXT, (WPARAM)0, (LPARAM)str);

				sprintf(str, "%d", m2);
				SendMessage(hEditM2, WM_SETTEXT, (WPARAM)0, (LPARAM)str);
			}
			
			

			else //а здесь с использованием класса
			{
				Heaps * MyHeapsPtr = new Heaps(stoneArrayCopy, numberOfStones);
				
				diff = MyHeapsPtr->print(hwnd, hdc, sx, sy, m, m1, m2);
				sprintf(str, "%d", diff);
				SendMessage(hEditDiff, WM_SETTEXT, (WPARAM)0, (LPARAM)str);

				sprintf(str, "%d", m);
				SendMessage(hEditM, WM_SETTEXT, (WPARAM)0, (LPARAM)str);

				sprintf(str, "%d", m1);
				SendMessage(hEditM1, WM_SETTEXT, (WPARAM)0, (LPARAM)str);

				sprintf(str, "%d", m2);
				SendMessage(hEditM2, WM_SETTEXT, (WPARAM)0, (LPARAM)str);
			}

			ReleaseDC(hwnd, hdc);
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

BOOL CALLBACK FirstFunc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDC_ButtonACCEPT:
				SendDlgItemMessage(hDlg, IDC_EditNumberOfStones, WM_GETTEXT, (WPARAM)256, (LPARAM)str);
				numberOfStones = atoi(str);
				if(numberOfStones > 18 || numberOfStones < 0)
				{
					MessageBoxA(hDlg, "Слишком много камней, попробуйте меньше", "Error", MB_OK);
					break;
				}
				EndDialog(hDlg, 0);
				break;

			case IDC_ButtonCLEAR:
				sprintf(str, "");
				SendDlgItemMessage(hDlg, IDC_EditNumberOfStones, WM_SETTEXT, (WPARAM)0, (LPARAM)str);
				break;

			case IDC_ButtonCANCEL:
				EndDialog(hDlg, 0);
				break;
		}
		return TRUE;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK SecondFunc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDC_ButtonByHand:
				bFlag = true;
				EndDialog(hDlg, 0);
				break;

			case IDC_ButtonAutomatically:
				bFlag = false;
				EndDialog(hDlg, 0);
				break;
		}
		return TRUE;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK ThirdFunc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	regex re("[a-zA-Z,.//\\!@#$%^&*()?]");	// всё, кроме цифр и пробела
	char str2[256] = "";
	char* token;
	int count = 0;
	switch(message)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDC_ButtonInput:
				SendDlgItemMessage(hDlg, IDC_EditInputMasElem, WM_GETTEXT, (WPARAM)256, (LPARAM)str);
				numberOfStones = 0;
				for (int i = 0; i < strlen(str); i++)
				{
					if(str[i] == ' ')
						numberOfStones++;
				}
				if(regex_search(str, re))
					strForRE = regex_replace(str, re, "");
				else
					strForRE = str;
				
				strcpy(str2, strForRE.c_str());
				
				token = strtok(str2, " ");
				
				stoneArray = new double[numberOfStones + 1];
				numberOfStones = 0;
				while(token != NULL)
				{
					stoneArray[numberOfStones++] = atof(token);
					token = strtok(NULL, " ");
				}
				for (int i = 0; i < numberOfStones; i++)
				{
					if(stoneArray[i] <= 0)
						count++;
				}
				if(count == 0)
					MessageBoxA(hDlg, "Вы восхитительны!", "", MB_OK);

				SendDlgItemMessage(hDlg, IDC_EditKoef, WM_GETTEXT, (WPARAM)256, (LPARAM)str);
				re = ("[a-zA-Z,.//\\!@#$%^&*()?] ");	// всё, кроме цифр
				if(regex_search(str, re))
					strForRE = regex_replace(str, re, "");
				else
					strForRE = str;
				koef = atoi(strForRE.c_str());
				if(koef != 1 && koef != 0)
				{
					for (int i = 0; i < numberOfStones; i++)
					{
						stoneArray[i] *= koef;
					}
				}
				EndDialog(hDlg, 0);
				break;

			case IDC_ButtonAutomatically:
				bFlag = false;
				EndDialog(hDlg, 0);
				break;
		}
		return TRUE;

	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}


BOOL CALLBACK FuncAbout (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		return TRUE;
	}
	return FALSE;
}