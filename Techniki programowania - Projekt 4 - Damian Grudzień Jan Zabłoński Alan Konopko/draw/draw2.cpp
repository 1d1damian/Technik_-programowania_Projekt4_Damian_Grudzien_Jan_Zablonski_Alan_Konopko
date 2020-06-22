// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <queue>
#include <Windows.h>
#include <string>

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;
INT kierunek = 1;

struct winda
{
	int wysokosc;
	int cel;
};
std::vector<int> wWindzie;
std::vector<int> wektor0;
std::vector<int> wektor1;
std::vector<int> wektor2;
std::vector<int> wektor3;
std::vector<int> wektor4;

std::queue<winda> kolejka_celu;

// buttons
HWND hwndButton;

// sent data
int n = 0;
int wysTer = 0;
int col = 0;
std::vector<Point> data;
std::priority_queue <INT> lift;
RECT drawArea1 = { 455, 55, 895, 605 };

RECT textRect{ 960, 70, 1025, 90, };

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);

void WejdzDoWindy(std::vector<int> &wektor)
{
	while ((wWindzie.size() < 8) && !wektor.empty())
	{
		wWindzie.push_back({ wektor.front() });
		wektor.erase(wektor.begin());
	}
}
void WyjdzZWindy(INT value)
{
	
	n = wWindzie.size();
	for (int i = n; i>0 ; i--)
	{
		if (wWindzie[i-1] == value)
		{
			wWindzie.erase(wWindzie.begin()+(i-1));
		}
	}
	n = 0;

}
bool SprawdzWinde(INT value)
{
	n = wWindzie.size();
	for (int i = n; i > 0; i--)
	{
		if (wWindzie[i - 1] == value)
		{
			return(true);
		}
	}
	n = 0;
}
void SprawdzNaPietrze(INT value)
{
	if (value == 0 && (!wektor0.empty()||SprawdzWinde(value) == true))
	{
		Sleep(1000);
		WyjdzZWindy(value);
		WejdzDoWindy(wektor0);
		Sleep(1000);
	}
	if (value == 100 && (!wektor1.empty() || SprawdzWinde(value) == true))
	{
		Sleep(1000);
		WyjdzZWindy(value);
		WejdzDoWindy(wektor1);
		Sleep(1000);
	}
	if (value == 200 && (!wektor2.empty() || SprawdzWinde(value) == true))
	{
		Sleep(1000);
		WyjdzZWindy(value);
		WejdzDoWindy(wektor2);
		Sleep(1000);
	}
	if (value == 300 && (!wektor3.empty() || SprawdzWinde(value) == true))
	{
		Sleep(1000);
		WyjdzZWindy(value);
		WejdzDoWindy(wektor3);
		Sleep(1000);
	}
	if (value == 400 && (!wektor4.empty() || SprawdzWinde(value) == true))
	{
		Sleep(1000);
		WyjdzZWindy(value);
		WejdzDoWindy(wektor4);
		Sleep(1000);
	}

}

void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));

	Pen pen2(Color(255, 25, 0, 255), 5);
	Pen pen3(Color(255, 250, 18, 18), 10);
	Pen pen4(Color(255, 250, 18, 18), 3);
	




	graphics.DrawRectangle(&pen3, 450, 50, 450, 560);



	graphics.DrawLine(&pen4, 20, 550, 450, 550);
	graphics.DrawLine(&pen4, 20, 350, 450, 350);
	graphics.DrawLine(&pen4, 20, 150, 450, 150);

	graphics.DrawLine(&pen4, 900, 250, 1330, 250);
	graphics.DrawLine(&pen4, 900, 450, 1330, 450);
}
void LiftPaint(HDC hdc)
{
	Graphics graphics(hdc);

	Pen pen2(Color(255, 25, 0, 255), 5);

	
	DrawTextA(hdc, std::to_string(wWindzie.size() * 70).c_str(), -1, &textRect, DT_CENTER);
	TextOut(hdc, 1010, 70, TEXT("Kg"), 2);

	graphics.DrawRectangle(&pen2, 480, 470 - value, 390, 80);
	graphics.DrawRectangle(&pen2, 950, 50, 100, 50);

}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea==NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	LiftPaint(hdc);
	Sleep(10);
	EndPaint(hWnd, &ps);
}

void inputData()
{	
	data.push_back(Point(0, 0));
	for (int i = 1; i < 100; i++){
		data.push_back(Point(2*i+1, 200 * rand()/RAND_MAX));
	}
}


int OnCreate(HWND window)
{

	inputData();
	return 0;
}


// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	
	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	                                                     
	

	//pietro 0
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		400, 560,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON3,
		GetModuleHandle(NULL),
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		350, 560,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON4,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 560,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON5,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		250, 560,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON6,
		hInstance,
		NULL);
	//pietro 2
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		400, 360,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON7,
		GetModuleHandle(NULL),
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		350, 360,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON8,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 360,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON9,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		250, 360,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON10,
		hInstance,
		NULL);
	//pietro 4
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		400, 160,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON11,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		350, 160,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON12,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		300, 160,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON13,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		250, 160,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON14,
		hInstance,
		NULL);
	//pietro 1
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		910, 460,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON15,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		960, 460,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON16,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1010, 460,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON17,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1060, 460,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON18,
		hInstance,
		NULL);
	//pietro 3
	hwndButton = CreateWindow(TEXT("button"),
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		910, 260,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON19,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		960, 260,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON20,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1010, 260,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON21,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1060, 260,
		40, 40,
		hWnd,
		(HMENU)ID_BUTTON22,
		hInstance,
		NULL);




	// create button and store the handle                                                       

/*	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer ON"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		300, 155, 100, 30, hWnd, (HMENU)ID_RBUTTON1, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer OFF"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		300, 200, 100, 30, hWnd, (HMENU)ID_RBUTTON2, GetModuleHandle(NULL), NULL); */

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;



	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			//pietro 0
		case ID_BUTTON3:
			KillTimer(hWnd, TMR_1);
			wektor0.push_back({ 100 });
			kolejka_celu.push({ 0, 100 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON4:
			KillTimer(hWnd, TMR_1);
			wektor0.push_back({ 200});
			kolejka_celu.push({ 0, 200 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON5:
			KillTimer(hWnd, TMR_1);
			wektor0.push_back({ 300 });
			kolejka_celu.push({ 0, 300 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON6:
			KillTimer(hWnd, TMR_1);
			wektor0.push_back({ 400 });
			kolejka_celu.push({ 0, 400 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
			//pietro 2
		case ID_BUTTON7:
			KillTimer(hWnd, TMR_1);
			wektor2.push_back({ 0 });
			kolejka_celu.push({ 200, 0 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON8:
			KillTimer(hWnd, TMR_1);
			wektor2.push_back({ 100 });
			kolejka_celu.push({ 200, 100 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON9:
			KillTimer(hWnd, TMR_1);
			wektor2.push_back({ 300 });
			kolejka_celu.push({ 200, 300 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON10:
			KillTimer(hWnd, TMR_1);
			wektor2.push_back({ 400 });
			kolejka_celu.push({ 200, 400 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
			//pietro 4
		case ID_BUTTON11:
			KillTimer(hWnd, TMR_1);
			wektor4.push_back({ 0 });
			kolejka_celu.push({ 400, 0 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON12:
			KillTimer(hWnd, TMR_1);
			wektor4.push_back({  100 });
			kolejka_celu.push({ 400, 100 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON13:
			KillTimer(hWnd, TMR_1);
			wektor4.push_back({  200 });
			kolejka_celu.push({ 400, 200 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON14:
			KillTimer(hWnd, TMR_1);
			wektor4.push_back({ 300 });
			kolejka_celu.push({ 400, 300 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
			//pietro 1
		case ID_BUTTON15:
			KillTimer(hWnd, TMR_1);
			wektor1.push_back({  0 });
			kolejka_celu.push({ 100, 0 });
			SetTimer(hWnd, TMR_1, 20, 0);
			
			break;
		case ID_BUTTON16:
			KillTimer(hWnd, TMR_1);
			wektor1.push_back({  200 });
			kolejka_celu.push({ 100, 200 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON17:
			KillTimer(hWnd, TMR_1);
			wektor1.push_back({  300 });
			kolejka_celu.push({ 100, 300 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON18:
			KillTimer(hWnd, TMR_1);
			wektor1.push_back({  400 });
			kolejka_celu.push({ 100, 400 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
			//pietro 3
		case ID_BUTTON19:
			KillTimer(hWnd, TMR_1);
			wektor3.push_back({  0 });
			kolejka_celu.push({ 300, 0 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON20:
			KillTimer(hWnd, TMR_1);
			wektor3.push_back({  100 });
			kolejka_celu.push({ 300, 100 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON21:
			KillTimer(hWnd, TMR_1);
			wektor3.push_back({  200 });
			kolejka_celu.push({ 300, 200 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		case ID_BUTTON22:
			KillTimer(hWnd, TMR_1);
			wektor3.push_back({ 400 });
			kolejka_celu.push({ 300, 400 });
			SetTimer(hWnd, TMR_1, 20, 0);
			break;
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
			
		MyOnPaint(hdc);
		LiftPaint(hdc);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &drawArea1);
			repaintWindow(hWnd, hdc, ps, &textRect);
		
			while (!kolejka_celu.empty())
			{
				if (value < kolejka_celu.front().wysokosc)
				{
					while (value < kolejka_celu.front().wysokosc)
					{
						SprawdzNaPietrze(value);
						value++;
						repaintWindow(hWnd, hdc, ps, &drawArea1);
						repaintWindow(hWnd, hdc, ps, &textRect);
					}
					
				}
				if (value > kolejka_celu.front().wysokosc)
				{
					while (value > kolejka_celu.front().wysokosc)
					{
						SprawdzNaPietrze(value);

						value--;

						repaintWindow(hWnd, hdc, ps, &drawArea1);
						repaintWindow(hWnd, hdc, ps, &textRect);
					}
					
				}
				if (value < kolejka_celu.front().cel)
				{
					while (value < kolejka_celu.front().cel)
					{
						SprawdzNaPietrze(value);

						value++;

						repaintWindow(hWnd, hdc, ps, &drawArea1);
						repaintWindow(hWnd, hdc, ps, &textRect);
					}
					
				}
				if (value > kolejka_celu.front().cel)
				{
					while (value > kolejka_celu.front().cel)
					{
						SprawdzNaPietrze(value);

						value--;

						repaintWindow(hWnd, hdc, ps, &drawArea1);
						repaintWindow(hWnd, hdc, ps, &textRect);
					}
					
				}
				
				Sleep(2000);
				kolejka_celu.pop();
				
				KillTimer(hWnd, TMR_1);
			}
			repaintWindow(hWnd, hdc, ps, &drawArea1);
			repaintWindow(hWnd, hdc, ps, &textRect);
		}
		
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
