#pragma once

struct cmSpriteData
{
	cmTexture* Texture = nullptr;
	uint32		Width = 0;
	uint32		Height = 0;
	uint32		PivotRow = 0;
	uint32		PivotCol = 0;
};
