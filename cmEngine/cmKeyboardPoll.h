#pragma once
#include "cmIKeyboard.h"

//////////////////////////////////////////////////////////////////////
// Poll �������� ���¸� ������Ʈ�ϴ� Ű���� Ŭ����
// Event ������ cmKeyboardEvent �� ����ϴ� ���� ����
//////////////////////////////////////////////////////////////////////

class cmKeyboardPoll : IMPLEMENTS cmIKeyboard
{
	ENGINE_MODULE_BODY();
public:
	cmKeyboardPoll();
	virtual ~cmKeyboardPoll();

	void Initialize() override
	{
		mKeyState.fill(eKeyState::Away);
	}

	void Update() override;

	[[nodiscard]] __forceinline bool IsAway(eKeyCode inKeyCode) const override { return mKeyState[(uint32)inKeyCode] == eKeyState::Away; }
	[[nodiscard]] __forceinline bool IsHold(eKeyCode inKeyCode) const override { return mKeyState[(uint32)inKeyCode] == eKeyState::Hold; }
	[[nodiscard]] __forceinline bool IsPressed(eKeyCode inKeyCode) const override { return mKeyState[(uint32)inKeyCode] == eKeyState::Pressed; }
	[[nodiscard]] __forceinline bool IsRelease(eKeyCode inKeyCode) const override { return mKeyState[(uint32)inKeyCode] == eKeyState::Release; }

	virtual void OnKeyDown(uint32 inMsg, WPARAM wParam, LPARAM lParam) override {};
	virtual void OnKeyUp(uint32 inMsg, WPARAM wParam, LPARAM lParam) override {};

	virtual void Reset() override { mKeyState.fill(eKeyState::Away); }

private:
	enum {KEY_STATE_MAX = 256};
	std::array<eKeyState, KEY_STATE_MAX> mKeyState = {};
};