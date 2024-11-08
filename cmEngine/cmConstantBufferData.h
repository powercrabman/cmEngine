#pragma once

struct cmConstantBufferDataBase {};

struct cmCBTransform : cmConstantBufferDataBase
{
	Matrix World;
	const inline static eConstantBufferType ConstantBufferType = eConstantBufferType::TransformData;
};

struct cmCBCamera : cmConstantBufferDataBase
{
	Matrix ViewProj;
	const inline static eConstantBufferType ConstantBufferType = eConstantBufferType::CameraData;
};