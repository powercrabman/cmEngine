#include "pch.h"
#include "cmLogger.h"
#include "cmLoggerGUI.h"
#include "cmRenderer.h"
#include "cmGUIRenderer.h"

cmLogger::cmLogger()
{
	// RESERVE
	mLogDatas.reserve(100000);
}

cmLogger::~cmLogger()
{
	ClearLog();
}

void cmLogger::Initialize()
{
	mGUI = cmHelper::RegisterGUI<cmLoggerGUI>();
	LOG_INFO("Logger Initialize Done.");

}

void cmLogger::LoggingCore(eLogLevel inLevel, const char* format, const va_list& args)
{
	cmLogData log = {};
	log.TimeStamp = Engine->GetTimer()->GetTotalTime();
	log.Level = inLevel;

	// �޽��� ������
	mTempBuffer.Print(format, args);
	log.Text = mTempBuffer.c_str();

	// ������ �߰�
	mLogDatas.push_back(std::move(log));

	// ��ũ�� �ʿ���
	if (mGUI) mGUI->NeedScroll();
}

void cmLogger::Logging(eLogLevel inLevel, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	mTempBuffer.Print(format, args);
	LoggingCore(inLevel, format, args);
	va_end(args);
}
