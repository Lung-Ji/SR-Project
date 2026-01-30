#pragma once

#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL PoolManager : public Base {
	DECLARE_SINGLETON(PoolManager)
private:
	explicit PoolManager();
	virtual ~PoolManager();

public:

private:

private:
	virtual VOID	Free();
};

END