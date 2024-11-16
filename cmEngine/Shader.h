#pragma once

namespace cmEngine
{
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

		void LoadRawString(
			std::string_view	inString,
			std::string_view	inEntryPoint,
			std::string_view	inShaderModel
		);

		void LoadBlob(std::wstring_view inPath);

		::ComPtr<ID3DBlob> GetBlob() const { return mBlob; }

		template <typename... ConstantBufferType>
		void SetConstantBuffers()
		{
			mConstantBufferList.clear();
			SetConstantBuffersEx<ConstantBufferType...>();
		}

		std::vector<ConstantBufferBase*>::const_iterator GetConstantBufferListConstBegin() const { return mConstantBufferList.cbegin(); }
		std::vector<ConstantBufferBase*>::const_iterator GetConstantBufferListConstEnd() const { return mConstantBufferList.cend(); }

	private:
		template <typename First, typename... Rest>
		void SetConstantBuffersEx()
		{
			mConstantBufferList.push_back(ConstantBufferPool::FindConstantBuffer<First>());
			if constexpr (sizeof...(Rest) > 0)
			{
				SetConstantBuffersEx<Rest...>();
			}
		}

	protected:
		::ComPtr<ID3DBlob> mBlob = {};
		std::vector<ConstantBufferBase*> mConstantBufferList;
	};
}


