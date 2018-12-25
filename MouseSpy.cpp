#include "stdafx.h"

namespace NMouseProc
{
	HHOOK g_mouseHook;

	LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam)
	{
		if (code >= 0)
		{
			MOUSEHOOKSTRUCT* pMouseStruct = (MOUSEHOOKSTRUCT*)lParam;
			if (pMouseStruct)
			{
				printf("mouse position: x=%d, y=%d\n", pMouseStruct->pt.x, pMouseStruct->pt.y);
			}
		}
		return CallNextHookEx(g_mouseHook, code, wParam, lParam);
	}
};

using namespace NMouseProc;

CMouseSpy& CMouseSpy::GetInstance()
{
	static CMouseSpy instance;
	return instance;
}

BOOL CMouseSpy::Run(HINSTANCE instance)
{
	if (!m_th.joinable())
	{
		std::thread th(&CMouseSpy::ThFunc, this, instance);
		m_th = std::move(th);

		return TRUE;
	}

	return FALSE;
}

void CMouseSpy::Stop()
{
	if (m_th.joinable())
	{
		PostThreadMessage(GetThreadId(m_th.native_handle()), WM_QUIT, 0, 0);
		m_th.join();
	}
}

void CMouseSpy::ThFunc(HINSTANCE instance)
{
	if (!MessageLoop(instance))
	{
		m_error = ::GetLastError();
	}
}

BOOL CMouseSpy::MessageLoop(HINSTANCE instance)
{
	g_mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, instance, 0);
	_S_API(g_mouseHook);

	MSG msg;
	BOOL retVal;
	
	while (retVal = GetMessage(&msg, 0, 0, 0))
	{
		if (retVal == -1)
		{
			return FALSE;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	_S_API(UnhookWindowsHookEx(g_mouseHook));

	return TRUE;
}