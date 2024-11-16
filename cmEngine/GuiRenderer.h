#pragma once
#include "GuiFrame.h"

namespace cmEngine
{
	class Gui;

	class GuiRenderer
	{
		friend class EngineCore;
	public:
		template<typename GuiFrameType>
		static GuiFrameType* CreateGuiFrame();

		template<typename GuiFrameType>
		static GuiFrameType* FindGuiFrameOrNull()
		{
			static_assert(std::is_base_of<GuiFrame, GuiFrameType>::value, "GuiFrameType must inherit from GuiFrame");
			auto iter = mGuiFrameRepo.find(TYPE_ID(GuiFrameType));

			if (iter == mGuiFrameRepo.end())
			{
				assert(false);
				ENGINE_LOG_DEBUG("do not exist gui frame");
				return nullptr;
			}
			else
			{
				return static_cast<GuiFrameType*>(iter->second.get());
			}
		}

		static Gui* CreateGui(std::string_view inGuiName);
		static Gui* FindGuiOrNull(std::string_view inGuiName);
		static bool RemoveGui(std::string_view inGuiName);

		static void Render();
	
	private:
		static void Initialize();
		static void Destroy();

	private:
		inline static std::unordered_map<TypeID, Scope<GuiFrame>>			mGuiFrameRepo = {};
		inline static std::unordered_map<std::string, Scope<Gui>>			mGuiRepo	  = {};
		inline static BatchSystem<Gui>										mGuiBatch	  = {};
	};

	//===================================================
	//                      Inline
	//===================================================

	template <typename GuiFrameType>
	inline GuiFrameType* GuiRenderer::CreateGuiFrame()
	{
		static_assert(std::is_base_of<GuiFrame, GuiFrameType>::value, "GuiFrameType must inherit from GuiFrame");

		const std::string typeName = typeid(GuiFrameType).name();
		ENGINE_LOG_INFO("Creating GuiFrame of type: {}", typeName);

		if (mGuiFrameRepo.find(TYPE_ID(GuiFrameType)) != mGuiFrameRepo.end()) {
			ENGINE_LOG_WARN("GuiFrame of this type already exists: {}", typeName);
			return static_cast<GuiFrameType*>(mGuiFrameRepo[TYPE_ID(GuiFrameType)].get());
		}

		// Create GUI object
		Gui* gui = CreateGui(typeName);
		if (!gui) {
			ENGINE_LOG_ERROR("Failed to create Gui for: {}", typeName);
			return nullptr;
		}

		// Create and store GuiFrame
		auto [iter, result] = mGuiFrameRepo.emplace(TYPE_ID(GuiFrameType), MakeScope<GuiFrameType>());
		if (!result) {
			ENGINE_LOG_ERROR("Failed to create GuiFrame. Type already exists: {}", typeName);
			return nullptr;
		}

		// Initialize GuiFrame
		auto* frame = static_cast<GuiFrameType*>(iter->second.get());
		frame->SetGui(gui);
		frame->Initialize();

		// Register layout callback
		gui->SetLayoutCallback([frame]() { frame->GuiLayout(); });

		ENGINE_LOG_INFO("GuiFrame created successfully: {}", typeName);
		return frame;
	}

}

