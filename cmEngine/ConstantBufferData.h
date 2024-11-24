#pragma once

namespace cmEngine
{
	INTERFACE ConstantBufferDataBase{};

	struct CBTransform : IMPLEMENTS ConstantBufferDataBase
	{
		Matrix World;
	};

	struct CBCamera : IMPLEMENTS ConstantBufferDataBase
	{
		Matrix ViewProj;
	};

	struct CBSprite : IMPLEMENTS ConstantBufferDataBase
	{
		float	OffsetX;
		float	OffsetY;
		float	NotUse[2];
	};
}
