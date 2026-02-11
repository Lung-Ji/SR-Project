#include "NoCloneBuffer.h"

NoCloneBuffer::NoCloneBuffer() : VertexBuffer(nullptr), IndexBuffer(nullptr), pVBufferPos(nullptr), VertexSize(0), VertexCount(0), VertexFormat(0), TRICount(0), IndexSize(0) {}
NoCloneBuffer::NoCloneBuffer(LPDIRECT3DDEVICE9 _GRPDEV) : Component(_GRPDEV),
VertexBuffer(nullptr), IndexBuffer(nullptr), pVBufferPos(nullptr), VertexSize(0), VertexCount(0), VertexFormat(0), TRICount(0), IndexSize(0) {
}
NoCloneBuffer::NoCloneBuffer(const NoCloneBuffer& _RHS) : Component(_RHS),
VertexBuffer(_RHS.VertexBuffer), IndexBuffer(_RHS.IndexBuffer), VertexSize(_RHS.VertexSize), VertexCount(_RHS.VertexCount),
VertexFormat(_RHS.VertexFormat), TRICount(_RHS.TRICount), IndexSize(_RHS.IndexSize), pVBufferPos(_RHS.pVBufferPos) {
	VertexBuffer->AddRef(); IndexBuffer->AddRef();
}
NoCloneBuffer::~NoCloneBuffer() {}


HRESULT NoCloneBuffer::Ready_Buffer(FLOAT& X1 , FLOAT& X2 , FLOAT& Y1 , FLOAT& Y2 )
{
	if (FAILED(Ready_Tile_Buffer(X1, X2,Y1,Y2)))
	{
		MSG_BOX("Small Tile Failed");
		return E_FAIL;
	}
	return S_OK;
}

VOID	NoCloneBuffer::Render_Buffer() {
	GRPDEV->SetStreamSource(0, VertexBuffer, 0, VertexSize);
	GRPDEV->SetFVF(VertexFormat);

	GRPDEV->SetIndices(IndexBuffer);
	GRPDEV->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, VertexCount, 0, TRICount);
}

HRESULT NoCloneBuffer::Ready_Tile_Buffer(FLOAT& X1, FLOAT& X2, FLOAT& Y1, FLOAT& Y2)
{
	VertexSize = sizeof(VTXCUBE);
	VertexCount = 4;
	TRICount = 2;
	VertexFormat = FVF_CUBE;

	IndexSize = sizeof(INDEX32);
	IndexFormat = D3DFMT_INDEX32;

	VTXCUBE* Vertex = NULL;
	if (FAILED(GRPDEV->CreateVertexBuffer(VertexSize * VertexCount, 0, VertexFormat, D3DPOOL_MANAGED, &VertexBuffer, NULL)))	return E_FAIL;
	if (FAILED(GRPDEV->CreateIndexBuffer(IndexSize * TRICount, 0, IndexFormat, D3DPOOL_MANAGED, &IndexBuffer, NULL)))			return E_FAIL;
	VertexBuffer->Lock(0, 0, (void**)&Vertex, 0);

	Vertex[0].vPosition = { -1.f, 0.f, 1.f };
	Vertex[0].dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Vertex[0].vTexUV = { X1,Y1 };

	Vertex[1].vPosition = { 1.f, 0.f, 1.f };
	Vertex[1].dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Vertex[1].vTexUV = { X2,Y1 };


	Vertex[2].vPosition = { 1.f, 0.f, -1.f };
	Vertex[2].dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Vertex[2].vTexUV = { X2,Y2 };

	Vertex[3].vPosition = { -1.f, 0.f, -1.f };
	Vertex[3].dwColor = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	Vertex[0].vTexUV = { X1,Y2 };

	VertexBuffer->Unlock();

	INDEX32* Index = nullptr;

	IndexBuffer->Lock(0, 0, (void**)&Index, 0);

	Index[0]._0 = 0;
	Index[0]._1 = 1;
	Index[0]._2 = 2;

	Index[1]._0 = 0;
	Index[1]._1 = 2;
	Index[1]._2 = 3;

	IndexBuffer->Unlock();
	return S_OK;
}

NoCloneBuffer* NoCloneBuffer::Create(LPDIRECT3DDEVICE9 _GRPDEV, FLOAT& X1 , FLOAT& X2 , FLOAT& Y1 , FLOAT& Y2 ) {
	NoCloneBuffer* BUF = new NoCloneBuffer(_GRPDEV);

	if (FAILED(BUF->Ready_Buffer(X1,X2,Y1,Y2))) {
		MSG_BOX("Cannot Create NoCloneBuffer.");
		Safe_Release(BUF);
		return nullptr;
	}
	return BUF;
}

VOID		NoCloneBuffer::Free() {

	Safe_Release(VertexBuffer);
	Safe_Release(IndexBuffer);

	Component::Free();
}