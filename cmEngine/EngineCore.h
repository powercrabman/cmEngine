#pragma once

namespace cmEngine
{
	class EngineCore
	{
		friend class Application;
	public:
		virtual ~EngineCore();

		static EngineCore* Get();

		void CloseGame() { mRunning = false; }
		bool IsRunning() const { return mRunning; }

	private:
		static void Create();

		void Initialize(
			const WindowResolution& inResolution,
			const WindowPosition& inPosition
		);
		void Destory();

		EngineCore() = default;
		EngineCore(const EngineCore&) = delete;
		EngineCore& operator=(const EngineCore&) = delete;

	private:
		bool mRunning						= false;
		inline static EngineCore* sInstance = nullptr;
	};

	// ====================================================================
	//								Inline
	// ====================================================================

	inline void EngineCore::Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new EngineCore;
		}
	}

	inline void EngineCore::Destory()
	{
		if (sInstance)
		{
			delete sInstance;
			sInstance = nullptr;
			mRunning = false;
		}
	}

	inline EngineCore* EngineCore::Get()
	{
		if (sInstance)
		{
			return sInstance;
		}
		else
		{
			ENGINE_LOG_FATAL("Engine isn't created");
			return nullptr;
		}
	}
}
