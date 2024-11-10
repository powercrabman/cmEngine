#pragma once
#include "cmComponent.h"
#include "cmIUpdateable.h"
#include "cmIFinalUpdateable.h"
#include "cmISetupable.h"

class cmScript
	: public cmComponent
	, IMPLEMENTS cmIUpdateable
	, IMPLEMENTS cmIFinalUpdateable
	, IMPLEMENTS cmISetupable
{
public:
	cmScript() = default;
	virtual ~cmScript() = default;

	constexpr inline static eComponentType ComponentType = eComponentType::Script;

private:
};

