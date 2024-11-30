#include "0. cmEngine/cmEngine.h"
#include "MasterRenderTarget.h"

cmEngine::MasterRenderTarget::MasterRenderTarget() = default;
cmEngine::MasterRenderTarget::~MasterRenderTarget() = default;

void cmEngine::MasterRenderTarget::Resize(uint32 inWidth, uint32 inHeight)
{
	HR hr = {};

	// RTV
	::ComPtr<ID3D11Texture2D> backBuffer;
	hr = Renderer::Ref().GetSwapChain()->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
	if (FAILED(hr))
	{
		ASSERT(false, "Failed to get Swap Chain back buffer");
	}

	hr = Renderer::Ref().GetDevice()->CreateRenderTargetView(backBuffer.Get(), nullptr, mRTV.GetAddressOf());
	if (FAILED(hr))
	{
		ASSERT(false, "Failed to create Render Target Veiw.");
	}

	// SRV
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;

	hr = Renderer::Ref().GetDevice()->CreateShaderResourceView(backBuffer.Get(), &srvDesc, mSRV.GetAddressOf());
	if (FAILED(hr))
	{
		ASSERT(false, "Failed to create Shader Resource View for Swap Chain back buffer");
	}

	// DSV
	D3D11_TEXTURE2D_DESC depthStencilDesc = {};
	depthStencilDesc.Width = inWidth;
	depthStencilDesc.Height = inHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

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

