#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)
struct ENGINE_DLL FontObject {
	_vec2		Position;
	wstring		Text;
	_int		TextScale;
	wstring		FontTag;
	wstring		FontType;
	BOOL		Visible;
	D3DCOLOR	TextColor;
	ID3DXFont*	DXFont;

	FontObject(_vec2 _Position, wstring _Text, _int _TextScale, wstring _FontTag, wstring _FontType, D3DCOLOR _Color, BOOL _Visible)
		: Position(_Position), Text(_Text), TextScale(_TextScale), FontTag(_FontTag), 
		FontType(_FontType), Visible(_Visible), TextColor(_Color), DXFont(nullptr){}

	VOID	Set_Text(wstring _TXT)	{ Text = _TXT; }
	wstring	Get_Text()				{ return Text; }
};
class ENGINE_DLL FontManager : public Base {
  DECLARE_SINGLETON(FontManager)
private:
  explicit	FontManager();
  virtual	~FontManager();

public:
	HRESULT Ready_FontManager(LPDIRECT3DDEVICE9 _GRPDEV);
	INT		Update_FontManager(CONST FLOAT& _DT);
	VOID	LateUpdate_FontManager(CONST FLOAT& _DT);
	VOID	Render_FontManager();

	HRESULT	Add_FontSprite(LPDIRECT3DDEVICE9 _GRPDEV, wstring _Text, _vec2 _Position, _int _TextScale, wstring _FontTag, 
		wstring _FontType, D3DCOLOR _Color = D3DCOLOR_ARGB(255, 255, 255, 255), BOOL _Visible = TRUE);
private:
	
	ID3DXSprite*	DXSprite;

	map<CONST TCHAR*, FontObject*>	FontList;
private:
  virtual	VOID Free();
};

END

