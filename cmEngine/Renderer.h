#pragma once


namespace cmEngine
{
	class Pipeline;
	class RenderComponent;
	class GameEntity;
	class CameraComponent;

	class Renderer
	{
		friend class EngineCore;

		struct RenderCoreDevice;
		struct RenderSubDevice;
		struct RenderCanvas;
		struct MultiSamplingProp;

	public:
		static void		RenderBegin();
		static void		Render();
		static void		RenderEnd();

		static void		SetClearColor(const Color& inClearColor) { mCanvas.ClearColor = inClearColor; }
		static Color	GetClearColor() { return mCanvas.ClearColor; }

		static bool		OnResize(const WindowResolution& inRes);

		static ::ComPtr<ID3D11Device>			GetDevice() { return mDevice.Device; }
		static ::ComPtr<ID3D11DeviceContext>	GetContext() { return mDevice.Context; }

		static void		RegisterRenderComponent(RenderComponent* inComp) { mRenderSystem.Push(inComp); };
		static void		UnregisterRenderComponent(RenderComponent* inComp) { mRenderSystem.Remove(inComp); };

		static float	GetAspectRatio() { return mCanvas.RenderViewport.AspectRatio(); }

		static void		RegisterCamera(CameraComponent* inCameraComponent) { mCameraSystem.MainCamera = inCameraComponent; };
		static void		UnregisterCamera(CameraComponent* inCameraComponent);
		static CameraComponent* GetCurrentCamera() { return mCameraSystem.MainCamera; }

	private:
		static bool Initialize();
		static void	Destroy();

		struct RenderCoreDevice
		{
			::ComPtr<ID3D11Device>			Device;
			::ComPtr<ID3D11DeviceContext>	Context;
		};

		struct RenderSubDevice
		{
			::ComPtr<IDXGIFactory>	Factory;
			::ComPtr<IDXGIAdapter>	Adapter;
			::ComPtr<ID3D11Debug>	Debugger;
		};

		struct RenderCanvas
		{
			::ComPtr<IDXGISwapChain>			SwapChain;
			::ComPtr<ID3D11RenderTargetView>	RenderTargetView;
			::ComPtr<ID3D11DepthStencilView>	DepthStencilView;
			cmEngine::Viewport					RenderViewport;

			Color								ClearColor = Colors::Tomato;
		};

		struct MultiSamplingProp
		{
			enum { MSAA_SAMPLE_COUNT = 4 };

			uint32	SampleCount;
			uint32	Quality;
			bool	Enable;
		};

		struct CameraSystem
		{
			Scope<GameEntity>	DefaultEntity = nullptr;
			CameraComponent* MainCamera       = nullptr;
		};

		inline static RenderCoreDevice	mDevice    = {};
		inline static RenderSubDevice	mSubDevice = {};
		inline static RenderCanvas		mCanvas    = {};

		inline static D3D_FEATURE_LEVEL	mFeatureLevel = {};
		inline static MultiSamplingProp mMSAA         = {};

		inline static Scope<Pipeline>				mPipeline     = nullptr;
		inline static BatchSystem<RenderComponent>	mRenderSystem = {};

		inline static CameraSystem		mCameraSystem = {};

		inline static constexpr wchar_t sSettingFilePath[] = L"RendererSetting.json";
	};
}