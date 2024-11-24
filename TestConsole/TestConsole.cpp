#include "entt.hpp"
#include <iostream>

// 샘플 컴포넌트
struct Health { int hp; };
struct Position { float x, y; };
struct Name { std::string value; };

// 엔티티 복제 함수
void CloneEntity(entt::registry& registry, entt::entity source, entt::entity target)
{
	for (auto [id, storage] : registry.storage())
	{
		if (id == entt::type_id<Health>().hash())
		{
			continue;
		}

		if (storage.contains(source))
		{
			storage.push(target, storage.value(source));
		}
	}
}

int main() {
	entt::registry registry;

	// 소스 엔티티 생성 및 컴포넌트 추가
	auto source = registry.create();
	registry.emplace<Health>(source, 100);
	registry.emplace<Position>(source, 1.0f, 2.0f);
	registry.emplace<Name>(source, "Player");

	// 대상 엔티티 생성
	auto target = registry.create();

	// 클론 수행
	CloneEntity(registry, source, target);

	// 클론된 엔티티 확인
	std::cout << "Cloned Position: (" << registry.get<Position>(target).x << ", " << registry.get<Position>(target).y << ")\n";
	std::cout << "Cloned Name: " << registry.get<Name>(target).value << "\n";

	return 0;
}
