#pragma once

struct cmTypeID
{
	inline bool operator==(const cmTypeID& inOther) const
	{
		return Value == inOther.Value;
	}

	const void* Value;
};

template<typename Ty>
class cmTypeIDGen
{
public:
	consteval inline static cmTypeID ID()
	{
		return m_typeID;
	}

private:
	constexpr inline static char m_value{};
	constexpr inline static cmTypeID m_typeID{ &m_value };
};

template<typename Ty>
consteval cmTypeID GetTypeID()
{
	return cmTypeIDGen<Ty>::ID();
}

namespace std
{
	template<>
	struct hash<cmTypeID>
	{
		std::size_t operator()(const cmTypeID& typeID) const noexcept
		{
			return std::hash<const void*>()(typeID.Value);
		}
	};
}