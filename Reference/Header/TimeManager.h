#pragma once

#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

struct ENGINE_DLL Timer {
	LARGE_INTEGER		FrameTime;
	LARGE_INTEGER		FixTime;
	LARGE_INTEGER		LastTime;
	LARGE_INTEGER		CpuTick;

	FLOAT				DeltaTime;

	BOOL				ActivateFlag;
};

class ENGINE_DLL TimeManager : public Base {
	DECLARE_SINGLETON(TimeManager)
private:
	explicit TimeManager();
	virtual ~TimeManager();

public:
	HRESULT		Ready_TimeManager();
	VOID		Update_TimeManager();

	VOID		Update_TimeManager(TIMERTYPE _TYPE);

	FLOAT		Get_DeltaTime(TIMERTYPE _TYPE) { return TimerList[(LONG)_TYPE]->DeltaTime; }

	VOID		Activate_Timer(TIMERTYPE _TYPE);
	VOID		DeActivate_Timer(TIMERTYPE _TYPE);

	BOOL		Check_TimerActivation(TIMERTYPE _TYPE) { return TimerList[(LONG)_TYPE]->ActivateFlag; }

	BOOL		Check_FixedFrame(FLOAT _DeltaTime, FLOAT _FixedFrame);

	VOID		Count_FrameAndDeltaTime(HWND _hWnd, TIMERTYPE _TYPE);

private:
	vector<Timer*>		TimerList;
	FLOAT				TimeAccumulation;
	FLOAT				FixedFrame;

	FLOAT				DeltaTime;
	UINT				Frame;
private:
	virtual void		Free();
};

END