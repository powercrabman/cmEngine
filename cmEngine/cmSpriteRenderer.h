#pragma once
#include "cmRenderComponent.h"
#include "cmIPreRenderable.h"
class cmSprite;

class cmSpriteRenderer 
	: public		cmRenderComponent
	, IMPLEMENTS	cmIPreRenderable
{
public:
	cmSpriteRenderer() = default;
	virtual ~cmSpriteRenderer() = default;
	
	void PreRender() override;

	void SetSprite(cmSprite* inFlipbook);
	cmSprite* GetSprite() const { return mSprite; }

private:
	cmSprite*	mSprite = nullptr;
};
