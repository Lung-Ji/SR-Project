#include "../Include/PCH.h"

Monster1::Monster1(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Monster1::Monster1(const GameObject& _RHS) : GameObject(_RHS) {}
Monster1::~Monster1() {}

HRESULT Monster1::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;

	Component_Transform->Get_Info(INFO_LOOK, &vDir);

	pTarget = nullptr;
	pTargetPos = nullptr;
	CurrState = MON1_IDLE;
	PrevState = CurrState;

	Timer1 = 0.f;
	Timer2 = 0.f;

	Default_Speed = 1.f;
	Speed = Default_Speed;

	return S_OK;
}
INT	Monster1::Update_GameObject(const _float& _DT) 
{
	// <플레이어 업데이트 시점>
	GameObject::Update_GameObject(_DT);
	
	Set_Target(L"Player");

	if (pTarget == nullptr)
	{
		Change_State(MON1_IDLE);
	}

	switch (CurrState)
	{
	case MON1_IDLE:
		State_Idle();
		break;
	case MON1_TRACKING:
		State_Tracking(_DT);
		break;
	case MON1_ATTACKING:
		State_Attacking(_DT);
		break;
	default:
		break;
	}
	
	D3DXVec3Normalize(&vDir, &vDir);
	Component_Transform->Move_Pos(&vDir, Speed, _DT);

	RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);
	return 0;
}
VOID Monster1::LateUpdate_GameObject(const _float& _DT) {
	GameObject::LateUpdate_GameObject(_DT);


}
VOID Monster1::Render_GameObject() {
	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

	Component_Texture->Set_Texture(L"Monster1.png");

	Component_Buffer->Render_Buffer();

	GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}
HRESULT Monster1::Component_Initialize() {

	Component_Buffer = ADD_COMPONENT_RECTTEX;
	Component_Transform = ADD_COMPONENT_TRANSFORM;

	Component_Transform->Set_Pos(10.f, 2.f, 10.f);
	Component_Transform->Set_Rotation(90.f, 0.f, 0.f);
	Component_Transform->Set_Scale(1.f, 1.f, 1.f);

	Component_Texture = ADD_COMPONENT_TEXTURE;
	Component_FSM = ADD_COMPONENT_FSM;

	Component_Texture->Import_TextureFromFolder(L"../../Resource/Monster");
	Component_FSM->FSM_StateInit(MONSTER_IDLE::GetInstance()->Instance());

	//pTarget = SceneManager::GetInstance()->Get_GameObject(L"Player");

	return S_OK;
}
Monster1* Monster1::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Monster1* MST = new Monster1(_GRPDEV);
	if (FAILED(MST->Ready_GameObject())) {
		MSG_BOX("Cannot Create Monster1.");
		Safe_Release(MST);
		return nullptr;
	}
	return MST;
}
VOID Monster1::Free() {

	MONSTER_IDLE::DestroyInstance();
	MONSTER_ATTACK::DestroyInstance();
	MONSTER_CHASE::DestroyInstance();
	MONSTER_DAMAGED::DestroyInstance();
	MONSTER_DEAD::DestroyInstance();

	GameObject::Free();
}

VOID Monster1::Set_Target(const TCHAR* _TAG)
{
	pTarget = SceneManager::GetInstance()->Get_GameObject(_TAG);
	if (pTarget != nullptr)
	{
		pTargetPos = POS(pTarget);
	}
}

VOID Monster1::Change_State(MONSTER1_STATE eState)
{
	PrevState = CurrState;
	CurrState = eState;
	Speed = 0.f;
	Timer1 = 0.f;
	Timer2 = 0.f;
}

VOID Monster1::State_Idle()
{
	Speed = 0.f;
	Timer2 = 0.f;
	Timer1 = 0.f;
	
	if (pTarget != nullptr)
	{
		vDir = *POS(pTarget) - *MYPOS;
		if (D3DXVec3Length(&vDir) < TRACKINGDIS)
		{
			Change_State(MON1_TRACKING);
		}
	}
}

VOID Monster1::State_Tracking(const _float& _DT)
{
	Speed = Default_Speed;
	vDir = *POS(pTarget) - *MYPOS;
	if (D3DXVec3Length(&vDir) < TRACKINGDIS)
	{
		Timer1 += _DT;
		Timer2 = 0.f;
	}
	else
	{
		Timer2 += _DT;
	}
	
	if (Timer1 >= TRACKINGMAX)
	{
		Change_State(MON1_ATTACKING);
	}

	if (Timer2 >= TRACKINGMIN)
	{
		Change_State(MON1_IDLE);
	}
}

VOID Monster1::State_Attacking(const _float& _DT)
{
	Timer1 += _DT;
	if (Timer1 < ATTACKREADY)
	{
		Speed = 0;
	}
	else if (Timer1 < ATTACKEND)
	{
		Speed = Default_Speed * 5;
	}
	else
	{
		Change_State(MON1_IDLE);
	}
}
