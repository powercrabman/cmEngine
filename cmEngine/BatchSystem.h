#pragma once

namespace cmEngine
{
	template <typename Ty>
	struct BatchSystem
	{
		BatchSystem()
		{
			mEntityMap.reserve(1024);
			mEntityList.reserve(1024);
		}

		void Push(Ty* inComp)
		{
			auto [iter, result] = mEntityMap.emplace(inComp, mEntityList.size());

			if (result)
			{
				mEntityList.push_back(inComp);
			}
		}

		void Remove(Ty* inComp)
		{
			auto iter = mEntityMap.find(inComp);

			if (iter != mEntityMap.end())
			{
				uint32 targetIdx        = iter->second;
				Ty* lastElement     = mEntityList.back();
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

		typename std::vector<Ty*>::const_iterator begin() const { return mEntityList.cbegin(); }
		typename std::vector<Ty*>::const_iterator end() const { return mEntityList.cend(); }

	private:
		std::unordered_map<Ty*, uint32>	mEntityMap;
		std::vector<Ty*>				mEntityList;
	};
}
