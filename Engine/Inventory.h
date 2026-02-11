#pragma once
#include "Component.h"

BEGIN(Engine)
class ENGINE_DLL Inventory :  public Component
{
private:
  explicit Inventory();
  explicit Inventory(LPDIRECT3DDEVICE9 _GRPDEV);
  explicit Inventory(CONST Inventory& _RHS);
  virtual  ~Inventory();

public:
  virtual HRESULT Ready_Component();
  virtual INT     Update_Component(CONST FLOAT& _DT);
  virtual VOID    LateUpdate_Component(CONST FLOAT& _DT);
  virtual VOID    Render_Component();


public:
  virtual Component* Clone();
  static  Inventory* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
  IDirect3DBaseTexture9* m_pTexture;
private:
  virtual VOID    Free();
};
END