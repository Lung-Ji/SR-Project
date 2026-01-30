#include "Transform.h"

Transform::Transform()		
    : m_vScale(1.f, 1.f, 1.f), m_vAngle(0.f, 0.f, 0.f)
{
    ZeroMemory(m_vInfo, sizeof(_vec3) * INFO_END);
    D3DXMatrixIdentity(&WorldMatrix);
}
Transform::Transform(LPDIRECT3DDEVICE9 _GRPDEV)
    : Component(_GRPDEV), m_vScale(1.f, 1.f, 1.f), m_vAngle(0.f, 0.f, 0.f)
{
    ZeroMemory(m_vInfo, sizeof(_vec3) * INFO_END);
    D3DXMatrixIdentity(&WorldMatrix);
}
Transform::Transform(const Transform& _RHS)
    :Component(_RHS), m_vScale(_RHS.m_vScale), m_vAngle(_RHS.m_vAngle)
{
    for (_uint i = 0; i < INFO_END; ++i) {
        m_vInfo[i] = _RHS.m_vInfo[i];
    }
    WorldMatrix = _RHS.WorldMatrix;
}
Transform::~Transform()													{}
HRESULT Transform::Ready_Component() {
	D3DXMatrixIdentity(&WorldMatrix);

	for (_uint i = 0; i < INFO_END; ++i) {
		memcpy(&m_vInfo[i], &WorldMatrix.m[i][0], sizeof(_vec3));
	}


	return S_OK;
}
INT			Transform::Update_Component(CONST FLOAT& _DT){
    D3DXMatrixIdentity(&WorldMatrix);

    // 크기 변환

    for (_uint i = 0; i < INFO_POS; ++i)
    {
        memcpy(&m_vInfo[i], &WorldMatrix.m[i][0], sizeof(_vec3));
    }

    for (_uint i = 0; i < INFO_POS; ++i)
    {
        D3DXVec3Normalize(&m_vInfo[i], &m_vInfo[i]);
        m_vInfo[i] *= *(((_float*)&m_vScale) + i);
    }

    // 회전 변환
    _matrix matRot[ROT_END];

    D3DXMatrixRotationX(&matRot[ROT_X], D3DXToRadian(m_vAngle.x));
    D3DXMatrixRotationY(&matRot[ROT_Y], D3DXToRadian(m_vAngle.y));
    D3DXMatrixRotationZ(&matRot[ROT_Z], D3DXToRadian(m_vAngle.z));

    for (_uint i = 0; i < INFO_POS; ++i)
    {
        for (_uint j = 0; j < ROT_END; ++j)
        {
            D3DXVec3TransformNormal(&m_vInfo[i], &m_vInfo[i], &matRot[j]);
        }
    }

    // 월드 행렬 구성

    for (_uint i = 0; i < INFO_END; ++i)
    {
        memcpy(&WorldMatrix.m[i][0], &m_vInfo[i], sizeof(_vec3));
    }


    return 0;
}
VOID		Transform::LateUpdate_Component(CONST FLOAT& _DT) {


}
Transform*	Transform::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Transform* TRF = new Transform(_GRPDEV);
	if (FAILED(TRF->Ready_Component())) {
		MSG_BOX("Cannot Create Transform.");
		Safe_Release(TRF);
		return nullptr;
	}
	return TRF;
}
Component*	Transform::Clone() {
	return new Transform(*this);
}
VOID		Transform::Free() {
	Component::Free();
}