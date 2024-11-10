#pragma once
#include "cmApplication.h"

class App : public cmApplication
{
public:
	void Initialize() override;
	void CleanUp() override;
};

