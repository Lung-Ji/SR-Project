#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
class ENGINE_DLL Component : public Base {
protected:
	explicit Component();
	explicit Component(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Component(CONST Component& _RHS);
	virtual ~Component();

public:
	virtual HRESULT		Ready_Component()						{ return 0; }
	virtual INT			Update_Component(CONST FLOAT& _DT)		{ return 0; }
	virtual VOID		LateUpdate_Component(CONST FLOAT& _DT)	{			}
	virtual VOID		Render_Component()						{			}

protected:
	LPDIRECT3DDEVICE9		GRPDEV;
	BOOL					CLONE;

public:
	virtual	Component*	Clone()	PURE;
protected:
	virtual	VOID		Free() { Safe_Release(GRPDEV); }
};
END