/* Copyright (C) 2026 Taichi Murakami. */
#include "stdafx.h"
#include "app.h"
#define FMTMSGFLAGS             (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM)

/**
* メッセージ ボックスを表示します。
* 最後のエラーを説明する文字列を表示します。
* @param hWnd メッセージ ボックスの親ウィンドウ。
*/
BOOL WINAPI
CheckWindowExtra(_In_ HWND hWnd, _In_ DWORD cbWndExtra)
{
	const BOOL bResult = cbWndExtra <= GetClassLong(hWnd, GCL_CBWNDEXTRA);
	if (!bResult) SetLastError(ERROR_NOT_ENOUGH_MEMORY);
	return bResult;
}

/**
* 指定したウィンドウを移動します。
* @param hWnd 移動するウィンドウ。
* @param lpRect 移動するウィンドウの大きさ。
*/
BOOL WINAPI
MoveWindowForRect(_In_ HWND hWnd, _In_ CONST RECT FAR *lpRect, _In_ BOOL bRepaint)
{
	const LONG X = lpRect->left;
	const LONG Y = lpRect->top;
	const LONG nWidth = lpRect->right - X;
	const LONG nHeight = lpRect->bottom - Y;
	return MoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
}

/**
* メッセージ ボックスを表示します。
* 最後のエラーを説明する文字列を表示します。
* @param hWnd メッセージ ボックスの親ウィンドウ。
*/
BOOL WINAPI
ShowError(_In_opt_ HWND hWnd)
{
	LPTSTR lpBuffer = NULL;
	DWORD dwResult;
	dwResult = GetLastError();
	dwResult = FormatMessage(FMTMSGFLAGS, NULL, dwResult, 0, (LPTSTR)&lpBuffer, 0, NULL);

	if (dwResult)
	{
		MessageBox(hWnd, lpBuffer, NULL, MB_ICONERROR);
	}

	LocalFree(lpBuffer);
	return dwResult;
}
