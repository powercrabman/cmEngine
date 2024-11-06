#pragma once

class cmGeometry
{
public:
	cmGeometry();
	virtual ~cmGeometry();

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