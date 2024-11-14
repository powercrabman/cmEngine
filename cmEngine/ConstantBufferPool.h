#pragma once

namespace cmEngine
{
	class ConstantBufferPool
	{
	public:
		template <typename ConstantBufferDataType>
		static ConstantBuffer<ConstantBufferDataType>* FindConstantBuffer()
		{
			static_assert(std::is_base_of<ConstantBufferDataBase, ConstantBufferDataType>::value);
			
			auto [iter, result] = mConstantBufferRepo.emplace(TYPE_ID(ConstantBufferDataType), std::make_unique<ConstantBuffer<ConstantBufferDataType>>());
			ConstantBuffer<ConstantBufferDataType>* ptr = static_cast<ConstantBuffer<ConstantBufferDataType>*>(iter->second.get());

			if (result)
			{
				ptr->Create();
			}

			return ptr;
		}

	private:
		static std::unordered_map<TypeID, std::unique_ptr<ConstantBufferBase>> mConstantBufferRepo;
	};
}
