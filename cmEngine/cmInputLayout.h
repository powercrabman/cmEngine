#pragma once
#include "cmInputLayoutBase.h"
#include "cmVertexShader.h"

// Lagacy
// Not Use

template<typename VertexType>
class cmInputLayout : public cmInputLayoutBase
{
public:
	cmInputLayout() = default;
	virtual ~cmInputLayout() = default;

	void Create(cmVertexShader* inVertexShader) override;
};

template<typename VertexType>
inline void cmInputLayout<VertexType>::Create(cmVertexShader* inVertexShader)
{
	mInputLayout.Reset();
	
	auto* dv = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();

	auto* blob = inVertexShader->GetBlob();
	HR hr = dv->CreateInputLayout(VertexType::sInputElems, VertexType::sInputElemsSize, blob->GetBufferPointer(), blob->GetBufferSize(), mInputLayout.GetAddressOf());
	DX_ASSERT(hr, "InputLayout create fail.");
	if (FAILED(hr)) { LOG_ERROR("InputLayout create fail."); }
}

