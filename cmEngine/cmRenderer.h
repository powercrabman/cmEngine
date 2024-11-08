#pragma once

class cmGraphicsDevice;
class cmGUIRenderer;
class cmWindow;
class cmViewport;
class cmRenderTargetView;
class cmPipeline;
class cmMeshRenderer;
class cmGraphicsResourceManager;
class cmGameObject;

class cmRenderer
{
	ENGINE_MODULE_BODY();
public:
	~cmRenderer();

	void SetClearColor(const Color& inColor) { mClearColor = inColor; }

	cmGraphicsDevice*			GetGraphicsDevice() const { return mGraphicsDevice.get(); }
	cmGUIRenderer*				GetGUIRenderer() const { return mGUIRenderer.get(); }
	cmGraphicsResourceManager*	GetGraphicsResourceManager() const { return mGraphicsResourceManager.get(); }

	void OnResize(const ScreenSize& inScreenSize);

	void RegistGameObject(cmGameObject* inGameObject);
	void UnregistGameObject(cmGameObject* inGameObject);

	cmViewport* GetViewport() const { return mViewport.get(); }

private:
	void Initialize(cmWindow* inMainWindow);
	void CleanUp();
	cmRenderer();

	void RenderBegin();
	void Render();
	void RenderEnd();

private:
	std::unique_ptr<cmGraphicsDevice> mGraphicsDevice = nullptr;
	std::unique_ptr<cmGUIRenderer> mGUIRenderer = nullptr;
	std::unique_ptr<cmGraphicsResourceManager> mGraphicsResourceManager = nullptr;

	Color mClearColor = cmColors::Aquamarine;

	std::unique_ptr<cmViewport> mViewport = nullptr;
	std::unique_ptr<cmRenderTargetView> mRTV = nullptr;
	std::unique_ptr<cmPipeline> mPipeline = nullptr;

	//Mesh Renderer
	struct GameObjectData
	{
		uint64 Index = 0;
		cmGameObject* GameObject = nullptr;
	};
	std::unordered_map<uint64, GameObjectData> mRenderRepo = {};
	std::vector<cmGameObject*> mRenderList = {};
};
