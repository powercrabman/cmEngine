#pragma once

struct cmConstantBufferDataBase {};

struct cmCBTransform : cmConstantBufferDataBase
{
	Matrix World;
};