#pragma once
#include "RenderComponent.h"

class Geometry;

namespace cmEngine
{
	class GeometryRenderer : public RenderComponent
	{
	public:
		COMPONENT_BODY(GeometryRenderer);

		GeometryRenderer();
		virtual ~GeometryRenderer();

		// 2D
		void SetQuadGeometry(const std::array<Color, 4>& inColor);
		void SetQuadGeometry(const Color& inColor)
		{
			SetQuadGeometry({ inColor, inColor, inColor, inColor });
		}

		void SetCircleGeometry(const Color& inColor);

		// 3D (TEMP)
		void SetCube(const std::array<Color, 8>& inColor);

	private:
		std::unique_ptr<Geometry> mGeometry = nullptr;
	};
};
