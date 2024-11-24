#pragma once

namespace cmEngine
{

	//===================================================
	//                 Json Meta Data 
	//===================================================

#define JSON_STRUCT_BODY(TypeName, ...)\
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(TypeName, __VA_ARGS__); \
		const char* ToString() const override { return #TypeName; }

	struct JsonMetaData
	{
		virtual ~JsonMetaData() = default;
		virtual const char* ToString() const = 0;
	};

	//===================================================
	//                  Json Serializer
	//===================================================

	template <typename JsonDataType>
	concept JsonDataConstraint = std::is_base_of_v<JsonMetaData, JsonDataType>;

	class JsonSerializer
	{
		friend class EngineCore;
	public:
		template <JsonDataConstraint JsonDataType>
		static void SerializeToFile(const JsonDataType& inData, std::wstring_view inFilePath, bool useAbsolutePath = false)
		{
			json& js = GetJsonEx(inFilePath, useAbsolutePath);
			js[inData.ToString()] = inData;
		}

		template <JsonDataConstraint JsonDataType>
		static void SerializeToSection(const JsonDataType& inData, std::wstring_view inFilePath, std::string_view inSectionName, bool useAbsolutePath = false)
		{
			json& js = GetJsonEx(inFilePath, useAbsolutePath);
			js[inSectionName] = inData;
		}

		template <JsonDataConstraint JsonDataType>
		static bool DeserializeFromFile(JsonDataType& inOutData, std::wstring_view inFilePath, bool useAbsolutePath = false)
		{
			json& js = GetJsonEx(inFilePath, useAbsolutePath);

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

		template <JsonDataConstraint JsonDataType>
		static bool DeserializeFromSection(JsonDataType& inOutData, std::wstring_view inFilePath, std::string_view inSectionName, bool useAbsolutePath = false)
		{
			json& js = GetJsonEx(inFilePath, useAbsolutePath);

			try
			{
				if (js.contains(inSectionName))
				{
					inOutData = js.at(inSectionName).get<JsonDataType>();
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

		static json& GetJson(std::wstring_view inFilePath, bool useAbsolutePath = false)
		{
			return GetJsonEx(inFilePath, useAbsolutePath);
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

		static json& GetJsonEx(std::wstring_view inFilePath, bool useAbsolutePath)
		{
			auto iter = mJsonRepo.find(inFilePath.data());

			if (iter == mJsonRepo.end())
			{
				return LoadJsonEx(inFilePath, useAbsolutePath);
			}
			else
			{
				return iter->second;
			}
		}

		static json& LoadJsonEx(std::wstring_view inFilePath, bool useAbsolutePath)
		{
			std::ifstream fs{ useAbsolutePath ? inFilePath : mJsonDirectory / inFilePath };
			json js = {};
			if (fs.is_open())
			{
				js = json::parse(fs);
			}
			return mJsonRepo.emplace(inFilePath.data(), js).first->second;
		}

		inline static std::unordered_map<std::wstring, json>	mJsonRepo = {};
		inline static std::filesystem::path						mJsonDirectory = {};

		inline static constexpr wchar_t mJsonDirectoryName[] = L"json";
	};
}
