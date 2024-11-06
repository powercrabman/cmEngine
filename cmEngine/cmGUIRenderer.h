#pragma once
#include "cmGUI.h"

class cmGUI;
class cmGraphicsDevice;

template<typename Ty>
concept TyBasedcmGUI = std::is_base_of<cmGUI, Ty>::value;

class cmGUIRenderer
{
	friend class cmRenderer;
public:
	virtual ~cmGUIRenderer();

	template<TyBasedcmGUI Ty>
	Ty* RegisterGUI()
	{
		// 이미 존재하는 GUI인지 탐색
		auto it = mGUINames.find(TYPE_ID(Ty));

		// 이미 존재할 경우
		if (it != mGUINames.end())
		{
			LOG_WARN("RegisterGUI Warn! Already exist GUI.");
			return static_cast<Ty*>(it->second.get());
		}

		std::unique_ptr<Ty> obj = std::make_unique<Ty>();
		obj->Initialize();

		Ty* ptr = obj.get();
		mGUIRepo.push_back(ptr);
		mGUINames[TYPE_ID(Ty)] = std::move(obj);
		LOG_INFO("%s : GUI Register Done.", typeid(Ty).name());

		return ptr;
	}

	template<TyBasedcmGUI Ty>
	[[nodiscard]] cmGUI* FindGUIOrNull()
	{
		auto iter = mGUINames.find(TYPE_ID(Ty));

		// 존재하지 않음
		if (iter == mGUINames.end())
		{
			LOG_ERROR("Ty* FindGUIOrNull() : Cannot find GUI! Return nullptr. ");
			return nullptr;
		}

		LOG_DEBUG("Find GUI %s", typeid(Ty).name());
		return iter->second.get();
	}

	// TODO : GUI 제거 로직

	void Render()
	{
		//GUI RENDER BEGIN
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//GUI RENDER
		for (const auto& gui : mGUIRepo)
		{
			gui->KeyHandler();

			if (gui->IsVisible())
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

	void CleanUp()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		mGUIRepo.clear();
	}

private:
	cmGUIRenderer();
	void Initialize(HWND hwnd, cmGraphicsDevice* inGfx);

private:
	std::vector<cmGUI*> mGUIRepo;
	std::unordered_map<cmTypeID, std::unique_ptr<cmGUI>> mGUINames;
};