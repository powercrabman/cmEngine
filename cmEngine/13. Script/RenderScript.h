#pragma once

namespace cmEngine
{
	//===================================================
	//			         Geometry
	//===================================================

	inline void GeometryRenderScript(Scene* inScene)
	{
		auto view = inScene->GetView<Transform, GeometryRender, RenderProfile>();

		for (auto entity : view)
		{
			auto [trans, geo, profile] = view.get<Transform, GeometryRender, RenderProfile>(entity);

			Renderer::Ref().GetPipeline()->Draw(
				&geo.geometry,
				trans.GetWorldMatrix(),
				profile.shaderSetHandle,
				profile.renderState
			);
		}
	}

	//===================================================
	//			         Flipbook
	//===================================================

	inline void FlipbookUpdateSystem(Scene* inScene)
	{
		auto view = inScene->GetView<FlipbookRender>();
		for (auto entity : view)
		{
			auto& fbRender = view.get<FlipbookRender>(entity);
			Flipbook* fb = ASSET_MANAGER.TryGetAsset(fbRender.flipbookHandle);
			if (fb)
			{
				// Flipbook Update
				const FlipbookData& data = fb->GetFlipbookData();

				if (!fbRender.play)
				{
					continue;
				}

				if (!fbRender.finish)
				{
					float duration = data.frameDuration * (1.f / fbRender.playbackSpeed);

					fbRender.timeAcc += Timer::Ref().GetDeltaTime();

					if (fbRender.timeAcc >= duration)
					{
						fbRender.timeAcc -= duration;

						if (fbRender.curFrame < data.frameCount - 1)
						{
							++fbRender.curFrame;
						}
						else
						{
							if (data.loop)
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
	}

	inline void FlipbookRenderScript(Scene* inScene)
	{
		auto view = inScene->GetView<Transform, FlipbookRender, RenderProfile>();

		for (auto entity : view)
		{
			auto [trans, fbRender, profile] = view.get<Transform, FlipbookRender, RenderProfile>(entity);

			Flipbook*	fb = ASSET_MANAGER.TryGetAsset(fbRender.flipbookHandle);
			ShaderSet*	ss = ASSET_MANAGER.TryGetAsset(profile.shaderSetHandle);
			if (fb && ss)
			{
				const FlipbookData& fbData = fb->GetFlipbookData();
				auto [width, height] = fbData.texture->GetSize();

				float offsetX = (fbData.pivotCol + fbRender.curFrame) * fbData.width / static_cast<float>(width);
				float offsetY = fbData.pivotRow * fbData.height / static_cast<float>(height);

				Renderer::Ref().GetPipeline()->DrawTexture(
					fbRender.flipbookHandle->GetGeometry(),
					trans.GetWorldMatrix(),
					profile.shaders,
					profile.renderState,
					fbData.texture,
					offsetX,
					offsetY
				);
			}
		}
	}

	//===================================================
	//			           Sprite
	//===================================================

	inline void SpriteRenderScript(Scene* inScene)
	{
		auto view = inScene->GetView<Transform, SpriteRender, RenderProfile>();

		for (auto entity : view)
		{
			auto [trans, spRender, profile] = view.get<Transform, SpriteRender, RenderProfile>(entity);

			if (spRender.sprite && profile.shaders)
			{
				const SpriteData& spData = spRender.sprite->GetSpriteData();

				auto [width, height] = spData.texture->GetSize();

				float offsetX = spData.pivotCol * spData.width / static_cast<float>(width);
				float offsetY = spData.pivotRow * spData.height / static_cast<float>(height);

				Renderer::Ref().GetPipeline()->DrawTexture(
					spRender.sprite->GetGeometry(),
					trans.GetWorldMatrix(),
					profile.shaders,
					profile.renderState,
					spData.texture,
					offsetX,
					offsetY
				);
			}
		}
	}

}
