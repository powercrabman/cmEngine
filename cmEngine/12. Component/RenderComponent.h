#pragma once

namespace cmEngine
{
	//===================================================
	//			      Geometry Render
	//===================================================

	// TODO
	struct GeometryRender
	{
		Geometry geometry;
	};

	//===================================================
	//			        Sprite Render
	//===================================================

	struct SpriteRender
	{
		Sprite* sprite = nullptr;

		CUSTOM_SERIALIZABLE_COMPONENT_BODY(SpriteRender, sprite);

		CUSTOM_COMPONENT_TO_JSON(SpriteRender)
		{
			inOutJson["sprite"] = inData.sprite->GetName();
		}

		CUSTOM_COMPONENT_FROM_JSON(SpriteRender)
		{
			inOutData.sprite = RESOURCE_MANAGER.TryFindResource<Sprite>(inJson["sprite"]);
		}
	};

	//===================================================
	//				   Flipbook Render
	//===================================================

	struct FlipbookRender
	{
		Flipbook*	flipbook = nullptr;

		uint32		curFrame      = 0;
		float		playbackSpeed = 1.f;
		float		timeAcc       = 0.f;
		bool		finish        = false;
		bool		play          = true;

		CUSTOM_SERIALIZABLE_COMPONENT_BODY(FlipbookRender);

		CUSTOM_COMPONENT_TO_JSON(FlipbookRender)
		{
			inOutJson["flipbook"]     = inData.flipbook->GetName();
			inOutJson["playbackSpeed"] = inData.playbackSpeed;
		}

		CUSTOM_COMPONENT_FROM_JSON(FlipbookRender)
		{
			inOutData.flipbook = RESOURCE_MANAGER.TryFindResource<Flipbook>(inJson["flipbook"]);
			inOutData.playbackSpeed = inJson["playbackSpeed"];

		}
	};

	//===================================================
	//				    RenderProfile
	//===================================================

	struct RenderProfile
	{
		ShaderSet*	shaders        = nullptr;
		RenderState renderState  = RenderState::DefaultState;

		CUSTOM_SERIALIZABLE_COMPONENT_BODY(RenderProfile);

		CUSTOM_COMPONENT_TO_JSON(RenderProfile)
		{
			inOutJson["shaders"]     = inData.shaders->GetName();
			inOutJson["renderState"] = inData.renderState;
		}

		CUSTOM_COMPONENT_FROM_JSON(RenderProfile)
		{
			inOutData.shaders     = RESOURCE_MANAGER.TryFindResource<ShaderSet>(inJson["shaders"]);
			inOutData.renderState = inJson["renderState"];
		}
	};
}
