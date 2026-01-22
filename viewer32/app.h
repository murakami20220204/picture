/* Copyright (C) 2026 Taichi Murakami. */
#pragma once
#include "stdafx.h"
#define STATIC_ASSERT(x)        static_assert((x), #x)
#define CANVASCLASSNAME         TEXT("Canvas")
#define DOCUMENTCLASSNAME       TEXT("Viewer")
#ifdef _WIN64
#define CANVASWINDOWEXTRA       0
#define DOCUMENTWINDOWEXTRA     8
#else
#define CANVASWINDOWEXTRA       0
#define DOCUMENTWINDOWEXTRA     4
#endif

EXTERN_C BOOL WINAPI CheckWindowExtra  (_In_ HWND hWnd, _In_ DWORD cbWndExtra);
EXTERN_C BOOL WINAPI MoveWindowForRect (_In_ HWND hWnd, _In_ CONST RECT FAR *lpRect, _In_ BOOL bRepaint);
EXTERN_C BOOL WINAPI ShowError         (_In_opt_ HWND hWnd);
