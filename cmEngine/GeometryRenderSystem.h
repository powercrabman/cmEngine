#pragma once

namespace cmEngine
{
	inline void GeometryRenderSystem(Scene* inScene)
	{
		auto view = inScene->GetView<Transform, GeometryRender>();

		for (auto entity : view)
		{
			auto [trans, geo] = view.get<Transform, GeometryRender>(entity);

			Renderer::GetPipeline()->Draw(
				&geo.geometry,
				trans.GetWorldMatrix(),
				geo.shaders,
				geo.renderState
			);
		}
	}
}