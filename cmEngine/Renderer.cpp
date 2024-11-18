#include "EnginePch.h"
#include "Renderer.h"
#include "Pipeline.h"
#include "GameEntity.h"
#include <fstream>

namespace cmEngine
{
	void Renderer::RenderBegin()
	{
		// InputLayout Setting
		mDevice.Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Clear Color
		mDevice.Context->ClearRenderTargetView(mCanvas.RenderTargetView.Get(), mCanvas.ClearColor);
		mDevice.Context->ClearDepthStencilView(mCanvas.DepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

		// Set Resterizer / Output Merget
		mDevice.Context->RSSetViewports(1, mCanvas.RenderViewport.GetViewport());
		mDevice.Context->OMSetRenderTargets(1, mCanvas.RenderTargetView.GetAddressOf(), mCanvas.DepthStencilView.Get());

		// Pipeline Clear
		mPipeline->Clear();
	}

	void Renderer::RenderEnd()
	{
		// Present
		mCanvas.SwapChain->Present(0, 0);
	}

	bool Renderer::OnResize(const WindowResolution& inRes)
	{
		HRESULT hr = {};

		// Swap Chain
		{
			if (mCanvas.SwapChain)
			{
				// Render Target View Release
				GetContext()->OMSetRenderTargets(0, nullptr, nullptr);
				mCanvas.DepthStencilView.Reset();
				mCanvas.RenderTargetView.Reset();

				hr = mCanvas.SwapChain->ResizeBuffers(0, inRes.Width, inRes.Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

				if (!DX_CHECK(hr))
				{
					OutputDebugString(L"ResizeBuffers failed with HRESULT: ");
					OutputDebugString(std::to_wstring(hr).c_str());
					ASSERT(false, "Resizing SwapChain Fail.");
					return false;
				}
			}
			else
			{
				// 없으면 생성
				DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
				swapChainDesc.BufferCount          = 2;
				swapChainDesc.BufferDesc.Width     = 0;
				swapChainDesc.BufferDesc.Height    = 0;
				swapChainDesc.BufferDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
				swapChainDesc.BufferUsage          = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.OutputWindow         = GameWindow::GetHwnd();
				swapChainDesc.SampleDesc.Count     = mMSAA.SampleCount;
				swapChainDesc.SampleDesc.Quality   = mMSAA.Quality;
				swapChainDesc.Windowed             = TRUE;

				HR hr = mSubDevice.Factory->CreateSwapChain(mDevice.Device.Get(), &swapChainDesc, mCanvas.SwapChain.GetAddressOf());
				if (!DX_CHECK(hr))
				{
					ASSERT(false, "Create SwapChain Fail.");
					return false;
				}
			}
		}

		// RenderTargetView
		{
			::ComPtr<ID3D11Buffer> buf = nullptr;
			HR hr = mCanvas.SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(buf.GetAddressOf()));

			if (!DX_CHECK(hr))
			{
				ASSERT(false, "Swapbuffer backbuffer Get fail.");
				return false;
			}

			hr = mDevice.Device->CreateRenderTargetView(buf.Get(), nullptr, mCanvas.RenderTargetView.GetAddressOf());

			if (!DX_CHECK(hr))
			{
				ASSERT(false, "Swapbuffer backbuffer Get fail.");
				return false;
			}
		}

		// Viewport
		{
			mCanvas.RenderViewport = Viewport{ GameWindow::GetWindowResolution() };
		}

		// DepthStencilView
		{
			D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
			dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			dsvDesc.Texture2D.MipSlice = 0;

			D3D11_TEXTURE2D_DESC textureDesc = {};
			textureDesc.Width = inRes.Width;
			textureDesc.Height = inRes.Height;
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			textureDesc.SampleDesc.Count = mMSAA.SampleCount;
			textureDesc.SampleDesc.Quality = mMSAA.Quality;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

			if (mMSAA.SampleCount > 1)
			{
				dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			}
			else
			{
				dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			}

			::ComPtr<ID3D11Texture2D> buf = nullptr;
			hr = mDevice.Device->CreateTexture2D(&textureDesc, nullptr, buf.GetAddressOf());

			if (!DX_CHECK(hr))
			{
				ASSERT(false, "DepthStencil Texture create fail.");
				return false;
			}

			hr = mDevice.Device->CreateDepthStencilView(buf.Get(), &dsvDesc, mCanvas.DepthStencilView.GetAddressOf());

			if (!DX_CHECK(hr))
			{
				ASSERT(false, "DepthStencilVIew create fail.");
				return false;
			}
		}

		return true;
	}

	void Renderer::Destroy()
	{
		// Save setting
		RendererConfig config = {};
		config.ClearColor = mCanvas.ClearColor;
		ConfigEngine::Save(config);

		mDevice.Context.Reset();
		mDevice.Device.Reset();

		mSubDevice.Adapter.Reset();
		mSubDevice.Debugger.Reset();
		mSubDevice.Factory.Reset();

		mCanvas.DepthStencilView.Reset();
		mCanvas.RenderTargetView.Reset();
		mCanvas.SwapChain.Reset();

		mPipeline.reset();
	}


	bool Renderer::Initialize()
	{
		HR hr = {};

		// Initialize Core Device
		{
			uint32 createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
			createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
			static D3D_FEATURE_LEVEL sFeatureLevels[] =
			{
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0
			};

			hr = D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_HARDWARE,
				nullptr,
				createDeviceFlags,
				sFeatureLevels,
				ARRAYSIZE(sFeatureLevels),
				D3D11_SDK_VERSION,
				mDevice.Device.GetAddressOf(),
				&mFeatureLevel,
				mDevice.Context.GetAddressOf()
			);
			if (!DX_CHECK(hr))
			{
				ASSERT(false, "Create Device Fail.");
				return false;
			}
		}

		// Initialize SubDevice
		{
			hr = CreateDXGIFactory1(__uuidof(IDXGIFactory), reinterpret_cast<void**>(mSubDevice.Factory.GetAddressOf()));
			if (!DX_CHECK(hr))
			{
				ASSERT(false, "Create Factory Fail.");
				return false;
			}

			hr = mSubDevice.Factory->EnumAdapters(0, mSubDevice.Adapter.GetAddressOf());
			if (!DX_CHECK(hr))
			{
				ASSERT(false, "Create Adapter Fail.");
				return false;
			}
		}

		// Initialize MSAA
		{
			static_assert(MultiSamplingProp::MSAA_SAMPLE_COUNT >= 1);

			mMSAA.Enable = true;
			mMSAA.SampleCount = MultiSamplingProp::MSAA_SAMPLE_COUNT;

			HRESULT hr = mDevice.Device->CheckMultisampleQualityLevels(
				DXGI_FORMAT_R8G8B8A8_UNORM,
				mMSAA.SampleCount,
				&mMSAA.Quality
			);

			if (FAILED(hr) || mMSAA.Quality == 0)
			{
				mMSAA.Enable = false;
				mMSAA.SampleCount = 1;
				mMSAA.Quality = 0;
				LOG_WARN("Requested MSAA level not supported. Falling back to no MSAA.");
			}
			else
			{
				mMSAA.Quality = mMSAA.Quality - 1;
			}
		}

		// Initialize RenderCanvas
		if (!OnResize(GameWindow::GetWindowResolution()))
		{
			ASSERT(false, "Creation of window dependencies failed.");
			return false;
		}

		// Pipeline
		mPipeline = MakeScope<Pipeline>();

		// Setting Load
		{
			RendererConfig config;
			if (ConfigEngine::Load(config))
			{
				mCanvas.ClearColor = config.ClearColor;
			}

		}

		ENGINE_LOG_INFO("Renderer Initialize Done.");

		return true;
	}

}
