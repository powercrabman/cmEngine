#include "pch.h"
#include "cmDebugGUI.h"
#include "cmWindowsManager.h"
#include "cmWindow.h"

void cmDebugGUI::Initialize()
{
	SetHotKey(ImGuiKey_F7);

#if defined(DEBUG) || defined(_DEBUG)
	SetVisible(true);
#else
	SetVisible(false);
#endif

}

void cmDebugGUI::RenderGUI()
{
	ImGuiIO& io = ImGui::GetIO();
	static ImGuiWindowFlags flag = ImGuiWindowFlags_NoNavInputs | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse;

	//위치 설정
	if (mNeedWindowPosAdjust)
	{
		ImGui::SetNextWindowPos(mScreenPosToAdjust);
		mNeedWindowPosAdjust = false;
	}

	// 플래그 설정
	ImGui::SetNextWindowBgAlpha(mWindowAlpha);
	ImGui::Begin(mWindowName, (bool*)0, flag | mMoveFlag);
	ImGui::SeparatorText("Debug Window");
	ImGui::Helper::Tooltip("Right-click for option");

	// 메뉴
	if (ImGui::BeginPopupContextWindow())
	{
		static bool noMoveButton = true;

		// 알파값 조절
		if (ImGui::BeginMenu("Adjust window's transparent"))
		{
			ImGui::Text("Adjust Transparent");
			ImGui::SliderFloat("##Trans", &mWindowAlpha, 0, 1.f);

			ImGui::End();
		}

		if (ImGui::BeginMenu("Set Position"))
		{
			static int margin = 20.f;
			static eCalcLayoutPositionX optX = eCalcLayoutPositionX::Left;
			static eCalcLayoutPositionY optY = eCalcLayoutPositionY::Top;

			ImGui::Text("Set margin");
			ImGui::SliderInt("px##margin", &margin, 0, 100.f, "%d pixel");

			ImGui::Separator();
			// 윈도우 위치 설정
			if (ImGui::Selectable("Left-Top", &mNeedWindowPosAdjust)) { optX = eCalcLayoutPositionX::Left;	optY = eCalcLayoutPositionY::Top; }
			if (ImGui::Selectable("Left-Mid", &mNeedWindowPosAdjust)) { optX = eCalcLayoutPositionX::Left;	optY = eCalcLayoutPositionY::Middle; }
			if (ImGui::Selectable("Left-Bottom", &mNeedWindowPosAdjust)) { optX = eCalcLayoutPositionX::Left;	optY = eCalcLayoutPositionY::Bottom; }
			if (ImGui::Selectable("Mid-Top", &mNeedWindowPosAdjust)) { optX = eCalcLayoutPositionX::Middle; optY = eCalcLayoutPositionY::Top; }
			if (ImGui::Selectable("Mid-Mid", &mNeedWindowPosAdjust)) { optX = eCalcLayoutPositionX::Middle; optY = eCalcLayoutPositionY::Middle; }
			if (ImGui::Selectable("Mid-Bottom", &mNeedWindowPosAdjust)) { optX = eCalcLayoutPositionX::Middle; optY = eCalcLayoutPositionY::Bottom; }
			if (ImGui::Selectable("Right-Top", &mNeedWindowPosAdjust)) { optX = eCalcLayoutPositionX::Right; optY = eCalcLayoutPositionY::Top; }
			if (ImGui::Selectable("Right-Mid", &mNeedWindowPosAdjust)) { optX = eCalcLayoutPositionX::Right; optY = eCalcLayoutPositionY::Middle; }
			if (ImGui::Selectable("Right-Bottom", &mNeedWindowPosAdjust)) { optX = eCalcLayoutPositionX::Right; optY = eCalcLayoutPositionY::Bottom; }

			if (mNeedWindowPosAdjust)
			{
				// 배치할 위치 계산
				const ImVec2& vp = ImGui::GetMainViewport()->Size;
				mScreenPosToAdjust.x = vp.x * 0.5f * (int)optX;
				mScreenPosToAdjust.y = vp.y * 0.5f * (int)optY;

				const ImVec2& winSize = ImGui::FindWindowByName(mWindowName)->Size;

				mScreenPosToAdjust = ImGui::Helper::CalcLayoutPosition(mScreenPosToAdjust, winSize, margin, optX, optY);
			}


			ImGui::EndMenu();
		}

		// Move Flag
		if (ImGui::Checkbox("No move", &noMoveButton)) { mMoveFlag = noMoveButton ? ImGuiWindowFlags_NoMove : ImGuiWindowFlags_None; };

		ImGui::Separator();
		if (ImGui::Selectable("Close")) { SetVisible(false); }

		ImGui::EndPopup();
	}

	ImGui::Separator();

	// 마우스
	if (ImGui::TreeNode("Mouse"))
	{
		// 마우스 위치
		if (ImGui::IsMousePosValid())
		{
			ImGui::Text("Mouse Position : (%1.f, %.1f)", io.MousePos.x, io.MousePos.y);
		}
		else
		{
			ImGui::Text("Mouse Position : None");
		}

		// 마우스 커서
		constexpr static const char* mouseCursorText[ImGuiMouseCursor_COUNT + 1] = { "None", "Arrow", "TextInpt", "ResizeAll", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE", "Hand", "NotAllowed" };
		ImGui::Text("Mouse Cursor : %s", mouseCursorText[ImGui::GetMouseCursor()]);

		// 마우스 위치 변화량
		ImGui::Text("Mouse Delta : (%1.f, %1.f) ", io.MouseDelta.x, io.MouseDelta.y);

		// 드래그
		const ImVec2& leftDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
		const ImVec2& rightDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
		const ImVec2& midDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Middle);
		ImGui::Text("Mouse Drag (Left) : (%1.f, %1.f) ", leftDelta.x, leftDelta.y);
		ImGui::Text("Mouse Drag (Right) : (%1.f, %1.f) ", rightDelta.x, rightDelta.y);
		ImGui::Text("Mouse Drag (Middle) : (%1.f, %1.f) ", midDelta.x, midDelta.y);

		ImGui::Text("Mouse wheel : %.1f", io.MouseWheel);

		ImGui::Text("Mouse down : ");
		for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }

		ImGui::TreePop();
	}

	// 키보드
	if (ImGui::TreeNode("Keyboard"))
	{
		ImGui::Text("TODO!!");
		ImGui::TreePop();
	}

	// 뷰포트
	if (ImGui::TreeNode("Viewport"))
	{
		const ImVec2& win = ImGui::GetWindowSize();
		const ImVec2& pos = ImGui::GetWindowPos();
		ImGui::Text("Debug Window Size : (%1.f, %1.f)", win.x, win.y);
		ImGui::Text("Debug Window Position : (%1.f, %1.f)", pos.x, pos.y);

		ImGuiViewport* vpmain = ImGui::GetMainViewport();
		ImGui::Text("Main Viewport Size : (%1.f, %1.f)", vpmain->Size.x, vpmain->Size.y);
		ImGui::Text("Main Viewport Position : (%1.f, %1.f)", vpmain->Pos.x, vpmain->Pos.y);

		ImGuiViewport* vpwin = ImGui::GetWindowViewport();
		ImGui::Text("Focused Viewport Size : (%1.f, %1.f)", vpwin->Size.x, vpwin->Size.y);
		ImGui::Text("Focused Viewport Position : (%1.f, %1.f)", vpwin->Pos.x, vpwin->Pos.y);

		ImGui::TreePop();
	}

	// 성능
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("Performence"))
	{
		ImGui::Text("Total Time : %.3f sec", Engine->GetTimer()->GetTotalTime());
		ImGui::Text("Delta Time : %.3f ms", Engine->GetTimer()->GetDeltaTime() * 1000.f);

		int fps = Engine->GetTimer()->GetFPS();

		ImGui::Text("Frame Per Sceond : %d update per sec", fps);

		static float timeAcc = 0.f;
		timeAcc += DELTA_TIME;

		enum {FPS_BUFFER_SIZE = 10};
		static int fpsBuffer[FPS_BUFFER_SIZE] = { 0 };
		static int fpsAcc = 0;
		static int index = 0;
		static int fpsCount = 0;

		if (timeAcc >= 1.f)
		{
			fpsAcc -= fpsBuffer[index]; 
			fpsBuffer[index] = fps;     
			fpsAcc += fpsBuffer[index]; 

			index = (index + 1) % FPS_BUFFER_SIZE;

			if (fpsCount < FPS_BUFFER_SIZE) fpsCount++;
			timeAcc -= 1.f;
		}

		if (fpsCount >= FPS_BUFFER_SIZE)
		{
			ImGui::Text("10-second Average FPS : %.1f updates per sec", fpsAcc / (float)FPS_BUFFER_SIZE);
		}
		else
		{
			ImGui::Text("10-second Average FPS : counting...");
		}

		ImGui::TreePop();
	}

	ImGui::End();
}
