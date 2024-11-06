#include "pch.h"
#include "cmGraphicsDevice.h"

cmGraphicsDevice::cmGraphicsDevice() = default;

void cmGraphicsDevice::CreateDeviceAndDC()
{
	uint32 createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	HRESULT hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		featureLevels,
		ARRAYSIZE(featureLevels),
		D3D11_SDK_VERSION,
		mDevice.GetAddressOf(),
		&mFeatureLevel,
		mDC.GetAddressOf()
	);

	DX_CHECK(hr, "Create Device Fail.");
}
void cmGraphicsDevice::CreateAdapterAndFactory()
{
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory), reinterpret_cast<void**>(mFactory.GetAddressOf()));
	DX_CHECK(hr, "Create Factory Fail.");

	hr = mFactory->EnumAdapters(0, mAdapter.GetAddressOf());
	DX_CHECK(hr, "Create Adapter Fail.");
}
cmGraphicsDevice::~cmGraphicsDevice() = default;
