#pragma once

namespace cmEngine
{
	class GameEntity
	{
	public:
		GameEntity(entt::registry* inRegistry, entt::entity inEntity)
			: mRegi(inRegistry)
			, mEntity(inEntity)
		{
		}
		GameEntity(entt::entity inEntity);
		operator entt::entity() const { return mEntity; }

		[[nodiscard]] entt::entity GetNakedEntity() const { return mEntity; }
		[[nodiscard]] uint32 GetID() const { return static_cast<uint32>(mEntity); }

		template<typename Ty, typename...Args>
		Ty& CreateComponent(Args&& ...args)
		{
			return mRegi->emplace<Ty>(mEntity, std::forward<Args>(args)...);
		}

		template<typename Ty, typename...Args>
		Ty& ReplaceComponent(Args&&... args)
		{
			return mRegi->emplace_or_replace<Ty>(mEntity, std::forward<Args>(args)...);
		}

		template<typename Ty>
		void RemoveComponent() const
		{
			mRegi->remove<Ty>(mEntity);
		}

		template<typename Ty>
		Ty& FindComponent()
		{
			return mRegi->get<Ty>(mEntity);
		}

		template<typename...Types>
		auto FindComponents() const
		{
			return mRegi->get<Types...>(mEntity);
		}

		template<typename Ty>
		bool HasComponent() const
		{
			return mRegi->all_of<Ty>(mEntity);
		}

		template<typename...Types>
		bool HasComponents() const
		{
			return mRegi->all_of<Types...>(mEntity);
		}

		template<typename...Types>
		bool HasAnyOfComponents() const
		{
			return mRegi->any_of<Types...>(mEntity);
		}

		void Destroy()
		{
			if (mRegi && mEntity != entt::null)
			{
				mRegi->destroy(mEntity);
				mEntity = entt::null;
			}
		}

		bool IsValid() const
		{
			return mRegi && mRegi->valid(mEntity);
		}


		static GameEntity NullEntity;

	private:
		entt::registry* mRegi = nullptr;
		entt::entity	mEntity = entt::null;
	};
}

