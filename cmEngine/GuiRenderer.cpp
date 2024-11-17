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

		mGuiFrameRepo.clear();
		mGuiRepo.clear();
		mGuiBatch.Clear();
	}

	inline Gui* GuiRenderer::CreateGui(std::string_view inGuiName)
	{
		std::string name = inGuiName.data();
		auto [iter, success] = mGuiRepo.emplace(name, MakeScope<Gui>(name));
		Gui* ptr = iter->second.get();

		if (success)
		{
			mGuiBatch.Push(ptr);
		}
		else
		{
			assert(false);
			ENGINE_LOG_ERROR("already exist gui");
		}

		return ptr;
	}

	inline Gui* GuiRenderer::FindGuiOrNull(std::string_view inGuiName)
	{
		std::string name = inGuiName.data();
		if (mGuiRepo.contains(name))
		{
			return mGuiRepo[name].get();
		}
		else
		{
			assert(false);
			ENGINE_LOG_ERROR("do not exist gui");
			return nullptr;
		}
	}

	inline bool GuiRenderer::RemoveGui(std::string_view inGuiName)
	{
		auto iter = mGuiRepo.find(inGuiName.data());

		if (iter == mGuiRepo.end())
		{
			assert(false);
			ENGINE_LOG_WARN("do not exist gui");
			return false;
		}

		mGuiBatch.Remove(iter->second.get());
		mGuiRepo.erase(iter);
		return true;
	}

	void GuiRenderer::Render()
	{
		//GUI RENDER BEGIN
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//GUI RENDER
		for (Gui* gui : mGuiBatch)
		{
			gui->HotKeyHandler();

			if (gui->GetVisible())
			{
				gui->RenderGUI();
			}
		}

		//GUI RENDER END
		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}
}