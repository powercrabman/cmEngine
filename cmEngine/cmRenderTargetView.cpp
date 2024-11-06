#include "pch.h"
#include "cmRenderTargetView.h"

void cmRenderTargetView::CreateFromSwapChain(IDXGISwapChain* inSwapChain)
{
	mRTV.Reset();

	UComPtr<ID3D11Buffer> buf = nullptr;
	HRESULT hr = inSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(buf.GetAddressOf()));
	DX_CHECK(hr, "Buffer Get Fail.");
	if (FAILED(hr)) { LOG_ERROR("Buffer Get Fail."); }

	Engine->GetRenderer()->GetGraphicsDevice()->GetDevice()->CreateRenderTargetView(buf.Get(), nullptr, mRTV.GetAddressOf());
}
