#include "0. cmEngine/cmEngine.h"
#include "ShaderSet.h"

namespace cmEngine
{
	ShaderSet::~ShaderSet()
	{
	}

	void ShaderSet::CreateByHLSL(
		std::wstring_view inFilePath,
		const D3D11_INPUT_ELEMENT_DESC* inInputElements,
		size_t							inInputElementsCount,
		std::string_view				inVSEntryPoint,
		std::string_view				inVSModel,
		std::string_view				inPSEntryPoint,
		std::string_view				inPSModel
	)
	{
		mVertexShader.LoadHLSL(inFilePath, inVSEntryPoint, inVSModel);
		mVertexShader.Create(inInputElements, inInputElementsCount);

		mPixelShader.LoadHLSL(inFilePath, inPSEntryPoint, inPSModel);
		mPixelShader.Create();

		mShaderSetFilePath = inFilePath;
		mShaderLoadType = eShaderLoadType::HLSL;
	}

	void ShaderSet::CreateByBlob(
		std::wstring_view inFilePath,
		const D3D11_INPUT_ELEMENT_DESC* inInputElements,
		size_t inInputElementsCount
	)
	{
		mVertexShader.LoadBlob(inFilePath);
		mVertexShader.Create(inInputElements, inInputElementsCount);

		mPixelShader.LoadBlob(inFilePath);
		mPixelShader.Create();

		mShaderSetFilePath = inFilePath;
		mShaderLoadType = eShaderLoadType::Binary;
	}

	void ShaderSet::SaveJsonToFile(const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory)
	{
		ShaderSetJson js = {};
		js.shaderSetName = GetName();
		js.shaderFile    = mShaderSetFilePath;
		js.loadType      = mShaderLoadType;

		//VS
		{
			ShaderDescription desc = {};
			ShaderAnalyzer::GetShaderDescription(&mVertexShader, &desc);
			js.inInputElements = DXInputElement::createFromD3D11InputElementsList(desc.inputElementList);
			js.vsEntryPoint    = desc.entryPoint;
			js.vsModel         = desc.entryPoint;
		}

		//PS
		{
			ShaderDescription desc = {};
			ShaderAnalyzer::GetShaderDescription(&mPixelShader, &desc);
			js.psEntryPoint = desc.entryPoint;
			js.psModel      = desc.entryPoint;
		}

		JsonSerializer::Ref().SerializeToFile(js, inFileName, inDirectory);
	}

	bool ShaderSet::LoadJsonFromFile(const std::filesystem::path& inFilePath, const std::filesystem::path& inDirectory)
	{
		ShaderSetJson js = {};

		if (JsonSerializer::Ref().DeserializerFromFile(js, inFilePath, inDirectory))
		{
			switch (js.loadType)
			{
			case eShaderLoadType::HLSL:
				CreateByHLSL(
					js.shaderFile,
					DXInputElement::ConvertToInputElementsList(js.inInputElements).data(),
					js.inInputElements.size(),
					js.vsEntryPoint,
					js.vsModel,
					js.psEntryPoint,
					js.psModel
				);
				break;
			case eShaderLoadType::Binary:
				CreateByBlob(
					js.shaderFile,
					DXInputElement::ConvertToInputElementsList(js.inInputElements).data(),
					js.inInputElements.size()
				);
				break;
			default:
				assert(false);
				ENGINE_LOG_ERROR("ShaderSet Deserialize fail.");
				return false;;
			}

			mShaderLoadType = js.loadType;
			mName = js.shaderSetName;
			return true;
		}

		return false;
	}
}
