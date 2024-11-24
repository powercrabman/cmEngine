#include "EnginePch.h"
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

	void ShaderSet::SaveJsonToFile(std::wstring_view inFilePath)
	{
		JsonSerializer::SerializeToFile(SaveJsonEx(), inFilePath);
	}

	void ShaderSet::SaveJsonToSection(std::wstring_view inFilePath, std::string_view inSectionName)
	{
		JsonSerializer::SerializeToSection(SaveJsonEx(), inFilePath, inSectionName);
	}

	ShaderSetJson ShaderSet::SaveJsonEx()
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

		return js;
	}

	bool ShaderSet::LoadJsonFromFile(std::wstring_view inFilePath)
	{
		ShaderSetJson js = {};
		if (JsonSerializer::DeserializeFromFile(js, inFilePath))
		{
			return LoadJsonEx(js);
		}

		assert(false);
		ENGINE_LOG_ERROR("ShaderSet Deserialize fail.");
		return false;
	}


	bool ShaderSet::LoadJsonFromSection(std::wstring_view inFilePath, std::string_view inSectionName)
	{
		ShaderSetJson js = {};
		if (JsonSerializer::DeserializeFromSection(js, inFilePath, inSectionName))
		{
			return LoadJsonEx(js);
		}

		assert(false);
		ENGINE_LOG_ERROR("ShaderSet Deserialize fail.");
		return false;
	}

	bool ShaderSet::LoadJsonEx(const ShaderSetJson& inJson)
	{
		switch (inJson.loadType)
		{
		case eShaderLoadType::HLSL:
			CreateByHLSL(
				inJson.shaderFile, 
				DXInputElement::ConvertToInputElementsList(inJson.inInputElements).data(), 
				inJson.inInputElements.size(), 
				inJson.vsEntryPoint, 
				inJson.vsModel, 
				inJson.psEntryPoint, 
				inJson.psModel
			);
			break;
		case eShaderLoadType::Binary:
			CreateByBlob(
				inJson.shaderFile, 
				DXInputElement::ConvertToInputElementsList(inJson.inInputElements).data(),
				inJson.inInputElements.size()
			);
			break;
		default:
			{
				assert(false);
				ENGINE_LOG_ERROR("ShaderSet Deserialize fail.");
				return false;;
			}
		}

		mShaderLoadType = inJson.loadType;
		mName           = inJson.shaderSetName;

		return true;
	}
}
