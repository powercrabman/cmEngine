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

	// TODO : �̸����� ó���� �� �ִ� ��� �߰�
	//std::unordered_map<std::string, uint64> mNameRepo;
};

