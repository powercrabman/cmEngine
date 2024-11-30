#pragma once

namespace cmEngine
{
	enum class eScriptUpdateLevel
	{
		Update,
		Count
	};

	enum class eScriptRenderLevel
	{
		Render,
		Count
	};

	class Scene;

	class ScriptStack
	{
		using ScriptCallback = std::function<void(Scene*)>;
	public:
		ScriptStack() = default;
		~ScriptStack() = default;

		//===================================================
		//			           Update
		//===================================================

		void AttachUpdateScript(const ScriptCallback& inCallback, eScriptUpdateLevel inLevel)
		{
			mUpdateStack[static_cast<uint32>(inLevel)].push_back(inCallback);
		}

		void DattachUpdateScript(const ScriptCallback& inCallback, eScriptUpdateLevel inLevel)
		{
			auto& updateStack = mUpdateStack[static_cast<uint32>(inLevel)];
			std::erase_if(updateStack, [&](const ScriptCallback& callback)
				{
					return callback.target<void(Scene*)>() == inCallback.target<void(Scene*)>();
				});
		}

		void OnUpdateScript(Scene* inScene) const
		{
			for (const auto& updateStack : mUpdateStack)
			{
				for (const auto& callback : updateStack)
				{
					callback(inScene);
				}
			}
		}

		//===================================================
		//			           Render
		//===================================================

		void AttachRenderScript(const ScriptCallback& inCallback, eScriptRenderLevel inLevel)
		{
			mRenderStack[static_cast<uint32>(inLevel)].push_back(inCallback);
		}

		void DattachRenderScript(const ScriptCallback& inCallback, eScriptRenderLevel inLevel)
		{
			auto& RenderStack = mRenderStack[static_cast<uint32>(inLevel)];
			std::erase_if(RenderStack, [&](const ScriptCallback& callback)
				{
					return callback.target<void(Scene*)>() == inCallback.target<void(Scene*)>();
				});
		}

		void OnRenderScript(Scene* inScene) const
		{
			for (const auto& RenderStack : mRenderStack)
			{
				for (const auto& callback : RenderStack)
				{
					callback(inScene);
				}
			}
		}

		// ect
		void Clear()
		{
			for (auto& updateStack : mUpdateStack) { updateStack.clear(); }
			for (auto& renderStack : mRenderStack) { renderStack.clear(); }
		}

	private:
		std::array<std::vector<ScriptCallback>, static_cast<uint32>(eScriptUpdateLevel::Count)> mUpdateStack;
		std::array<std::vector<ScriptCallback>, static_cast<uint32>(eScriptRenderLevel::Count)> mRenderStack;
	};

}
