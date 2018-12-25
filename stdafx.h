// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#include "targetver.h"


#include <Windows.h>
#include <stdio.h>
#include <thread>
#include <atomic>
#include <tchar.h>

// TODO: reference additional headers your program requires here

#define _S_API(exp) if (!(exp)) { return FALSE; }

#include "MouseSpy.h"