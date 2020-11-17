#include "stdafx.h"
#include "mainGame.h"
//#include "mapTool.h"
//#include "switcher.h"
mutex mlock;
HINSTANCE _hInstance;	//APP �޽��� ��ȣ
HWND	_hWnd;			//APP ���� ��ȣ
//LPTSTR _lpszClass = LPTSTR("Window Class Name");		//������ Ŭ���� �̸�   ?�갡 ���ϴ¾ִ���?

POINT _ptMouse;
BOOL _leftMouseButton = FALSE;
gameNode* _mg = new mainGame;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//������ ���ν��� �� �Լ� ������ Ÿ��

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG message;			//������ �޽��� ����ü
	WNDCLASS wndClass;		//������ ���� ����ü

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸� ����
	wndClass.cbWndExtra = 0;										//������ ���� �޸� ����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//������ ��׶��� Į��
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ�� ���
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������ ���
	wndClass.hInstance = hInstance;									//������ �ν��Ͻ� ��ȣ
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;								//������ Ŭ�����̸�
	wndClass.lpszMenuName = NULL;									//������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ â ��Ÿ��

	RegisterClass(&wndClass);			//������ ���� ���

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW,			//������ â ��Ÿ��
		WINSTARTX,						//������ ������ǥ X
		WINSTARTY,						//������ ������ǥ Y
		WINSIZEX,						//������ â ����ũ��(width)
		WINSIZEY,						//������ â ����ũ��(height)
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	setWindowsSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	ShowWindow(_hWnd, cmdShow);		//������ â ȭ�鿡 �����

	if (FAILED(_mg->init()))
	{
		return 0;
	}

	//�޽��� ����
	//GetMessage : ������ �޽����� �߻��ϸ� �׶� ó���Ѵ�
	//PeekMessage : �޽����� ������ �ȿ��� ��� �����ִ�.
	
	/*
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);		//Ű���� �� ���콺 Ŭ�� �� �Է¿� �ش��ϴ� ���� �޽��� ó�� ���
		DispatchMessage(&message);		//���� �߻��� �޽����� ������� ���� ���
	}
	*/
	
	//���ӿ� Ÿ�̸�
	while ( true )
	{
		if ( PeekMessage(&message, NULL, 0, 0, PM_REMOVE) )
		{
			if ( message.message == WM_QUIT ) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}
	

	_mg->release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

//Ŭ���̾�Ʈ ���� ������ �Լ�
void setWindowsSize(int x, int y, int width, int height)
{
	//������ ��Ʈ
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;
	
	AdjustWindowRect(&winRect, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y, (winRect.right - winRect.left),
		(winRect.bottom - winRect.top), SWP_NOZORDER | SWP_NOMOVE);

}