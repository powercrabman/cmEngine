#pragma once
#include "cmGUI.h"

class OldcmLogGUI : public cmGUI
{
public:
	OldcmLogGUI();
	virtual ~OldcmLogGUI() = default;

	void Initialize() override;
	void SetupGUILayout() override;

	void Logging(const char* format, const va_list& args);
	void Logging(eLogType inType, const char* format, const va_list& args);

	ImVec4 GetTextColor(eLogType inType);
	const char* GetTextString(eLogType inType);

private:
	void Logging(const char* format, ...);
	void Logging(eLogType inType, const char* format, ...);

	void ShowSaveDlg();
	bool SaveFile(std::string_view inFilePath, std::string_view inFileName) const;

private:
	// 로그 데이터
	std::string mLogBuffer;

	struct LogData
	{
		size_t Index = 0;
		size_t Length = 0;
		eLogType Type = eLogType::None;
	};

	// 로그 데이터
	std::vector<LogData> mLogDatas;

	// TempBuffer
	cmStaticTextBuffer<1024> mTempBuffer;

	// 로그 텍스처 관련
	inline static std::array<ImVec4, static_cast<size_t>(eLogType::Count)> sLogTextColor =
	{
		ImVec4{1.f, 1.f, 1.f, 1.f},      
		ImVec4{0.500f, 0.500f, 0.500f, 1.f},
		ImVec4{0.910f, 0.825f, 0.107, 1.f},
		ImVec4{0.86f, 0.08f, 0.24f, 1.f} 
	};

	inline static std::array<const char*, static_cast<size_t>(eLogType::Count)> sLogTextStr =
	{
		"",
		"Info",
		"Warning",
		"Error"
	};

	// 오토 스크롤 관련
	bool mNeedScroll = false;
	bool mAutoScroll = true;

	// 파일 관리자
	bool mShowSaveDlg = false;
};

inline void OldcmLogGUI::Logging(const char* format, const va_list& args)
{
	Logging(eLogType::None, format, args);
}

inline ImVec4 OldcmLogGUI::GetTextColor(eLogType inType)
{
	return sLogTextColor[static_cast<int>(inType)];
}

inline const char* OldcmLogGUI::GetTextString(eLogType inType)
{
	return sLogTextStr[static_cast<int>(inType)];
}