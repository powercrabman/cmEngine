#pragma once
#include "Shader.h"

namespace cmEngine
{
	class PixelShader : public Shader
	{
	public:
		PixelShader() {}
		~PixelShader() {}

		void Create();

		::ComPtr<ID3D11PixelShader> GetShader() const { mShader; }

	private:
		::ComPtr<ID3D11PixelShader> mShader;
	};
}
