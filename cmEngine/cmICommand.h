#pragma once

//===========================================
// Ŀ�ǵ� �ڵ�� ���� ���Ϸ� �����ϱⰡ ����
// �׷��Ƿ� Ŀ�ǵ� �ڵ带 ���Ϸ� ���� �����ϴ°� ����� ��
// help �Լ� ������ ���ؼ�, helpDesc = (��ɾ� ����...)
// ��ɾ� ȣ���� struct�� �߰��ϱ�
// ��� ��ɾ�� ���ٷ� ���� ���� cmICommand ����
// �Ļ��� �͸� �޵��� �Ѵ�.
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