#include "EnginePch.h"
#include "Texture.h"

namespace cmEngine
{

	void Texture::Load(std::wstring_view inFilePath)
	{
		HR hr = LoadFromWICFile(
			inFilePath.data(),
			WIC_FLAGS_NONE,
			&mMetaData,
			mImage,
			nullptr
		);

		if (!DX_CHECK(hr))
		{
			assert(false);
			ENGINE_LOG_ERROR("\"{}\" Load Success!", String::ConvertToString(inFilePath));
			return;
		}

		ENGINE_LOG_INFO("\"{}\" Load Success! ", String::ConvertToString(inFilePath));
	}

	void Texture::Save(std::wstring_view inFilePath, eTextureFormat inFormat)
	{
		HR hr = DirectX::SaveToWICFile(
			*mImage.GetImage(0, 0, 0),
			WIC_FLAGS_NONE,
			DirectX::GetWICCodec(static_cast<DirectX::WICCodecs>(inFormat)),
			inFilePath.data()
		);

		if (FAILED(hr))
		{
			assert(false);
			ENGINE_LOG_ERROR("Texture Save Fail.");
			return;
		}

		ENGINE_LOG_INFO("\"{}\" Save Success! ", String::ConvertToString(inFilePath));
	}

	void Texture::Create()
	{
		if (mImage.GetImages() == nullptr)
		{
			ASSERT(false, "Image is not loaded");
			LOG_ERROR("Image is not loaded");
			return;
		}

		::ComPtr<ID3D11Resource> res = nullptr;
		HR hr = DirectX::CreateTexture(
			Renderer::GetDevice().Get(),
			mImage.GetImages(),
			mImage.GetImageCount(),
			mMetaData,
			res.GetAddressOf()
		);

		if (FAILED(hr))
		{
			ASSERT(false, "Create Texture Fail.");
			LOG_ERROR("Create Texture Fail.");
			return;
		}

		hr = res.As(&mTex);

		if (FAILED(hr))
		{
			ASSERT(false, "Create Texture Fail.");
			LOG_ERROR("Create Texture Fail.");
			return;
		}

		hr = DirectX::CreateShaderResourceView(
			Renderer::GetDevice().Get(),
			mImage.GetImages(),
			mImage.GetImageCount(),
			mMetaData,
			mSRV.GetAddressOf()
		);

		if (FAILED(hr))
		{
			ASSERT(false, "Create Shader Resource View Fail.");
			LOG_ERROR("Create Shader Resource View Fail.");
			return;
		}
	}
}


// TODO : 나중에 포맷 변환 전 후로 성능 테스트 해보기
// 내부적으로 텍스처는 모두 DDS 형식 TODO
//hr = DirectX::Compress(
//	img.GetImages(),
//	img.GetImageCount(),
//	mMetaData,
//	DXGI_FORMAT_BC1_UNORM,
//	DirectX::TEX_COMPRESS_DEFAULT,
//	0.5f,
//	mImage);
// DX_ASSERT(hr, "DDS Compression Fail.");
