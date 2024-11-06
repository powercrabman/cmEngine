#pragma once
#include "cmVertexData.h"
#include "cmInputLayoutBase.h"

template<typename VertexType>
class cmInputLayout : public cmInputLayoutBase
{
public:
	cmInputLayout() = default;
	virtual ~cmInputLayout() = default;

	void Create(cmVertexShader* inVertexShader)
	{
		mInputLayout.Reset();

		auto* dv = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();

		auto* blob = inVertexShader->GetBlob();
		HRESULT hr = dv->CreateInputLayout(VertexType::sInputElems, VertexType::sInputElemsSize, blob->GetBufferPointer(), blob->GetBufferSize(), mInputLayout.GetAddressOf());
		DX_CHECK(hr, "InputLayout create fail.");
		if (FAILED(hr)) { LOG_ERROR("InputLayout create fail."); }
	}
};