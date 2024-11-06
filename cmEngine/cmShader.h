#pragma once
#include "cmResourceBase.h"

class cmShader : public cmResourceBase
{
public:
	cmShader() = default;
	virtual ~cmShader() = default;

	void LoadAndCompileHLSL(
		std::wstring_view inFilePath,
		std::string_view inEntryPoint,
		std::string_view inShaderModel
	);

	void LoadBlob(std::wstring_view inFilePath)
	{
		HRESULT hr = D3DReadFileToBlob(inFilePath.data(), mBlob.GetAddressOf());
		DX_CHECK(hr, "Load binary file Fail.");
	}

	ID3DBlob* GetBlob() const
	{
		ASSERT(mBlob != nullptr, "Blob is nullptr.");
		return mBlob.Get();
	}

	// Blob 파일을 Load 합니다.
	// 만약, HLSL 파일을 Load 하고 싶다면, LoadAndCompileHLSL 을 사용해야 합니다.
	void Load(std::wstring_view inFilePath) override { LoadBlob(inFilePath); }
	void Save(std::wstring_view inFilePath) override;

	virtual void Create() abstract;

	//컨스턴트 버퍼의 순서는 반드시 slot에 맞게 설정해야합니다.
	void SetConstantBuffers(const std::vector<cmConstantBufferBase*>& inConstantBuffers)
	{
		mConstantBuffers = inConstantBuffers;
	}

private:
	UComPtr<ID3DBlob> mBlob = nullptr;
	std::vector<cmConstantBufferBase*> mConstantBuffers = {};
};
