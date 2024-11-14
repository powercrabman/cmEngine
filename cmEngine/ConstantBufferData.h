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
		float	PivotCol;
		float	PivotRow;
		float	NotUse[2];
	};
}
