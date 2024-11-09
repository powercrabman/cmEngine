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