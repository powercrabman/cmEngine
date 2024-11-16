#pragma once

#include "ResourceBase.h"

namespace cmEngine
{
	// TODO - use flag for optional shader 

	class ShaderSet : public ResourceBase
	{
	public:
		RESOURCE_BODY(ShaderSet);

		ShaderSet(std::string_view inName);
		virtual ~ShaderSet() {}

		void Create(
			const VertexShader& inVertexShader,
			const PixelShader& inPixelShader
		)
		{
			mVertexShader.reset();
			mPixelShader.reset();

			mVertexShader = MakeScope<VertexShader>(inVertexShader);
			mPixelShader  = MakeScope<PixelShader>(inPixelShader);
		}

		VertexShader*	GetVertexShader() const { return mVertexShader.get(); }
		PixelShader*	GetPixelShader() const { return mPixelShader.get(); }

	private:
		Scope<VertexShader>	mVertexShader = nullptr;
		Scope<PixelShader>	mPixelShader = nullptr;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline ShaderSet::ShaderSet(std::string_view inName)
		: ResourceBase(inName)
	{
		mVertexShader = MakeScope<VertexShader>();
		mPixelShader = MakeScope<PixelShader>();
	}
}
