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
	inline static eResourceType	ResourceType = eResourceType::ResourceClassName;\
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
		uint32					GetID() const { return mID; }

	protected:
		ResourceBase();

	private:
		virtual bool	LoadJsonFromFile(std::wstring_view inFilePath)                                    = 0;
		virtual void	SaveJsonToFile(std::wstring_view inFilePath)                                      = 0;
		virtual bool	LoadJsonFromSection(std::wstring_view inFilePath, std::string_view inSectionName) = 0;
		virtual void	SaveJsonToSection(std::wstring_view inFilePath, std::string_view inSectionName)   = 0;

	protected:
		std::string mName	= {};
		uint32		mID		= {};
	};
}