// Sceleton.cpp : Defines the entry point for the application.
//

#include "stdafx.h"



char name[]="Qwerty";//Необходимо для регистрации окна

HINSTANCE hInst;
int APIENTRY WinMain(HINSTANCE hInstance,//хендлер приложения
                     HINSTANCE ,
                     LPSTR     lpCmdLine,//командная строка
                     int       nCmdShow)//вид окна
{
	
	hInst = hInstance;
	// 1.Создание внешнего вида ОКНА
	WNDCLASS win;//объект для информации об окне
	win.style=CS_HREDRAW|CS_VREDRAW;//Стили перерисовки
	win.lpfnWndProc=WFunc;//Имя оконной функции
	win.cbClsExtra=win.cbWndExtra=0;
	win.hInstance=hInstance;//имя приложения, к которому привязано окно
	win.hIcon=LoadIcon(NULL,IDI_ASTERISK);//иконка, идентификатор иконки ID_APPLIKATION
	win.hCursor=LoadCursor(NULL,IDC_ARROW); //курсор
	win.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//Цвет фона
	win.lpszMenuName = (TCHAR*)IDR_MENU1;//меню отсутствует
	win.lpszClassName=name;//Имя для регистрации

	//2.Регистрация окна в Операционной системе
	if (!RegisterClass(&win))
	{
		MessageBox(NULL,"Окно не зарегистрировано","Ошибка",MB_OK);
		return -1;//если окно не зарегистрировано
	}

	//3.Создание ОКНА
	HWND hwnd; //Объявление хендлера Окна
	hwnd=CreateWindow(name,"Задача с камнями",WS_OVERLAPPEDWINDOW/*|WS_VISIBLE*/,500,150,
		              700,700,HWND_DESKTOP,NULL,hInstance,NULL);//Создание хендлера Окна

	

	//4*.Отображение окна

	ShowWindow(hwnd,nCmdShow); //nCmdShow - для показа  окна
	UpdateWindow (hwnd); //обновить сразу окно - перерисовка

	//5.создание насоса сообщений
	MSG msg; //описание переменной Сообщения
	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);  //разрешает использовать клавиатуру
		DispatchMessage(&msg); //отправка обработанного сообщения в ОС
	}
	return msg.wParam; //корректное закрытие основной программы
}


