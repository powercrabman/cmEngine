#pragma once

namespace cmEngine
{

	//===================================================
	//                 Json Meta Data 
	//===================================================

#define JSON_STRUCT_BODY(StructName, ...)							\
		enum { JSON_STRUCT_VALIDATION = 1 };						\
		const char* ToString() const {return #StructName;}			\
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(StructName, __VA_ARGS__)		\

	//===================================================
	//                  Json Serializer
	//===================================================
	
	class JsonSerializer
	{
		SINGLETON(JsonSerializer);
	public:
		//===================================================
		//			         Serializer
		//===================================================

		template <typename JsonDataType>
		void SerializeToFile(const JsonDataType& inData, const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory = "")
		{
			static_assert(JsonDataType::JSON_STRUCT_VALIDATION);

			json& js = GetJson(inFileName, inDirectory);
			js[inData.ToString()] = inData;
		}

		template <typename JsonDataType>
		void SerializeToFileWithTag(const JsonDataType& inData, const std::filesystem::path& inFileName, std::string_view inTag, const std::filesystem::path& inDirectory = "")
		{
			static_assert(JsonDataType::JSON_STRUCT_VALIDATION);
			json& js = GetJson(inFileName, inDirectory);
			js[inTag] = inData;

		}

		//===================================================
		//			        Deserializer
		//===================================================

		template <typename JsonDataType>
		bool DeserializerFromFile(JsonDataType& inOutData, const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory = "")
		{
			static_assert(JsonDataType::JSON_STRUCT_VALIDATION);
			json& js = GetJson(inFileName, inDirectory);

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


		template <typename JsonDataType>
		bool DeserializerFromFileWithTag(JsonDataType& inOutData, const std::filesystem::path& inFileName, std::string_view inTag, const std::filesystem::path& inDirectory = "")
		{
			static_assert(JsonDataType::JSON_STRUCT_VALIDATION);
			json& js = GetJson(inFileName, inDirectory);

			try
			{
				if (js.contains(inTag))
				{
					inOutData = js.at(inTag).get<JsonDataType>();
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

		//===================================================
		//			          GetJson
		//===================================================

		json& GetJson(const std::filesystem::path& inFileName, const std::filesystem::path& inDirectory = "")
		{
			auto iter = mJsonRepo.find(inFileName);

			if (iter == mJsonRepo.end())
			{
				if (inDirectory.empty())
				{
					return LoadJson(mDefaultJsonPath / inFileName);
				}
				else
				{
					return LoadJson(inDirectory / inFileName);
				}
			}
			else
			{
				// cache
				return iter->second;
			}
		}

	private:
		json& LoadJson(const std::filesystem::path& inPath)
		{
			std::ifstream fs{ inPath };
			json js = {};

			// 파일 Validation 확인
			if (fs.is_open() && std::filesystem::file_size(inPath) != 0)
			{
				js = json::parse(fs);
			}
			return mJsonRepo.emplace(inPath.filename(), js).first->second;
		}

		JsonSerializer();
		~JsonSerializer();

		std::unordered_map<std::wstring, json>	mJsonRepo = {};
		std::filesystem::path					mDefaultJsonPath = {};
	};
}
