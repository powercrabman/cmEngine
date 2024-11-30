#pragma once
namespace cmEngine
{
	class Editor
	{
	public:
		static void Initialize();

		template <typename ComponentType>
		static void AttachEditCallback(const std::function<void(GameEntity&)>& inCallback)
		{
			mEditCallbackRepo.emplace_back(
				EditCallbackData{
					.id = TYPE_ID(ComponentType),
					.callback = inCallback
				});
		}

		template <typename ComponentType>
		static void DattachEditCallback()
		{
			std::erase_if(mEditCallbackRepo, [](const EditCallbackData& inData)
				{
					return inData.id == TYPE_ID(ComponentType);
				});
		}

		static void RenderEditLayer(GameEntity inGameEntity)
		{
			for (const EditCallbackData& data : mEditCallbackRepo)
			{
				data.callback(inGameEntity);
			}
		}

		inline static const wchar_t* sEditorConfigPath = L"EditorConfig.json";

	private:
		struct EditCallbackData
		{
			TypeID							 id;
			std::function<void(GameEntity&)> callback;
		};
		inline static std::vector<EditCallbackData> mEditCallbackRepo;
	};
}
