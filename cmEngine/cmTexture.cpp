#include "pch.h"
#include "cmTexture.h"

void cmTexture::Load(std::wstring_view inFilePath)
{
	//ScratchImage img = {};
	HR hr = LoadFromWICFile(
		inFilePath.data(),
		WIC_FLAGS_NONE,
		&mMetaData,
		mImage,
		nullptr);
	DX_ASSERT(hr, "Texture Load Fail.");

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
	
	DX_ASSERT(hr, "DDS Compression Fail.");

	if (SUCCEEDED(hr))
	{
		LOG_INFO("\"%s\" Load Success! ", inFilePath.data());
	}
}

void cmTexture::Save(std::wstring_view inFilePath, eTextureFormat inFormat)
{
	HR hr = DirectX::SaveToWICFile(
		*mImage.GetImage(0, 0, 0),
		WIC_FLAGS_NONE,
		DirectX::GetWICCodec(static_cast<DirectX::WICCodecs>(inFormat)),
		inFilePath.data());

	if (FAILED(hr))
	{
		DX_ASSERT(hr, "Texture Save Fail.");
		LOG_ERROR("Texture Save Fail.");
		return;
	}

	LOG_INFO("\"%s\" Save Success! ", inFilePath.data());
}

void cmTexture::Create()
{
	if (mImage.GetImages() == nullptr)
	{
		ASSERT(false, "Image is not loaded");
		LOG_ERROR("Image is not loaded");
		return;
	}

	// 텍스처 생성 

	auto* dv = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();

	UComPtr<ID3D11Resource> res = nullptr;
	HR hr = DirectX::CreateTexture(dv, mImage.GetImages(), mImage.GetImageCount(), mMetaData, res.GetAddressOf());
	
	if (FAILED(hr))
	{
		ASSERT(false, "Create Texture Fail.");
		LOG_ERROR("Create Texture Fail.");
		return;
	}

	hr = res.As(&mTex); // 확인 필요

	if (FAILED(hr))
	{
		ASSERT(false, "Create Texture Fail.");
		LOG_ERROR("Create Texture Fail.");
		return;
	}

	hr = DirectX::CreateShaderResourceView(dv, mImage.GetImages(), mImage.GetImageCount(), mMetaData, mSRV.GetAddressOf());

	if (FAILED(hr))
	{
		ASSERT(false, "Create Shader Resource View Fail.");
		LOG_ERROR("Create Shader Resource View Fail.");
		return;
	}
}

