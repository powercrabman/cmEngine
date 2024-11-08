#include "pch.h"
#include "cmComponent.h"

cmComponent::cmComponent()
{
	mComponentID = sComponentIDCounter++;
}

cmComponent::~cmComponent()
{
}
