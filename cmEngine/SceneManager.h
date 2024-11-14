#pragma once

namespace cmEngine
{
	class SceneManager
	{
	public:
		static void UpdateCore();

		template<typename Ty>
		static Ty* CreateScene()
		{
			static_assert(std::is_base_of<Scene, Ty>::value, "Ty must derived by Scene.");
			auto iter = mScecneRepo.find(TYPE_ID(Ty));

			if (iter != mScecneRepo.end())
			{
				ENGINE_LOG_WARN("already exist scene.");
				return static_cast<Ty*>(iter->second.get());
			}

			std::unique_ptr<Ty> sc = std::make_unique<Ty>();
			Ty* ptr = sc.get();
			mScecneRepo[TYPE_ID(Ty)] = std::move(sc);

			return ptr;
		}

		template<typename Ty>
		static Ty* FindSceneOrNull()
		{
			static_assert(std::is_base_of<Scene, Ty>::value, "Ty must derived by Scene.");
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
		static void RemoveScene()
		{
			static_assert(std::is_base_of<Scene, Ty>::value, "Ty must derived by Scene.");
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

		static Scene* GetCurrentScene() { return mCurrentScene; }

	private:
		static std::unordered_map<TypeID, std::unique_ptr<Scene>> mScecneRepo;
		inline static Scene* mCurrentScene = nullptr;
	};

}