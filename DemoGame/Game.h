#pragma once
#include "../cmEngine/1. Application/Application.h"

class Game : public cmEngine::Application
{
public:
	void Init() override;
	void Shutdown() override;
};