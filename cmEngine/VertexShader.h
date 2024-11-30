#pragma once
#include "Shader.h"

class InputLayout;

namespace cmEngine
{
	class VertexShader : public Shader
	{
	public:
		VertexShader();
		~VertexShader();

		void Create(const D3D11_INPUT_ELEMENT_DESC* inInputElements, size_t inInputElementsCount);

		::ComPtr<ID3D11VertexShader> GetShader() const { return mShader; }
		::ComPtr<ID3D11InputLayout>  GetInputLayout() const { return mInputLayout; }

	private:
		::ComPtr<ID3D11VertexShader>	mShader;
		::ComPtr<ID3D11InputLayout>		mInputLayout;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void VertexShader::Create(
		const D3D11_INPUT_ELEMENT_DESC* inInputElements,
		size_t							inInputElementsCount
	)
	{
		mInputLayout.Reset();
		mShader.Reset();

		// create Vertex Shader
		{
			HR hr = Renderer::GetDevice()->CreateVertexShader(
				mBlob->GetBufferPointer(),
				mBlob->GetBufferSize(),
				nullptr,
				mShader.GetAddressOf()
			);

			if (!DX_CHECK(hr))
			{
				assert(false);
				ENGINE_LOG_ERROR("VertexShader create Fail.");
				return;
			}
		}
		
		// create Input Layout
		{
			HR hr = Renderer::GetDevice()->CreateInputLayout(
				inInputElements,
				inInputElementsCount,
				GetBlob()->GetBufferPointer(),
				GetBlob()->GetBufferSize(),
				mInputLayout.GetAddressOf()
			);

			if (!DX_CHECK(hr))
			{
				assert(false);	
				ENGINE_LOG_ERROR("create inputlayout fail");
				return;
			}
		}

		ENGINE_LOG_INFO("VertexShader create Done.");
	}
}

