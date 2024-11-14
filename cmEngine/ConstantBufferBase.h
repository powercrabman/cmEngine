#pragma once

namespace cmEngine
{
	class ConstantBufferBase
	{
	public:
		ConstantBufferBase() {}
		virtual ~ConstantBufferBase() {}

		::ComPtr<ID3D11Buffer> GetBuffer() const { return mBuffer; }
		
	protected:
		::ComPtr<ID3D11Buffer> mBuffer;
	};
}
