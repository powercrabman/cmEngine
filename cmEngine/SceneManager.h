#pragma once

namespace cmEngine
{
	class SceneManager
	{
	public:
		static void Update();
		static void Render();

		template<typename Ty>
		static Ty* CreateScene()
		{
			static_assert(std::is_base_of<Scene, Ty>::value, "Ty must derived by Scene.");
			auto iter = mSceneRepo.find(TYPE_ID(Ty));

			if (iter != mSceneRepo.end())
			{
				ENGINE_LOG_WARN("already exist scene.");
				return static_cast<Ty*>(iter->second.get());
			}

			Scope<Ty> sc = MakeScope<Ty>();
			Ty* ptr = sc.get();
			mSceneRepo[TYPE_ID(Ty)] = std::move(sc);

			return ptr;
		}

		template<typename Ty>
		static Ty* FindSceneOrNull()
		{
			static_assert(std::is_base_of_v<Scene, Ty>, "Ty must derived by Scene.");
			auto iter = mSceneRepo.find(TYPE_ID(Ty));

			if (iter == mSceneRepo.end())
			{
				ASSERT(false, "do not exist scene.");
				LOG_ERROR("do not exist scene.");
				return nullptr;
			}

			return static_cast<Ty*>(iter->second.get());
		}

		template<typename Ty>
		static void RemoveScene()
		{
			static_assert(std::is_base_of_v<Scene, Ty>, "Ty must derived by Scene.");
			auto iter = mSceneRepo.find(TYPE_ID(Ty));

			if (iter == mSceneRepo.end())
			{
				ASSERT(false, "do not exist scene.");
				LOG_ERROR("do not exist scene.");
				return;
			}

			mSceneRepo.erase(TYPE_ID(Ty));
		}

		template<typename Ty>
		static void ChangeScene()
		{
			Scene* sc = FindSceneOrNull<Ty>();

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

		static void Destroy()
		{
			mCurrentScene->ExitSceneCore();
			mSceneRepo.clear();
			mCurrentScene = nullptr;
		}

		static Scene* GetCurrentScene() { return mCurrentScene; }

	private:
		inline static std::unordered_map<TypeID, Scope<Scene>> mSceneRepo = {};
		inline static Scene* mCurrentScene                                = nullptr;
	};
}
