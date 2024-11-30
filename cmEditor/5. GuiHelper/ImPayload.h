#pragma once

namespace ImPayload
{
	inline const char* GetResourcePayload(eResourceType inType)
	{
		static const char* sPayloadList[static_cast<uint32>(eResourceType::Count)] =
		{
			"TEXTURE_PAYLOAD",
			"SPRITE_PAYLOAD",
			"FLIPBOOK_PAYLOAD",
			"SHADERSET_PAYLOAD"
		};

		return sPayloadList[static_cast<uint32>(inType)];
	}
}