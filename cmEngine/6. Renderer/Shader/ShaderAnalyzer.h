#pragma once

namespace cmEngine
{
    struct ShaderDescription
    {
        std::string entryPoint = {};
        std::string shaderModel = {};
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementList = {};
    };

    class ShaderAnalyzer
    {
    public:
        static bool GetShaderDescription(Shader* inShader, ShaderDescription* inOutShaderDesc)
        {
            ::ComPtr<ID3DBlob> blob = inShader->GetBlob();
            ::ComPtr<ID3D11ShaderReflection> reflection;

            HRESULT hr = D3DReflect(
                blob->GetBufferPointer(),
                blob->GetBufferSize(),
                IID_ID3D11ShaderReflection,
                reinterpret_cast<void**>(reflection.GetAddressOf())
            );

            if (FAILED(hr))
            {
                ENGINE_LOG_ERROR("Shader Analyzer shader reflection fail.");
                return false;
            }

            D3D11_SHADER_DESC desc = {};
            reflection->GetDesc(&desc);

            inOutShaderDesc->entryPoint = desc.Creator;
            inOutShaderDesc->shaderModel = std::format("{}_{}", (desc.Version >> 16), (desc.Version & 0xFFFF));
            inOutShaderDesc->inputElementList.resize(desc.InputParameters);
            for (uint32_t i = 0; i < desc.InputParameters; ++i)
            {
                D3D11_SIGNATURE_PARAMETER_DESC params = {};
                reflection->GetInputParameterDesc(i, &params);

                D3D11_INPUT_ELEMENT_DESC inputElement = {};
                inputElement.SemanticName             = params.SemanticName;
                inputElement.SemanticIndex            = params.SemanticIndex;
                inputElement.Format                   = ToDXGIFormatFromComponentType(params.ComponentType, params.Mask);
                inputElement.InputSlot                = 0; 
                inputElement.AlignedByteOffset        = D3D11_APPEND_ALIGNED_ELEMENT; 
                inputElement.InputSlotClass           = D3D11_INPUT_PER_VERTEX_DATA; 
                inputElement.InstanceDataStepRate     = 0; 

                inOutShaderDesc->inputElementList[i] = inputElement;
            }
            return true;
        }

    private:
        static DXGI_FORMAT ToDXGIFormatFromComponentType(D3D_REGISTER_COMPONENT_TYPE componentType, BYTE mask)
        {
            switch (componentType)
            {
            case D3D_REGISTER_COMPONENT_UINT32:
                if (mask == 1) return DXGI_FORMAT_R32_UINT;
                if (mask <= 3) return DXGI_FORMAT_R32G32_UINT;
                if (mask <= 7) return DXGI_FORMAT_R32G32B32_UINT;
                if (mask <= 15) return DXGI_FORMAT_R32G32B32A32_UINT;
                break;
            case D3D_REGISTER_COMPONENT_SINT32:
                if (mask == 1) return DXGI_FORMAT_R32_SINT;
                if (mask <= 3) return DXGI_FORMAT_R32G32_SINT;
                if (mask <= 7) return DXGI_FORMAT_R32G32B32_SINT;
                if (mask <= 15) return DXGI_FORMAT_R32G32B32A32_SINT;
                break;
            case D3D_REGISTER_COMPONENT_FLOAT32:
                if (mask == 1) return DXGI_FORMAT_R32_FLOAT;
                if (mask <= 3) return DXGI_FORMAT_R32G32_FLOAT;
                if (mask <= 7) return DXGI_FORMAT_R32G32B32_FLOAT;
                if (mask <= 15) return DXGI_FORMAT_R32G32B32A32_FLOAT;
                break;
            }
            return DXGI_FORMAT_UNKNOWN; 
        }
    };
}