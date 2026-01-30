#include "TimeManager.h"

IMPLEMENT_SINGLETON(TimeManager)

TimeManager::TimeManager() : TimeAccumulation(0.f), FixedFrame(0.f), DeltaTime(0.f), Frame(0) {}
TimeManager::~TimeManager() { Free(); }

HRESULT TimeManager::Ready_TimeManager() {

	if (TimerList.size() == (LONG)TIMERTYPE::TIMER_END - 1)	return E_FAIL;

	for (LONG TIMER = 0; TIMER < (LONG)TIMERTYPE::TIMER_END; ++TIMER) {
		TimerList.push_back(new Timer);

		ZeroMemory(&TimerList[TIMER]->CpuTick, sizeof(LARGE_INTEGER));
		ZeroMemory(&TimerList[TIMER]->FixTime, sizeof(LARGE_INTEGER));
		ZeroMemory(&TimerList[TIMER]->FrameTime, sizeof(LARGE_INTEGER));
		ZeroMemory(&TimerList[TIMER]->LastTime, sizeof(LARGE_INTEGER));

		TimerList[TIMER]->DeltaTime = 0.f;
		TimerList[TIMER]->ActivateFlag = FALSE;
	}

	return S_OK;
}
VOID	TimeManager::Update_TimeManager() {

	for (auto& Timer : TimerList) {
		if (Timer->ActivateFlag) {
			QueryPerformanceCounter(&Timer->FrameTime);

			if (Timer->FrameTime.QuadPart - Timer->FixTime.QuadPart >= Timer->CpuTick.QuadPart) {
				QueryPerformanceFrequency(&Timer->CpuTick);
				Timer->FixTime = Timer->FrameTime;
			}

			Timer->DeltaTime = (Timer->FrameTime.QuadPart - Timer->LastTime.QuadPart) / (_float)Timer->CpuTick.QuadPart;

			Timer->LastTime = Timer->FrameTime;
		}
	}
}
VOID	TimeManager::Update_TimeManager(TIMERTYPE _TYPE) {
	if (TimerList[(LONG)_TYPE]->ActivateFlag) {
		QueryPerformanceCounter(&TimerList[(LONG)_TYPE]->FrameTime);

		if (TimerList[(LONG)_TYPE]->FrameTime.QuadPart - TimerList[(LONG)_TYPE]->FixTime.QuadPart >= TimerList[(LONG)_TYPE]->CpuTick.QuadPart) {
			QueryPerformanceFrequency(&TimerList[(LONG)_TYPE]->CpuTick);
			TimerList[(LONG)_TYPE]->FixTime = TimerList[(LONG)_TYPE]->FrameTime;
		}

		TimerList[(LONG)_TYPE]->DeltaTime = (TimerList[(LONG)_TYPE]->FrameTime.QuadPart - TimerList[(LONG)_TYPE]->LastTime.QuadPart) / (_float)TimerList[(LONG)_TYPE]->CpuTick.QuadPart;

		TimerList[(LONG)_TYPE]->LastTime = TimerList[(LONG)_TYPE]->FrameTime;
	}
}
VOID	TimeManager::Activate_Timer(TIMERTYPE _TYPE) {
	TimerList[(LONG)_TYPE]->ActivateFlag = TRUE;

	QueryPerformanceCounter(&TimerList[(LONG)_TYPE]->FrameTime);
	QueryPerformanceCounter(&TimerList[(LONG)_TYPE]->LastTime);
	QueryPerformanceCounter(&TimerList[(LONG)_TYPE]->FixTime);

	QueryPerformanceFrequency(&TimerList[(LONG)_TYPE]->CpuTick);

}
VOID	TimeManager::DeActivate_Timer(TIMERTYPE _TYPE) {
	TimerList[(LONG)_TYPE]->ActivateFlag = FALSE;
}
BOOL	TimeManager::Check_FixedFrame(FLOAT _DeltaTime, FLOAT _FixedFrame) {

	TimeAccumulation += _DeltaTime;

	if (TimeAccumulation >= 1 / _FixedFrame) {
		TimeAccumulation = 0;
		return TRUE;
	}
	return FALSE;
}
VOID	TimeManager::Count_FrameAndDeltaTime(HWND _hWnd, TIMERTYPE _TYPE) {
	DeltaTime += TimeManager::GetInstance()->Get_DeltaTime(_TYPE);
	Frame++;

	if (DeltaTime >= 1.f) {
		WCHAR FPS[100] = { 0 };
		swprintf_s(FPS, L"FPS : %d || DeltaTime : %lf", Frame, DeltaTime);
		SetWindowText(_hWnd, FPS);

		DeltaTime = 0;
		Frame = 0;
	}
}
VOID	TimeManager::Free() {
	for_each(TimerList.begin(), TimerList.end(), Safe_Delete<Timer*>);
}