#pragma once

namespace cmEngine
{
	class Pipeline
	{
	public:
		Pipeline();
		virtual ~Pipeline() = default;

		void Draw(
			Geometry* inGeometry, 
			const Matrix& inWorld, 
			ShaderSet* inShaders, 
			const RenderState& inRenderState
		)
		{
			SetWorld(inWorld);
			SetShaders(inShaders);
			SetRenderState(inRenderState);
			SetGeometry(inGeometry);

			Renderer::GetContext()->DrawIndexed(inGeometry->GetIndexBuffer()->GetBufferSize(), 0, 0);
		}

		void DrawTexture(
			Geometry* inGeometry, 
			const Matrix& inWorld, 
			ShaderSet* inShaders, 
			const RenderState& inRenderState,
			Texture* inTexture,
			float inOffsetRow,
			float inOffsetCol
		)
		{
			SetWorld(inWorld);
			SetShaders(inShaders);
			SetRenderState(inRenderState);
			SetTexture(inTexture, inOffsetCol, inOffsetRow);
			SetGeometry(inGeometry);

			Renderer::GetContext()->DrawIndexed(inGeometry->GetIndexBuffer()->GetBufferSize(), 0, 0);
		}

		void SetGeometry(Geometry* inGeometry)
		{
			if (mGeometry != inGeometry)
			{
				mGeometry = inGeometry;
				Renderer::GetContext()->IASetIndexBuffer(inGeometry->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
				VertexBuffer* vb = inGeometry->GetVertexBuffer();
				Renderer::GetContext()->IASetVertexBuffers(0, 1, vb->GetBuffer().GetAddressOf(), vb->GetStrideAddr(), vb->GetOffsetAddr());
			}
		}

		void SetViewProj(const Matrix& inViewProj) const
		{
			mCameraCB->UpdateBuffer(CBCamera{ .ViewProj = inViewProj });
		}

		void SetViewProj(const Matrix& inView, const Matrix& inProj) const
		{
			SetViewProj(inView * inProj);
		}

		void Clear();

	private:
		void SetRenderState(const RenderState& inRenderState);
		void SetShaders(ShaderSet* inShaders)
		{
			if (mShaders != inShaders)
			{
				mShaders = inShaders;
				Renderer::GetContext()->VSSetShader(mShaders->GetVertexShader()->GetShader().Get(), nullptr, 0);
				Renderer::GetContext()->IASetInputLayout(mShaders->GetVertexShader()->GetInputLayout().Get());
				Renderer::GetContext()->PSSetShader(mShaders->GetPixelShader()->GetShader().Get(), nullptr, 0);
			}
		}

		void SetWorld(const Matrix& inWorld) const
		{
			mTransformCB->UpdateBuffer(CBTransform{ .World = inWorld });
		}

		void SetTexture(Texture* inTextrue, float offsetX = 0.f, float offsetY = 0.f)
		{
			if (mTexture != inTextrue)
			{
				mTexture = inTextrue;
				Renderer::GetContext()->PSSetShaderResources(0, 1, mTexture->GetShaderResourceView().GetAddressOf());
			}

			mSpriteCB->UpdateBuffer(CBSprite{
					.PivotCol = offsetX,
					.PivotRow = offsetY
				});
		}

	private:
		// Transform
		Geometry* mGeometry                          = nullptr;
		ConstantBuffer<CBTransform>*	mTransformCB = nullptr;

		// Camera
		Matrix						mViewProj = Matrix::Identity;
		ConstantBuffer<CBCamera>*	mCameraCB = nullptr;

		// Texture
		Texture*					mTexture    = nullptr;
		ConstantBuffer<CBSprite>*	mSpriteCB   = nullptr;

		// RenderState
		RenderState mRenderState = {};
		inline static FLOAT sBlendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		inline static UINT sSampleMask = 0xFFFFFFFF;

		// Shader
		ShaderSet* mShaders = {};
	};
};
