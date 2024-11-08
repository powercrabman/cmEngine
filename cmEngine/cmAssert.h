#pragma once


#define ABORT_MESSAGE(msg)                                            \
OutputDebugStringA("============== Occure Assert! ==============\n"); \
OutputDebugStringA(msg);                                              \
OutputDebugStringA("\n");                                             \
OutputDebugStringA("============================================\n");


// 나중에 로그 형태로 바꾸기
#ifdef _DEBUG
#define ASSERT(cond, hint)		                        \
if (!(cond))					                        \
{								                        \
    ABORT_MESSAGE(hint);                           \
    __debugbreak();                                            \
}
#else
#define ASSERT(cond, hint) (void)0
#endif

//HRESULT ERROR Translate
std::string GetErrorMessage(HRESULT hr);

#ifdef _DEBUG
#define DX_CHECK(cond, hint)														\
if (FAILED(cond))																	\
{																					\
    std::string errorMsg = GetErrorMessage(cond);									\
    std::string fullMsg = "DirectX Error: " + errorMsg + "\nHint: " + hint;		    \
    ABORT_MESSAGE(hint);                                                            \
    __debugbreak();																		\
}
#else
#define DX_CHECK(cond, hint) (void)0
#endif

