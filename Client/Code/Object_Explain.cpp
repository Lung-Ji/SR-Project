#include "../Include/PCH.h"
#include "Object_Explain.h"

Object_Explain::Object_Explain(LPDIRECT3DDEVICE9 _GRPDEV) : GameObject(_GRPDEV) {}
Object_Explain::Object_Explain(CONST GameObject& _RHS) : GameObject(_RHS) {}
Object_Explain::~Object_Explain() {}

HRESULT	Object_Explain::Ready_GameObject() {
	if (FAILED(Component_Initialize())) return E_FAIL;
	return S_OK;

}
INT		Object_Explain::Update_GameObject(CONST FLOAT& _DT) {
	GameObject::Update_GameObject(_DT);
	RenderManager::GetInstance()->Add_RenderGroup(RENDER_UI, this);

	return 0;
}
VOID	Object_Explain::LateUpdate_GameObject(CONST FLOAT& _DT) {

}
VOID	Object_Explain::Render_GameObject() {

	//UIManager::GetInstance()->Render_UI(GRPDEV, Object);
}
HRESULT Object_Explain::Component_Initialize() {
	//UIManager::GetInstance()->Import_UISprite(
	//	GRPDEV, Object, L"../../UI/Inventory_UI/EquipMent_Status_Window.png", 300.f, 400.f, 200.f, 40.f, TRUE, 255.f);
	return S_OK;
}
Object_Explain* Object_Explain::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	Object_Explain* OE = new Object_Explain(_GRPDEV);
	if (FAILED(OE->Ready_GameObject())) {
		MSG_BOX("Cannot Create Object_Explain.");
		Safe_Release(OE);
		return nullptr;
	}
	return OE;
}
VOID	Object_Explain::Free() {
	GameObject::Free();
}