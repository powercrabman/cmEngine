#include "0. cmEngine/cmEngine.h"
#include "SubRenderTarget.h"

cmEngine::SubRenderTarget::SubRenderTarget() = default;
cmEngine::SubRenderTarget::~SubRenderTarget() = default;

void cmEngine::SubRenderTarget::Resize(uint32 inWidth, uint32 inHeight)
{
	auto d = Renderer::Ref().GetDevice();
	HR hr = {};

	//RTV
	D3D11_TEXTURE2D_DESC textureDesc = {};
	textureDesc.Width                = inWidth;
	textureDesc.Height               = inHeight;
	textureDesc.MipLevels            = 1;
	textureDesc.ArraySize            = 1;
	textureDesc.Format               = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count     = 1;
	textureDesc.Usage                = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags            = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

	::ComPtr<ID3D11Texture2D> tex = nullptr;
	hr = d->CreateTexture2D(&textureDesc, nullptr, tex.GetAddressOf());
	if (FAILED(hr))
	{
		assert(false);
		return;
	}

	hr = d->CreateRenderTargetView(tex.Get(), nullptr, mRTV.GetAddressOf());
	if (FAILED(hr))
	{
		assert(false);
		return;
	}

	// SRV
	hr = d->CreateShaderResourceView(tex.Get(), nullptr, mSRV.GetAddressOf());
	if (FAILED(hr))
	{
		assert(false);
		return;
	}

	// DSV
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width                = inWidth;
	depthStencilDesc.Height               = inHeight;
	depthStencilDesc.MipLevels            = 1;
	depthStencilDesc.ArraySize            = 1;
	depthStencilDesc.Format               = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Quality   = 0;
	depthStencilDesc.SampleDesc.Count     = 1;
	depthStencilDesc.Usage                = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags            = D3D11_BIND_DEPTH_STENCIL;

	::ComPtr<ID3D11Texture2D> depthStencil;
	hr = Renderer::Ref().GetDevice()->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf());
	if (FAILED(hr))
		ASSERT(false, "Failed to create Depth Stencil");

	hr = Renderer::Ref().GetDevice()->CreateDepthStencilView(depthStencil.Get(), nullptr, mDSV.GetAddressOf());
	if (FAILED(hr))
		ASSERT(false, "Failed to create Depth Stencil View");

	// Viewport ¼³Á¤
	mViewport.X = 0;
	mViewport.Y = 0;
	mViewport.Width = static_cast<float>(inWidth);
	mViewport.Height = static_cast<float>(inHeight);
	mViewport.MinDepth = 0.0f;
	mViewport.MaxDepth = 1.0f;
}