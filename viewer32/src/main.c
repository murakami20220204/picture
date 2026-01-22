/* Copyright (C) 2026 Taichi Murakami. */
#include "stdafx.h"
#include "app.h"
#include "resource.h"

extern LRESULT CALLBACK CanvasWindowProc      (_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
extern LRESULT CALLBACK DocumentWindowProc    (_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
static HWND    WINAPI   CreateDocumentWindow  (_In_opt_ HINSTANCE hInstance);
static ATOM    WINAPI   RegisterCanvasClass   (_In_opt_ HINSTANCE hInstance);
static ATOM    WINAPI   RegisterDocumentClass (_In_opt_ HINSTANCE hInstance);

/**
* アプリケーションのメイン エントリ ポイントです。
*/
int WINAPI
wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInst, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	HACCEL hAccel;
	HWND hWnd;
	MSG msg;
	BOOL bResult = -1;

	if (RegisterDocumentClass(hInstance) && RegisterCanvasClass(hInstance))
	{
		hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MAIN));

		if (hAccel)
		{
			hWnd = CreateDocumentWindow(hInstance);

			if (hWnd)
			{
				ShowWindow(hWnd, nCmdShow);
				UpdateWindow(hWnd);

				while (TRUE)
				{
					bResult = GetMessage(&msg, NULL, 0, 0);

					if (bResult <= 0)
					{
						break;
					}
					else if (!TranslateAccelerator (hWnd, hAccel, &msg))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
			}

			DestroyAcceleratorTable(hAccel);
		}
	}

	_CrtDumpMemoryLeaks();
	return bResult;
}

/**
* ドキュメント ウィンドウを作成します。
* @result 新しいウィンドウまたは NULL を返します。
*/
static HWND WINAPI
CreateDocumentWindow(_In_opt_ HINSTANCE hInstance)
{
	TCHAR strName[16];
	LoadString(hInstance, IDS_PRODUCTNAME, strName, ARRAYSIZE(strName));
	return CreateWindow(DOCUMENTCLASSNAME, strName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
}

/**
* 描画領域ウィンドウ クラスを登録します。
* @result 操作が成功した場合は 0 以外を返します。
*/
static ATOM WINAPI
RegisterCanvasClass(_In_opt_ HINSTANCE hInstance)
{
	const WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),
		CS_VREDRAW | CS_HREDRAW,
		CanvasWindowProc,
		0,
		CANVASWINDOWEXTRA,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE + 1),
		NULL,
		CANVASCLASSNAME,
	};

	return RegisterClassEx(&wc);
}

/**
* ドキュメント ウィンドウ クラスを登録します。
* @result 操作が成功した場合は 0 以外を返します。
*/
static ATOM WINAPI
RegisterDocumentClass(_In_opt_ HINSTANCE hInstance)
{
	const WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),
		CS_VREDRAW | CS_HREDRAW,
		DocumentWindowProc,
		0,
		DOCUMENTWINDOWEXTRA,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_3DFACE + 1),
		MAKEINTRESOURCE(IDR_MAIN),
		DOCUMENTCLASSNAME,
	};

	return RegisterClassEx(&wc);
}
