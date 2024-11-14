#pragma once

namespace cmEngine
{
	class Gui
	{
	public:
		Gui(std::string_view inName);
		virtual ~Gui() {}
		
		// Core
		void	RenderGUI();
		void	HotKeyHandler();

		// Callback
		void	SetLayoutCallback(const std::function<void()>& inCallback) { mLayoutCallback = inCallback; }

		// Visible
		void	SetVisible(bool visible) { mVisible = visible; }
		bool	GetVisible() const { return mVisible; }
		void	ToggleVisible() { mVisible = !mVisible; }
		bool*	GetVisibleAddr() { return &mVisible; }

		// Hotkey
		void		SetHotKey(eKeyCode inKeyCode) { mHotKey = inKeyCode; }
		eKeyCode	GetHotKey() const { return mHotKey; }
		bool		HasHotKey() const { return mHotKey != eKeyCode::None; }

		const char* GetName() const { return mName.c_str(); }

	private:
		std::string mName    = {};
		bool		mVisible = true;
		eKeyCode	mHotKey  = eKeyCode::None;

		std::function<void()> mLayoutCallback = nullptr;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline cmEngine::Gui::Gui(std::string_view inName)
		: mName(inName)
	{
	}

	inline void Gui::RenderGUI()
	{
		if (mLayoutCallback)
		{
			mLayoutCallback();
		}
	}

	inline void Gui::HotKeyHandler()
	{
		if (mLayoutCallback && HasHotKey() && Input::IsPressed(mHotKey))
		{
			ToggleVisible();
		}
	}

}

