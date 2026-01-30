#pragma once
#include "EditorWindow.h"
#include <filesystem>
class EditorManager	{
	DECLARE_SINGLETON(EditorManager)
private:
	EditorManager();
public:
	enum STATE { DISABLE, ACTIVE, DESTROYED };

	static void	Initialize();
	static void	Update();
	static void	Render();
	static void	Release();

private:
	static void	IMGUIInitialize();
	static void	IMGUIRender();
	static void	DockSpaceUpdate();
	static void	DockSpaceRender();

	static void OpenProject();
	static void NewScene();
	static void SaveScene();
	static void SaveSceneAs();
	//static void OpenScene(const filesystem::path& path);

	static D3DXVECTOR2 ViewportBounds[2];
	static D3DXVECTOR2 ViewportSize;
	static bool ViewportFocused;
	static bool ViewportHovered;
	
	static void	UpdatePlatform();
	static void	DarkTheme();

	template <typename T>
	T* GetWindow(const wstring& name)
	{
		auto iter = EditorWindows.find(name);
		if (iter == EditorWindows.end())
			return nullptr;

		return dynamic_cast<T*>(iter->second);
	}

private:
	static ImGuiWindowFlags		Flags;
	static ImGuiDockNodeFlags	DockspaceFlags;
	static STATE				State;
	static bool					FullScreen;
	static bool					Padding;
	FLOAT EyeX[3] = { 0.f, 0.f, 0.f }, EyeY[3] = { 0.f, 0.f, 0.f }, EyeZ[3] = { 0.f, 0.f, 0.f };
	static map<wstring, EditorWindow*> EditorWindows;
};

