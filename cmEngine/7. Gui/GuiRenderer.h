#pragma once

#include "7. Gui/Gui.h"

template<typename GuiType>
concept GuiConstraint = std::is_base_of_v<cmEngine::Gui, GuiType> &&
						!std::is_same_v<cmEngine::Gui, GuiType>;

namespace cmEngine
{
	class GuiRenderer
	{
		SINGLETON(GuiRenderer);
		struct			GuiNode;
	public:
		// Create
		Gui* CreateGui(std::string_view inName);

		template <GuiConstraint GuiType>
		GuiType* CreateConcreteGui();

		// Find
		Gui* FindGuiOrNull(std::string_view inName);

		template <GuiConstraint GuiType>
		GuiType* FindConcreteGuiOrNull();

		// Remove
		bool RemoveGui(std::string_view inName);

		template <GuiConstraint GuiType>
		bool RemoveConcreteGui();

	private:
		GuiRenderer();
		~GuiRenderer();

		// Core
		void Render();

	private:
		struct GuiNode
		{
			Scope<Gui>	gui;
			uint64		listIdx;
		};

		std::unordered_map<std::string, GuiNode>	mGuiRepo         = {};
		std::unordered_map<TypeID, GuiNode>			mConcreteGuiRepo = {};
		std::vector<Gui*>							mGuiList         = {};
	};

	//===================================================
	//                      Inline
	//===================================================

	template <GuiConstraint GuiType>
	GuiType* GuiRenderer::CreateConcreteGui()
	{
		if (mConcreteGuiRepo.contains(TYPE_ID(GuiType)))
		{
			assert(false);
			ENGINE_LOG_ERROR("already exist gui");
			return static_cast<GuiType*>(mConcreteGuiRepo[TYPE_ID(GuiType)].gui.get());
		}

		// make instance
		Scope<GuiType> gui = Scope<GuiType>(new GuiType);
		gui->mTypeID       = TYPE_ID(GuiType);
		GuiType* pGui      = gui.get();

		// insert to list
		uint64 pushIdx = mGuiList.size();
		mGuiList.push_back(pGui);

		// insert to hash map
		mConcreteGuiRepo.emplace(TYPE_ID(GuiType), GuiNode{
			                         .gui = std::move(gui),
			                         .listIdx = pushIdx }
		);

		return pGui;
	}

	template <GuiConstraint GuiType>
	GuiType* GuiRenderer::FindConcreteGuiOrNull()
	{
		auto iter = mConcreteGuiRepo.find(TYPE_ID(GuiType));

		if (iter == mConcreteGuiRepo.end())
		{
			return nullptr;
		}
		else
		{
			return static_cast<GuiType*>(iter->second.gui.get());
		}
	}

	template <GuiConstraint GuiType>
	bool GuiRenderer::RemoveConcreteGui()
	{
		auto iter = mConcreteGuiRepo.find(TYPE_ID(GuiType));

		if (iter == mConcreteGuiRepo.end())
		{
			assert(false);
			ENGINE_LOG_ERROR("{} : gui do not exist.", TYPE_ID(GuiType));
			return false;
		}
		else
		{
			uint64 eraseListIdx = iter->second.listIdx;

			// delete in mGuiList
			if (eraseListIdx != mGuiList.size() - 1)
			{
				Gui* successor = mGuiList.back();
				std::swap(mGuiList[eraseListIdx], mGuiList.back());
				mConcreteGuiRepo[successor->GetTypeID()].listIdx = eraseListIdx;
			}

			mGuiList.pop_back();
			mConcreteGuiRepo.erase(iter);

			return true;
		}
	}
}

