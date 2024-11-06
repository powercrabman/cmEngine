#pragma once
#include "cmCommonCommand.h"
#include "cmConsoleData.h"

//===============================
// 콘솔 데이터 보관 및 커맨드 처리
//===============================

class cmConsoleGUI;

class cmConsole
{
	ENGINE_MODULE_BODY();
	using CommandCallback = std::function<bool(std::string_view)>;
public:
	virtual ~cmConsole() = default;

	//초기화
	void Initialize();

	//명령어 실행
	void ExecuteCommand(const std::string& inCmd, const std::vector<std::string>& inArgv);

	//커맨드 추가 추가
	template<typename CmdClassType>
	void AddCommand();

	//에러 핸들러
	void CommandErrorHandler() { PushConsoleData("incorrect command :(", eConsoleDataType::Error); }

	//등록된 커맨드 리스트 확인 
	std::vector<cmICommand*> GetCommandList();

	//콘솔 데이터 Manage
	void ClearConsoleDatas();
	void PushConsoleData(std::string_view inMsg, eConsoleDataType inDataType = eConsoleDataType::Normal) { mConsoleDatas.push_back({ inDataType, inMsg.data() }); }
	const std::vector<cmConsoleData>& GetConsoleDatas() const { return mConsoleDatas; }

private:
	cmConsole();

	cmConsoleGUI* mGUI = nullptr;

	std::map<std::string, std::unique_ptr<cmICommand>> mCommandHandlerRepo;
	std::vector<cmConsoleData> mConsoleDatas;
};

//커맨드 추가 추가
template<typename CmdClassType>
void cmConsole::AddCommand()
{
	static_assert(std::is_base_of<cmICommand, CmdClassType>::value, "cmICommand를 상속받은 클래스여야 합니다.");
	std::unique_ptr<CmdClassType> cmd = std::make_unique<CmdClassType>();
	auto iter = mCommandHandlerRepo.find(cmd->GetCommandText());
	ASSERT(iter == mCommandHandlerRepo.end(), "Already Registed Command.");
	mCommandHandlerRepo[cmd->GetCommandText()] = std::move(cmd);
}
