#pragma once

enum class eConsoleDataType
{
	Normal,
	Command,
	Error,

	Count
};

struct cmConsoleData
{
	eConsoleDataType TextType;
	std::string Text;

	inline static ImVec4 TextColor[(uint64)eConsoleDataType::Count] =
	{
		ImVec4{1.f,1.f,1.f,1.f},
		ImVec4{0.f,1.f,1.f,1.f},
		ImVec4(0.945f, 0.282f, 0.282f, 1.000f)
	};
};