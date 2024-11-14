#pragma once
#include "RenderComponent.h"
#include "IPreRenderable.h"

namespace cmEngine
{
	class Sprite;

	class SpriteRenderer
		: public		RenderComponent
		, IMPLEMENTS	IPreRenderable
	{
	public:
		COMPONENT_BODY(SpriteRenderer);

		SpriteRenderer() = default;
		virtual ~SpriteRenderer() = default;

		void PreRender() override;

		void	SetSprite(Sprite* inSprite);
		Sprite* GetSprite() const { return mSprite; }

	private:
		Sprite* mSprite = nullptr;
	};

}
