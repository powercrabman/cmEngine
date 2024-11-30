#pragma once

namespace cmEngine
{
	enum class eResourceType
	{
		Texture,
		Sprite,
		Flipbook,
		ShaderSet,

		Count
	};

	inline constexpr const char* ToString(eResourceType e)
	{
		switch (e)
		{
		case eResourceType::Texture: return "Texture";
		case eResourceType::Sprite: return "Sprite";
		case eResourceType::Flipbook: return "Flipbook";
		case eResourceType::ShaderSet: return "ShaderSet";
		case eResourceType::Count: return "Count";
		default: return "unknown";
		}
	}

	JSON_SERIALIZE_ENUM(
		eResourceType,
		ENUM_ENTRY(eResourceType::Texture, "Texture"),
		ENUM_ENTRY(eResourceType::Sprite, "Sprite"),
		ENUM_ENTRY(eResourceType::Flipbook, "Flipbook"),
		ENUM_ENTRY(eResourceType::ShaderSet, "ShaderSet")
	);

#define RESOURCE_BODY(ResourceClassName) \
	virtual const char*			ToString() override { return #ResourceClassName; }; \
	virtual eResourceType		GetResourceType() override { return eResourceType::ResourceClassName;}\
	inline static eResourceType	sResourceType = eResourceType::ResourceClassName;\
	inline static const char*	sResourceString = #ResourceClassName;\
	friend class ResourceManager

	class ResourceBase
	{
		friend class ResourceManager;
	public:
		virtual ~ResourceBase() = default;

		virtual const char*		ToString() = 0;
		virtual eResourceType	GetResourceType() = 0;
		const char*				GetName() const { return mName.c_str(); }
		
	protected:
		ResourceBase() {}

		virtual void SaveJsonToFile(const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory = "") = 0;
		virtual bool LoadJsonFromFile(const std::filesystem::path& inFilePath, const std::filesystem::path& inDirectory = "") = 0;

		std::string mName	  = {};
	};
}
