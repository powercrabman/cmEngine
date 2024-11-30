#pragma once

namespace cmEngine
{
	struct ApplicationProp
	{
		WindowResolution	windowResolution;
		WindowPosition		windowPosition;
		const wchar_t*		titleName;
	};

	class Application
	{
	public:
		virtual			~Application();

		virtual void	Setup(const ApplicationProp& inWindowProp) final;
		virtual int		Run() final;

	protected:
		Application();

		virtual void	Init()	    = 0;
	};
}

