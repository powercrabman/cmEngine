#include "pch.h"
#include "cmPixelShader.h"

void cmPixelShader::Create()
{
    auto* d = Engine->GetRenderer()->GetGraphicsDevice()->GetDevice();
    auto* blob = GetBlob();
    ASSERT(blob != nullptr, "PixelShader create fail.");

    if (blob)
    {
        HR hr = d->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, mPS.GetAddressOf());
        DX_ASSERT(hr, "PixelShader create fail.");
    }
    else
    {
        LOG_ERROR("PixelShader create fail.");
    }
}
