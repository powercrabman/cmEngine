#pragma once

namespace cmEngine
{

#define RESOURCE_BODY(ResourceClassName) \
	virtual const char*			ToString() override { return #ResourceClassName; }; \
	inline static eResourceType	ResourceType = eResourceType::ResourceClassName

	class ResourceBase
	{
	public:
		ResourceBase(std::string_view inName);;
		virtual ~ResourceBase() = default;

		virtual const char*			ToString() = 0;

	private:
		std::string mName = {};
	};

	//===================================================
	//                      Inline
	//===================================================

	inline ResourceBase::ResourceBase(std::string_view inName)
		: mName(inName)
	{
	}
}