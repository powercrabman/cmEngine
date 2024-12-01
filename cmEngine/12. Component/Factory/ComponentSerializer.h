#pragma once

namespace cmEngine
{
#define SERIALIZABLE_COMPONENT_BODY(ClassName, ...)										\
	inline static const char* sComponentName = #ClassName;								\
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(ClassName, __VA_ARGS__);								\
	inline static bool _##ClassName##_registered = []() {								\
		ComponentSerializer::Ref().RegistSerializer<ClassName>();						\
		return true;																	\
	}()

#define CUSTOM_SERIALIZABLE_COMPONENT_BODY(ClassName)									\
	inline static const char* sComponentName = #ClassName;								\
	inline static bool _##ClassName##_registered = []() {								\
		ComponentSerializer::Ref().RegistSerializer<ClassName>();						\
		return true;																	\
	}()

	class ComponentSerializer
	{
		SINGLETON(ComponentSerializer);
	public:
		template <typename Ty>
		void RegistSerializer()
		{
			mSerializer.emplace(entt::type_hash<Ty>::value(), [](const GameEntity& e, json& inOutJson, void* inData)
				{
					Ty* data = static_cast<Ty*>(inData);
					inOutJson[std::to_string(e.GetID())][Ty::sComponentName] = *data;
				});

			mDeserializer.emplace(entt::type_hash<Ty>::value(), [](const GameEntity& e, json& inOutJson)
				{
					Ty data = inOutJson[std::to_string(e.GetID())][Ty::sComponentName];
					e.TryCreateComponent<Ty>(data);
				});

			mMapper.emplace(Ty::sComponentName, entt::type_hash<Ty>::value());
		}

		void Serializer(std::string_view inString, const GameEntity& e, json& inOutJson, void* inData)
		{
			auto iter = mMapper.find(inString.data());
			if (iter != mMapper.end()) { Serializer(iter->second, e, inOutJson, inData); }
		}

		void Serializer(entt::id_type inID, const GameEntity& e, json& inOutJson, void* inData)
		{
			auto iter = mSerializer.find(inID);
			if (iter != mSerializer.end()) { iter->second(e, inOutJson, inData); }
		}

		void Deserializer(std::string_view inString, const GameEntity& e, json& inOutJson)
		{
			auto iter = mMapper.find(inString.data());
			if (iter != mMapper.end()) { Deserializer(iter->second, e, inOutJson); }
		}

		void Deserializer(entt::id_type inID, const GameEntity& e, json& inOutJson)
		{
			auto iter = mDeserializer.find(inID);
			if (iter != mDeserializer.end()) { iter->second(e, inOutJson); }
		}

	private:
		ComponentSerializer();
		~ComponentSerializer() = default;

		std::unordered_map<entt::id_type, std::function<void(const GameEntity&, json&, void*)>>	mSerializer;
		std::unordered_map<entt::id_type, std::function<void(const GameEntity&, json&)>>		mDeserializer;
		std::unordered_map<std::string, entt::id_type>											mMapper;
	};
}
