#include "../Include/PCH.h"
#include "Arrow.h"

Arrow::Arrow(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Arrow::Arrow(const GameObject& _RHS) : GameObject(_RHS) {}
Arrow::~Arrow() {}

HRESULT Arrow::Ready_GameObject()
{
    if (FAILED(Component_Initialize())) return E_FAIL;

    _type = ArrowType::IceArrow_LV1;

    return S_OK;
}

INT Arrow::Update_GameObject(const _float& _DT)
{
    GameObject::Update_GameObject(_DT);
    RenderManager::GetInstance()->Add_RenderGroup(RENDER_ALPHA, this);

    return S_OK;
}

VOID Arrow::LateUpdate_GameObject(const _float& _DT)
{
    GameObject::LateUpdate_GameObject(_DT);
}

VOID Arrow::Render_GameObject()
{
    GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    GRPDEV->SetTransform(D3DTS_WORLD, Component_Transform->Get_World());

    SetGrahpic();

    Component_Buffer->Render_Buffer();

    GRPDEV->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

    return VOID();
}

HRESULT Arrow::Component_Initialize()
{
    Component_Buffer = ADD_COMPONENT_RECTTEX;
    Component_Transform = ADD_COMPONENT_TRANSFORM;
    Component_Texture = ADD_COMPONENT_TEXTURE;

    return S_OK;
}

void Arrow::SetGrahpic()
{
    //TCHAR FileName[128] = L"";

    switch (_type) {
    case ArrowType::IceArrow_LV1:
        GRPDEV->SetTexture(0, ResourceManager::GetInstance()->Find_Texture(L"IceArrow_LV1_1.png"));
        break;

    default:
        GRPDEV->SetTexture(0, ResourceManager::GetInstance()->Find_Texture(L"IceArrow_LV1_1.png"));
        break;
    }
    
    //Component_Texture->Set_Texture(FileName);
}

Arrow* Arrow::Create(LPDIRECT3DDEVICE9 _GRPDEV)
{
    Arrow* arrow = new Arrow(_GRPDEV);
    if (FAILED(arrow->Ready_GameObject())) {
        MSG_BOX("Cannot Create arrow.");
        Safe_Release(arrow);
        return nullptr;
    }
    return arrow;
}

VOID Arrow::Free()
{
    GameObject::Free();
}
