#pragma once
#include "GameObject.h"

class CubeTile :
    public GameObject
{
private:
    explicit CubeTile();
    explicit CubeTile(LPDIRECT3DDEVICE9 _GRPDEV);
    explicit CubeTile(const GameObject& ths);
    virtual ~CubeTile();

public:

    virtual			HRESULT		Ready_GameObject();
    virtual			INT			Update_GameObject(CONST FLOAT& _DT);
    virtual			VOID		LateUpdate_GameObject(CONST FLOAT& _DT);
    virtual			VOID		Render_GameObject();

private:
    HRESULT			Component_Initialize();

    Buffer*         m_pBuffer;
    Transform*      m_pTransform;
public:
    static         CubeTile* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
   virtual  void            Free();

};

