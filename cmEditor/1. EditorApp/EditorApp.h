#pragma once
#include "1. Application/Application.h"

namespace cmEngine
{
	class EditorApp : public Application
	{
	public:
		~EditorApp() override = default;
		void Init() override;

	private:
		SubRenderTarget* mSubRenderTarget = nullptr;
	};
}
