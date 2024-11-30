#pragma once

namespace cmEngine
{
	class SceneSerializer
	{
	public:
		SceneSerializer() { std::filesystem::create_directory(std::filesystem::current_path() / sSceneFileDirectory); }
		~SceneSerializer() = default;

		void SerializeSceneToFile(Scene* inScene)
		{
			SerializeSceneToFile(inScene, inScene->GetName());
		}

		void SerializeSceneToFile(Scene* inScene, const std::filesystem::path& inFile, const std::filesystem::path& inDirectory = "") const
		{
			json js = {};

			// Scene �⺻ ����
			js["SceneName"] = inScene->GetName();

			// Serializer ������ Component ��� Get
			entt::registry& r = inScene->GetRegistry();

			entt::id_type m = entt::type_hash<Name>();

			for (auto [hash, set] : r.storage())
			{
				for (entt::entity e : set)
				{
					COMPONENT_SERIALIZER.Serializer(hash, GameEntity{inScene, e}, js, set.value(e));
				}
			}

			// ī�޶� ����
			const GameEntity& cmr = inScene->TryGetSceneCamera();
			if (cmr.IsNull())
			{
				js["SceneCamera"] = -1;
			}
			else
			{
				js["SceneCamera"] = cmr.GetID();
			}

			// ���Ϸ� ����
			std::ofstream ofs;

			std::filesystem::path path = {};
			if (inDirectory.empty())
			{
				path = sSceneFileDirectory / inFile;
			}
			else
			{
				path = inDirectory / inFile;
			}

			if (!path.has_extension()) { path += ".json"; }
			ofs.open(path);

			if (ofs.fail())
			{
				assert(false);
				ENGINE_LOG_ERROR("Scene Save Fail");
				return;
			}

			ofs << js.dump(0);
			ofs.close();
		}

		bool DeserializeSceneFromFile(const std::filesystem::path& inFile, const std::filesystem::path& inDirectory = "")
		{
			std::ifstream ifs;
			
			std::filesystem::path path = {};
			if (inDirectory.empty())
			{
				path = sSceneFileDirectory / inFile;
			}
			else
			{
				path = inDirectory / inFile;
			}
			ifs.open(path);
			
			if (ifs.fail())
			{
				ENGINE_LOG_ERROR("Scene Load Fail");
				return false;
			}

			// �̸� �ҷ�����
			json js = json::parse(ifs);
			Scene* sc = SCENE_MANAGER.CreateOrReplaceScene(js["SceneName"]);

			// ��ƼƼ, ������Ʈ ����
			for (const auto& [header, item] : js.items())
			{
				if (header == "SceneName" || header == "SceneCamera") continue;

				GameEntity e = sc->CreateGameEntityByID(std::stoi(header));
				for (const auto& [compName, _] : item.items())
				{
					COMPONENT_SERIALIZER.Deserializer(compName, e, js);
				}
			}

			// ���� ī�޶� ����
			int entityID = js["SceneCamera"];
			if (entityID != -1)
			{
				sc->SetSceneCamera(GameEntity{ sc, static_cast<entt::entity>(entityID) });
			}

		}

		inline static const char* sSceneFileDirectory = "Scenes";
	};
}


