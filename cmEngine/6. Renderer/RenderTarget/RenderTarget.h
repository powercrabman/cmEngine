#pragma once

namespace cmEngine
{
	class RenderTarget
	{
	public:
		RenderTarget() = default;
		virtual ~RenderTarget() = default;

		virtual void	Resize(uint32 inWidth, uint32 inHeight) = 0;

		auto			GetResolution() const { return std::make_pair(mViewport.Width, mViewport.Height); }
		float			GetAspectRatio() const { return mViewport.AspectRatio(); }

		void			ResetResource();
		void			ClearBuffer() const;
		void			Bind();

		::ComPtr<ID3D11ShaderResourceView>	GetShaderResourceView() const { return mSRV; }
		::ComPtr<ID3D11RenderTargetView>	GetRenderTargetView() const { return mRTV; }
		::ComPtr<ID3D11DepthStencilView>	GetDepthStencilView() const { return mDSV; }

	protected:
		::ComPtr<ID3D11ShaderResourceView>	mSRV;
		::ComPtr<ID3D11DepthStencilView>	mDSV;
		::ComPtr<ID3D11RenderTargetView>	mRTV;
		cmEngine::Viewport					mViewport;
		Color								mClearColor = Colors::Black;
	};


	inline void RenderTarget::ResetResource()
	{
		mSRV.Reset();
		mDSV.Reset();
		mRTV.Reset();
	}

	inline void RenderTarget::ClearBuffer() const
	{
		Renderer::Ref().GetContext()->ClearRenderTargetView(mRTV.Get(), mClearColor);
		Renderer::Ref().GetContext()->ClearDepthStencilView(mDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	}

	inline void RenderTarget::Bind()
	{
		Renderer::Ref().GetContext()->RSSetViewports(1, mViewport.GetViewport());
		Renderer::Ref().GetContext()->OMSetRenderTargets(1, mRTV.GetAddressOf(), mDSV.Get());
	}
}
