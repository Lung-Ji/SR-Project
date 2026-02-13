#include"GameObject.h"

#define FRAMETICK 0.2f

#pragma region Macros
#define POS(GAMEOBJECT)			static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Position()
#define ROTATION(GAMEOBJECT)	static_cast<Transform*>(GAMEOBJECT->Get_Component(COMPONENT_TYPE::COMPONENT_TRANSFORM))->Get_Rotation()
#define MYPOS					Component_Transform->Get_Position()
#define MYSCALE					Component_Transform->Get_Scale()
#define MYROTATION				Component_Transform->Get_Rotation()
#define STATS(MONSTER_STATISTICS) fStatistics[MONSTER_STATISTICS]
#define CURRSTATE
#pragma endregion
#pragma region MonsterSummon&MonsterDeath
#define MONSTER_SUMMON01_PLAYTIME	1.f
#define MONSTER_SUMMON02_PLAYTIME	1.1f
#define MONSTER_SUMMON03_PLAYTIME	1.f
#define MONSTER_DEATH_PLAYTTIME		1.f
#pragma endregion
#pragma region Bat
#define BAT_SPEED					1.f			//	기본 이동 속도
#define BAT_HP						100.f		//	기본 체력

#define BAT_TRACKINGDIS				5.f			//	플레이어 감지 범위
#define BAT_TRACKING_TIME			3.f			//	공격 쿨타임					TRACKING	-> CASTING
#define BAT_LOST_TIME				2.f			//	추적 놓치는 시간				TRACKING	-> IDLE

#define BAT_CASTING_TIME			1.f			//	시전 시간(선딜)				CASTING		-> CHANNELING

#define BAT_CHANNELING_TIME			2.f			//	공격 패턴 유지 시간(후딜)		CHANNELING	-> IDLE
#define BAT_BULLET_NUM				5			//	총알 갯수
#define BAT_RUSHSPEED				2.f			//	CHANELING 중 이동 속도

#define BAT_HORIZONTALFLIP_BUFFER	0.1f		//	이미지 좌우 반전 버퍼
#pragma endregion
#pragma region Bullet_Standard
#define	BULLET_STANDARD_SPEED  1.f
#pragma endregion

#pragma region ScorpionEvilSoul
#define SCORPIONEVILSOUL_SPEED					1.f			//	기본 이동 속도
#define SCORPIONEVILSOUL_HP						100.f		//	기본 체력

#define SCORPIONEVILSOUL_TRACKINGDIS			5.f			//	플레이어 감지 범위
#define SCORPIONEVILSOUL_TRACKINGMIN			2.f			//  이 이상 가까워지려하지 않음
#define SCORPIONEVILSOUL_TRACKING_TIME			3.f			//	공격 쿨타임					TRACKING	-> CASTING
#define SCORPIONEVILSOUL_LOST_TIME				2.f			//	추적 놓치는 시간				TRACKING	-> IDLE

#define SCORPIONEVILSOUL_CASTING_TIME			1.f			//	시전 시간(선딜)				CASTING		-> CHANNELING

#define SCORPIONEVILSOUL_CHANNELING_TIME		2.f			//	공격 패턴 유지 시간(후딜)		CHANNELING	-> IDLE
#define SCORPIONEVILSOUL_BULLET_NUM				5			//	총알 갯수
#define SCORPIONEVILSOUL_RUSHSPEED				2.f			//	CHANELING 중 이동 속도

#define SCORPIONEVILSOUL_HORIZONTALFLIP_BUFFER	0.1f		//	이미지 좌우 반전 버퍼
#pragma endregion

#pragma region ShotGunEvilSoul
#define SHOTGUNEVILSOUL_SPEED					1.f			//	기본 이동 속도
#define SHOTGUNEVILSOUL_HP						100.f		//	기본 체력

#define SHOTGUNEVILSOUL_TRACKINGDIS				5.f			//	플레이어 감지 범위
#define SHOTGUNEVILSOUL_TRACKING_TIME			3.f			//	공격 쿨타임					TRACKING	-> CASTING
#define SHOTGUNEVILSOUL_LOST_TIME				2.f			//	추적 놓치는 시간				TRACKING	-> IDLE

#define SHOTGUNEVILSOUL_CASTING_TIME			1.f			//	시전 시간(선딜)				CASTING		-> CHANNELING

#define SHOTGUNEVILSOUL_CHANNELING_TIME			0.5f		//	공격 패턴 유지 시간(후딜)		CHANNELING	-> IDLE
#define SHOTGUNEVILSOUL_BULLET_NUM				12			//	총알 갯수
#define SHOTGUNEVILSOUL_SPREAD					30.f		//	분산 범위

#define SHOTGUNEVILSOUL_HORIZONTALFLIP_BUFFER	0.1f		//	이미지 좌우 반전 버퍼
#pragma endregion

#pragma region EvilSlime
#define EVILSLIME_SPEED						1.f			//	기본 이동 속도
#define EVILSLIME_HP						100.f		//	기본 체력

#define EVILSLIME_TRACKINGDIS				5.f			//	플레이어 감지 범위
#define EVILSLIME_TRACKING_TIME				3.f			//	공격 쿨타임					TRACKING	-> CASTING
#define EVILSLIME_LOST_TIME					2.f			//	추적 놓치는 시간				TRACKING	-> IDLE

#define EVILSLIME_CASTING_TIME				3.f			//	시전 시간(선딜)				CASTING		-> CHANNELING
#define EVILSIME_JUMP_HEIGHT				1.f			//	점프 공격 높이

#define EVILSLIME_CHANNELING_TIME			0.3f		//	공격 패턴 유지 시간(후딜)		CHANNELING	-> IDLE
#define EVILSLIME_BULLET_NUM				8			//	총알 갯수
#define EVILSLIME_RUSHSPEED					2.f			//	CHANELING 중 이동 속도

#define EVILSLIME_HORIZONTALFLIP_BUFFER		0.1f		//	이미지 좌우 반전 버퍼
#pragma endregion
enum MONSTER_STATE
{
	MONSTER_STATE_SUMMON,
	MONSTER_STATE_APPEAR,
	MONSTER_STATE_IDLE,
	MONSTER_STATE_TRACKING,
	MONSTER_STATE_CASTING,
	MONSTER_STATE_CHANNELING,
	MONSTER_STATE_HIT,
	MONSTER_STATE_DEAD,
	MONSTER_STATE_END
};
enum MONSTER_TRIGGER {
	MONSTER_TRIGGER_SUMMONSTER,
	MONSTER_TRIGGER_END,
};
enum MONSTER_STATISTICS {
	MONSTER_STAT_HP,
	MONSTER_STAT_ATK,
	MONSTER_STAT_END
};

typedef struct tagTextureInfo
{
	tagTextureInfo() :_frame(0), _Endframe(0), _frameTick(0.f) { _vecTexture.reserve(32); }
	~tagTextureInfo() { _vecTexture.clear(); }

	vector<IDirect3DTexture9*>	_vecTexture;
	TCHAR						_Filename[256];
	_uint						_frame;
	_uint						_Endframe;
	_float						_frameTick;

}TEXINFO;


typedef struct tagMonsterInfo {
	tagMonsterInfo() :
		bTrigger{}, eState{}, fStatistics{}, fTimer{}, pGameObj{},
		vDirection{-1.f,0.f,-1.f}, fSpeed(0.f)				{}
	~tagMonsterInfo() {}

	VOID	Change_State(MONSTER_STATE _eState) 
	{
		eState[1]			= eState[0];
		eState[0]			= _eState;
		fSpeed				= 0.f;
		memset(fTimer, 0, sizeof(fTimer));
	}

	BOOL						bTrigger[4];
	MONSTER_STATE				eState[2];
	_float						fTimer[4];
	GameObject*					pGameObj[16];

	_vec3						vDirection;
	_float						fSpeed;

	TEXINFO						Textureinfo;

	_float						fStatistics[MONSTER_STAT_END];

	_float						fHp;
	_float						fAtk;
}MONSTERINFO, MONINFO, MONBULLETINFO;
class Monster
{
public:
	static	GameObject* Set_Target(CONST TCHAR* _TAG, GameObject*& GameObj);
	static	GameObject* Set_Target(CONST TCHAR* _TAG);
	static	_vec3		Normalize(_vec3 vec);

//렌더링 관련
public:
	static	HRESULT			Set_TextureList(CONST TCHAR* __FileName, TEXINFO* __Textures);
	static	HRESULT			Set_TextureList(CONST TCHAR* __FileName, MONINFO* _MonsterInfo);
	static	FLOAT			BillBoard(Transform* TransCom, LPDIRECT3DDEVICE9 _GRPDEV, _vec3 vRight = { 1.f, 0.f,0.f });
	static	HRESULT			Flip_Horizontal(Transform* TransCom, _vec3* pDir, _float Buffer);
	static	VOID			BillBoard_Standard(LPDIRECT3DDEVICE9 GRPDEV, Transform* Component_Transform);
// 충돌 관련
public:


	//생성 관련
public:
	static VOID Add_Monster_to_Scene(GameObject* pMonster); // 씬& 콜리전 오브젝트 리스트에 오브젝트를 추가, _TAG는 클래스 이름
	static uint64_t XorShift128plus(uint64_t& _Seed1, uint64_t& _Seed2);	// 랜덤 비트연산 

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

		pTransCom->Get_Position()->y = pTransCom->Get_Scale()->y * 0.5f;
		//static_cast<Collider*>(MST->Get_Component(COMPONENT_TYPE::COMPONENT_COLLIDER))->Set_Scale();
		return MST;
	}
};