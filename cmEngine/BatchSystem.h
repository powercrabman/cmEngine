#pragma once

namespace cmEngine
{
	template <typename Entity>
	struct BatchSystem
	{
		BatchSystem()
		{
			mEntityMap.reserve(1024);
			mEntityList.reserve(1024);
		}

		void Push(Entity* inComp)
		{
			auto [iter, result] = mEntityMap.emplace(inComp, mEntityList.size());

			if (result)
			{
				mEntityList.push_back(inComp);
			}
		}

		void Remove(Entity* inComp)
		{
			auto iter = mEntityMap.find(inComp);

			if (iter != mEntityMap.end())
			{
				uint32 targetIdx        = iter->second;
				Entity* lastElement     = mEntityList.back();
				mEntityList[targetIdx]  = lastElement;
				mEntityMap[lastElement] = targetIdx;
				mEntityList.pop_back();
				mEntityMap.erase(inComp);
			}
		}

		void Clear()
		{
			mEntityMap.clear();
			mEntityList.clear();
		}

		typename std::vector<Entity*>::const_iterator begin() const { return mEntityList.cbegin(); }
		typename std::vector<Entity*>::const_iterator end() const { return mEntityList.cend(); }

	private:
		std::unordered_map<Entity*, uint32>	mEntityMap;
		std::vector<Entity*>				mEntityList;
	};
}
