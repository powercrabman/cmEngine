#pragma once

namespace cmEngine
{

	class EngineCore
	{
		friend class Application;
	public:
		virtual ~EngineCore();

		static EngineCore* Get();

		void CloseEngine() { mRunning = false; }
		bool IsRunning() const { return mRunning; }

	private:
		static void Create(
			const WindowResolution& inResolution = { 800, 600 },
			const WindowPosition&	inPosition   = {0,0}
		);

		void Destory();

		EngineCore(const WindowResolution& inResolution, const WindowPosition& inPosition);
		EngineCore(const EngineCore&) = delete;
		EngineCore& operator=(const EngineCore&) = delete;

	private:
		bool mRunning						= false;
		inline static EngineCore* sInstance = nullptr;
	};

	// ====================================================================
	//								Inline
	// ====================================================================

	inline void EngineCore::Create(const WindowResolution& inResolution, const WindowPosition& inPosition)
	{
		if (sInstance != nullptr)
		{
			sInstance = new EngineCore(inResolution, inPosition);
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
