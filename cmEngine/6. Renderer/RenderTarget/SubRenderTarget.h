#pragma once

namespace cmEngine
{
	class SubRenderTarget final : public RenderTarget
	{
	public:
		SubRenderTarget();
		~SubRenderTarget() override;
		void Resize(uint32 inWidth, uint32 inHeight) override;
	};
}


