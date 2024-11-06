#pragma once

class cmWindow;

class cmApplication
{
public:
	virtual ~cmApplication() = default;

	virtual void Setup(const ScreenSize& inScreenSize, const ScreenPos& inScreenPos = {100,100}) final;
	virtual void Run();

protected:
	cmApplication() = default;

	virtual void Initialize()	abstract;
	virtual void Update()		abstract;
	virtual void CleanUp()		abstract;

	virtual void UpdateCore()		final;
	virtual void CleanUpCore()		final;
};