#include "EnginePch.h"
#include "ResourceBase.h"


cmEngine::ResourceBase::ResourceBase()
{
	static uint32 sIdCounter = 0;
	mID = sIdCounter++;
}
