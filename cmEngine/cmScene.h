#pragma once

class cmGameObject;

class cmScene
{
public:
	cmScene();
	virtual ~cmScene();
	
	void EnterSceneCore();
	void UpdateScene();
	void LateUpdate();
	void ExitSceneCore();

	cmGameObject* CreateGameObject(bool isActive);
	cmGameObject* FindGameObjectByIDOrNull(const uint64& inObjID) const;
	void RemoveGameObject(const uint64& inObjID);

protected:
	virtual void EnterScene() abstract;
	virtual void ExitScene() abstract;
	
private:
	std::unordered_map<uint64, std::unique_ptr<cmGameObject>> mObjectRepo;
	std::vector<cmGameObject*> mUpdateList;

	// TODO : 이름으로 처리할 수 있는 기능 추가
	//std::unordered_map<std::string, uint64> mNameRepo;
};

