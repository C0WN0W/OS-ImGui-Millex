#include "OS-ImGui_Base.h"
#include "imgui/font.h"
#include "imgui/image.h"

namespace texture {
    ID3D11ShaderResourceView* preview_slow = nullptr;
}

namespace font {
    ImFont* icomoon_logo = nullptr;
    ImFont* icomoon_page = nullptr;
    ImFont* inter_semibold = nullptr;
    ImFont* icon_notify = nullptr;
}

namespace OSImGui
{
    bool OSImGui_Base::InitImGui(ID3D11Device* device, ID3D11DeviceContext* device_context)
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImFontConfig cfg = {};

        cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;
        font::inter_semibold = io.Fonts->AddFontFromMemoryTTF(Fonts::inter_semibold, sizeof(Fonts::inter_semibold), 15.f, &cfg, io.Fonts->GetGlyphRangesChineseFull());
        font::icomoon_page = io.Fonts->AddFontFromMemoryTTF(Fonts::icomoon_page, sizeof(Fonts::icomoon_page), 17.f, &cfg, io.Fonts->GetGlyphRangesChineseFull());
        font::icomoon_logo = io.Fonts->AddFontFromMemoryTTF(Fonts::icomoon_page, sizeof(Fonts::icomoon_page), 30.f, &cfg, io.Fonts->GetGlyphRangesChineseFull());
        font::icon_notify = io.Fonts->AddFontFromMemoryTTF(Fonts::icon_notify, sizeof(Fonts::icon_notify), 17.f, &cfg, io.Fonts->GetGlyphRangesChineseFull());

        ImGui::StyleColorsDark();

        D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
        if (texture::preview_slow == nullptr)
            D3DX11CreateShaderResourceViewFromMemory(device, preview_slow, sizeof(preview_slow), &info, pump, &texture::preview_slow, 0);
        
        io.LogFilename = nullptr;

        if (!ImGui_ImplWin32_Init(Window.hWnd))
            throw OSException("ImGui_ImplWin32_Init() call failed.");
        if (!ImGui_ImplDX11_Init(device, device_context))
            throw OSException("ImGui_ImplDX11_Init() call failed.");

        return true;
    }

    void OSImGui_Base::CleanImGui()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        if(g_Device.g_pd3dDevice)
            g_Device.CleanupDeviceD3D();

        // Only destroy window in external mode.
        if (Window.hWnd && !Window.Name.empty())
        {
            DestroyWindow(Window.hWnd);
            UnregisterClassA(Window.ClassName.c_str(), Window.hInstance);
        }
    }

    std::wstring OSImGui_Base::StringToWstring(std::string& str)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        return converter.from_bytes(str);
    }

}