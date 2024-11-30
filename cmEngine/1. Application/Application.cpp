#include "0. cmEngine/cmEngine.h"
#include "Application.h"


namespace cmEngine
{
	Application::Application()
	{
		::CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	}

	Application::~Application()
	{
		::CoUninitialize();
	}

	void Application::Setup(const ApplicationProp& inWindowProp)
	{
		EngineCore::Ref().Init(inWindowProp);
		Init();
	}

	int Application::Run()
	{
		return EngineCore::Ref().Run();
	}
}
