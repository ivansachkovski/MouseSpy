#include "stdafx.h"

int main()
{
	CMouseSpy& spy = CMouseSpy::GetInstance();
	spy.Run(GetModuleHandle(NULL));

	Sleep(100000);
	spy.Stop();

	return 0;
}