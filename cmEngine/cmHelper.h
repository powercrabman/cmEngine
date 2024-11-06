#pragma once

namespace cmHelper
{
	template<typename Ty>
	inline auto RegisterGUI() -> decltype(Engine->GetRenderer()->GetGUIRenderer()->RegisterGUI<Ty>())
	{
		return Engine->GetRenderer()->GetGUIRenderer()->RegisterGUI<Ty>();
	}
}
