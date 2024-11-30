#pragma once

namespace cmEngine
{
	class GameEntity
	{
	public:
		GameEntity(Scene* inScene, entt::entity inEntity);
		operator entt::entity() const { return mEntity; }

		friend bool operator==(const GameEntity& inLhs, const GameEntity& inRhs)
		{
			return inLhs.mRegi == inRhs.mRegi
				&& inLhs.mEntity == inRhs.mEntity;
		}

		friend bool operator!=(const GameEntity& inLhs, const GameEntity& inRhs)
		{
			return !(inLhs == inRhs);
		}

		[[nodiscard]] entt::entity GetNakedEntity() const { return mEntity; }
		[[nodiscard]] uint32 GetID() const { return static_cast<uint32>(mEntity); }

		template<typename Ty, typename...Args>
		Ty& CreateComponent(Args&& ...args) const
		{
			return mRegi->emplace<Ty>(mEntity, std::forward<Args>(args)...);
		}

		template<typename Ty, typename...Args>
		[[maybe_unused]] bool TryCreateComponent(Args&& ...args) const
		{
			if (TryFindComponent<Ty>())
			{
				ENGINE_LOG_WARN("Already exist component.");
				return false;
			}
			else
			{
				mRegi->emplace<Ty>(mEntity, std::forward<Args>(args)...);
				return true;
			}
		}

		template<typename Ty, typename...Args>
		Ty& ReplaceComponent(Args&&... args) const
		{
			return mRegi->emplace_or_replace<Ty>(mEntity, std::forward<Args>(args)...);
		}

		template<typename Ty>
		void RemoveComponent() const
		{
			mRegi->remove<Ty>(mEntity);
		}

		template<typename Ty>
		void TryRemoveComponent() const
		{
			if (HasComponent<Ty>())
			{
				mRegi->remove<Ty>(mEntity);
			}
		}

		template<typename Ty>
		Ty* TryFindComponent() const
		{
			return mRegi->try_get<Ty>(mEntity);
		}

		template<typename ...Types>
		auto TryFindComponents() const
		{
			return mRegi->try_get<Types...>(mEntity);
		}

		template<typename Ty>
		Ty& FindComponent() const
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

		bool IsNull() const
		{
			return mRegi == nullptr || mEntity == entt::null;
		}

		static GameEntity NullEntity;

	private:
		entt::registry* mRegi = nullptr;
		entt::entity	mEntity = entt::null;
	};
}

