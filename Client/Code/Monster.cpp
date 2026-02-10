#include "../Include/PCH.h"

GameObject* Monster::Set_Target(const TCHAR* _TAG, GameObject* GameObj)
{
	GameObj = SceneManager::GetInstance()->Get_GameObject(_TAG);
	return GameObj;
}

D3DSURFACE_DESC Monster::Get_SurfaceDesc(LPDIRECT3DTEXTURE9 pTexture)
{
	return D3DSURFACE_DESC();
}

IDirect3DTexture9* Monster::Find_CurrTexture(const TCHAR* _FileName, IDirect3DTexture9* pTexture)
{
	pTexture = ResourceManager::GetInstance()->Find_Texture(_FileName);
	return pTexture;
}

size_t Monster::Set_TextureList(const TCHAR* __FileName, vector<IDirect3DTexture9*>* __Textures)
{

	size_t Frame = __Textures->size();

	if (Frame > 0) return Frame;

	while (++Frame)
	{
		IDirect3DTexture9* pTexture = nullptr;
		TCHAR Filename[256] = L"";
		swprintf_s(Filename, 256, L"%s_%02d.png", __FileName,  Frame);
		pTexture = ResourceManager::GetInstance()->Find_Texture(Filename);
		if (nullptr == pTexture) return --Frame;
		else __Textures->push_back(pTexture);
	}
}