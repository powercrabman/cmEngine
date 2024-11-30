#pragma once

namespace cmEngine
{
	class MasterRenderTarget final : public RenderTarget
	{
	public:
		MasterRenderTarget();
		~MasterRenderTarget() override;

		void Resize(uint32 inWidth, uint32 inHeight) override;
	};
}

