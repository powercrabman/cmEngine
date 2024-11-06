#pragma once

class cmResourceBase
{
public:
	cmResourceBase() = default;
	virtual ~cmResourceBase() = default;

	virtual void Load(std::wstring_view inFilePath) abstract;
	virtual void Save(std::wstring_view inFilePath) abstract;
};