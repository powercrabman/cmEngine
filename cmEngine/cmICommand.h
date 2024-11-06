#pragma once

//===========================================
// 커맨드 코드는 따로 파일로 저장하기가 힘듦
// 그러므로 커맨드 코드를 파일로 따로 관리하는건 어려울 듯
// help 함수 구현을 위해서, helpDesc = (명령어 설명...)
// 명령어 호출을 struct에 추가하기
// 모든 명령어는 람다로 받지 말고 cmICommand 에서
// 파생된 것만 받도록 한다.
//===========================================

//=====================================
// Interface
//=====================================

struct cmICommand
{
	virtual bool operator()(const std::vector<std::string>& inArgs) const abstract;
	virtual const char* GetHelpDesc() const abstract;
	virtual const char* GetCommandText() const abstract;
};