#pragma once

namespace cmEngine::GuiHelper
{
	//심플한 툴팁
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

	//(?) 모양의 툴팁
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

	// 색상 TextWrap
	inline void TextColoredWrap(const ImVec4& inColor, const char* inMsg)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, inColor);
		ImGui::TextWrapped(inMsg);
		ImGui::PopStyleColor();
	}

	// 가운데 정렬 텍스트
	inline void TextCenterAlign(const char* inText)
	{

		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 textSize = ImGui::CalcTextSize(inText);

		ImVec2 centerPos((windowSize.x - textSize.x) * 0.5f, (windowSize.y - textSize.y) * 0.5f);
		ImGui::SetCursorPos(centerPos);

		ImGui::TextUnformatted(inText);
	}

	inline void TextWrapCenterAlign(const char* inText)
	{

		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 textSize = ImGui::CalcTextSize(inText);

		ImVec2 centerPos((windowSize.x - textSize.x) * 0.5f, (windowSize.y - textSize.y) * 0.5f);
		ImGui::SetCursorPos(centerPos);
		ImGui::TextWrapped(inText);
	}

	inline void TextColoredCenterAlign(const char* inText, const ImVec4& inColor)
	{

		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 textSize = ImGui::CalcTextSize(inText);

		ImVec2 centerPos((windowSize.x - textSize.x) * 0.5f, (windowSize.y - textSize.y) * 0.5f);
		ImGui::SetCursorPos(centerPos);

		ImGui::PushStyleColor(ImGuiCol_Text, inColor);
		ImGui::TextUnformatted(inText);
		ImGui::PopStyleColor();
	}

	inline void TextColoredWrapCenterAlign(const char* inText, const ImVec4& inColor)
	{

		ImVec2 windowSize = ImGui::GetWindowSize();
		ImVec2 textSize = ImGui::CalcTextSize(inText);

		ImVec2 centerPos((windowSize.x - textSize.x) * 0.5f, (windowSize.y - textSize.y) * 0.5f);
		ImGui::SetCursorPos(centerPos);

		ImGui::PushStyleColor(ImGuiCol_Text, inColor);
		ImGui::TextWrapped(inText);
		ImGui::PopStyleColor();
	}

	inline void TextMiddle(const char* text)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text);
		float textPosX = (ImGui::GetWindowSize().x - textSize.x) * 0.5f;
		textPosX = max(0.f, textPosX);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textPosX);
		ImGui::TextUnformatted(text);
	}

	inline void TextWrapMiddle(const char* inText)
	{
		ImVec2 textSize = ImGui::CalcTextSize(inText);
		float textPosX = (ImGui::GetWindowSize().x - textSize.x) * 0.5f;
		textPosX = max(0.f, textPosX);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + textPosX);
		ImGui::TextWrapped(inText);
	}

}

