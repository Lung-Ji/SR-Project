#pragma once

#include "Base.h"
#include "Engine_Define.h"
#include <fmod.hpp>
#include <fmod.h>
#include <fmod_errors.h>

using namespace FMOD;

BEGIN(Engine)
class ENGINE_DLL SoundManager : public Base {
	DECLARE_SINGLETON(SoundManager)
private:
	explicit SoundManager();
	virtual ~SoundManager();

public:
	HRESULT		Ready_SoundManager();
	VOID		Update_SoundManager();

	HRESULT		Play_Sound(CONST TCHAR* _FilePath, CHANNELID _SoundChannel);
	HRESULT		Stop_Sound(CHANNELID _SoundChannel);
	HRESULT		Stop_AllSound();
	HRESULT		IsPlaying(CHANNELID _SoundChannel);

private:
	System*	SoundSystem;

	map<CONST TCHAR*, Sound*>	SoundMap;
	
	Channel* SoundChannel[(LONG)CHANNELID::SOUND_END];

private:
	virtual VOID	Free();
};

END