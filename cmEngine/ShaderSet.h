#pragma once

#include "ResourceBase.h"

namespace cmEngine
{
	struct DXInputElement
	{
		DXInputElement() = default;
		DXInputElement(const D3D11_INPUT_ELEMENT_DESC& inDesc)
			: SemanticName(inDesc.SemanticName)
			, SemanticIndex(inDesc.SemanticIndex)
			, Format(inDesc.Format)
			, InputSlot(inDesc.InputSlot)
			, AlignedByteOffset(inDesc.AlignedByteOffset)
			, InputSlotClass(inDesc.InputSlotClass)
			, InstanceDataStepRate(inDesc.InstanceDataStepRate)
		{
		}

		static std::vector<DXInputElement> createFromD3D11InputElementsList(const std::vector<D3D11_INPUT_ELEMENT_DESC>& inList)
		{
			std::vector<DXInputElement> result = {};
			result.reserve(inList.size());
			for (const auto& elem : inList) { result.push_back(elem); }
			return result;
		}

		static std::vector<D3D11_INPUT_ELEMENT_DESC> ConvertToInputElementsList(const std::vector<DXInputElement>& inList)
		{
			std::vector<D3D11_INPUT_ELEMENT_DESC> result = {};
			result.reserve(inList.size());
			for (const auto& elem : inList) { result.push_back(elem.ToInputElement()); }
			return result;
		}

		D3D11_INPUT_ELEMENT_DESC ToInputElement() const
		{
			return D3D11_INPUT_ELEMENT_DESC{
			.SemanticName = SemanticName.c_str(),
				.SemanticIndex = SemanticIndex,
				.Format = Format,
				.InputSlot = InputSlot,
				.AlignedByteOffset = AlignedByteOffset,
				.InputSlotClass = InputSlotClass,
				.InstanceDataStepRate = InstanceDataStepRate
			};
		}

		std::string					SemanticName;
		UINT						SemanticIndex;
		DXGI_FORMAT					Format;
		UINT						InputSlot;
		UINT						AlignedByteOffset;
		D3D11_INPUT_CLASSIFICATION	InputSlotClass;
		UINT						InstanceDataStepRate;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(
			DXInputElement,
			SemanticName,
			SemanticIndex,
			Format,
			InputSlot,
			AlignedByteOffset,
			InputSlotClass,
			InstanceDataStepRate
		);
	};

	struct ShaderSetJson : JsonMetaData
	{
		std::string								shaderSetName;
		eResourceType							resourceType;
		std::wstring							shaderFile;
		eShaderLoadType							loadType;
		std::vector<DXInputElement>				inInputElements;
		std::string								vsEntryPoint;
		std::string								vsModel;
		std::string								psEntryPoint;
		std::string								psModel;

		JSON_STRUCT_BODY(
			ShaderSetJson,
			shaderSetName,
			resourceType,
			shaderFile,
			loadType,
			inInputElements,
			vsEntryPoint,
			vsModel,
			psEntryPoint,
			psModel
		);
	};

	class ShaderSet : public ResourceBase
	{
	public:
		RESOURCE_BODY(ShaderSet);

		~ShaderSet() override;

		void CreateByHLSL(
			std::wstring_view				inFilePath,
			const D3D11_INPUT_ELEMENT_DESC* inInputElements,
			size_t							inInputElementsCount,
			std::string_view				inVSEntryPoint = "VS",
			std::string_view				inVSModel = "vs_5_0",
			std::string_view				inPSEntryPoint = "PS",
			std::string_view				inPSModel = "ps_5_0"
		);

		void CreateByBlob(
			std::wstring_view inFilePath,
			const D3D11_INPUT_ELEMENT_DESC* inInputElements,
			size_t							inInputElementsCount
		);

		VertexShader*		GetVertexShader() { return &mVertexShader; }
		PixelShader*		GetPixelShader() { return &mPixelShader; }

		const wchar_t*		GetShaderFilePath() const { return mShaderSetFilePath.c_str(); }
		eShaderLoadType		GetShaderLoadType() const { return mShaderLoadType; }

	private:
		ShaderSet() {};

		bool			LoadJsonFromFile(std::wstring_view inFilePath) override;
		bool			LoadJsonFromSection(std::wstring_view inFilePath, std::string_view inSectionName) override;
		bool			LoadJsonEx(const ShaderSetJson& inJson);

		void			SaveJsonToFile(std::wstring_view inFilePath) override;
		void			SaveJsonToSection(std::wstring_view inFilePath, std::string_view inSectionName) override;
		ShaderSetJson	SaveJsonEx();

		VertexShader		mVertexShader = {};
		PixelShader			mPixelShader = {};

		std::wstring		mShaderSetFilePath = {};
		eShaderLoadType		mShaderLoadType = eShaderLoadType::None;
	};
}
