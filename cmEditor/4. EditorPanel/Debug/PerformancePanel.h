#pragma once

struct PerformancePanelJson
{
	bool visible    = false;
	JSON_STRUCT_BODY(PerformancePanelJson, visible);
};

class PerformancePanel : public Gui
{
public:
	PerformancePanel();
	~PerformancePanel() override;

	void RenderGui() override;

	TO_STRING(PerformancePanel);

private:
	PerformancePanelJson mConfig = {};
};

