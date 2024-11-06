#include "pch.h"
#include "cmGUIRenderer.h"
#include "cmGraphicsDevice.h"

cmGUIRenderer::cmGUIRenderer()
{
	mGUIRepo.reserve(64);
}
cmGUIRenderer::~cmGUIRenderer() = default;

void cmGUIRenderer::Initialize(HWND hwnd, cmGraphicsDevice* inGfx)
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

	//ImGui::StyleColorsClassic();
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(inGfx->GetDevice(), inGfx->GetContext());
}

