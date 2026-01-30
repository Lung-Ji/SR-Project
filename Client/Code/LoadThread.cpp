#include "../Include/PCH.h"
#include "LoadThread.h"

LoadThread::LoadThread(LPDIRECT3DDEVICE9 _GRPDEV) : GRPDEV(_GRPDEV), Finish(false), LID(LOADID::LOADING_END) {
	ZeroMemory(LoadState, sizeof(LoadState));
	GRPDEV->AddRef();
}
LoadThread::~LoadThread()	{}

UINT LoadThread::Thread_Main(LPVOID ARG) {
    LoadThread* LOAD = reinterpret_cast<LoadThread*>(ARG);

    int iFlag(0);

    EnterCriticalSection(LOAD->Get_CRTSEC());

    switch (LOAD->Get_LoadID())
    {
    case LOADID::LOADING_STAGE:
        iFlag = LOAD->Loading_Stage();
        break;

    case LOADID::LOADING_BOSS:
        break;
    }

    LeaveCriticalSection(LOAD->Get_CRTSEC());

    //_endthreadex(0);

    return iFlag;       // 0 리턴 시, _endthreadex가 자동 호출
}
HRESULT LoadThread::Ready_Loading(LOADID _LID) {
	InitializeCriticalSection(&CRTSEC);
	LID = _LID;

	ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, Thread_Main, this, 0, NULL);

	return S_OK;
}
UINT LoadThread::Loading_Stage() {
    //lstrcpy(LoadState, L"Buffer Loading.....................................");
    //
    //if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_TriCol", Engine::CTriCol::Create(m_pGraphicDev))))
    //    return E_FAIL;
    //
    //if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_RcCol", Engine::CRcCol::Create(m_pGraphicDev))))
    //    return E_FAIL;
    //
    //lstrcpy(LoadState, L"Texture Loading.....................................");
    //
    //if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_PlayerTexture", Engine::CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Ma.jpg", 1))))
    //    return E_FAIL;
    //
    //lstrcpy(LoadState, L"Etc Loading.....................................");
    //
    //if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_Transform", Engine::CTransform::Create(m_pGraphicDev))))
    //    return E_FAIL;
    //
    //lstrcpy(LoadState, L"Loading Complete !!!!");

    Finish = TRUE;

    return 0;
}
LoadThread* LoadThread::Create(LPDIRECT3DDEVICE9 _GRPDEV, LOADID _LID) {
    LoadThread* LOAD = new LoadThread(_GRPDEV);

    if (FAILED(LOAD->Ready_Loading(_LID))){
        Safe_Release(LOAD);
        MSG_BOX("Cannot Create LoadThread.");
        return nullptr;
    }

    return LOAD;
}
VOID	LoadThread::Free() {
    WaitForSingleObject(ThreadHandle, INFINITE);
    CloseHandle(ThreadHandle);
    DeleteCriticalSection(&CRTSEC);
    Safe_Release(GRPDEV);
}