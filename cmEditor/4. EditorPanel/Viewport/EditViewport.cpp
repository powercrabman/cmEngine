#include "0. cmEditor/cmEditor.h"
#include "EditViewport.h"

#include <threads.h>

EditViewport::EditViewport()
{
	mSubRenderTarget = Renderer::Ref().CreateSubRenderTarget(1600, 900);
	SetVisible(true);
}

void EditViewport::RenderGui()
{
	ImWindow window = { "Viewport", GetVisiblePtr() };

	ImVec2 availableSize = ImGui::GetContentRegionAvail();
	float aspectRatio    = mSubRenderTarget->GetAspectRatio();

	ImVec2 viewportSize = {};
	if (availableSize.x / aspectRatio <= availableSize.y)
	{
		viewportSize.x = availableSize.x;
		viewportSize.y = availableSize.x / aspectRatio;
	}
	else
	{
		viewportSize.x = availableSize.y * aspectRatio;
		viewportSize.y = availableSize.y;
	}

	ImVec2 cursorPos   = ImGui::GetCursorScreenPos();
	ImVec2 centeredPos = ImVec2(
		cursorPos.x + (availableSize.x - viewportSize.x) * 0.5f,
		cursorPos.y + (availableSize.y - viewportSize.y) * 0.5f
	);

	ImGui::SetCursorScreenPos(centeredPos);
	ImGui::Image(reinterpret_cast<ImTextureID>(mSubRenderTarget->GetShaderResourceView().Get()), viewportSize);
}
