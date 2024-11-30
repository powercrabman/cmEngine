#pragma once

namespace cmEngine
{
	enum class eKeyCode
	{
		None = 0,
		Tab = 512,
		Left,
		Right,
		Up,
		Down,
		PageUp,
		PageDown,
		Home,
		End,
		Insert,
		Delete,
		Backspace,
		Space,
		Enter,
		Escape,
		LeftCtrl, LeftShift, LeftAlt, LeftSuper,
		RightCtrl, RightShift, RightAlt, RightSuper,
		Menu,
		Num_0, Num_1, Num_2, Num_3, Num_4, Num_5, Num_6, Num_7, Num_8, Num_9,
		A, B, C, D, E, F, G, H, I, J,
		K, L, M, N, O, P, Q, R, S, T,
		U, V, W, X, Y, Z,
		F1, F2, F3, F4, F5, F6,
		F7, F8, F9, F10, F11, F12,
		F13, F14, F15, F16, F17, F18,
		F19, F20, F21, F22, F23, F24,
		Apostrophe,
		Comma,
		Minus,
		Period,
		Slash,
		Semicolon,
		Equal,
		LeftBracket,
		Backslash,
		RightBracket,
		GraveAccent,
		CapsLock,
		ScrollLock,
		NumLock,
		PrintScreen,
		Pause,
		Keypad0, Keypad1, Keypad2, Keypad3, Keypad4,
		Keypad5, Keypad6, Keypad7, Keypad8, Keypad9,
		KeypadDecimal,
		KeypadDivide,
		KeypadMultiply,
		KeypadSubtract,
		KeypadAdd,
		KeypadEnter,
		KeypadEqual,
		AppBack,
		AppForward,

		GamepadStart,
		GamepadBack,
		GamepadFaceLeft,
		GamepadFaceRight,
		GamepadFaceUp,
		GamepadFaceDown,
		GamepadDpadLeft,
		GamepadDpadRight,
		GamepadDpadUp,
		GamepadDpadDown,
		GamepadL1,
		GamepadR1,
		GamepadL2,
		GamepadR2,
		GamepadL3,
		GamepadR3,
		GamepadLStickLeft,
		GamepadLStickRight,
		GamepadLStickUp,
		GamepadLStickDown,
		GamepadRStickLeft,
		GamepadRStickRight,
		GamepadRStickUp,
		GamepadRStickDown,

		MouseLeft, MouseRight, MouseMiddle, MouseX1, MouseX2, MouseWheelX, MouseWheelY,

		ReservedForModCtrl, ReservedForModShift, ReservedForModAlt, ReservedForModSuper,
		COUNT,
	};

	enum class eKeyState
	{
		Pressed,
		Hold,
		Release,
		Away,

		Count
	};

	class Input
	{
	public:
		static NODISCARD FORCEINLINE bool IsAway(eKeyCode inKeyCode) { return !ImGui::IsKeyDown(static_cast<ImGuiKey>(inKeyCode)); }
		static NODISCARD FORCEINLINE bool IsHold(eKeyCode inKeyCode) { return ImGui::IsKeyDown(static_cast<ImGuiKey>(inKeyCode)); }
		static NODISCARD FORCEINLINE bool IsPressed(eKeyCode inKeyCode) { return ImGui::IsKeyPressed(static_cast<ImGuiKey>(inKeyCode)); }
		static NODISCARD FORCEINLINE bool IsRelease(eKeyCode inKeyCode) { return ImGui::IsKeyReleased(static_cast<ImGuiKey>(inKeyCode)); }

		static NODISCARD FORCEINLINE bool IsKeyState(eKeyCode inKeyCode, eKeyState inKeyState)
		{
			switch (inKeyState)
			{
			case eKeyState::Pressed:	return IsPressed(inKeyCode);
			case eKeyState::Hold:		return IsHold(inKeyCode);
			case eKeyState::Release:	return IsRelease(inKeyCode);
			case eKeyState::Away:	 	return IsAway(inKeyCode);
			default: assert(false);
			}

			return false;
		}

		static auto GetMousePosition()
		{
			ImVec2 vec = ImGui::GetMousePos();
			return std::make_pair(vec.x, vec.y);
		}
	};

	//===================================================
	//                    ToString
	//===================================================

	inline const char* ToString(eKeyCode inKeyCode) 
	{
		return ImGui::GetKeyName((ImGuiKey)inKeyCode);
	}
}
