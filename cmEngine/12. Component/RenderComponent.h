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
		AssetHandle<Sprite> spriteHandle;

		CUSTOM_SERIALIZABLE_COMPONENT_BODY(SpriteRender);

		CUSTOM_TO_JSON(SpriteRender)
		{
			inOutJson["spriteName"] = ASSET_MANAGER.TryGetAsset<Sprite>(inData.spriteHandle)->GetName();
		}

		CUSTOM_FROM_JSON(SpriteRender)
		{
			std::string name       = inJson["spriteName"];
			inOutData.spriteHandle = ASSET_MANAGER.TryFindHandle<Sprite>(name);
		}
	};

	//===================================================
	//				   Flipbook Render
	//===================================================

	struct FlipbookRender
	{
		AssetHandle<Flipbook>	flipbookHandle;

		uint32		curFrame      = 0;
		float		playbackSpeed = 1.f;
		float		timeAcc       = 0.f;
		bool		finish        = false;
		bool		play          = true;

		CUSTOM_SERIALIZABLE_COMPONENT_BODY(FlipbookRender);

		CUSTOM_TO_JSON(FlipbookRender)
		{
			inOutJson["flipbookName"]  = ASSET_MANAGER.TryGetAsset<Flipbook>(inData.flipbookHandle)->GetName();
			inOutJson["playbackSpeed"] = inData.playbackSpeed;
		}

		CUSTOM_FROM_JSON(FlipbookRender)
		{
			std::string name         = inJson["flipbookName"];
			inOutData.flipbookHandle = ASSET_MANAGER.TryFindHandle<Flipbook>(name);
			inOutData.playbackSpeed  = inJson["playbackSpeed"];
		}
	};

	//===================================================
	//				    RenderProfile
	//===================================================

	struct RenderProfile
	{
		AssetHandle<ShaderSet>	shaderSetHandle;
		RenderState				renderState		= RenderState::DefaultState;

		CUSTOM_SERIALIZABLE_COMPONENT_BODY(RenderProfile);

		CUSTOM_TO_JSON(RenderProfile)
		{
			inOutJson["ShaderSetName"]     = ASSET_MANAGER.TryGetAsset<ShaderSet>(inData.shaderSetHandle)->GetName();
			inOutJson["renderState"]       = inData.renderState;
		}

		CUSTOM_FROM_JSON(RenderProfile)
		{
			std::string name = inJson["ShaderSetName"];
			inOutData.shaderSetHandle = ASSET_MANAGER.TryFindHandle<ShaderSet>(name);
			inOutData.renderState     = inJson["renderState"];
		}
	};
}