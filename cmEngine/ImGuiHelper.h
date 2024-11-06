#pragma once

namespace ImGui
{
	inline void SetNextWindowPos(const ScreenPos& pos, ImGuiCond cond = 0, const ImVec2& pivot = { 0,0 })
	{
		ImVec2 vec;
		vec.x = static_cast<float>(pos.X);
		vec.y = static_cast<float>(pos.Y);

		ImGui::SetNextWindowPos(vec, cond, pivot);
	}
}

namespace ImGui::Helper
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

	//파일 시스템
	class FileDialogHelper
	{
	public:
		FileDialogHelper() = default;
		virtual ~FileDialogHelper() = default;

		void Show(const char* inDlgTitle, bool* open, cmStaticTextBufferBase* outBuffer);
	};

	// GUI 배치를 위해 위치를 계산합니다.
	inline ImVec2 CalcLayoutPosition(const ImVec2& inPosition, const ImVec2& pivotWindow = { 0.f,0.f }, int margin = 0.f, eCalcLayoutPositionX inStdX = eCalcLayoutPositionX::Left, eCalcLayoutPositionY inStdY = eCalcLayoutPositionY::Top)
	{
		ImGuiViewport* vp = ImGui::GetMainViewport();
		const ImVec2& s = vp->Pos;

		ImVec2 result = inPosition;
		result.x += s.x - (int)inStdX * pivotWindow.x * 0.5f;
		result.y += s.y - (int)inStdY * pivotWindow.y * 0.5f;

		// margin 계산
		if (inStdX == eCalcLayoutPositionX::Left) result.x += margin;
		else if (inStdX == eCalcLayoutPositionX::Right) result.x -= margin;

		if (inStdY == eCalcLayoutPositionY::Top) result.y += margin;
		else if (inStdY == eCalcLayoutPositionY::Bottom) result.y -= margin;

		return result;
	}

	inline ImVec2 CalcLayoutPosition(const ScreenPos& inPosition, const ImVec2& pivotWindow = { 0.f,0.f }, int margin = 0.f, eCalcLayoutPositionX inStdX = eCalcLayoutPositionX::Left, eCalcLayoutPositionY inStdY = eCalcLayoutPositionY::Top)
	{
		return CalcLayoutPosition(ImVec2{ (float)inPosition.X, (float)inPosition.Y }, pivotWindow, margin, inStdX, inStdY);
	}
}
