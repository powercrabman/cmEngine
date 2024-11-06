#include "pch.h"
#include "cmViewport.h"
#include "cmWindow.h"

cmViewport::cmViewport(cmWindow* inWindow)
	: cmViewport(inWindow->GetScreenSize())
{
}

void cmViewport::SetFrom(cmWindow* inWindow)
{
	SetFrom(inWindow->GetScreenSize());
}
