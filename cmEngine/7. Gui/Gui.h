#pragma once

namespace cmEngine
{
	class Gui
	{
	public:
		virtual ~Gui() = default;

		// Core
		virtual void	RenderGui();

		// Layout
		void		SetLayoutCallback(const std::function<void()>& inLayoutCallback) { mLayoutCallback = inLayoutCallback; }

		// HotKey
		void		SetHotKey(eKeyCode inKey) { mHotKey = inKey; }
		eKeyCode	GetHotKey() const { return mHotKey; }
		bool		HasHotKey() const { return mHotKey != eKeyCode::None; }

		// mVisible
		bool*		GetVisiblePtr() { return &mVisible; }
		void		ToggleVisible() { mVisible = !mVisible; }
		void		SetVisible(bool inVisible) { mVisible = inVisible; }
		bool		IsVisible() const { return mVisible; }

		// Name
		const char* GetName() const { return mName.c_str(); }

		// TypeID
		TypeID		GetTypeID() const { return mTypeID; }

	protected:
		friend class GuiRenderer;
		Gui() = default;

	private:
		std::string				mName;
		std::function<void()>	mLayoutCallback;
		eKeyCode				mHotKey = eKeyCode::None;
		bool					mVisible;
		TypeID					mTypeID;
	};
}
