#include "0. cmEngine/cmEngine.h"
#include "Renderer.h"
#include "6. Renderer/RenderTarget/RenderTarget.h"

namespace cmEngine
{
	Renderer::Renderer() = default;
	Renderer::~Renderer()
	{
		ConstantBufferPool::CleanUp();
		RenderStatePool::CleanUp();
	}

	void Renderer::RenderBegin() const
	{
		// InputLayout Setting TODO: 제거
		mDevice.Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		if (mSubRenderTarget)
		{
			// 멀티 뷰포트 지원
			mSubRenderTarget->Bind();
			mSubRenderTarget->ClearBuffer();
		}
		else
		{
			// 싱글 뷰포트
			mMasterRenderTarget->Bind();
		}

		mMasterRenderTarget->ClearBuffer();

		// Pipeline Clear
		mPipeline->Clear();
	}

	void Renderer::RenderEnd() const
	{
		// 멀티 뷰포트의 경우
		if (mSubRenderTarget)
		{
			mMasterRenderTarget->Bind();

			// 서브 뷰포트 TODO

		}
	}

	bool Renderer::OnResize(uint32 inWidth, uint32 inHeight)
	{
		HRESULT hr = {};

		// Render Target View Release
		GetContext()->Flush();
		GetContext()->OMSetRenderTargets(0, nullptr, nullptr);
		mMasterRenderTarget->ResetResource();

		// Swap Chain
		{
			if (mSwapChain)
			{

				if (!DX_CHECK(hr = mSwapChain->ResizeBuffers(2, inWidth, inHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0)))
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
				swapChainDesc.BufferCount = 2;
				swapChainDesc.BufferDesc.Width = inWidth;
				swapChainDesc.BufferDesc.Height = inHeight;
				swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
				swapChainDesc.OutputWindow = GameWindow::Ref().GetWindowHandle();
				swapChainDesc.SampleDesc.Count = 1;
				swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
				swapChainDesc.Windowed = TRUE;

				hr = mSubDevice.Factory->CreateSwapChain(mDevice.Device.Get(), &swapChainDesc, mSwapChain.GetAddressOf());
				if (!DX_CHECK(hr))
				{
					ASSERT(false, "Create SwapChain Fail.");
					return false;
				}
			}
		}

		mMasterRenderTarget->Resize(inWidth, inHeight);

		return true;
	}

	float Renderer::GetAspectRatio() const
	{
		if (mSubRenderTarget) { return mSubRenderTarget->GetAspectRatio(); }
		else { return mMasterRenderTarget->GetAspectRatio(); }
	}

	SubRenderTarget* Renderer::CreateSubRenderTarget(uint32 inWidth, uint32 inHeight)
	{
		mSubRenderTarget = MakeScope<SubRenderTarget>();
		mSubRenderTarget->Resize(inWidth, inHeight);
		return mSubRenderTarget.get();
	}

	void Renderer::Init(const WindowResolution& inRes)
	{
		HR hr = {};

		// Init Core Device
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
			}
		}

		// Init SubDevice
		{
			hr = CreateDXGIFactory1(__uuidof(IDXGIFactory), reinterpret_cast<void**>(mSubDevice.Factory.GetAddressOf()));
			if (!DX_CHECK(hr))
			{
				ASSERT(false, "Create Factory Fail.");
			}

			hr = mSubDevice.Factory->EnumAdapters(0, mSubDevice.Adapter.GetAddressOf());
			if (!DX_CHECK(hr))
			{
				ASSERT(false, "Create Adapter Fail.");
			}
		}

		// Init RenderTarget
		mMasterRenderTarget = MakeScope<MasterRenderTarget>();
		if (!OnResize(inRes.Width, inRes.Height))
		{
			ASSERT(false, "Creation of window dependencies failed.");
		}

		// Pipeline
		mPipeline = MakeScope<Pipeline>();

		// Preload RenderState
		RenderStatePool::Initialize();

		// Attach Event
		EventDispatcher::Ref().AttachEventHandler<WindowResizeEvent>([&](const WindowResizeEvent& e) { OnResize(e.windowWidth, e.windowHeight); });
		EventDispatcher::Ref().AttachEventHandler<AppShutdownEvent>([](const AppShutdownEvent& e) { Destroy(); });

		ENGINE_LOG_INFO("Renderer Init Done.");
	}
}
