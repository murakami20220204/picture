/* Copyright (C) 2026 Taichi Murakami. */
#include "stdafx.h"
#include "app.h"
#define DEFPROC                 DefWindowProc((hWnd), (uMsg), (wParam), (lParam))

/**
* 描画領域ウィンドウ プロシージャです。
*/
LRESULT CALLBACK
CanvasWindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	return DEFPROC;
}
