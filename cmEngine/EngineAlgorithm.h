#pragma once

namespace cmEngine::String
{
	inline std::vector<std::string> Split(const std::string& inString, char delimiter = ' ')
	{
		std::vector<std::string> result;
		std::stringstream ss(inString);
		std::string token;

		while (std::getline(ss, token, delimiter))
		{
			result.push_back(token);
		}

		return result;
	}

	inline std::vector<float> MapToFloat(const std::vector<std::string>& inStringVector)
	{
		std::vector<float> result;
		result.reserve(inStringVector.size());

		for (const std::string& str : inStringVector)
		{
			result.push_back(std::stof(str));
		}
		return result;
	}

	inline std::vector<float> SplitAndMapToFloat(const std::string& inString, char delimiter = ' ')
	{
		return MapToFloat(Split(inString));
	}

	std::string ConvertToString(std::wstring_view inString);
	std::wstring ConvertToWString(std::string_view inString);
}

namespace cmEngine::Random
{
	inline static std::random_device rd;
	inline static std::mt19937 gen{ rd() };

	inline int GetInt(int min = 0, int max = INT32_MAX)
	{
		std::uniform_int_distribution<> dist(min, max);
		return dist(gen);
	}

	inline float Getfloat(float min = 0.0, float max = 1.0)
	{
		std::uniform_real_distribution<> dist(min, max);
		return static_cast<float>(dist(gen));
	}

	inline float GetNormal(float mean = 0.0, float stddev = 1.0)
	{
		std::normal_distribution<> dist(mean, stddev);
		return static_cast<float>(dist(gen));
	}
}

