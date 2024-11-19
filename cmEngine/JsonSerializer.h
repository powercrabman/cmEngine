#pragma once

namespace cmEngine
{

	//===================================================
	//                 Json Meta Data 
	//===================================================

#define JSON_STRUCT_BODY(TypeName, FileName, ...)\
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(TypeName, __VA_ARGS__); \
		const wchar_t* GetPath() const override { return FileName; }\
		const char* ToString() const override { return #TypeName; }

	struct JsonMetaData
	{
		virtual ~JsonMetaData() = default;
		virtual const wchar_t*	GetPath() const = 0;
		virtual const char*		ToString() const = 0;
	};

	//===================================================
	//                  Json Serializer
	//===================================================

	template <typename JsonDataType>
	concept JsonConstraint = std::is_base_of_v<JsonMetaData, JsonDataType>;

	class JsonSerializer
	{
		friend class EngineCore;
	public:
		template <JsonConstraint JsonDataType>
		static void Serialize(const JsonDataType& inData)
		{
			json& js = GetJson(inData.GetPath());
			js[inData.ToString()] = inData;
		}

		template <JsonConstraint JsonDataType>
		static bool Deserialize(JsonDataType& inOutData)
		{
			json& js = GetJson(inOutData.GetPath());

			try
			{
				if (js.contains(inOutData.ToString()))
				{
					inOutData = js.at(inOutData.ToString()).get<JsonDataType>();
				}
				else
				{
					return false;
				}
			}
			catch (const std::exception& e)
			{
				ENGINE_LOG_ERROR("{} : parsing failed. Error: {}", inOutData.ToString(), e.what());
				return false;
			}

			return true;
		}

	private:
		static void Destroy()
		{
			std::ofstream f = {};

			for (auto iter : mJsonRepo)
			{
				f.open(mJsonDirectory / iter.first);

				if (!f.is_open())
				{
					assert(false);
					f.clear();
					continue;
				}

				assert(!iter.second.is_null());
				f << iter.second.dump(4);

				f.close();
				f.clear();
			}
		}

		static void Initialize()
		{
			mJsonDirectory = std::filesystem::current_path() / mJsonDirectoryName;

			// Directory 가 없을 경우 생성
			std::filesystem::create_directory(mJsonDirectory);
		}

		static json& GetJson(std::wstring_view inFilePath)
		{
			auto iter = mJsonRepo.find(inFilePath.data());

			if (iter == mJsonRepo.end())
			{
				return LoadJson(inFilePath);
			}
			else
			{
				return iter->second;
			}
		}

		static json& LoadJson(std::wstring_view inFilePath)
		{
			std::ifstream fs{ inFilePath.data() };
			json js = {};
			if (fs.is_open())
			{
				js = json::parse(fs);
			}
			return mJsonRepo.emplace(inFilePath.data(), js).first->second;
		}

		inline static std::unordered_map<std::wstring, json>	mJsonRepo = {};
		inline static std::filesystem::path						mJsonDirectory = {};

		inline static constexpr wchar_t mJsonDirectoryName[] = L"Config";
	};
}
