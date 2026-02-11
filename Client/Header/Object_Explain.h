#pragma once
#include"GameObject.h"

class Object_Explain : public GameObject
{
private:
	explicit Object_Explain(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Object_Explain(CONST GameObject& _RHS);
	virtual ~Object_Explain();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual INT			Update_GameObject(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
	virtual VOID		Render_GameObject();

public:
	HRESULT Component_Initialize();
	static	Object_Explain* Create(LPDIRECT3DDEVICE9 _GRPDEV);

private:
	SpriteObject* Component_Sprite;
	Texture* Component_Texture;

private:
	virtual	VOID		Free();

};

