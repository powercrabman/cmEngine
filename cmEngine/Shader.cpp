#include "EnginePch.h"
#include "Shader.h"

namespace cmEngine
{
	void Shader::LoadHLSL(std::wstring_view inPath, std::string_view inEntryPoint, std::string_view inShaderModel)
	{
		HR hr = {};

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(_DEBUG) | defined(DEBUG)
		dwShaderFlags |= D3DCOMPILE_DEBUG;
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		::ComPtr<ID3DBlob> pErrorBlob = nullptr;
		hr = D3DCompileFromFile(
			inPath.data(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			inEntryPoint.data(),
			inShaderModel.data(),
			dwShaderFlags,
			0,
			mBlob.GetAddressOf(),
			pErrorBlob.GetAddressOf());

		if (!DX_CHECK(hr))
		{
			if (pErrorBlob != nullptr)
			{
				OutputDebugStringA(static_cast<const char*>(pErrorBlob->GetBufferPointer()));
				pErrorBlob->Release();
			}
			ASSERT(false, "Shader Compile fail!");
			LOG_ERROR("Shader Compile fail!");
			return;
		}

		mLoadType = eShaderLoadType::HLSL;
		LOG_INFO("Shader compile done.");
	}

//	void Shader::LoadRawString(std::string_view inString, std::string_view inEntryPoint, std::string_view inShaderModel)
//	{
//		HRESULT hr = {};
//
//		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
//
//#if defined(_DEBUG) | defined(DEBUG)
//		dwShaderFlags |= D3DCOMPILE_DEBUG;
//		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
//#endif
//
//		ComPtr<ID3DBlob> pErrorBlob = nullptr;
//		hr = D3DCompile(
//			inString.data(),
//			inString.size(),
//			nullptr,
//			nullptr,
//			D3D_COMPILE_STANDARD_FILE_INCLUDE,
//			inEntryPoint.data(),
//			inShaderModel.data(),
//			dwShaderFlags,
//			0,
//			mBlob.GetAddressOf(),
//			pErrorBlob.GetAddressOf()
//		);
//
//		if (!DX_CHECK(hr))
//		{
//			if (pErrorBlob != nullptr)
//			{
//				OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
//				pErrorBlob->Release();
//			}
//			ASSERT(false, "Shader compile from string fail!");
//			LOG_ERROR("Shader compile from string fail!");
//			return;
//		}
//
//		LOG_INFO("Shader compile from string done.");
//	}

	void Shader::LoadBlob(std::wstring_view inPath)
	{
		HR hr = D3DReadFileToBlob(inPath.data(), mBlob.GetAddressOf());
		if (!DX_CHECK(hr))
		{
			ASSERT(false, "Load binary file fail!");
			LOG_ERROR("Load binary file fail!");
			return;
		}

		mLoadType = eShaderLoadType::Binary;
		DX_ASSERT(hr, "Load binary file done.");
	}
}