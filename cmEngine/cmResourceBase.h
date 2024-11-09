#pragma once

class cmResourceBase
{
public:
	cmResourceBase() = default;
	virtual ~cmResourceBase() = default;

	virtual void Create() abstract;
};