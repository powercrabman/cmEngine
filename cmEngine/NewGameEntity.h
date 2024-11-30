#pragma once

namespace cmEngine
{
	class NewGameEntity
	{
	public:
		NewGameEntity(entt::entity inEntity);

		operator entt::entity() const { return GetEnttEntity(); }
		entt::entity	GetEnttEntity() const { return mEntity; }
		uint32			GetID() const { return static_cast<uint32>(mEntity); }

		template <typename ComponentType, typename...Args>
		void EmplaceComponent(Args&& ...args)
		{
			mRegistry->emplace<ComponentType>(mEntity, std::forward<Args>(args)...);
		}

		template <typename ComponentType>
		void RemoveComponent()
		{
			mRegistry->remove<ComponentType>(mEntity);
		}

		template <typename ComponentType>
		bool HasComponent()
		{
			return mRegistry->all_of<ComponentType>(mEntity);
		}

		template <typename...Args>
		bool HasComponents()
		{
			return mRegistry->all_of<Args...>(mEntity);
		}

		template <typename...Args>
		bool HasAnyOfComponents()
		{
			return mRegistry->any_of<Args...>(mEntity);
		}

		template <typename ComponentType>
		auto& FindComponent()
		{
			return mRegistry->get<ComponentType>(mEntity);
		}

		template <typename...Args>
		auto FindComponents()
		{
			return mRegistry->get<Args...>(mEntity);
		}

	private:
		entt::registry* mRegistry = nullptr;
		entt::entity	mEntity = entt::null;
	};
}