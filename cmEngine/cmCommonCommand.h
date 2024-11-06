#pragma once
#include "cmICommand.h"

//=====================================
// Concrete
//=====================================

struct cmClearColorCmd : public cmICommand
{
	virtual bool operator()(const std::vector<std::string>& inArgs) const override;

	const char* GetHelpDesc() const override;
	const char* GetCommandText() const override;
};

struct cmHelpCmd : public cmICommand
{
	bool operator()(const std::vector<std::string>& inArgs) const override;

	const char* GetHelpDesc() const override;
	const char* GetCommandText() const override;
};


struct cmClearCmd : public cmICommand
{
	bool operator()(const std::vector<std::string>& inArgs) const override;

	const char* GetHelpDesc() const override;
	const char* GetCommandText() const override;
};


struct cmExitCmd : public cmICommand
{
	bool operator()(const std::vector<std::string>& inArgs) const override;

	const char* GetHelpDesc() const override;
	const char* GetCommandText() const override;
};

struct cmSayCmd : public cmICommand
{
	bool operator()(const std::vector<std::string>& inArgs) const override;

	const char* GetHelpDesc() const override;
	const char* GetCommandText() const override;
};

struct cmResizeScreenCmd : public cmICommand
{
	bool operator()(const std::vector<std::string>& inArgs) const override;

	const char* GetHelpDesc() const override;
	const char* GetCommandText() const override;
};
