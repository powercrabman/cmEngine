#pragma once

INTERFACE cmIRenderable
{
public:
	cmIRenderable() = default;
	virtual ~cmIRenderable() = default;

	virtual void Render() abstract;
};

