#pragma once
#include "cmShader.h"

struct cmVertexDataBase;

class cmVertexShader : public cmShader
{
public:
	cmVertexShader() = default;
	virtual ~cmVertexShader();

	template <typename VertexDataType>
	void Create();
	bool IsCreated() const { return mVS != nullptr; }

	ID3D11VertexShader* GetShader() const { return mVS.Get(); }
	ID3D11InputLayout* GetInputlayout() const { return mInputLayout.Get(); }

private:
	UComPtr<ID3D11VertexShader> mVS          = nullptr;
	UComPtr<ID3D11InputLayout>	mInputLayout = nullptr;
};

template<typename VertexDataType>
inline void cmVertexShader::Create()
{
	static_assert(std::is_base_of<cmVertexDataBase, VertexDataType>::value);

	//Cteate Vertex Shader
	auto* d = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();
	auto* blob = GetBlob();
	ASSERT(blob != nullptr, "VertexShader create fail.");

	if (blob)
	{
		HR hr = d->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, mVS.GetAddressOf());
		DX_ASSERT(hr, "VertexShader create fail.");
	}
	else
	{
		LOG_ERROR("VertexShader create fail.");
		return;
	}

	//Cteate Inputlayout
	HR hr = d->CreateInputLayout(
		VertexDataType::sInputElems, 
		VertexDataType::sInputElemsSize, 
		blob->GetBufferPointer(), 
		blob->GetBufferSize(), 
		mInputLayout.GetAddressOf()
	);

	if (!DX_CHECK(hr))
	{
		ASSERT(false, "Create InputLayout Fail.");
		LOG_ERROR("Create InputLayout Fail.");
		return;
	}
}
