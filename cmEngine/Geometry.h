#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace cmEngine
{
	class Geometry
	{
	public:
		Geometry();
		~Geometry();

		template<typename VertexType>
		void Create(
			const std::vector<VertexType>&	inVertices,
			const std::vector<UINT>&		inIndices
		);

		void			Clear() { mIndexBuffer.reset(); mVertexBuffer.reset(); }

		IndexBuffer*	GetIndexBuffer() const { return mIndexBuffer.get(); }
		VertexBuffer*	GetVertexBuffer() const { return mVertexBuffer.get(); }

	private:
		Scope<IndexBuffer>	mIndexBuffer  = nullptr;
		Scope<VertexBuffer>	mVertexBuffer = nullptr;
	};

	//===================================================
	//                      Inline
	//===================================================

	template<typename VertexType>
	inline void Geometry::Create(const std::vector<VertexType>& inVertices, const std::vector<UINT>& inIndices)
	{
		static_assert(std::is_base_of<IVertexBase, VertexType>::value);

		mIndexBuffer.reset();
		mVertexBuffer.reset();

		mIndexBuffer = MakeScope<IndexBuffer>();
		mVertexBuffer = MakeScope<VertexBuffer>();

		mIndexBuffer->Create(inIndices);
		mVertexBuffer->Create(inVertices);
	}
}



