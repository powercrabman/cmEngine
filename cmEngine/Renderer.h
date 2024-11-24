#pragma once


namespace cmEngine
{
	class Pipeline;
	class RenderComponent;
	class GameEntity;
	class CameraComponent;

	struct RendererConfig : public JsonMetaData
	{
		Color clearColor;

		JSON_STRUCT_BODY(
			RendererConfig,
			clearColor
		)
	};

	class Renderer
	{
		friend class EngineCore;

		struct RenderCoreDevice;
		struct RenderSubDevice;
		struct RenderCanvas;
		struct MultiSamplingProp;

	public:
		static void		RenderBegin();
		static void		RenderEnd();

		static void		SetClearColor(const Color& inClearColor) { mCanvas.ClearColor = inClearColor; }
		static Color	GetClearColor() { return mCanvas.ClearColor; }

		static bool		OnResize(const WindowResolution& inRes);

		static ::ComPtr<ID3D11Device>			GetDevice() { return mDevice.Device; }
		static ::ComPtr<ID3D11DeviceContext>	GetContext() { return mDevice.Context; }

		static float	 GetAspectRatio() { return mCanvas.RenderViewport.AspectRatio(); }

		static Pipeline* GetPipeline() { return mPipeline.get(); }

		inline static const wchar_t* sConfigPath = L"EngineConfig.json";

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
			Viewport							RenderViewport;

			Color								ClearColor = Colors::Tomato;
		};

		struct MultiSamplingProp
		{
			enum { MSAA_SAMPLE_COUNT = 4 };

			uint32	SampleCount;
			uint32	Quality;
			bool	Enable;
		};

		inline static RenderCoreDevice	mDevice    = {};
		inline static RenderSubDevice	mSubDevice = {};
		inline static RenderCanvas		mCanvas    = {};

		inline static D3D_FEATURE_LEVEL	mFeatureLevel = {};
		inline static MultiSamplingProp mMSAA         = {};

		inline static Scope<Pipeline>	mPipeline     = nullptr;
	};
}