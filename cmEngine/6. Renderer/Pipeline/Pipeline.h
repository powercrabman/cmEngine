#pragma once

namespace cmEngine
{
	class Pipeline
	{
	public:
		Pipeline();
		virtual ~Pipeline() = default;

		void Draw(
			Geometry*				inGeometry, 
			const Matrix&			inWorld, 
			AssetHandle<ShaderSet>	inShaderSet,
			const RenderState&		inRenderState
		)
		{
			SetWorld(inWorld);
			SetShaders(inShaderSet);
			SetRenderState(inRenderState);
			SetGeometry(inGeometry);

			Renderer::Ref().GetContext()->DrawIndexed(inGeometry->GetIndexBuffer()->GetBufferSize(), 0, 0);
		}

		void DrawTexture(
			Geometry*				inGeometry, 
			const Matrix&			inWorld, 
			AssetHandle<ShaderSet>	inShaderSet,
			const RenderState&		inRenderState,
			AssetHandle<Texture>	inTexture,
			float					inOffsetX,
			float					inOffsetY
		)
		{
			SetWorld(inWorld);
			SetShaders(inShaderSet);
			SetRenderState(inRenderState);
			SetTexture(inTexture, inOffsetX, inOffsetY);
			SetGeometry(inGeometry);

			Renderer::Ref().GetContext()->DrawIndexed(inGeometry->GetIndexBuffer()->GetBufferSize(), 0, 0);
		}

		void SetGeometry(Geometry* inGeometry)
		{
			if (mGeometry != inGeometry)
			{
				mGeometry = inGeometry;
				Renderer::Ref().GetContext()->IASetIndexBuffer(inGeometry->GetIndexBuffer()->GetBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
				VertexBuffer* vb = inGeometry->GetVertexBuffer();
				Renderer::Ref().GetContext()->IASetVertexBuffers(0, 1, vb->GetBuffer().GetAddressOf(), vb->GetStrideAddr(), vb->GetOffsetAddr());
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
		void SetShaders(AssetHandle<ShaderSet> inShaders)
		{
			if (mShaders != inShaders)
			{
				mShaders = inShaders;
				ShaderSet* shaderSet = ASSET_MANAGER.TryGetAsset(mShaders);
				Renderer::Ref().GetContext()->VSSetShader(shaderSet->GetVertexShader()->GetShader().Get(), nullptr, 0);
				Renderer::Ref().GetContext()->IASetInputLayout(shaderSet->GetVertexShader()->GetInputLayout().Get());
				Renderer::Ref().GetContext()->PSSetShader(shaderSet->GetPixelShader()->GetShader().Get(), nullptr, 0);
			}
		}

		void SetWorld(const Matrix& inWorld) const
		{
			mTransformCB->UpdateBuffer(CBTransform{ .World = inWorld });
		}

		void SetTexture(AssetHandle<Texture> inTexHandle, float offsetX = 0.f, float offsetY = 0.f)
		{
			if (mTexture != inTexHandle)
			{
				mTexture = inTexHandle;
				Renderer::Ref().GetContext()->PSSetShaderResources(0, 1, ASSET_MANAGER.TryGetAsset(mTexture)->GetShaderResourceView().GetAddressOf());
			}

			mSpriteCB->UpdateBuffer(CBSprite{
					.OffsetX = offsetX,
					.OffsetY = offsetY
				});
		}

	private:
		// Transform
		Geometry* mGeometry                          = nullptr;
		ConstantBuffer<CBTransform>*	mTransformCB = nullptr;

		// Camera
		Matrix						mViewProj = Matrix::Identity;
		ConstantBuffer<CBCamera>*	mCameraCB = nullptr;

		// texture
		AssetHandle<Texture>		mTexture    = AssetHandle<Texture>::sNullHandle;
		ConstantBuffer<CBSprite>*	mSpriteCB   = nullptr;

		// RenderState
		RenderState mRenderState            = {};
		inline static FLOAT sBlendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		inline static UINT sSampleMask      = 0xFFFFFFFF;

		// Shader
		AssetHandle<ShaderSet>		mShaders	= AssetHandle<ShaderSet>::sNullHandle;
	};
};
