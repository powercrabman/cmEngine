#pragma once

enum class eImTextAlignHorizon : int
{
    Left   = -1,   
    Center = 0,  
    Right  = 1    
};

enum class eImTextAlignVertical : int
{
    Top    = -1,    
    Center = 0,  
    Bottom = 1   
};

inline ImVec2 CalculateAlignedPosition(const char* text, eImTextAlignHorizon horizontalAlign, eImTextAlignVertical verticalAlign)
{
    ImVec2 windowSize = ImGui::GetWindowSize();  
    ImVec2 textSize   = ImGui::CalcTextSize(text); 
    ImVec2 cursorPos  = ImGui::GetCursorPos();    

    float hAlignFactor = static_cast<int>(horizontalAlign);
    float vAlignFactor = static_cast<int>(verticalAlign);

    float xOffset = cursorPos.x + (hAlignFactor + 1) * (windowSize.x - textSize.x) * 0.5f;
    float yOffset = cursorPos.y + (vAlignFactor + 1) * (windowSize.y - textSize.y) * 0.5f;

    return ImVec2(xOffset, yOffset);
}

inline void ImTextAlign(const char* text, eImTextAlignHorizon horizontalAlign, eImTextAlignVertical verticalAlign)
{
    ImVec2 alignedPos = CalculateAlignedPosition(text, horizontalAlign, verticalAlign);
    ImGui::SetCursorPos(alignedPos);
    ImGui::TextUnformatted(text);
}

inline void ImTextAlign(const ImVec4& inColor, const char* text, eImTextAlignHorizon horizontalAlign, eImTextAlignVertical verticalAlign)
{
    ImVec2 alignedPos = CalculateAlignedPosition(text, horizontalAlign, verticalAlign);
    ImGui::SetCursorPos(alignedPos);
    ImGui::TextColored(inColor, text);
}
