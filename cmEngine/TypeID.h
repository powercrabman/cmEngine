#pragma once

namespace cmEngine
{
	struct TypeID
	{
		inline bool operator==(const TypeID& inOther) const
		{
			return Value == inOther.Value;
		}

		const void* Value;
	};

	template<typename Ty>
	class TypeIDGen
	{
	public:
		consteval inline static TypeID ID()
		{
			return mTypeID;
		}

	private:
		constexpr inline static char mValue{};
		constexpr inline static TypeID mTypeID{ &mValue };
	};
}

namespace std
{
	template<>
	struct hash<cmEngine::TypeID>
	{
		std::size_t operator()(const cmEngine::TypeID& typeID) const noexcept
		{
			return std::hash<const void*>()(typeID.Value);
		}
	};
}