#pragma once
#include "cmResourceBase.h"

class cmShader : public cmResourceBase
{
public:
	virtual ~cmShader() = default;

	void LoadAndCompileHLSL(
		std::wstring_view inFilePath,
		std::string_view inEntryPoint,
		std::string_view inShaderModel
	);
	void LoadBlob(std::filesystem::path inFilePath);

	ID3DBlob* GetBlob() const;

	void Save(std::wstring_view inFilePath) const;
	void SetConstantBuffers(const std::vector<cmConstantBufferBase*>& inConstantBuffers);
	const std::vector<cmConstantBufferBase*>& FindConstantBuffers() const;

protected:
	cmShader() = default;

private:
	UComPtr<ID3DBlob> mBlob = nullptr;
	std::vector<cmConstantBufferBase*> mConstantBuffers = {};
};

inline void cmShader::SetConstantBuffers(const std::vector<cmConstantBufferBase*>& inConstantBuffers)
{
	mConstantBuffers = inConstantBuffers;
}

inline const std::vector<cmConstantBufferBase*>& cmShader::FindConstantBuffers() const
{
	return mConstantBuffers;
}

inline ID3DBlob* cmShader::GetBlob() const
{
	ASSERT(mBlob != nullptr, "Blob is nullptr.");
	return mBlob.Get();
}

inline void cmShader::LoadBlob(std::filesystem::path inFilePath)
{
	HR hr = D3DReadFileToBlob(inFilePath.c_str(), mBlob.GetAddressOf());
	DX_ASSERT(hr, "Load binary file Fail.");
}

