#pragma once

class cmConstantBufferBase;
class cmRenderState;

class cmGraphicsResourceManager
{
	friend class cmRenderer;
public:
	virtual ~cmGraphicsResourceManager();

	void Initialize();

	ID3D11SamplerState* FindSamplerState(eSamplerStateFilter inFilter, eSamplerStateAddress inModeU, eSamplerStateAddress inModeV);

	template <typename ConstantBufferDataType>
	cmConstantBuffer<ConstantBufferDataType>* FindConstantBuffer()
	{
		using Ty = ConstantBufferDataType;

		static_assert(std::is_base_of<cmConstantBufferDataBase, Ty>::value);
		auto iter = mCBufferRepo.find(TYPE_ID(Ty));

		if (iter == mCBufferRepo.end())
		{
			auto inst = std::make_unique<cmConstantBuffer<Ty>>();
			inst->Create();
			cmConstantBuffer<Ty>* ptr = inst.get();
			mCBufferRepo[TYPE_ID(Ty)] = std::move(inst);
			return ptr;
		}

		return static_cast<cmConstantBuffer<Ty>*>(iter->second.get());
	}

private:
	cmGraphicsResourceManager();

	std::unique_ptr<cmRenderState> mRenderState = nullptr;
	std::unordered_map<cmTypeID, std::unique_ptr<cmConstantBufferBase>> mCBufferRepo = {};
};