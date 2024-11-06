#include "pch.h"
#include "cmAssert.h"

std::string GetErrorMessage(HRESULT hr)
{
	LPWSTR errorText = nullptr;

	FormatMessageW(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&errorText,
		0,
		nullptr);

	std::wstring errorMessage = L"Unknown error";
	if (errorText)
	{
		errorMessage = errorText;
		LocalFree(errorText);
	}

	// TEMP 고쳐야 함
	return std::string{ errorMessage.begin(), errorMessage.end() };
}
