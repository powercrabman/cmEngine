#pragma once

namespace cmEngine
{
	struct ConfigBase;

	struct ConfigSystem
	{
		template<typename ConfigType>
		static bool Save(const ConfigType& inConfigData)
		{
			static_assert(std::is_base_of<ConfigBase, ConfigType>::value);
			std::ofstream f{ inConfigData.GetConfigPath() };

			if (!f.is_open())
			{
				return false;
			}

			json js;
			js[inConfigData.ToString()] = inConfigData;
			f << js.dump(4);
			return true;
		}

		template<typename ConfigType>
		static bool Load(ConfigType& inOutConfigData)
		{
			static_assert(std::is_base_of<ConfigBase, ConfigType>::value);
			std::ifstream f{ inOutConfigData.GetConfigPath() };

			if (!f.is_open())
			{
				return false;
			}
			json js = json::parse(f);
			inOutConfigData = js[inOutConfigData.ToString()];

			return true;
		}
	};
}