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

	// Blob ������ Load �մϴ�.
	// ����, HLSL ������ Load �ϰ� �ʹٸ�, LoadAndCompileHLSL �� ����ؾ� �մϴ�.
	void Load(std::wstring_view inFilePath) override { LoadBlob(inFilePath); }
	void Save(std::wstring_view inFilePath) override;

	virtual void Create() abstract;

	//������Ʈ ������ ������ �ݵ�� slot�� �°� �����ؾ��մϴ�.
	void SetConstantBuffers(const std::vector<cmConstantBufferBase*>& inConstantBuffers)
	{
		mConstantBuffers = inConstantBuffers;
	}

private:
	UComPtr<ID3DBlob> mBlob = nullptr;
	std::vector<cmConstantBufferBase*> mConstantBuffers = {};
};
