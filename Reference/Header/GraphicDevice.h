#pragma once

#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class ENGINE_DLL GraphicDevice : public Base {
	DECLARE_SINGLETON(GraphicDevice)
private:
	explicit GraphicDevice();
	virtual ~GraphicDevice();

public:
	HRESULT		Ready_GraphicDevice(HWND _hWnd, WINMODE _MODE, CONST UINT& _SX, CONST UINT& _SY, GraphicDevice** _GRPD);

	void		Render_Begin(D3DXCOLOR _CLR);
	void		Render_End();

public:
	LPDIRECT3DDEVICE9	Get_Device()		{	return GRPDEV;		}
	IDirect3DSurface9*	Get_TempSurface()	{	return TempSurface;	}

private:
	IDirect3DSurface9* BackSurface, *TempSurface;
	LPDIRECT3D9			SDK;
	LPDIRECT3DDEVICE9	GRPDEV;

private:
	virtual void		Free();
};

END