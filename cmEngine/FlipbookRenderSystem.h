#pragma once

namespace cmEngine
{
	inline void FlipbookUpdateSystem(Scene* inScene)
	{
		auto view = inScene->GetView<FlipbookRender>();
		for (auto entity : view)
		{
			auto& fbRender = view.get<FlipbookRender>(entity);

			// Flipbook Update
			const FlipbookData& data = fbRender.flipbook->GetFlipbookData();

			if (!fbRender.finish)
			{
				float duration = data.FrameDuration * (1.f / fbRender.playbackSpeed);

				fbRender.timeAcc += Timer::GetDeltaTime();

				if (fbRender.timeAcc >= duration)
				{
					fbRender.timeAcc -= duration;

					if (fbRender.curFrame < data.FrameCount - 1)
					{
						++fbRender.curFrame;
					}
					else
					{
						if (data.Loop)
						{
							fbRender.curFrame = 0;
						}
						else
						{
							fbRender.finish = true;
						}
					}
				}
			}
		}
	}

	inline void FlipbookRenderSystem(Scene* inScene)
	{
		auto view = inScene->GetView<Transform, FlipbookRender>();

		for (auto entity : view)
		{
			auto [trans, fbRender] = view.get<Transform, FlipbookRender>(entity);

			const FlipbookData& fbData = fbRender.flipbook->GetFlipbookData();
			auto [width, height] = fbData.Texture->GetSize();

			float pivotRow = fbData.PivotRow / height;
			float pivotCol = (fbData.PivotCol + fbData.Width * fbRender.curFrame) / static_cast<float>(width);

			Renderer::GetPipeline()->DrawTexture(
				fbRender.flipbook->GetGeometry(),
				trans.GetWorldMatrix(),
				fbRender.shaders,
				fbRender.rendererState,
				fbData.Texture,
				pivotRow,
				pivotCol
			);
		}
	}
}