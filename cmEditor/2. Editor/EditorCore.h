#pragma once

class EditorCore
{
	SINGLETON(EditorCore);
public:
	void				SetEditEntity(const GameEntity& inGameEntity) { mEditEntity = inGameEntity; }
	const GameEntity&	TryGetEditEntity() const { return mEditEntity; }

private:
	EditorCore();
	~EditorCore() = default;

	GameEntity	mEditEntity = GameEntity::NullEntity;
};

