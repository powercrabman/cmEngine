#pragma once
#include "cmResourceBase.h"

class cmMesh : public cmResourceBase
{
public:
	cmMesh() = default;
	virtual ~cmMesh() = default;

	void Load(std::wstring_view inFilePath) { /* TODO */ }
	void Save(std::wstring_view inFilePath) { /* TODO */ }

	template<typename VertexType>
	void Create(
		const std::vector<VertexType>& inVertices,
		const std::vector<UINT>& inIndices
	)
	{
		mVertexbuf.Create(inVertices);
		mIndexBuf.Create(inIndices);
	}

	void Create(
		const cmVertexBuffer& inVertexBuffer,
		const cmIndexBufferU32& inIndexBuffer
	)
	{
		mVertexbuf = inVertexBuffer;
		mIndexBuf = inIndexBuffer;
	}

	cmVertexBuffer* GetVertexBuffer() { return &mVertexbuf; }
	cmIndexBufferU32* GetIndexBuffer() { return &mIndexBuf; }

private:
	cmVertexBuffer		mVertexbuf;
	cmIndexBufferU32	mIndexBuf;
};