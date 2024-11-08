#pragma once

//=======================================================
// 그래픽 디바이스, 디바이스 컨텍스트(immediate),
// 팩토리, 어댑터 등을 초기화하고 관리
//=======================================================

class cmGraphicsDevice
{
	friend class cmRenderer;
public:
	virtual ~cmGraphicsDevice();

	void Initailize(HWND hwnd)
	{
		CreateAdapterAndFactory();
		CreateDeviceAndDC();
		EnableMSAA(MSAA_DEFAULT_SAMPLE_COUNT);
		CreateSwapChain(hwnd);

		isInitialzed = true;
	}

	void ResizeSwapChain(const ScreenSize& inScreensize)
	{
		mSwapChain->ResizeBuffers(0, inScreensize.Width, inScreensize.Height, DXGI_FORMAT_UNKNOWN, 0);
	}

	bool IsInitialized() const { return isInitialzed; }

	ID3D11Device* GetDevice() const { return mDevice.Get(); }
	ID3D11DeviceContext* GetContext() const { return mDC.Get(); }
	IDXGISwapChain* GetSwapChain() const { return mSwapChain.Get(); }

	void ClearUp()
	{
#if defined(DEBUG) || defined(_DEBUG)
		mDebug->ReportLiveDeviceObjects(D3D11_RLDO_SUMMARY | D3D11_RLDO_DETAIL | D3D11_RLDO_SUMMARY);
#endif
	}

private:
	cmGraphicsDevice();

	void CreateDeviceAndDC();
	void CreateAdapterAndFactory();

	void CreateSwapChain(HWND hWnd)
	{
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = 0;
		swapChainDesc.BufferDesc.Height = 0;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.SampleDesc.Count = mUseMSAA ? mMSAACount : 1;
		swapChainDesc.SampleDesc.Quality = mUseMSAA ? mMSAAQuality - 1 : 0;
		swapChainDesc.Windowed = TRUE;

		HRESULT hr = mFactory->CreateSwapChain(mDevice.Get(), &swapChainDesc, mSwapChain.GetAddressOf());
		DX_CHECK(hr, "Create Swapchain Fail.");
	}

	void EnableMSAA(uint32 sampleCount)
	{
		mUseMSAA = true;
		mMSAACount = sampleCount;

		HRESULT hr = mDevice->CheckMultisampleQualityLevels(
			DXGI_FORMAT_R8G8B8A8_UNORM,
			sampleCount,
			&mMSAAQuality
		);
		if (FAILED(hr) || mMSAAQuality <= 0)
		{
			mUseMSAA = false;
			mMSAACount = 1;
			mMSAAQuality = 0;
		}
	}

private:
	UComPtr<ID3D11Device> mDevice = nullptr;
	UComPtr<ID3D11DeviceContext> mDC = nullptr;
	UComPtr<IDXGISwapChain> mSwapChain = nullptr;
	UComPtr<IDXGIFactory> mFactory = nullptr;
	UComPtr<IDXGIAdapter> mAdapter = nullptr;
	UComPtr<ID3D11Debug> mDebug = nullptr;

	D3D_FEATURE_LEVEL mFeatureLevel = {};

	enum { MSAA_DEFAULT_SAMPLE_COUNT = 4 };
	bool mUseMSAA = false;
	uint32 mMSAACount = 4;
	uint32 mMSAAQuality = 0;

	bool isInitialzed = false;
};
