#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL Transform : public Component {
private:
	explicit Transform();
	explicit Transform(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Transform(CONST Transform& _RHS);
	virtual ~Transform();

public:
	virtual HRESULT		Ready_Component();
	virtual INT			Update_Component(CONST FLOAT& _DT);
	virtual VOID		LateUpdate_Component(CONST FLOAT& _DT);


public:
	_matrix*		Get_World()		{ return &WorldMatrix; }
public:
	VOID		Move_Pos(CONST _vec3* _Direction, CONST _float& _Speed, CONST _float& _DT){
		m_vInfo[INFO_POS] += *_Direction * _Speed * _DT;
	}
	VOID		Rotation(ROTATION eType, const _float& fAngle) {
		*(((_float*)&m_vAngle) + eType) += fAngle;
	}
	VOID				Get_Info(INFO eType, _vec3* pInfo)
	{
		memcpy(pInfo, &WorldMatrix.m[eType][0], sizeof(_vec3));
	}

private:
	_vec3		m_vInfo[INFO_END];
	_vec3		m_vScale;
	_vec3		m_vAngle;

	_matrix		WorldMatrix;

public:
	static		Transform* Create(LPDIRECT3DDEVICE9 _GRPDEV);
	virtual		Component* Clone();

private:
	virtual		VOID	Free();
};

END