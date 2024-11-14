#pragma once

namespace cmEngine
{

#define RESOURCE_BODY(ResourceClassName) \
	virtual const char*			ToString() override { return #ResourceClassName; }; \
	inline static eResourceType	ResourceType = eResourceType::ResourceClassName

	class ResourceBase
	{
	public:
		ResourceBase() = default;
		virtual ~ResourceBase() = default;

		virtual const char*			ToString() abstract;
	};
}