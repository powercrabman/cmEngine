#pragma once

class cmPipeline
{
	// Constant Buffer의 Dirty bit는 자체적으로 관리함
	enum ePipelineDirtyFlag
	{
		PIPELINE_DIRTY_FLAG_NONE         = 0,
		PIPELINE_DIRTY_FLAG_GEOMETRY     = 1 << 0,
		PIPELINE_DIRTY_FLAG_INPUTLAYOUT  = 1 << 1,
		PIPELINE_DIRTY_FLAG_VERTEXSHADER = 1 << 2,
		PIPELINE_DIRTY_FLAG_PIXELSHADER  = 1 << 3,
	};

public:
	cmPipeline() = default;
	virtual ~cmPipeline() = default;

	void DrawIndices()
	{
		ID3D11DeviceContext* context = Engine->GetRenderer()->GetGraphicsDevice()->GetContext();
		context->DrawIndexed(mPipData.Geometry->GetIndexBuffer()->GetBufferSize(), 0, 0);
	}

	void Draw()
	{
		ID3D11DeviceContext* context = Engine->GetRenderer()->GetGraphicsDevice()->GetContext();
		context->Draw(mPipData.Geometry->GetVertexBuffer()->GetBufferSize(), 0);
	}

	void SetPipeline(const cmPipelineData& inPipelineDate)
	{
		if (mPipData.Geometry != inPipelineDate.Geometry)
		{
			mPipData.Geometry = inPipelineDate.Geometry;
			EnableDirtyBit(PIPELINE_DIRTY_FLAG_GEOMETRY);
		}

		if (mPipData.InputLayout != inPipelineDate.InputLayout)
		{
			mPipData.InputLayout = inPipelineDate.InputLayout;
			EnableDirtyBit(PIPELINE_DIRTY_FLAG_INPUTLAYOUT);
		}

		if (mPipData.VertexShader != inPipelineDate.VertexShader)
		{
			mPipData.VertexShader = inPipelineDate.VertexShader;
			EnableDirtyBit(PIPELINE_DIRTY_FLAG_VERTEXSHADER);
		}

		if (mPipData.PixelShader != inPipelineDate.PixelShader)
		{
			mPipData.PixelShader = inPipelineDate.PixelShader;
			EnableDirtyBit(PIPELINE_DIRTY_FLAG_PIXELSHADER);
		}
	}

	void SubmitPipeline()
	{
		ID3D11DeviceContext* context = Engine->GetRenderer()->GetGraphicsDevice()->GetContext();

		if (mDirtyBits != PIPELINE_DIRTY_FLAG_NONE)
		{
			if (mDirtyBits & PIPELINE_DIRTY_FLAG_GEOMETRY)
			{
				cmVertexBuffer* vertexBuffer = mPipData.Geometry->GetVertexBuffer();
				cmIndexBufferU32* indexBuffer = mPipData.Geometry->GetIndexBuffer();
				context->IASetVertexBuffers(0, 1, vertexBuffer->GetBufferRef(), vertexBuffer->GetStrideRef(), vertexBuffer->GetOffsetRef());
				context->IASetIndexBuffer(indexBuffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
				DisableDirtyBit(PIPELINE_DIRTY_FLAG_GEOMETRY);
			}
			if (mDirtyBits & PIPELINE_DIRTY_FLAG_INPUTLAYOUT)
			{
				context->IASetInputLayout(mPipData.InputLayout->GetInputLayout());
				DisableDirtyBit(PIPELINE_DIRTY_FLAG_INPUTLAYOUT);
			}
			if (mDirtyBits & PIPELINE_DIRTY_FLAG_VERTEXSHADER)
			{
				context->VSSetShader(mPipData.VertexShader->GetShader(), nullptr, 0);
				DisableDirtyBit(PIPELINE_DIRTY_FLAG_VERTEXSHADER);
			}
			if (mDirtyBits & PIPELINE_DIRTY_FLAG_PIXELSHADER)
			{
				context->PSSetShader(mPipData.PixelShader->GetShader(), nullptr, 0);
				DisableDirtyBit(PIPELINE_DIRTY_FLAG_PIXELSHADER);
			}
		}
	}

	void Clear()
	{
		mPipData.Clear();
		mDirtyBits = PIPELINE_DIRTY_FLAG_NONE;
	}

private:
	void EnableDirtyBit(ePipelineDirtyFlag flag)
	{
		mDirtyBits |= flag;
	}

	void DisableDirtyBit(ePipelineDirtyFlag flag)
	{
		mDirtyBits &= ~flag;
	}

private:
	// Dirty bits
	uint32 mDirtyBits = PIPELINE_DIRTY_FLAG_NONE;

	cmPipelineData mPipData = {};
};