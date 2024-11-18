#pragma once

namespace cmEngine
{
	class Application
	{
	public:
		virtual ~Application();

		virtual void	Setup(const WindowResolution& inWindowResolution, const WindowPosition& inWindowPosition) final;
		virtual int		Run();

	protected:
		Application();

		virtual void Initialize()	= 0;
		virtual void CleanUp()		= 0;

		virtual void UpdateCore()		final;
		virtual void CleanUpCore()		final;
	};
}

