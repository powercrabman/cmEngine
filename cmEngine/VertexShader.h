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

		template<typename VertexType>
		void Create();

		::ComPtr<ID3D11VertexShader> GetShader() const { return mShader; }
		::ComPtr<ID3D11InputLayout>  GetInputLayout() const { mInputLayout; }

	private:
		::ComPtr<ID3D11VertexShader>	mShader;
		::ComPtr<ID3D11InputLayout>		mInputLayout;


	};

	//===================================================
	//                      Inline
	//===================================================

	template<typename VertexType>
	inline void VertexShader::Create()
	{
		static_assert(std::is_base_of<IVertexBase, VertexType>::value);

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
				VertexType::InputElemnets,
				VertexType::InputElemnetsSize,
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

		ENGINE_LOG_ERROR("VertexShader create Done.");
	}
}

