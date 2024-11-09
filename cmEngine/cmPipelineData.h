#pragma once

class cmTexture;

struct cmPipelineData
{
	void Clear()
	{
		Mesh		 = nullptr;
		VertexShader = nullptr;
		PixelShader  = nullptr;
		Texture      = nullptr;
		SamplerState = nullptr;
	}

	cmMesh*					Mesh               = nullptr;
	cmVertexShader*			VertexShader       = nullptr;
	cmPixelShader*			PixelShader        = nullptr;
	cmTexture*				Texture            = nullptr;
	ID3D11SamplerState*		SamplerState       = nullptr;
};