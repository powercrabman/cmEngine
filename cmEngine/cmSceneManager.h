#pragma once
#include "cmScene.h"

class cmSceneManager
{
	ENGINE_MODULE_BODY();
public:
	cmSceneManager() = default;
	virtual ~cmSceneManager() = default;

	void UpdateCore();

	template<typename Ty>
	Ty* CreateScene()
	{
		static_assert(std::is_base_of<cmScene, Ty>::value, "Ty must derived by Scene.");
		auto iter = mScecneRepo.find(TYPE_ID(Ty));

		if (iter != mScecneRepo.end())
		{
			LOG_WARN("already exist scene.");
			return static_cast<Ty*>(iter->second.get());
		}

		std::unique_ptr<Ty> sc = std::make_unique<Ty>();
		Ty* ptr = sc.get();
		mScecneRepo[TYPE_ID(Ty)] = std::move(sc);

		return ptr;
	}

	template<typename Ty>
	Ty* FindSceneOrNull()
	{
		static_assert(std::is_base_of<cmScene, Ty>::value, "Ty must derived by Scene.");
		auto iter = mScecneRepo.find(TYPE_ID(Ty));

		if (iter == mScecneRepo.end())
		{
			ASSERT(false, "do not exist scene.");
			LOG_ERROR("do not exist scene.");
			return nullptr;
		}

		return static_cast<Ty*>(iter->second.get());
	}

	template<typename Ty>
	void RemoveScene()
	{
		static_assert(std::is_base_of<cmScene, Ty>::value, "Ty must derived by Scene.");
		auto iter = mScecneRepo.find(TYPE_ID(Ty));

		if (iter == mScecneRepo.end())
		{
			ASSERT(false, "do not exist scene.");
			LOG_ERROR("do not exist scene.");
			return;
		}

		mScecneRepo.erase(TYPE_ID(Ty));
	}

	template<typename Ty>
	void ChangeScene()
	{
		cmScene* sc = FindSceneOrNull<Ty>();

		if (sc == nullptr)
		{
			ASSERT(false, "Scene Change Fail.");
			LOG_ERROR("Scene Change Fail.");
			return;
		}

		
		if (mCurrentScene) { mCurrentScene->ExitSceneCore(); }

		mCurrentScene = sc;
		mCurrentScene->EnterSceneCore();
	}

	cmScene* GetCurrentScene() const { return mCurrentScene; }

private:
	std::unordered_map<cmTypeID, std::unique_ptr<cmScene>> mScecneRepo;
	cmScene* mCurrentScene = nullptr;
};
