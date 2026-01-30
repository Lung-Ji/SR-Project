#pragma once
#include "GameObject.h"

class NPC : public GameObject {
private:
	explicit NPC(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit NPC(const GameObject& _RHS);
	virtual ~NPC();

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			INT			Update_GameObject(const _float& _DT);
	virtual			VOID		LateUpdate_GameObject(const _float& _DT);
	virtual			VOID		Render_GameObject();

private:
	HRESULT			Component_Initialize();

private:
	Buffer*		Component_Buffer;
	Transform*	Component_Transform;
	Texture*	Component_Texture;

	GameObject* Player;

public:
	static NPC* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
	virtual VOID Free();
};