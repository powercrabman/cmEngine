#pragma once
#include "cmApplication.h"

class Demo : public cmApplication
{
public:
	Demo() = default;
	virtual ~Demo() = default;

private:
	void Initialize() override;
	void CleanUp() override;
};
