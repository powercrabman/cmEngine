#pragma once
#include <Imgui\imgui.h>
#include "ImOp.h"
#include "ImFlag.h"
#include "ImWindow.h"
#include "ImText.h"
#include "ImFileDialog.h"
#include "ImPayload.h"
#include "ImDraw.h"
#include "ImFlipbook.h"

static inline ImTextureID CastToImTextureID(const Texture* inTex) { return reinterpret_cast<ImTextureID>(inTex->GetShaderResourceView().Get()); }