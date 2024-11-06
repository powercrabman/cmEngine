#include "pch.h"
#include "cmConsole.h"
#include "cmConsoleGUI.h"
#include "cmRenderer.h"
#include "cmGUIRenderer.h"
#include "cmConsoleGUI.h"

cmConsole::cmConsole() = default;

void cmConsole::Initialize()
{
	// Console Data Reserve
	mConsoleDatas.reserve(100000);

	// CLI GUI ����
	mGUI = cmHelper::RegisterGUI<cmConsoleGUI>();

	//�⺻���� Ŀ�ǵ� ����
	AddCommand<cmExitCmd>();
	AddCommand<cmClearColorCmd>();
	AddCommand<cmHelpCmd>();
	AddCommand<cmSayCmd>();
	AddCommand<cmClearCmd>();
	AddCommand<cmResizeScreenCmd>();
}

void cmConsole::ExecuteCommand(const std::string& inCmd, const std::vector<std::string>& inArgv)
{
	auto it = mCommandHandlerRepo.find(inCmd);

	if (it == mCommandHandlerRepo.end())
	{
		//�������� �ʴ� ��ɾ�
		CommandErrorHandler();
	}
	else
	{
		//��ɾ� ����
		if (!(*it->second)(inArgv))
		{
			//�߸��� ��ɾ�
			CommandErrorHandler();
		}
	}
}

std::vector<cmICommand*> cmConsole::GetCommandList()
{
	std::vector<cmICommand*> ret;
	ret.reserve(mCommandHandlerRepo.size());
	for (const auto& cmd : mCommandHandlerRepo)
	{
		ret.push_back(cmd.second.get());
	}

	return ret;
}

void cmConsole::ClearConsoleDatas()
{
	mConsoleDatas.clear();
	if (mGUI) { mGUI->ClearHistory(); }
}
