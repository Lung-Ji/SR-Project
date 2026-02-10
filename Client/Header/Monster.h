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

class Monster
{
public:
	explicit Monster() {}
	virtual ~Monster() {}

	static GameObject*	Set_Target(CONST TCHAR* _TAG, GameObject* GameObj = nullptr);

	static D3DSURFACE_DESC	Get_SurfaceDesc(LPDIRECT3DTEXTURE9 pTexture);

	static IDirect3DTexture9* Find_CurrTexture(CONST TCHAR* _FileName, IDirect3DTexture9* pTexture = nullptr);

	static size_t Set_TextureList(CONST TCHAR* __FileName, vector<IDirect3DTexture9*>* __Textures);
};