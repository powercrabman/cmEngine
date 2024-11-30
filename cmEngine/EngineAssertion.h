#pragma once

#ifdef _DEBUG
#define ASSERT(cond) if (!(cond)) {__debugbreak();}
#else
#define ASSERT(cond, hint) (void)0
#endif

#ifdef _DEBUG
#define DX_ASSERT(cond)	if (FAILED(cond)) {__debugbreak();}
#else
#define DX_CHECK(cond, hint) (void)0
#endif

#define DX_CHECK(hr) SUCCEEDED(hr)