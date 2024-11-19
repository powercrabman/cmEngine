#pragma once

namespace cmEngine::GuiHelper
{
	//������ ����
	inline void Tooltip(const char* inMsg)
	{
		if (ImGui::BeginItemTooltip())
		{
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(inMsg);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	//(?) ����� ����
	inline void QuestionTooltip(const char* inMsg)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::BeginItemTooltip())
		{
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(inMsg);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	// ���� TextWrap
	inline void TextColoredWrap(const ImVec4& inColor, const char* inMsg)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, inColor);
		ImGui::TextWrapped(inMsg);
		ImGui::PopStyleColor();
	}
}

