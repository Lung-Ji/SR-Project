#include"GameObject.h"

#pragma region Macros
#define POS(GAMEOBJECT)			static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Position()
#define ROTATION(GAMEOBJECT)	static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Rotation()
#define MYPOS					Component_Transform->Get_Position()
#define MYSCALE					Component_Transform->Get_Scale()
#define MYROTATION				Component_Transform->Get_Rotation()
#pragma endregion

#pragma region MonsterSummon
#define MONSTERSUMMON01PLAYTIME 0.5f
#define MONSTERSUMMON02PLAYTIME	0.5f
#define MONSTERSUMMON03PLAYTIME 0.55f

#pragma endregion

#pragma region Bat
#define BATTRACKINGDIS	5.f
#define BATTRACKINGMAX	3.f
#define BATTRACKINGMIN	2.f
#define BATATTACKREADY	1.f
#define BATATTACKEND	2.f
#define BATRUSHSPEED	2.f
#pragma endregion

typedef struct tagTextureInfo
{
	vector<IDirect3DTexture9*>	_vecTexture;
	TCHAR						_Filename[256]	= L"";
	_uint						_frame			=	0;
	_uint						_Endframe		=	0;
	_float						_frameTick		=	0.f;
}TEXINFO;

typedef struct tagCollisionInfo
{
	_float _hp		= 0.f;
	_float _atk		= 0.f;

}COLINFO;

class Monster
{
public:
	static	GameObject* Set_Target(CONST TCHAR* _TAG, GameObject*& GameObj);
	static	GameObject* Set_Target(CONST TCHAR* _TAG);

//렌더링 관련
public:
	static	HRESULT			Set_TextureList(CONST TCHAR* __FileName, TEXINFO* __Textures);
	static	FLOAT			BillBoard(Transform* TransCom, LPDIRECT3DDEVICE9 _GRPDEV, _vec3 vRight = { 1.f, 0.f,0.f });
	static	HRESULT			Flip_Horizontal(Transform* TransCom, _vec3* pDir, _float Buffer);

// 충돌 관련
public:


	//생성 관련
public:
	static VOID Add_Monster_to_Scene(GameObject* pMonster); // 씬& 콜리전 오브젝트 리스트에 오브젝트를 추가, _TAG는 클래스 이름

	template<typename T>
	static	GameObject* Create(LPDIRECT3DDEVICE9 _GRPDEV)
	{
		GameObject* MST = new T(_GRPDEV);
		if (FAILED(MST->Ready_GameObject())) {
			string ErrorMsg = string("Cannot Create ") + typeid(T).name();
			//MSG_BOX(ErrorMsg.c_str());
			Safe_Release(MST);
			return nullptr;
		}
		return MST;
	}//기초 생성용  "," 찍고 위치 및 배율 설정 가능

	template<typename T>
	static	GameObject* Create(LPDIRECT3DDEVICE9 _GRPDEV, _vec3 _vPos, _float _fScalemult = 3.f)	// 배율 3은 주고 생각할것
	{
		GameObject* MST = Create<T>(_GRPDEV);

		Transform* pTransCom = static_cast<Transform*>(MST->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM));
		pTransCom->Set_Pos(_vPos);
		*pTransCom->Get_Scale() *= _fScalemult;

		//static_cast<Collider*>(MST->Get_Component(COMPONENT_TYPE::COMPONENT_COLLIDER))->Set_Scale();


		return MST;
	}

};