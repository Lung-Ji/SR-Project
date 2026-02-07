#include "../Include/PCH.h"
#include "MapScene.h"

MapScene::MapScene(LPDIRECT3DDEVICE9 _GRPDEV) : Scene(_GRPDEV) {}
MapScene::~MapScene() {}
HRESULT	MapScene::Ready_Scene() {
	Scene::Ready_Scene();

	ProtoManager::GetInstance()->Ready_Prototype(GRPDEV);

	ResourceManager::GetInstance()->GlobalImport_Texture(GRPDEV, L"../../Tile/Stage1");
	ResourceManager::GetInstance()->GlobalImport_Texture(GRPDEV, L"../../Tile/AnimationObject");
	Ready_GameLogic_Layer(L"GameLogic_Layer");
	KeyManager::GetInstance()->Ready_KeyManager(hInst, hWnd);
	return S_OK;
}
INT	 MapScene::Update_Scene(CONST FLOAT& _DT) {
	TileManager::GetInstance()->Update_TileList(_DT);
	return Scene::Update_Scene(_DT);
}
VOID MapScene::LateUpdate_Scene(CONST FLOAT& _DT) {
	Scene::LateUpdate_Scene(_DT);
}
VOID MapScene::Render_Scene() {
	//Scene::Render_Scene();
}
HRESULT MapScene::Ready_Enviroment_Layer(CONST TCHAR* _LTAG) {
	Layer* LYR = Layer::Create();
	if (nullptr == LYR) return E_FAIL;

	GameObject* GOBJ = nullptr;

	LayerList.push_back(LYR);

	return S_OK;
}
HRESULT MapScene::Ready_GameLogic_Layer(CONST TCHAR* _LTAG) {
	
	
	Add_GameObjectToScene<CameraObject>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_CAMERA, L"Camera");
	Add_GameObjectToScene<Player>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_MONSTER, L"Player");

	Add_GameObjectToScene<Terrain>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_TERRAIN, L"Terrain");
	Add_GameObjectToScene<Tile>(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_TERRAIN, L"Tile");


	return S_OK;
}
HRESULT MapScene::Ready_UserInterface_Layer(CONST TCHAR* _LTAG) {
	return S_OK;
}
MapScene* MapScene::Create(LPDIRECT3DDEVICE9 _GRPDEV) {
	MapScene* LS = new MapScene(_GRPDEV);
	SceneManager::GetInstance()->Set_CurrentScene(LS);
	if (FAILED(LS->Ready_Scene())) {
		MSG_BOX("Cannot Create MapScene.");
		Safe_Release(LS);
		return nullptr;
	}
	return LS;
}
void MapScene::Free() {
	Scene::Free();
}