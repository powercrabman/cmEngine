#pragma once

class cmPipeline
{
public:
	cmPipeline() = default;
	virtual ~cmPipeline() = default;

	void DrawIndices()
	{
		ID3D11DeviceContext* context = Engine->GetRenderer()->GetGraphicsDevice()->GetContext();
		context->DrawIndexed(mPipeData.Mesh->GetIndexBuffer()->GetBufferSize(), 0, 0);
	}

	void Draw()
	{
		ID3D11DeviceContext* context = Engine->GetRenderer()->GetGraphicsDevice()->GetContext();
		context->Draw(mPipeData.Mesh->GetVertexBuffer()->GetBufferSize(), 0);
	}

	void SubmitPipeline(const cmPipelineData& inPipelineDate)
	{
		ID3D11DeviceContext* context = Engine->GetRenderer()->GetGraphicsDevice()->GetContext();

		if (mPipeData.Mesh != inPipelineDate.Mesh)
		{
			mPipeData.Mesh = inPipelineDate.Mesh;


			cmVertexBuffer* vertexBuffer = mPipeData.Mesh->GetVertexBuffer();
			cmIndexBufferU32* indexBuffer = mPipeData.Mesh->GetIndexBuffer();
			context->IASetVertexBuffers(0, 1, vertexBuffer->GetBufferRef(), vertexBuffer->GetStrideRef(), vertexBuffer->GetOffsetRef());
			context->IASetIndexBuffer(indexBuffer->GetBuffer(), DXGI_FORMAT_R32_UINT, 0);
		}

		if (mPipeData.VertexShader != inPipelineDate.VertexShader)
		{
			mPipeData.VertexShader = inPipelineDate.VertexShader;
			context->VSSetShader(mPipeData.VertexShader->GetShader(), nullptr, 0);
			context->IASetInputLayout(mPipeData.VertexShader->GetInputlayout());
		}

		if (mPipeData.PixelShader != inPipelineDate.PixelShader)
		{
			mPipeData.PixelShader = inPipelineDate.PixelShader;
			context->PSSetShader(mPipeData.PixelShader->GetShader(), nullptr, 0);
		}

		// TEMP
		if (mPipeData.Texture != inPipelineDate.Texture)
		{
			mPipeData.Texture = inPipelineDate.Texture;
			context->PSSetShaderResources(0, 1, mPipeData.Texture->GetShaderResourcePtr());
		}

		if (mPipeData.SamplerState != inPipelineDate.SamplerState)
		{
			mPipeData.SamplerState = inPipelineDate.SamplerState;
			context->PSSetSamplers(0, 1, &mPipeData.SamplerState);
		}

	}

	void SubmitGraphicsData()
	{
		ID3D11DeviceContext* context = Engine->GetRenderer()->GetGraphicsDevice()->GetContext();

		// Constant Buffer

		// VS
		const std::vector<cmConstantBufferBase*>& vsCBList = mPipeData.VertexShader->FindConstantBuffers();
		for (int idx = 0; idx < vsCBList.size(); ++idx)
		{
			cmConstantBufferBase* cb = vsCBList[idx];
			if (cb != ConstantBufferDatas[idx])
			{
				context->VSSetConstantBuffers(idx, 1, cb->GetBufferPtr());
			}
		}

		// PS
		const std::vector<cmConstantBufferBase*>& psCBList = mPipeData.PixelShader->FindConstantBuffers();
		for (int idx = 0; idx < psCBList.size(); ++idx)
		{
			cmConstantBufferBase* cb = psCBList[idx];
			if (cb != ConstantBufferDatas[idx])
			{
				context->PSSetConstantBuffers(idx, 1, cb->GetBufferPtr());
			}
		}
	}

	void Clear()
	{
		mPipeData.Clear();
		ConstantBufferDatas.fill(nullptr);
	}

private:
	// Dirty bits
	cmPipelineData mPipeData = {};

	enum { CONSTANTBUFFER_SLOT_MAX = 10 }; // TEMP
	std::array<cmConstantBufferBase*, CONSTANTBUFFER_SLOT_MAX> ConstantBufferDatas = {}; // TODO : 없애도 될듯
};