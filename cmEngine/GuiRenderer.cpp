#include "EnginePch.h"
#include "Gui.h"

namespace cmEngine
{
	void GuiRenderer::Initialize()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(GameWindow::GetHwnd());
		ImGui_ImplDX11_Init(Renderer::GetDevice().Get(), Renderer::GetContext().Get());
	}

	void GuiRenderer::Destroy()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		mGuiRepo.clear();
		mConcreteGuiRepo.clear();
		mGuiList.clear();
	}

	Gui* GuiRenderer::CreateGui(std::string_view inName)
	{
		if (mGuiRepo.contains(inName.data()))
		{
			assert(false);
			ENGINE_LOG_ERROR("already exist gui");
			return mGuiRepo[inName.data()].gui.get();
		}

		// make instance
		Scope<Gui> gui = Scope<Gui>(new Gui);
		gui->mName     = inName;
		Gui* pGui  = gui.get();

		// insert to list
		uint64 pushIdx = mGuiList.size();
		mGuiList.push_back(pGui);

		// insert to hash map
		mGuiRepo.emplace(inName, GuiNode{
			                 .gui = std::move(gui),
			                 .listIdx = pushIdx}
		);

		return pGui;
	}

	Gui* GuiRenderer::FindGuiOrNull(std::string_view inName)
	{
		auto iter = mGuiRepo.find(inName.data());

		if (iter == mGuiRepo.end())
		{
			return  nullptr;
		}
		else
		{
			return iter->second.gui.get();
		}
	}

	bool GuiRenderer::RemoveGui(std::string_view inName)
	{
		auto iter = mGuiRepo.find(inName.data());

		if (iter == mGuiRepo.end())
		{
			assert(false);
			ENGINE_LOG_ERROR("{} : gui do not exist.", inName);
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
				mGuiRepo[successor->GetName()].listIdx = eraseListIdx; 
			}

			mGuiList.pop_back(); 
			mGuiRepo.erase(iter); 

			return true;
		}
	}

	void GuiRenderer::Render()
	{
		//Gui Render Begin
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//Gui Render
		for (Gui* gui : mGuiList)
		{
			// Gui Hotkey Handler
			if (gui->HasHotKey() && Input::IsPressed(gui->GetHotKey()))
			{
				gui->ToggleVisible();
			}

			// Gui Layout Render
			if (gui->IsVisible())
			{
				gui->RenderGui();
			}
		}

		//Gui Render End
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}