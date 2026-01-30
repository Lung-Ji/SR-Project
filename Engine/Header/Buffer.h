#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL Buffer : public Component {
private:
	explicit Buffer();
	explicit Buffer(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit Buffer(CONST Buffer& _RHS);
	virtual ~Buffer();

public:
	virtual		HRESULT	Ready_Buffer(BUFFER_TYPE _TYPE);
	virtual		VOID	Render_Buffer();

public:
	HRESULT		Ready_Triangle_Buffer();
	HRESULT		Ready_Rectangle_Buffer();
	HRESULT		Ready_Texture_Buffer();
	HRESULT		Ready_Terrain_Buffer();

protected:
	LPDIRECT3DVERTEXBUFFER9		VertexBuffer;
	LPDIRECT3DINDEXBUFFER9		IndexBuffer;

	ULONG						VertexSize;
	ULONG						VertexCount;
	ULONG						VertexFormat;
	ULONG						TRICount;

	ULONG						IndexSize;
	D3DFORMAT					IndexFormat;

public:
	static		Buffer* Create(LPDIRECT3DDEVICE9 _GRPDEV, BUFFER_TYPE _TYPE);
	virtual		Component* Clone();

protected:
	virtual		void	Free();
};

END