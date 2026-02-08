#pragma once
#include "GameObject.h"

#pragma region Macros
#define POS(GAMEOBJECT)			static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Position()
#define ROTATION(GAMEOBJECT)	static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Rotation()
#define MYPOS					Component_Transform->Get_Position()

#pragma endregion

#define BatIMGX 287.f
#define BatIMGY 173.f

#define TRACKINGDIS 10.f
#define TRACKINGMAX 3.f
#define TRACKINGMIN 2.f
#define ATTACKREADY 1.f
#define ATTACKEND	2.f
#define RUSHSPEED	2.f

enum BAT_STATE { BAT_IDLE, BAT_TRACKING, BAT_ATTACKING, BAT_Hit, BAT_DEAD };

class Bat : public GameObject
{
private:
	explicit Bat(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Bat(CONST GameObject& _RHS);
	virtual ~Bat();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(CONST FLOAT& _DT);
	virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();

private:
	Buffer* Component_Buffer;
	Transform* Component_Transform;
	Collider* Component_Collider;

public:
	static Bat* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();

	VOID Set_Target(CONST TCHAR* _TAG);

	GameObject* pTarget;
	_vec3* pTargetPos;
	_vec3		vDir;

	BAT_STATE CurrState;
	BAT_STATE PrevState;

	VOID Change_State(BAT_STATE eState);
	VOID State_Idle();
	VOID State_Tracking(const _float& _DT);
	VOID State_Attacking(const _float& _DT);

	_float Timer1;
	_float Timer2;

	_float Default_Speed;
	_float Speed;


	_uint _frame;
	_float _frameTick;

};