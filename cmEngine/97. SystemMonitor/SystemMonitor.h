#pragma once

namespace cmEngine
{
	class SystemMonitor
	{
	public:
		static float	GetCPUUsage();
		static float	GetGPUFrameTime();
		static size_t	GetTotalMemory();
		static size_t	GetUsedMemory();

	private:
		static uint64_t FileTimeToInt64(const FILETIME& ft)
		{
			return (static_cast<uint64_t>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
		}
	};
}
