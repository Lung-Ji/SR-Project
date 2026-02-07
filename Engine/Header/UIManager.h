#pragma once

#include "Component.h"
#include "GameObject.h"
#include "UISprite.h"

BEGIN(Engine)

//삽입 삭제가 활발히 이루어지는 특수한 UI들만 적용되는 enum
enum UIType {
	Inventory,
	Object,
	Settings
};

class ENGINE_DLL UIManager : public Component {
	DECLARE_SINGLETON(UIManager)

private:
	explicit UIManager();
	virtual ~UIManager();

public:
	HRESULT Ready_UIObject(UIManager* _Component_Sprite );
	
public:
	HRESULT		Ready_UI();
	INT				Update_UI();
	VOID			Delete_UI(CONST TCHAR* _uiName);
	VOID			Render_UI(UIType _uitype, CONST TCHAR* _UINAME);

	HRESULT		Import_UISprite(UIType _uitype, CONST TCHAR* _PATH, UINT _WIDTH,
		UINT _HEIGHT, FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY);

public:
	static  UIManager* Create(LPDIRECT3DDEVICE9 _GRPDEV,CONST TCHAR* _uiName,CONST TCHAR* _PATH, UINT _WIDTH, UINT _HEIGHT,
  FLOAT _POSX, FLOAT _POSY, BOOL _VIS, INT _OPACITY);

	BOOL		isActive;

private: 
	ID3DXSprite* Sprite;

	map<UIType, map<CONST _tchar*, SpriteINFO>> UIList;
	//map<const _tchar*,SpriteINFO>UIList;
	vector<pair<UIType,vector<SpriteINFO>>> vecList;
private:
	virtual VOID Free();

};

END