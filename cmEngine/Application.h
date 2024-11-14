#pragma once

namespace cmEngine
{
	class Application
	{
	public:
		virtual ~Application();

		virtual void Setup(const WindowResolution& inWindowResolution, const WindowPosition& inWindowPosition) final;
		virtual void Run();

	protected:
		Application();

		virtual void Initialize()	abstract;
		virtual void CleanUp()		abstract;

		virtual void UpdateCore()		final;
		virtual void CleanUpCore()		final;
	};
}

