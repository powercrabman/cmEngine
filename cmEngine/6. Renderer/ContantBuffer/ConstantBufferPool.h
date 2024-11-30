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

			auto [iter, result] = mConstantBufferRepo.emplace(TYPE_ID(ConstantBufferDataType), MakeScope<ConstantBuffer<ConstantBufferDataType>>());
			ConstantBuffer<ConstantBufferDataType>* ptr = static_cast<ConstantBuffer<ConstantBufferDataType>*>(iter->second.get());

			if (result)
			{
				ptr->Create();
			}

			return ptr;
		}

		static void CleanUp() { mConstantBufferRepo.clear(); }

	private:
		inline static std::unordered_map<TypeID, Scope<ConstantBufferBase>> mConstantBufferRepo = {};
	};
}
