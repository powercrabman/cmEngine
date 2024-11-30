#include "0. cmEditor/cmEditor.h"
#include "PerformancePanel.h"

PerformancePanel::PerformancePanel()
{
	SetVisible(false);
	if (JsonSerializer::Ref().DeserializerFromFileWithTag(mConfig, Config::gEditorPanelConfigFileName, sClassName))
	{
		SetVisible(mConfig.visible);
	}
}

PerformancePanel::~PerformancePanel()
{
	PerformancePanelJson js = mConfig;
	js.visible = IsVisible();
	JsonSerializer::Ref().SerializeToFileWithTag(js, Config::gEditorPanelConfigFileName, sClassName);
}

void PerformancePanel::RenderGui()
{
	ImGui::Begin("Performance Check", GetVisiblePtr());

	ImGui::SeparatorText("Frame Performance");
	ImGui::Text("Total Timer : %.3f sec", Timer::Ref().GetTotalTime());
	ImGui::Text("Delta Time : %.3f sec", Timer::Ref().GetDeltaTime());
	ImGui::Text("Frame per sec : %.3f update per sec", Timer::Ref().GetFPS());

	ImGui::End();
}
