#pragma once
#include "GameObject.h"
#include "Texture.h"
#include "Sprite.h"

class PlayerEquipMent : public GameObject
{
private:
  explicit PlayerEquipMent(LPDIRECT3DDEVICE9 _GRPDEV);
  explicit PlayerEquipMent(CONST GameObject& _rhs);
  explicit PlayerEquipMent(LPDIRECT3DDEVICE9 _GRPDEV, CONST TCHAR* _TAG);
  virtual  ~PlayerEquipMent();

public:
  HRESULT Component_Initialize(){}
public:
  virtual	HRESULT		Ready_GameObject();
  virtual INT			Update_GameObject(CONST FLOAT& _DT);
  virtual VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
  virtual VOID		Render_GameObject();

  static PlayerEquipMent* Create(LPDIRECT3DDEVICE9 _GRPDEV);
private:
  virtual VOID Free();

private:
  Texture*      Component_texture;
  SpriteObject* Component_Sprite;
};

