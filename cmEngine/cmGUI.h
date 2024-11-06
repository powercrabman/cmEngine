#pragma once

class cmGUI
{
public:
	virtual ~cmGUI();

	virtual void Initialize() abstract;
	virtual void RenderGUI() abstract;

	virtual void KeyHandler() final;
	
	// Name
	void SetName(std::string_view inName) { mName = inName.data(); }
	std::string_view GetName() const { return mName; }

	// Visible
	void SetVisible(bool visible) { mVisible = visible; }
	void ToggleVisible() { mVisible = !mVisible; }
	bool* GetVisiblePtr() { return &mVisible; }
	bool IsVisible() const { return mVisible; }

	// Hotkey
	void SetHotKey(ImGuiKey inKey) { mUseHotKey = true; mHotKey = inKey; }
	ImGuiKey GetHotKey() const { return mHotKey; }
	const char* GetHotKeyToString() const
	{
		return mHotKey == ImGuiKey_None ? "" : ImGui::GetKeyName(mHotKey);
	}

protected:
	cmGUI();

private:
	std::string mName = "";

	bool mVisible = true;
	ImGuiKey mHotKey = ImGuiKey_None;
	bool mUseHotKey = false;
};
