#pragma once

class cmConstantBufferBase;

class cmGraphicsResourceManager
{
	friend class cmRenderer;
public:
	virtual ~cmGraphicsResourceManager();

#pragma region Constant Buffer

	template<typename ConstantBufferData>
	cmConstantBuffer<ConstantBufferData>* CreateConstantBuffer()
	{
		using Ty = ConstantBufferData;
		static_assert(std::is_base_of<cmConstantBufferDataBase, Ty>::value, "Ty must derived by ConstantBufferDataBase");

		uint32 idx = (uint32)Ty::ConstantBufferType;

		if (mCBufferRepo[(uint32)ConstantBufferData::ConstantBufferType])
		{
			ASSERT(false, "Already Exist Constant Buffer.");
			LOG_WARN("Already Exist Constant Buffer.");
			return static_cast<cmConstantBuffer<Ty>*>(mCBufferRepo[idx].get());
		}

		std::unique_ptr<cmConstantBuffer<Ty>> inst = std::make_unique<cmConstantBuffer<Ty>>();
		inst->Create();
		cmConstantBuffer<Ty>* retVal = inst.get();
		mCBufferRepo[idx] = std::move(inst);
		return retVal;
	}

	template<typename ConstantBufferData>
	cmConstantBuffer<ConstantBufferData>* FindConstantBufferOrNull()
	{
		using Ty = ConstantBufferData;
		static_assert(std::is_base_of<cmConstantBufferDataBase, Ty>::value, "Ty must derived by ConstantBufferDataBase");

		const std::unique_ptr<cmConstantBufferBase>& inst = mCBufferRepo[(uint32)Ty::ConstantBufferType];

		if (inst)
		{
			return static_cast<cmConstantBuffer<Ty>*>(inst.get());
		}
		else
		{
			return nullptr;
		}
	}

#pragma endregion

#pragma region InputLayout
	template<typename VertexData>
	cmInputLayout<VertexData>* CreateInputLayout(cmVertexShader* inVertexShader)
	{
		using Ty = VertexData;
		static_assert(std::is_base_of<cmVertexBase, Ty>::value, "Ty must derived by cmVertexBase");
		auto iter = mInputLayoutRepo.find(TYPE_ID(Ty));

		if (iter != mInputLayoutRepo.end())
		{
			ASSERT(false, "Already exist constant buffer.");
			LOG_WARN("Already exist constant buffer.");

			return static_cast<cmInputLayout<Ty>*>(iter->second.get());
		}

		std::unique_ptr<cmInputLayout<Ty>> inst = std::make_unique<cmInputLayout<Ty>>();
		inst->Create(inVertexShader);
		cmInputLayout<Ty>* ptr = inst.get();
		mInputLayoutRepo[TYPE_ID(Ty)] = std::move(inst);
		return ptr;
	}

	template<typename VertexData>
	cmInputLayout<VertexData>* FindInputLayoutOrNull()
	{
		using Ty = VertexData;
		static_assert(std::is_base_of<cmVertexBase, Ty>::value, "Ty must derived by cmVertexBase");
		auto iter = mInputLayoutRepo.find(TYPE_ID(Ty));

		if (iter == mInputLayoutRepo.end())
		{
			ASSERT(false, "Do not exist constant buffer.");
			LOG_WARN("Do not exist constant buffer.");

			return nullptr;
		}

		return static_cast<cmInputLayout<Ty>*>(iter->second.get());
	}
#pragma endregion

#pragma region Geometry
	cmGeometry* CreateGeometry(std::string_view inString)
	{
		auto iter = mGeometryRepo.find(inString.data());
		if (iter != mGeometryRepo.end())
		{
			ASSERT(false, "Already exist Geometry");
			LOG_WARN("Already exist Geometry");
			return nullptr;
		}

		std::unique_ptr<cmGeometry> inst = std::make_unique<cmGeometry>();
		cmGeometry* ptr = inst.get();
		mGeometryRepo[inString.data()] = std::move(inst);

		return ptr;
	}

	cmGeometry* FindGeometryOrNull(std::string_view inString)
	{
		auto iter = mGeometryRepo.find(inString.data());

		if (iter == mGeometryRepo.end())
		{
			ASSERT(false, "Do not exist Geometry");
			LOG_ERROR("Do not exist Geometry");
			return nullptr;
		}

		return iter->second.get();
	}

#pragma endregion

private:
	cmGraphicsResourceManager();

	std::array<std::unique_ptr<cmConstantBufferBase>, (uint32)eConstantBufferType::Count> mCBufferRepo = {};
	std::unordered_map<cmTypeID, std::unique_ptr<cmInputLayoutBase>> mInputLayoutRepo = {};
	std::unordered_map<std::string, std::unique_ptr<cmGeometry>> mGeometryRepo = {};
};