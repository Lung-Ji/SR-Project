#pragma once
#include "Base.h"
#include "Engine_Define.h"

class LoadThread : public Base {
public:
	enum class LOADID { LOADING_STAGE, LOADING_BOSS, LOADING_END };

public:
	explicit LoadThread(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual ~LoadThread();

public:
	CONST TCHAR*	Get_LoadingState()	{ return LoadState; }
	LOADID			Get_LoadID()		{ return LID;		}
	BOOL			Check_Finished()	{ return Finish;	}

	CRITICAL_SECTION* Get_CRTSEC()		{ return &CRTSEC;	}

public:
	static UINT CALLBACK Thread_Main(LPVOID ARG);

public:
	HRESULT		Ready_Loading(LOADID _LID);
	UINT		Loading_Stage();

private:
	LPDIRECT3DDEVICE9		GRPDEV;
	TCHAR					LoadState[128];

	HANDLE					ThreadHandle;
	LOADID					LID;

	CRITICAL_SECTION		CRTSEC;
	BOOL					Finish;

public:
	static LoadThread*	Create(LPDIRECT3DDEVICE9	_GRPDEV, LOADID _LID);
private:
	virtual		VOID	Free();
};

