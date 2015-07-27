// stdafx.cpp : source file that includes just the standard includes
//	Sceleton.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

extern HINSTANCE hInst;

LRESULT CALLBACK WFunc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu1;
	const int SPAN = 10;

	PAINTSTRUCT ps;	// ��� ���������� ����
	HDC hdc;	//������� ��������� ����������
	int mx, my;
	static double mod, vx, vy, xt, yt;	
	static HDC memDC;	
	static HPEN hpen;	// ����� ��� ���������� ������� ��������
	static int x, y, cx, cy, scrx, scry;
	static HBITMAP hCircle;		// ������� ��� ��������
	static bool play;		// ���������� �������� �������� ������ ��� ���


	switch (message)
	{
	case WM_CREATE:
		hMenu1 = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));	// ��������� ����
		SetMenu(hwnd, hMenu1);	// ���������� ����

		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));	// ������ ����� �������� ����� ��� ������� ��������
		hCircle = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));	// ��������� ������
		hdc = GetDC(hwnd);	// �������� �������� ����������
		memDC = CreateCompatibleDC(hdc);	// �������� �������� ���������� ����������� � �������
		SelectObject(memDC, hCircle);	// ������ � �������� ���������� ����������� ����������� ������
		ReleaseDC(hwnd, hdc);	// ����������� hdc
		break;

	case WM_SIZE:
		scrx = LOWORD(lParam);	// ������������ �������� �� ��
		scry = HIWORD(lParam);	// ������������ �������� �� ��
		x = (cx = scrx/2) - 16;	// cx = �������� ��, x = �������� - 16 �������� ��� ������ ������
		y = (cy = scry/2) - 16;	// c� = �������� ��, � = �������� - 16 �������� ��� ������ ������
		break;

	case WM_LBUTTONDOWN:
		if (!play)	// ���� �������� �������� ������ �� ����������
		{ 
			mx = LOWORD(lParam);	// ���������� � �� ������� ������� �����
			my = HIWORD(lParam);	// ���������� � �� ������� ������� �����
			vx = mx - cx;	// ������ ������� �� ��
			vy = my - cy;	// ������ ������� �� ��
			// ��������� � ������������� ����������
			mod = sqrt(vx*vx+vy*vy);
			vx = vx/mod;
			vy = vy/mod;
			hdc = GetDC(hwnd);	// �������� ��������� ����������
			SelectObject(hdc, hpen);	// �������� �����
			MoveToEx(hdc, cx, cy, 0);	// ������������ � �������� ����
			LineTo(hdc, mx, my);	// ������ ����� � ����������� ������� ������� �����
			// ������ ���������� �������
			// ������ �������
			LineTo(hdc, mx - (vx - vy)*SPAN, my - (vy + vx)*SPAN);	 
			// ������� �������
			MoveToEx(hdc, mx - (vx + vy)*SPAN, my - (vy - vx)*SPAN, 0);
			LineTo(hdc, mx, my);
			ReleaseDC(hwnd, hdc);	// ����������� hdc
			play = true;	// �������� ����������
		}
		break;

	case WM_TIMER:
		hdc = GetDC(hwnd);	// �������� �������� ����������
		BitBlt(hdc, x, y, 32, 32, NULL, 0, 0, PATCOPY);	// � ������� ������� ��������� ������ ������� ���� ���� (PATCOPY)
		if (x + 31 > scrx || x < 1) vx = -vx;	// �� ����� �� �� �� ������� ���� �� ��, ���� �����, �� ������ ���� ���������� ���������� vx
		if (y + 31 > scry || y < 1) vy = -vy;	// �� ����� �� �� �� ������� ���� �� ��, ���� �����, �� ������ ���� ���������� ���������� v�
		// ���������� ���������� xt & yt
		xt += vx*10;	
		yt += vy*10;
		// ��������� �������� �������� �� ������
		x = int(xt + 0.5);	
		y = int(yt + 0.5);
		BitBlt(hdc, x, y, 32, 32, memDC, 0, 0, SRCCOPY);	// ������� ����������� � ����� �������
		ReleaseDC(hwnd, hdc);
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_PLAY_BEGIN:
			// �������� �������� ������ � ������� ���������(������� ��������� ��������� WM_TIMER
			SetTimer(hwnd, 1, (int)(sqrt(double(cx*cx+cy*cy))/mod)*10, NULL);
			xt = x;		// ��������� ���������� � � �
			yt = y;
			InvalidateRect(hwnd, NULL, TRUE);	// �������� ����������� ���� (������� ��������� �����������)
			break;

		case ID_PLAY_END:
			KillTimer(hwnd, 1);	// ������� ������
			x = cx - 16;	// ��������� ���������� ������ �
			y = cy - 16;	// ��������� ���������� ������ �
			InvalidateRect(hwnd, NULL, TRUE);	// �������������� ����
			play = false;	// �������� �� ����������
			break;

		case ID_PLAY_EXIT:
			DestroyWindow(hwnd);
			break;
		}
		break;


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);	// �������� hdc
		BitBlt(hdc, x, y, 32, 32, memDC, 0, 0, SRCCOPY);	// �������������� ��� ����
		EndPaint(hwnd, &ps);	// ����������� hdc
		break;


	case WM_DESTROY:
		DeleteDC(memDC);	// ���������� �������
		DeleteObject(hpen);
		PostQuitMessage(0); //�������� ��������� � WM_QUIT
		break;
	default:
		return
			DefWindowProc(hwnd,message,wParam,lParam);//������� ��������������� ���������
	}
	return 0L;
}

