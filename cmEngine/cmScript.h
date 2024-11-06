#pragma once
#include "cmComponent.h"

class cmScript : public cmComponent
{
public:
	cmScript() = default;
	virtual ~cmScript() = default;

	virtual void Initialize()	abstract; /* 자원을 생성, 단 한 번만 호출됨 */
	virtual void Update()		abstract; /* 메인 업데이트 */
	virtual void LateUpdate()	abstract; /* Update 에서 갱신된 내용을 통해 오브젝트 상태 보정 및 결정 */

private:
};

