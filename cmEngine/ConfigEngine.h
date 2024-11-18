#pragma once

namespace cmEngine
{
	struct ConfigEngine
	{
		static void Destroy()
		{
			for (const auto& iter : mConfigRepo)
			{
				std::ofstream f{ iter.first };

				if (!f.is_open())
				{
					assert(false);
					continue;
				}

				assert(!iter.second.is_null());

				f << iter.second.dump(4);
			}
		}

		template<typename ConfigType>
		static bool Save(const ConfigType& inConfigData)
		{
			static_assert(std::is_base_of<ConfigBase, ConfigType>::value);

			auto [iter, inserted] = mConfigRepo.emplace(inConfigData.GetConfigPath(), json{});
			iter->second[inConfigData.ToString()] = inConfigData;

			return true;
		}

		template<typename ConfigType>
		static bool Load(ConfigType& inOutConfigData)
		{
			static_assert(std::is_base_of<ConfigBase, ConfigType>::value);

			auto iter = mConfigRepo.find(inOutConfigData.GetConfigPath());
			if (iter == mConfigRepo.end())
			{
				json parsedJson = LoadJsonFromFile(inOutConfigData.GetConfigPath());

				auto [newIter, inserted] = mConfigRepo.emplace(inOutConfigData.GetConfigPath(), std::move(parsedJson));
				iter = newIter; 
			}

			json& js = iter->second;

			if (js.contains(inOutConfigData.ToString()))
			{
				inOutConfigData = js[inOutConfigData.ToString()];
				return true;
			}

			return false;
		}

	private:
		static json LoadJsonFromFile(const std::wstring& filePath)
		{
			std::ifstream f{ filePath };
			if (f.is_open())
			{
				return json::parse(f);
			}
			return json{};
		}

		inline static std::unordered_map<std::wstring, json> mConfigRepo = {};
	};
}