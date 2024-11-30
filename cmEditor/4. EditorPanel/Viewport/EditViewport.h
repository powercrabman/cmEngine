#pragma once

class EditViewport : public Gui
{
public:
	EditViewport();
	~EditViewport() override {};
	void RenderGui() override;

private:
	SubRenderTarget* mSubRenderTarget = nullptr;
};
