#pragma once

namespace cmEngine
{
	enum class eShaderLoadType
	{
		None = 0,
		HLSL,
		Binary
	};

	constexpr const char* ToString(eShaderLoadType e)
	{
		switch (e)
		{
		case eShaderLoadType::None: return "None";
		case eShaderLoadType::HLSL: return "HLSL";
		case eShaderLoadType::Binary: return "Binary";
		default: return "Undefined";
		}
	}

	class Shader
	{
	public:
		Shader() {}
		~Shader() {}

		void LoadHLSL(
			std::wstring_view	inPath,
			std::string_view	inEntryPoint,
			std::string_view	inShaderModel
		);

		void LoadBlob(std::wstring_view inPath);

		eShaderLoadType		GetShaderLoadType() const { return mLoadType; }
		::ComPtr<ID3DBlob>	GetBlob() const { return mBlob; }

	protected:
		::ComPtr<ID3DBlob>	mBlob           = {};
		eShaderLoadType		mLoadType       = eShaderLoadType::None;
	};
}


