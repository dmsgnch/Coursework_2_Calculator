#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


#pragma warning(suppress : 4996)

#include "Functions.h"
#include "resource.h"



static TCHAR szWindowClass[] = L"win32app";
static TCHAR szTitle[] = L"Калькулятор";
char buf[256];

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Главная часть программы-------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 11);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Помилка реєстрації класу!", L"Калькулятор", NULL);
		return 0;
	}
	// ------------------------------------------------------------------------------------------------------------

	// Создаём окно---------------------------------------------------------------------------------------
	hInst = hInstance;

	int width = 400, height = 250; //Для размещения окна по центру экрана

	HWND hWnd = CreateWindow(
		szWindowClass,                // Имя класса                   
		szTitle, // Текст заголовка
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,        // Стиль окна                                             
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,                  // Позиция левого верхнего угла  
		width, height,                  // Ширина и высота окна    
		(HWND)NULL,                // Указатель на родительское окно NULL    
		(HMENU)NULL,               // Используется меню класса окна              
		(HINSTANCE)hInstance,       // Указатель на текущее приложение
		NULL);                  // Передается в качестве lParam в событие WM_CREATE

	if (!hWnd)
	{
		MessageBox(NULL,
			L"Call to CreateWindow failed!",
			L"Win32 Guided Tour",
			0);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	std::string temp = "";


	switch (message)
	{
	case WM_CREATE:
		static HWND hButton[31], hEdit[2], hListBox, hStatic;

		hEdit[0] = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL, 10, 5, 366, 20, hWnd, (HMENU)ID_EDIT, hInst, 0);
		hEdit[1] = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_READONLY, 170, 30, 206, 20, hWnd, (HMENU)ID_EDIT_1, hInst, 0);
		hButton[0] = CreateWindow(L"Button", L"0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 170, 40, 30, hWnd, (HMENU)ID_BUTTON, hInst, 0);
		hButton[1] = CreateWindow(L"Button", L"1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 135, 40, 30, hWnd, (HMENU)ID_BUTTON_1, hInst, 0);
		hButton[2] = CreateWindow(L"Button", L"2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 135, 40, 30, hWnd, (HMENU)ID_BUTTON_2, hInst, 0);
		hButton[3] = CreateWindow(L"Button", L"3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 135, 40, 30, hWnd, (HMENU)ID_BUTTON_3, hInst, 0);
		hButton[4] = CreateWindow(L"Button", L"4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 100, 40, 30, hWnd, (HMENU)ID_BUTTON_4, hInst, 0);
		hButton[5] = CreateWindow(L"Button", L"5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 100, 40, 30, hWnd, (HMENU)ID_BUTTON_5, hInst, 0);
		hButton[6] = CreateWindow(L"Button", L"6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 100, 40, 30, hWnd, (HMENU)ID_BUTTON_6, hInst, 0);
		hButton[7] = CreateWindow(L"Button", L"7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 65, 40, 30, hWnd, (HMENU)ID_BUTTON_7, hInst, 0);
		hButton[8] = CreateWindow(L"Button", L"8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 65, 40, 30, hWnd, (HMENU)ID_BUTTON_8, hInst, 0);
		hButton[9] = CreateWindow(L"Button", L"9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 65, 40, 30, hWnd, (HMENU)ID_BUTTON_9, hInst, 0);
		hButton[10] = CreateWindow(L"Button", L"+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 100, 43, 30, hWnd, (HMENU)ID_BUTTON_ADD, hInst, 0);
		hButton[11] = CreateWindow(L"Button", L"-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 196, 100, 43, 30, hWnd, (HMENU)ID_BUTTON_SUB, hInst, 0);
		hButton[12] = CreateWindow(L"Button", L"*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 135, 43, 30, hWnd, (HMENU)ID_BUTTON_MUL, hInst, 0);
		hButton[13] = CreateWindow(L"Button", L"/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 196, 135, 43, 30, hWnd, (HMENU)ID_BUTTON_DIV, hInst, 0);
		hButton[14] = CreateWindow(L"Button", L"=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 100, 170, 40, 30, hWnd, (HMENU)ID_BUTTON_RES, hInst, 0);
		hButton[15] = CreateWindow(L"Button", L"C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 30, 40, 30, hWnd, (HMENU)ID_BUTTON_C, hInst, 0);
		hButton[16] = CreateWindow(L"Button", L"sqrt", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 334, 135, 43, 30, hWnd, (HMENU)ID_BUTTON_SQRT, hInst, 0);
		hButton[17] = CreateWindow(L"Button", L"x^y", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 334, 170, 43, 30, hWnd, (HMENU)ID_BUTTON_EXP, hInst, 0);
		hButton[18] = CreateWindow(L"Button", L",", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 55, 170, 40, 30, hWnd, (HMENU)ID_BUTTON_COMMA, hInst, 0);
		hButton[19] = CreateWindow(L"Button", L"sin", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 242, 65, 43, 30, hWnd, (HMENU)ID_BUTTON_SIN, hInst, 0);
		hButton[20] = CreateWindow(L"Button", L"cos", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 242, 100, 43, 30, hWnd, (HMENU)ID_BUTTON_COS, hInst, 0);
		hButton[21] = CreateWindow(L"Button", L"tg", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 242, 135, 43, 30, hWnd, (HMENU)ID_BUTTON_TAN, hInst, 0);
		hButton[22] = CreateWindow(L"Button", L"ctg", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 242, 170, 43, 30, hWnd, (HMENU)ID_BUTTON_COT, hInst, 0);
		hButton[23] = CreateWindow(L"Button", L"abs", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 288, 65, 43, 30, hWnd, (HMENU)ID_BUTTON_ABS, hInst, 0);
		hButton[24] = CreateWindow(L"Button", L"Pi", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 288, 100, 43, 30, hWnd, (HMENU)ID_BUTTON_Pi, hInst, 0);
		hButton[25] = CreateWindow(L"Button", L"e", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 288, 135, 43, 30, hWnd, (HMENU)ID_BUTTON_E, hInst, 0);
		hButton[26] = CreateWindow(L"Button", L"ln", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 334, 65, 43, 30, hWnd, (HMENU)ID_BUTTON_LN, hInst, 0);
		hButton[27] = CreateWindow(L"Button", L"log", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 334, 100, 43, 30, hWnd, (HMENU)ID_BUTTON_LOG, hInst, 0);
		hButton[28] = CreateWindow(L"Button", L"<---", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 65, 89, 30, hWnd, (HMENU)ID_BUTTON_BACK, hInst, 0);
		hStatic = CreateWindow(L"static", L"Результат:", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 90, 32, 75, 30, hWnd, (HMENU)ID_BUTTON_RESULT, hInst, 0);
		hButton[29] = CreateWindow(L"Button", L"(", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 150, 170, 43, 30, hWnd, (HMENU)ID_BUTTON_LEFT_PAR, hInst, 0);
		hButton[30] = CreateWindow(L"Button", L")", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 196, 170, 43, 30, hWnd, (HMENU)ID_BUTTON_RIGHT_PAR, hInst, 0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_BUTTON:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "0";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_1:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "1";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_2:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "2";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_3:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "3";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_4:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "4";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_5:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "5";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_6:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "6";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_7:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "7";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_8:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "8";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_9:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "9";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_ADD:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += " + ";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_SUB:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += " - ";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_MUL:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += " * ";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_DIV:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += " / ";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_SQRT:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "sqrt(";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_EXP:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "^(";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_COMMA:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += ",";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_SIN:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "sin(";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_COS:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "cos(";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_TAN:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "tg(";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_COT:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "ctg(";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_ABS:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "||";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_Pi:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "Pi";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_E:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "e";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_LN:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "ln(";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_LOG:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "log(";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_BACK:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			if (temp.size() > 0) {
				temp.resize(temp.size() - 1);
			}
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_LEFT_PAR:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += "(";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_RIGHT_PAR:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp += ")";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;

		case ID_BUTTON_RES:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			if (temp.size() > 0) {
				strcpy_s(buf, Calculate(temp).c_str());
				SetWindowTextA(hEdit[1], buf);
			}
			break;

		case ID_BUTTON_C:
			GetWindowTextA(hEdit[0], buf, sizeof(buf));
			temp = buf;
			temp = "";
			strcpy_s(buf, temp.c_str());
			SetWindowTextA(hEdit[0], buf);
			break;
		default:
			return ERROR;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}