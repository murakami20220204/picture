/* Copyright (C) 2026 Taichi Murakami. */
#include "stdafx.h"
#include "app.h"
#include "resource.h"
#define DEFPROC                 DefWindowProc((hWnd), (uMsg), (wParam), (lParam))
#define WS_HWNDCLIENT           (WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL)

/* ウィンドウのメモリ配置 */
typedef struct tagDOCUMENTWINDOWEXTRA
{
	DWORD_PTR hwndClient;
} WINDOWEXTRA;

#define GWLP_HWNDCLIENT         offsetof(WINDOWEXTRA, hwndClient)

static BOOL WINAPI OnCommand    (_In_ HWND hWnd, _In_ UINT uID);
static BOOL WINAPI OnCreate     (_In_ HWND hWnd, _In_ CONST CREATESTRUCT FAR *lpCreate);
static void WINAPI OnDestroy    (_In_ HWND hWnd);
static void WINAPI OnSize       (_In_ HWND hWnd, _In_ UINT uSize);
static HWND WINAPI CreateClient (_In_ HWND hWnd, _In_opt_ HINSTANCE hInstance);
static void WINAPI Layout       (_In_ HWND hWnd);
STATIC_ASSERT(sizeof(WINDOWEXTRA) == DOCUMENTWINDOWEXTRA);

/**
* ドキュメント ウィンドウ プロシージャです。
*/
LRESULT CALLBACK
DocumentWindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	LRESULT nResult;

	switch (uMsg)
	{
	case WM_COMMAND:
		nResult = OnCommand(hWnd, LOWORD(wParam));
		if (!nResult) nResult = DEFPROC;
		break;
	case WM_CREATE:
		nResult = OnCreate(hWnd, (LPCREATESTRUCT)lParam);
		if (!nResult) nResult = DEFPROC;
		break;
	case WM_DESTROY:
		OnDestroy(hWnd);
		nResult = DEFPROC;
		break;
	case WM_SIZE:
		OnSize(hWnd, LOWORD(wParam));
		nResult = 0;
		break;
	default:
		nResult = DEFPROC;
		break;
	}

	return nResult;
}

/**
* 指定したメニュー項目を実行します。
* @param uID メニュー項目。
* @result メッセージを処理した場合は 0 を返します。
*/
static BOOL WINAPI
OnCommand(_In_ HWND hWnd, _In_ UINT uID)
{
	BOOL bResult = FALSE;

	switch (uID)
	{
	case IDM_EXIT:
		SendMessage(hWnd, WM_CLOSE, 0, 0);
		break;
	default:
		bResult = TRUE;
		break;
	}

	return bResult;
}

/**
* コントロールを作成します。
* @param lpCreate 作成方法。
* @result メッセージを処理した場合は 0 を返します。
*/
static BOOL WINAPI
OnCreate(_In_ HWND hWnd, _In_ CONST CREATESTRUCT FAR *lpCreate)
{
	BOOL bResult;

	if (CheckWindowExtra(hWnd, sizeof(WINDOWEXTRA)) && CreateClient(hWnd, lpCreate->hInstance))
	{
		bResult = 0;
	}
	else
	{
		bResult = -1;
	}

	return bResult;
}

/**
* ウィンドウを破棄します。
*/
static void WINAPI
OnDestroy(_In_ HWND hWnd)
{
	PostQuitMessage(0);
}

/**
* コントロールを再配置します。
*/
static void WINAPI
OnSize(_In_ HWND hWnd, _In_ UINT uSize)
{
	if ((uSize == SIZE_RESTORED) || (uSize == SIZE_MAXIMIZED))
	{
		Layout(hWnd);
	}
}

/**
* 描画領域を作成します。
* @result 新しいウィンドウまたは NULL を返します。
*/
static HWND WINAPI
CreateClient(_In_ HWND hWnd, _In_opt_ HINSTANCE hInstance)
{
	HWND hWndClient;
	hWndClient = (HWND)GetWindowLongPtr(hWnd, GWLP_HWNDCLIENT);

	if (!hWndClient)
	{
		hWndClient = CreateWindowEx(WS_EX_CLIENTEDGE, CANVASCLASSNAME, NULL, WS_HWNDCLIENT, 0, 0, 0, 0, hWnd, NULL, hInstance, NULL);

		if (hWndClient)
		{
			SetWindowLongPtr(hWnd, GWLP_HWNDCLIENT, (LONG_PTR)hWndClient);
		}
	}

	return hWndClient;
}

/**
* コントロールを配置します。
*/
static void WINAPI
Layout(_In_ HWND hWnd)
{
	HWND hWndChild;
	RECT rcClient;

	if (GetClientRect(hWnd, &rcClient))
	{
		hWndChild = (HWND)GetWindowLongPtr(hWnd, GWLP_HWNDCLIENT);

		if (hWndChild)
		{
			MoveWindowForRect(hWndChild, &rcClient, TRUE);
		}
	}
}
