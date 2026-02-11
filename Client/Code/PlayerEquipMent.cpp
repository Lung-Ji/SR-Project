#include "../Include/PCH.h"
#include "PlayerEquipMent.h"

PlayerEquipMent::PlayerEquipMent(LPDIRECT3DDEVICE9 _GRPDEV):GameObject(_GRPDEV) {}
PlayerEquipMent::PlayerEquipMent(const GameObject& _rhs):GameObject(_rhs){}
PlayerEquipMent::PlayerEquipMent(LPDIRECT3DDEVICE9 _GRPDEV, const TCHAR* _TAG)
:GameObject(_GRPDEV,_TAG){}
PlayerEquipMent::~PlayerEquipMent(){}


HRESULT PlayerEquipMent::Ready_GameObject()
{
  if (FAILED(Component_Initialize())) return E_FAIL;

  return S_OK;
}

INT			PlayerEquipMent::Update_GameObject(CONST FLOAT& _DT) {
  GameObject::Update_GameObject(_DT);
  RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);
  
  return S_OK;
}
VOID		PlayerEquipMent::LateUpdate_GameObject(CONST FLOAT& _DT) {
}
VOID		PlayerEquipMent::Render_GameObject() {
  UIManager::GetInstance()->Render_UI(GRPDEV, Inventory);
}
//HRESULT PlayerEquipMent::Component_Initialize() {
//  //UIManager::GetInstance()->Import_UISprite(GRPDEV, Inventory, L"../../UI/MainUI/WeaponBG_Arrow.png", 100.f, 100.f, 410.f, 250.f, TRUE, 255);
//
//}
PlayerEquipMent* PlayerEquipMent::Create(LPDIRECT3DDEVICE9 _GRPDEV)
{
  PlayerEquipMent* PEM = new PlayerEquipMent(_GRPDEV);
  if (FAILED(PEM->Ready_GameObject())) {
    MSG_BOX("Cannot Create MainMenu.");
    Safe_Release(PEM);
    return nullptr;
  }
}

VOID PlayerEquipMent::Free() {
  GameObject::Free();
}