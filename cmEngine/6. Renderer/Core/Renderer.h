#pragma once

namespace cmEngine
{
	class Pipeline;
	class RenderComponent;
	class GameEntity;
	class CameraComponent;
	class RenderTarget;
	class MasterRenderTarget;
	class SubRenderTarget;

	class Renderer
	{
		SINGLETON(Renderer);
		struct		RenderCoreDevice;
		struct		RenderSubDevice;
		struct		MultiSamplingProp;

	public:
		void		RenderBegin() const;
		void		RenderEnd() const;
		void		Present() const { mSwapChain->Present(0, 0); }

		bool		OnResize(uint32 inWidth, uint32 inHeight);
		float		GetAspectRatio() const;

		SubRenderTarget*				CreateSubRenderTarget(uint32 inWidth, uint32 inHeight);
		SubRenderTarget*				TryGetSubRenderTarget() const { return mSubRenderTarget.get(); };

		Pipeline*						GetPipeline() const { return mPipeline.get(); }
		::ComPtr<ID3D11Device>			GetDevice() { return mDevice.Device; }
		::ComPtr<ID3D11DeviceContext>	GetContext() { return mDevice.Context; }
		::ComPtr<IDXGISwapChain>		GetSwapChain() { return mSwapChain; }

		inline static const wchar_t* sConfigName = L"EngineConfig.json";

	private:
		Renderer();
		~Renderer();
		void		Init(const WindowResolution& inRes);

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

		RenderCoreDevice			mDevice       = {};
		RenderSubDevice				mSubDevice    = {};
		::ComPtr<IDXGISwapChain>	mSwapChain    = {};

		D3D_FEATURE_LEVEL			mFeatureLevel = {};

		Scope<SubRenderTarget>				mSubRenderTarget    = nullptr;
		Scope<MasterRenderTarget>			mMasterRenderTarget = nullptr;
		Scope<Pipeline>						mPipeline           = nullptr;
	};
}
