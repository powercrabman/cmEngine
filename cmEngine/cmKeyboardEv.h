#pragma once
#include "cmIKeyboard.h"

class cmKeyboardEv : public cmIKeyboard
{
public:
    virtual void Initialize() override
    {
        mKeyStates.fill(eKeyState::Away);
    }

    virtual void Update() override
    {
        for (auto& state : mKeyStates)
        {
            if (state == eKeyState::Pressed)
            {
                state = eKeyState::Hold;
            }
            else if (state == eKeyState::Release)
            {
                state = eKeyState::Away;
            }
        }
    }

    virtual [[nodiscard]] __forceinline bool IsAway(eKeyCode inKeyCode) const override
    {
        return mKeyStates[(uint32)inKeyCode] == eKeyState::Away;
    }

    virtual [[nodiscard]] __forceinline bool IsHold(eKeyCode inKeyCode) const override
    {
        return mKeyStates[(uint32)inKeyCode] == eKeyState::Hold;
    }

    virtual [[nodiscard]] __forceinline bool IsPressed(eKeyCode inKeyCode) const override
    {
        return mKeyStates[(uint32)inKeyCode] == eKeyState::Pressed;
    }

    virtual [[nodiscard]] __forceinline bool IsRelease(eKeyCode inKeyCode) const override
    {
        return mKeyStates[(uint32)inKeyCode] == eKeyState::Release;
    }

    virtual void OnKeyDown(uint32 inMsg, WPARAM wParam, LPARAM lParam) override
    {
        uint32 keyCode = static_cast<uint32>(wParam);
        eKeyState& state = mKeyStates[keyCode];

        if (state == eKeyState::Away || state == eKeyState::Release)
        {
            state = eKeyState::Pressed;
        }
    }

    virtual void OnKeyUp(uint32 inMsg, WPARAM wParam, LPARAM lParam) override
    {
        uint32 keyCode = static_cast<uint32>(wParam);
        mKeyStates[keyCode] = eKeyState::Release;
    }

    virtual void Reset() override { mKeyStates.fill(eKeyState::Away); }

private:
    enum { KEY_STATE_MAX = 256 };
    std::array<eKeyState, KEY_STATE_MAX> mKeyStates = {};
};