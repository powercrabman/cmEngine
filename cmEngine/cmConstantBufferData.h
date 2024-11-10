#pragma once

struct cmConstantBufferDataBase {};

struct cmCBTransform : cmConstantBufferDataBase
{
	Matrix World;
};

struct cmCBCamera : cmConstantBufferDataBase
{
	Matrix ViewProj;
};

struct cmCBSprite : cmConstantBufferDataBase
{
	float PivotCol;
	float PivotRow;
	float Pad[2]; // NOT USE
};
