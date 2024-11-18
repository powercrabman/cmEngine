#pragma once

namespace cmEngine
{
	inline void SpriteRenderSystem(Scene* inScene)
	{
		auto view = inScene->GetView<Transform, SpriteRender>();

		for (auto entity : view)
		{
			auto [trans, spRender] = view.get<Transform, SpriteRender>(entity);

			const SpriteData& spData = spRender.sprite->GetSpriteData();

			auto [width, height] = spData.Texture->GetSize();

			float pivotRow = spData.PivotRow / height;
			float pivotCol = spData.PivotCol / width;

			Renderer::GetPipeline()->DrawTexture(
				spRender.sprite->GetGeometry(),
				trans.GetWorldMatrix(),
				spRender.shaders,
				spRender.rendererState,
				spData.Texture,
				0, 0
			);
		}
	}
}