#pragma once

enum class eLogLevel
{
	Trace,	/* �Ϲ� �޽��� */
	Debug,	/* ����� ��忡���� Ȱ��ȭ. �����ڿ� �α� */
	Info,	/* �ý��� ���³� �̺�Ʈ ���� ��� */
	Warn,	/* ���������� ������ �߻�������, �ý��� �۵��� ������ ���� ��� */
	Error,	/* ������ �߻��Ͽ� ��û�� ������ ��� */
	Fatal,	/* �ɰ��� ������ �ý��� �۵��� ������ �߻��� ��� */

	Count
};

struct cmLogData
{
	float TimeStamp;
	eLogLevel Level;
	std::string Text;

	inline static const char* sLogLevelString[(uint32)eLogLevel::Count] =
	{
		"Trace",
		"Debug",
		"Info",
		"Warn",
		"Error",
		"Fatal"
	};

	inline static ImVec4 sLogLevelColor[(uint32)eLogLevel::Count] = {
	ImVec4{ 1.f, 0.980, 0.941f, 1.f },	/* Trace */
	ImVec4{ 0.283f, 0.758f, 0.914f, 1.f },	/* Debug */
	ImVec4{ 0.220f, 0.906f, 0.085f, 1.f },	/* Info */
	ImVec4{ 0.973f, 0.980f, 0.327f, 1.f },	/* Warn */
	ImVec4{ 0.946f, 0.283f, 0.283f, 1.f },	/* Error */
	ImVec4{ 1.f, 0.f, 0.8f, 1.f } 	/* Fatal */
	};
};