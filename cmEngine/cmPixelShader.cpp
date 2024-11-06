#include "pch.h"
#include "cmPixelShader.h"

void cmPixelShader::Create()
{
    auto* d = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();
    auto* blob = GetBlob();
    ASSERT(blob != nullptr, "PixelShader create fail.");

    if (blob)
    {
        HRESULT hr = d->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, mPS.GetAddressOf());
        DX_CHECK(hr, "PixelShader create fail.");
    }
    else
    {
        LOG_ERROR("PixelShader create fail.");
    }
}
