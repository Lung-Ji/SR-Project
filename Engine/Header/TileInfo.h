#pragma once
#include "Component.h"
#include "Engine_Define.h"

class TileInfo :
    public Component
{
private:
    explicit TileInfo();
    explicit TileInfo(LPDIRECT3DDEVICE9 _GRPDEV);
    explicit TileInfo(const TileInfo& ths);
    virtual ~TileInfo();

public:

    virtual HRESULT		        Ready_Component();
    virtual INT			        Update_Component(CONST FLOAT& _DT);
    virtual VOID		        LateUpdate_Component(CONST FLOAT& _DT);
  
    //이건.. 지형이 가지고 있는 타일의 인덱스 정보를 담기위함 해당 인덱스가 가진 위치위에 이 타일이 놓여있다는걸 확인하기 위해서
    void            Set_TileId(TILE_SIDE eid) { m_eTileSide = eid; }
    void            Set_TileNumber(_int iTileNumber) { m_iTileNumber = iTileNumber; }
    void            Set_TileAll(const _tchar* pPath, const _tchar* pName, Engine::TILE_SIDE eId, TILE_STATE eState, TILEMODE_CHANGE eMode, _int iTileNumber = 0)
    {
        m_pPathName = pPath;
        m_pTileName = pName;
        m_eTileSide = eId;
        m_eTileState = eState;
        m_eTileMode = eMode;
        m_iTileNumber = iTileNumber;

    }
    void            Set_TileAnimaiton(const _tchar* pName, _int iCnt, Engine::TILE_SIDE eId, TILE_STATE eState, TILEMODE_CHANGE eMode, _int iTileNumber = 0)
    {
        m_iTextureCount = iCnt;
        m_pAnimationName = pName;
        m_eTileSide = eId;
        m_eTileState = eState;
        m_eTileMode = eMode;
        m_iTileNumber = iTileNumber;

        for (int i = 0; i < iCnt; ++i)
        {
            TCHAR   Name[128] = L"";
            wsprintf(Name, pName, i);
            m_vecAnimationName.push_back(Name);

        }
    
    }
    void            Set_TileState(TILE_STATE eid) { m_eTileState = eid; }

    void            Set_Texture(_uint& index)
    {
            
    }

    _int                   Get_TileNumber()      { return m_iTileNumber;}
    TILE_SIDE              Get_TileSideName()    { return m_eTileSide;  }
    TILE_STATE             Get_TileStateName()   { return m_eTileState; }
    TILEMODE_CHANGE        Get_TileMode()        { return m_eTileMode;  }
    _int                   Get_TileTextureNumber() { return m_iTextureCount; }
    const _tchar*          Get_TileTextureName() { return m_pTileName;  }
    const _tchar*          Get_TilePathName()    { return m_pPathName;  }
    const _tchar*          Get_AnimationName(_uint iCnt) { return m_vecAnimationName[iCnt].c_str(); }
    
private:
    TILE_SIDE              m_eTileSide;
    TILE_STATE             m_eTileState;
    TILEMODE_CHANGE        m_eTileMode;

    const  _tchar*         m_pTileName;
    const  _tchar*         m_pPathName;
    const  _tchar*         m_pAnimationName;

    vector<wstring>  m_vecAnimationName;
private:
    _int                   m_iTileNumber;
    _int                   m_iTextureCount;
public:
    static          TileInfo* Create(LPDIRECT3DDEVICE9 pGraphicDev);
    virtual		    Component* Clone();

private:
    virtual  void            Free();

};

