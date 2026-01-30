#include "../Include/PCH.h"
#include "GUIManager.h"

IMPLEMENT_SINGLETON(GUIManager)

GUIManager::GUIManager()  {};
GUIManager::~GUIManager()	{};

VOID GUIManager::Ready_GUIManager() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    Setting_DarkTheme();

    GRPDEV = GraphicDevice::GetInstance()->Get_Device();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableSetMousePos 
                        | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

    ImGuiStyle& Style = ImGui::GetStyle();
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        Style.WindowRounding = 0.f;
        Style.Colors[ImGuiCol_WindowBg].w = 1.f;
    }

    if (!ImGui_ImplDX9_Init(GRPDEV)) {
        MSG_BOX("Cannot Initialize IMGUI.");
        return;
    }
    if (!ImGui_ImplWin32_Init(GRPDEV)) {
        MSG_BOX("Cannot Initialize IMGUI.");
        return;
    }

    Camera = SceneManager::GetInstance()->Get_CurrentScene()->
        Get_GameObject(LAYER_TYPE::LAYER_DYNAMIC_OBJECT, GAMEOBJECT_TYPE::OBJECT_CAMERA);
   
}
VOID GUIManager::Update_GUIManager() {
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

}
VOID GUIManager::LateUpdate_GUIManager() {
    
}
VOID GUIManager::Render_GUIManager() {
    
    // 카메라 세팅
    {
        ImGui::Begin("Camera Setting");
        ImGui::Text("Transform");

        _vec3* EyeVec = dynamic_cast<CameraObject*>(Camera)->Get_EyeVec();
        FLOAT EYEVEC[3] = { EyeVec->x, EyeVec->y, EyeVec->z };
        ImGui::InputFloat3("Eye", EYEVEC);
        dynamic_cast<CameraObject*>(Camera)->Set_EyeVec({ EYEVEC[0], EYEVEC[1] , EYEVEC[2] });

        _vec3* AtVec = dynamic_cast<CameraObject*>(Camera)->Get_AtVec();
        FLOAT ATVEC[3] = { AtVec->x, AtVec->y, AtVec->z };
        ImGui::InputFloat3("At", ATVEC);
        //dynamic_cast<CameraObject*>(Camera)->Set_EyeVec({ ATVEC[0], ATVEC[1] , ATVEC[2] });

        FLOAT Speed = *dynamic_cast<CameraObject*>(Camera)->Get_Speed();
        ImGui::InputFloat("CamSpeed", &Speed);
        dynamic_cast<CameraObject*>(Camera)->Set_Speed(Speed);

        ImGui::Separator();

        ImGui::SliderFloat("FOV", dynamic_cast<CameraObject*>(Camera)->Get_FOV(), D3DXToRadian(30.f), D3DXToRadian(90.f));
        ImGui::SameLine();
        ImGui::Button("Reset") ? dynamic_cast<CameraObject*>(Camera)->Set_FOV(D3DXToRadian(60.f)) : FALSE;
        ImGui::Separator();

        ImGui::End();
    }
   
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

VOID GUIManager::Release_GUIManager() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

VOID GUIManager::Setting_DarkTheme() {
    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

    // Headers
    colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
    colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
}


