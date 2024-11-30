#pragma once

class DockSpacePanel : public Gui
{
public:
	~DockSpacePanel() override {};
	void RenderGui() override;

	void DrawContext();
};