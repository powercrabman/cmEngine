#pragma once

class cmRenderTargetView
{
public:
	cmRenderTargetView() = default;
	virtual ~cmRenderTargetView() = default;

	void CreateFromSwapChain(IDXGISwapChain* inSwapChain);

	ID3D11RenderTargetView* GetRTV() const { return mRTV.Get(); }
	ID3D11RenderTargetView* const* GetRTVPtr() { return mRTV.GetAddressOf(); }

private:
	UComPtr<ID3D11RenderTargetView> mRTV = nullptr;
};

