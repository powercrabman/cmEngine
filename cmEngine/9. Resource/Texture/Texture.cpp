#include "0. cmEngine/cmEngine.h"
#include "Texture.h"

namespace cmEngine
{
	void Texture::LoadTextureImage(std::wstring_view inFilePath)
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
			ENGINE_LOG_ERROR("\"{}\" LoadTextureImage Fail.", String::ConvertToString(inFilePath));
			return;
		}

		mImagePath = inFilePath;
		Create();
		ENGINE_LOG_INFO("\"{}\" LoadTextureImage Success! ", String::ConvertToString(inFilePath));
	}

	void Texture::SaveTextureImage(std::wstring_view inFilePath, eTextureFormat inFormat) const
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
			ENGINE_LOG_ERROR("texture SaveTextureImage Fail.");
			return;
		}

		ENGINE_LOG_INFO("\"{}\" SaveTextureImage Success! ", String::ConvertToString(inFilePath));
	}

	void Texture::Create()
	{
		if (mImage.GetImages() == nullptr || mImage.GetImageCount() == 0)
		{
			ASSERT(false, "Image data is invalid");
			LOG_ERROR("Image data is invalid");
			return;
		}

		::ComPtr<ID3D11Resource> res = nullptr;
		HR hr = DirectX::CreateTexture(
			Renderer::Ref().GetDevice().Get(),
			mImage.GetImages(),
			mImage.GetImageCount(),
			mMetaData,
			res.GetAddressOf()
		);

		if (FAILED(hr))
		{
			ASSERT(false, "Create texture Fail.");
			LOG_ERROR("Create texture Fail.");
			return;
		}

		hr = res.As(&mTex);

		if (FAILED(hr))
		{
			ASSERT(false, "Create texture Fail.");
			LOG_ERROR("Create texture Fail.");
			return;
		}

		hr = DirectX::CreateShaderResourceView(
			Renderer::Ref().GetDevice().Get(),
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

	void Texture::SaveJsonToFile(const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory)
	{
		TextureJson js  = {};
		js.resourceType = GetResourceType();
		js.textureName  = GetName();
		js.imagePath    = String::ConvertToString(mImagePath);
		JsonSerializer::Ref().SerializeToFile(js, inFileName, inDirectory);
	}

	bool Texture::LoadJsonFromFile(const std::filesystem::path& inFilePath, const std::filesystem::path& inDirectory)
	{
		TextureJson js = {};
		if (JsonSerializer::Ref().DeserializerFromFile(js, inFilePath, inDirectory))
		{
			mName = js.textureName;
			LoadTextureImage(String::ConvertToWString(js.imagePath));

			return true;
		}

		return false;
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
