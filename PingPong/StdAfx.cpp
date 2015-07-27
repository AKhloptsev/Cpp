// stdafx.cpp : source file that includes just the standard includes
//	Sceleton.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

extern HINSTANCE hInst;

LRESULT CALLBACK WFunc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu1;
	const int SPAN = 10;

	PAINTSTRUCT ps;	// для прорисовки окна
	HDC hdc;	//хендлер контекста устройства
	int mx, my;
	static double mod, vx, vy, xt, yt;	
	static HDC memDC;	
	static HPEN hpen;	// кисть для прорисовки вектора скорости
	static int x, y, cx, cy, scrx, scry;
	static HBITMAP hCircle;		// хендлер для кружочка
	static bool play;		// определена скорость движения шарика или нет


	switch (message)
	{
	case WM_CREATE:
		hMenu1 = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));	// Загружаем меню
		SetMenu(hwnd, hMenu1);	// Подключаем меню

		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));	// создаём кисть красного цвета для вектора скорости
		hCircle = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));	// загружаем кружок
		hdc = GetDC(hwnd);	// получаем контекст устройства
		memDC = CreateCompatibleDC(hdc);	// получаем контекст устройства совместимый с текущим
		SelectObject(memDC, hCircle);	// ставим в контекст устройства загруженное изображение кружка
		ReleaseDC(hwnd, hdc);	// освобождаем hdc
		break;

	case WM_SIZE:
		scrx = LOWORD(lParam);	// максимальное значение по ох
		scry = HIWORD(lParam);	// максимальное значение по оу
		x = (cx = scrx/2) - 16;	// cx = середина ох, x = середина - 16 пикселей для вывода шарика
		y = (cy = scry/2) - 16;	// cу = середина оу, у = середина - 16 пикселей для вывода шарика
		break;

	case WM_LBUTTONDOWN:
		if (!play)	// если скорость движения шарика не определена
		{ 
			mx = LOWORD(lParam);	// координаты х на текущей позиции мышки
			my = HIWORD(lParam);	// координаты у на текущей позиции мышки
			vx = mx - cx;	// размер вектора по ох
			vy = my - cy;	// размер вектора по оу
			// переводим в относительные координаты
			mod = sqrt(vx*vx+vy*vy);
			vx = vx/mod;
			vy = vy/mod;
			hdc = GetDC(hwnd);	// получаем контекста устройства
			SelectObject(hdc, hpen);	// выбираем кисть
			MoveToEx(hdc, cx, cy, 0);	// перемещаемся к середине окна
			LineTo(hdc, mx, my);	// рисуем линию к координатам текущей позиции мышки
			// рисуем наконечник стрелки
			// нижняя стрелка
			LineTo(hdc, mx - (vx - vy)*SPAN, my - (vy + vx)*SPAN);	 
			// верхняя стрелка
			MoveToEx(hdc, mx - (vx + vy)*SPAN, my - (vy - vx)*SPAN, 0);
			LineTo(hdc, mx, my);
			ReleaseDC(hwnd, hdc);	// освобождаем hdc
			play = true;	// скорость определена
		}
		break;

	case WM_TIMER:
		hdc = GetDC(hwnd);	// получаем контекст устройства
		BitBlt(hdc, x, y, 32, 32, NULL, 0, 0, PATCOPY);	// в позицию старого положения шарика выводим цвет фона (PATCOPY)
		if (x + 31 > scrx || x < 1) vx = -vx;	// не вышли ли мы за пределы окна по ох, если вышли, то меняем знак приращения координаты vx
		if (y + 31 > scry || y < 1) vy = -vy;	// не вышли ли мы за пределы окна по оу, если вышли, то меняем знак приращения координаты vу
		// наращиваем координаты xt & yt
		xt += vx*10;	
		yt += vy*10;
		// округляем скорость движения до целого
		x = int(xt + 0.5);	
		y = int(yt + 0.5);
		BitBlt(hdc, x, y, 32, 32, memDC, 0, 0, SRCCOPY);	// выводим изображение в новой позиции
		ReleaseDC(hwnd, hdc);
		break;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_PLAY_BEGIN:
			// скорость движения шарика в третьем параметре(частота генерации сообщения WM_TIMER
			SetTimer(hwnd, 1, (int)(sqrt(double(cx*cx+cy*cy))/mod)*10, NULL);
			xt = x;		// начальные координаты х и у
			yt = y;
			InvalidateRect(hwnd, NULL, TRUE);	// вызываем перерисовку окна (убираем стрелочку направления)
			break;

		case ID_PLAY_END:
			KillTimer(hwnd, 1);	// убиваем таймер
			x = cx - 16;	// возращаем координаты центра х
			y = cy - 16;	// возращаем координаты центра у
			InvalidateRect(hwnd, NULL, TRUE);	// перерисовываем окно
			play = false;	// скорость не определена
			break;

		case ID_PLAY_EXIT:
			DestroyWindow(hwnd);
			break;
		}
		break;


	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);	// получаем hdc
		BitBlt(hdc, x, y, 32, 32, memDC, 0, 0, SRCCOPY);	// перерисовываем фон окна
		EndPaint(hwnd, &ps);	// освобождаем hdc
		break;


	case WM_DESTROY:
		DeleteDC(memDC);	// возвращаем ресурсы
		DeleteObject(hpen);
		PostQuitMessage(0); //отправка сообщения в WM_QUIT
		break;
	default:
		return
			DefWindowProc(hwnd,message,wParam,lParam);//возврат неотработанного сообщения
	}
	return 0L;
}

