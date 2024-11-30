#pragma once

namespace cmEngine
{
	class SystemMonitor
	{
	public:
		static float GetCPUUsage()
		{
			static FILETIME prevIdleTime, prevKernelTime, prevUserTime;
			FILETIME idleTime, kernelTime, userTime;

			if (GetSystemTimes(&idleTime, &kernelTime, &userTime))
			{
				uint64_t idle   = FileTimeToInt64(idleTime) - FileTimeToInt64(prevIdleTime);
				uint64_t kernel = FileTimeToInt64(kernelTime) - FileTimeToInt64(prevKernelTime);
				uint64_t user   = FileTimeToInt64(userTime) - FileTimeToInt64(prevUserTime);

				prevIdleTime = idleTime;
				prevKernelTime = kernelTime;
				prevUserTime = userTime;

				uint64_t total = kernel + user;
				return total ? (100.0f * (1.0f - (float)idle / total)) : 0.0f;
			}
			return 0.0f;
		}

		static float GetGPUFrameTime()
		{
			D3D11_QUERY_DESC queryDesc = {};
			queryDesc.Query = D3D11_QUERY_TIMESTAMP_DISJOINT;

			ID3D11Query* disjointQuery = nullptr;
			Renderer::GetDevice()->CreateQuery(&queryDesc, &disjointQuery);

			queryDesc.Query = D3D11_QUERY_TIMESTAMP;
			ID3D11Query* startQuery = nullptr;
			ID3D11Query* endQuery = nullptr;
			Renderer::GetDevice()->CreateQuery(&queryDesc, &startQuery);
			Renderer::GetDevice()->CreateQuery(&queryDesc, &endQuery);

			Renderer::GetContext()->Begin(disjointQuery);
			Renderer::GetContext()->End(startQuery);

			Renderer::GetContext()->End(endQuery);
			Renderer::GetContext()->End(disjointQuery);

			D3D11_QUERY_DATA_TIMESTAMP_DISJOINT disjointData;
			UINT64 startTime = 0, endTime = 0;

			while (Renderer::GetContext()->GetData(disjointQuery, &disjointData, sizeof(disjointData), 0) == S_FALSE);
			while (Renderer::GetContext()->GetData(startQuery, &startTime, sizeof(startTime), 0) == S_FALSE);
			while (Renderer::GetContext()->GetData(endQuery, &endTime, sizeof(endTime), 0) == S_FALSE);

			if (disjointData.Disjoint == FALSE)
			{
				double frequency = static_cast<double>(disjointData.Frequency);
				double gpuTimeMs = (endTime - startTime) / frequency * 1000.0; 
				return static_cast<float>(gpuTimeMs);
			}

			disjointQuery->Release();
			startQuery->Release();
			endQuery->Release();

			return 0.0f;
		}

		static size_t GetTotalMemory()
		{
			MEMORYSTATUSEX memInfo = {};
			memInfo.dwLength = sizeof(MEMORYSTATUSEX);
			if (GlobalMemoryStatusEx(&memInfo))
			{
				return static_cast<size_t>(memInfo.ullTotalPhys / (1024 * 1024));
			}
			return 0;
		}

		static size_t GetUsedMemory()
		{
			MEMORYSTATUSEX memInfo = {};
			memInfo.dwLength = sizeof(MEMORYSTATUSEX);
			if (GlobalMemoryStatusEx(&memInfo))
			{
				return static_cast<size_t>((memInfo.ullTotalPhys - memInfo.ullAvailPhys) / (1024 * 1024));
			}
			return 0;
		}

	private:
		static uint64_t FileTimeToInt64(const FILETIME& ft)
		{
			return ((uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
		}
	};
}
