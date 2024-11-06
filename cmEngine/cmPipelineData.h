#pragma once

struct cmPipelineData
{
	void Clear()
	{
		Geometry = nullptr;
		InputLayout = nullptr;
		VertexShader = nullptr;
		PixelShader = nullptr;
	}

	cmGeometry*				Geometry           = nullptr;
	cmInputLayoutBase*		InputLayout        = nullptr;
	cmVertexShader*			VertexShader       = nullptr;
	cmPixelShader*			PixelShader        = nullptr;
};

