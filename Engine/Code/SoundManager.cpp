#include "SoundManager.h"

IMPLEMENT_SINGLETON(SoundManager)

SoundManager::SoundManager()  {			}
SoundManager::~SoundManager() { Free(); }

HRESULT SoundManager::Ready_SoundManager() {
	System_Create(&SoundSystem);
	SoundSystem->init(32, FMOD_INIT_NORMAL, NULL);

	return S_OK;
}
VOID SoundManager::Update_SoundManager() {

}
HRESULT SoundManager::Play_Sound(const TCHAR* _FilePath, CHANNELID _SoundChannel) {
	Sound* SoundObject = nullptr;

	string RootPath = "../../Sound/";
	wstring strUni = _FilePath;

	int len = WideCharToMultiByte(CP_ACP, 0, &strUni[0], -1, NULL, 0, NULL, NULL);
	string strMulti(len, 0);
	WideCharToMultiByte(CP_ACP, 0, &strUni[0], -1, &strMulti[0], len, NULL, NULL);
	RootPath += strMulti;

	auto iter = find_if(SoundMap.begin(), SoundMap.end(), CTag_Finder(_FilePath));

	if (iter == SoundMap.end()) {
		SoundSystem->createStream(RootPath.c_str(), FMOD_LOOP_NORMAL | FMOD_2D | FMOD_IGNORETAGS, nullptr, &SoundObject);
		SoundMap.insert({ _FilePath, SoundObject });
		SoundSystem->playSound(SoundObject, NULL, FALSE, &SoundChannel[(LONG)_SoundChannel]);
	}
	else {
		SoundSystem->playSound(iter->second, NULL, FALSE, &SoundChannel[(LONG)_SoundChannel]);
	}
	return S_OK;
}
HRESULT SoundManager::Stop_Sound(CHANNELID _SoundChannel) {
	SoundChannel[(LONG)_SoundChannel]->stop();
	return S_OK;
}
HRESULT SoundManager::Stop_AllSound() {
	for (INT ID = 0; ID < (LONG)CHANNELID::SOUND_END; ++ID) {
		SoundChannel[(LONG)ID]->stop();
	}
	return S_OK;
}
HRESULT SoundManager::IsPlaying(CHANNELID _SoundChannel) {
	bool PlayingCheck = FALSE;
	SoundChannel[(LONG)_SoundChannel]->isPlaying(&PlayingCheck);
	return PlayingCheck;
}
VOID SoundManager::Free() {
	for (auto& Sound : SoundMap) {
		Sound.second->release();
	}
	SoundMap.clear();
	SoundSystem->release();
	SoundSystem->close();
}