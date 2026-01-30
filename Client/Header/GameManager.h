#pragma once

class GameManager : public Base {
private:
	explicit GameManager();
	virtual ~GameManager();

public:
	HRESULT		Ready_GameManager();
	VOID		Update_GameManager(CONST FLOAT& _DT);
	VOID		LateUpdate_GameManager(CONST FLOAT& _DT);
	VOID		Render_GameManager();

public:
	HRESULT		Ready_DefaultSetting();
	HRESULT		Ready_SceneSetting();

	GraphicDevice*		Get_DeviceClass()	{ return DEVCLASS;	}
	LPDIRECT3DDEVICE9	Get_GraphicDevice() { return GRPDEV;	}
private:
	GraphicDevice*				DEVCLASS;
	LPDIRECT3DDEVICE9			GRPDEV;

public:
	static	GameManager*		Create();
	virtual	VOID				Free();
};