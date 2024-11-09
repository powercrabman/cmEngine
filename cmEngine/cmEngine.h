#pragma once

class cmWindowsManager;
class cmRenderer;
class cmConsole;
class cmLogger;
class cmDebugger;
class cmTimer;
class cmResourceManager;
class cmSceneManager;
class cmIKeyboard;

class cmEngine
{
	friend class cmApplication;
public:
	virtual ~cmEngine();
	static cmEngine* GetOrCreate();

	cmEngine(const cmEngine&) = delete;
	cmEngine& operator=(const cmEngine&) = delete;

	void CloseGame() { mRunning = false; }
	bool IsRunning() const { return mRunning; }
	bool IsInitialized() const { return mInitalized; }

	cmWindowsManager*	GetWindowsManager() const { return mWindowsManager.get(); }
	cmRenderer*			GetRenderer() const { return mRenderer.get(); }
	cmConsole*			GetConsole() const { return mConsole.get(); }
	cmLogger*			GetLogger() const { return mLogger.get(); }
	cmTimer*			GetTimer() const { return mTimer.get(); }
	cmResourceManager*	GetResourceManager() const { return mResourceManager.get(); }
	cmSceneManager*		GetSceneManager() const { return mSceneManager.get(); }
	cmIKeyboard*		GetKeyboard() const { return mKeyboard.get(); }

private:
	void Initialize() const;
	void FinalInitialize();
	void LoadCommonResources() const;

	void Destory() { delete sInst; sInst = nullptr; }

	cmEngine();

private:
	std::unique_ptr<cmWindowsManager> mWindowsManager = nullptr;
	std::unique_ptr<cmRenderer> mRenderer = nullptr;
	std::unique_ptr<cmConsole> mConsole = nullptr;
	std::unique_ptr<cmLogger> mLogger = nullptr;
	std::unique_ptr<cmTimer> mTimer = nullptr;
	std::unique_ptr<cmResourceManager> mResourceManager = nullptr;
	std::unique_ptr<cmSceneManager> mSceneManager = nullptr;
	std::unique_ptr<cmIKeyboard> mKeyboard = nullptr;

	bool mRunning = true;
	bool mInitalized = false;

	inline static cmEngine* sInst = nullptr;
};

extern cmEngine* Engine;

inline cmEngine* cmEngine::GetOrCreate()
{
	if (sInst == nullptr)
	{
		sInst = new cmEngine;
	}

	return sInst;
}