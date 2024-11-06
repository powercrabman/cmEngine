#pragma once
#include "cmCommonCommand.h"
#include "cmConsoleData.h"

//===============================
// �ܼ� ������ ���� �� Ŀ�ǵ� ó��
//===============================

class cmConsoleGUI;

class cmConsole
{
	ENGINE_MODULE_BODY();
	using CommandCallback = std::function<bool(std::string_view)>;
public:
	virtual ~cmConsole() = default;

	//�ʱ�ȭ
	void Initialize();

	//��ɾ� ����
	void ExecuteCommand(const std::string& inCmd, const std::vector<std::string>& inArgv);

	//Ŀ�ǵ� �߰� �߰�
	template<typename CmdClassType>
	void AddCommand();

	//���� �ڵ鷯
	void CommandErrorHandler() { PushConsoleData("incorrect command :(", eConsoleDataType::Error); }

	//��ϵ� Ŀ�ǵ� ����Ʈ Ȯ�� 
	std::vector<cmICommand*> GetCommandList();

	//�ܼ� ������ Manage
	void ClearConsoleDatas();
	void PushConsoleData(std::string_view inMsg, eConsoleDataType inDataType = eConsoleDataType::Normal) { mConsoleDatas.push_back({ inDataType, inMsg.data() }); }
	const std::vector<cmConsoleData>& GetConsoleDatas() const { return mConsoleDatas; }

private:
	cmConsole();

	cmConsoleGUI* mGUI = nullptr;

	std::map<std::string, std::unique_ptr<cmICommand>> mCommandHandlerRepo;
	std::vector<cmConsoleData> mConsoleDatas;
};

//Ŀ�ǵ� �߰� �߰�
template<typename CmdClassType>
void cmConsole::AddCommand()
{
	static_assert(std::is_base_of<cmICommand, CmdClassType>::value, "cmICommand�� ��ӹ��� Ŭ�������� �մϴ�.");
	std::unique_ptr<CmdClassType> cmd = std::make_unique<CmdClassType>();
	auto iter = mCommandHandlerRepo.find(cmd->GetCommandText());
	ASSERT(iter == mCommandHandlerRepo.end(), "Already Registed Command.");
	mCommandHandlerRepo[cmd->GetCommandText()] = std::move(cmd);
}
