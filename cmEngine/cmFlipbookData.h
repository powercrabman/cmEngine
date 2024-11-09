#pragma once

struct cmFlipbookData
{
	cmTexture*	Texture        = nullptr;
	uint32		Width          = 0;
	uint32		Height         = 0;
	uint32		PivotRow       = 0;
	uint32		PivotCol       = 0;
	float		FrameDuration  = 0.f;
	bool		Loop           = true;
};