#pragma once
#include "cmComponent.h"

class cmScript : public cmComponent
{
public:
	cmScript() = default;
	virtual ~cmScript() = default;

	virtual void Initialize()	abstract; /* �ڿ��� ����, �� �� ���� ȣ��� */
	virtual void Update()		abstract; /* ���� ������Ʈ */
	virtual void LateUpdate()	abstract; /* Update ���� ���ŵ� ������ ���� ������Ʈ ���� ���� �� ���� */

private:
};

