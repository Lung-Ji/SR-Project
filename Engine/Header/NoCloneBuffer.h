#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL NoCloneBuffer : public Component {
private:
	explicit NoCloneBuffer();
	explicit NoCloneBuffer(LPDIRECT3DDEVICE9 _GRPDEV);
	explicit NoCloneBuffer(CONST NoCloneBuffer& _RHS);
	virtual ~NoCloneBuffer();

public:
	virtual		HRESULT	Ready_Buffer(FLOAT& X1 , FLOAT& X2 , FLOAT& Y1 , FLOAT& Y2 );
	virtual		VOID	Render_Buffer();

	_vec3* Get_BufferPos(_int iArray) { return		&pVBufferPos[iArray]; } //버퍼 pos 가져오기
public:
	HRESULT		Ready_Tile_Buffer(FLOAT& X1, FLOAT& X2 , FLOAT& Y1 , FLOAT& Y2 ); // 타일 추가 윗면 비교용
protected:
	LPDIRECT3DVERTEXBUFFER9		VertexBuffer;
	LPDIRECT3DINDEXBUFFER9		IndexBuffer;

	ULONG						VertexSize;
	ULONG						VertexCount;
	ULONG						VertexFormat;
	ULONG						TRICount;

	ULONG						IndexSize;
	D3DFORMAT					IndexFormat;


	_vec3* pVBufferPos; //버퍼 인덱스 담는 용도
public:
	static		NoCloneBuffer* Create(LPDIRECT3DDEVICE9 _GRPDEV, FLOAT& X1 , FLOAT& X2 , FLOAT& Y1 , FLOAT& Y2 );
	virtual		Component* Clone() { return nullptr; }
	
protected:
	virtual		void	Free();
};

END