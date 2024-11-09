#pragma once
#include "cmIKeyboard.h"

//////////////////////////////////////////////////////////////////////
// Poll 형식으로 상태를 업데이트하는 키보드 클래스
// Event 형식의 cmKeyboardEvent 을 사용하는 것을 권장
//////////////////////////////////////////////////////////////////////

class cmKeyboard : public cmIKeyboard
{
	ENGINE_MODULE_BODY();
public:
	cmKeyboard();
	virtual ~cmKeyboard();

	void Initialize() override
	{
		mKeyState.fill(eKeyState::Away);
	}

	void Update() override;

	[[nodiscard]] __forceinline bool IsAway(eKeyCode inKeyCode) const override { return mKeyState[(uint32)inKeyCode] == eKeyState::Away; }
	[[nodiscard]] __forceinline bool IsHold(eKeyCode inKeyCode) const override { return mKeyState[(uint32)inKeyCode] == eKeyState::Hold; }
	[[nodiscard]] __forceinline bool IsPressed(eKeyCode inKeyCode) const override { return mKeyState[(uint32)inKeyCode] == eKeyState::Pressed; }
	[[nodiscard]] __forceinline bool IsRelease(eKeyCode inKeyCode) const override { return mKeyState[(uint32)inKeyCode] == eKeyState::Release; }

private:
	enum {KEY_STATE_MAX = 256};
	std::array<eKeyState, KEY_STATE_MAX> mKeyState = {};
};