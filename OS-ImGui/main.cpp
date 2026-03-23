#define IMGUI_DEFINE_MATH_OPERATORS
#include <iostream>
#include "main.h"
#include "OS-ImGui.h"

void DrawCallBack()
{

	// static float color[4] = { 0.f, 1.f, 0.f, 1.f };
	// c::accent = { color[0], color[1], color[2], 1.f };

    ImGui::SetNextWindowSizeConstraints(ImVec2(c::bg::size.x, c::bg::size.y), ImGui::GetIO().DisplaySize);
    ImGui::Begin("M1LL3X", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
    {
        ImGuiStyle* style = &ImGui::GetStyle();

        const ImVec2& pos = ImGui::GetWindowPos();
        const ImVec2& region = ImGui::GetContentRegionMax();
        const ImVec2& spacing = style->ItemSpacing;

        style->WindowPadding = ImVec2(0, 0);
        style->ItemSpacing = ImVec2(20, 20);
        style->WindowBorderSize = 0;
        style->ScrollbarSize = 10.f;

        c::bg::background = ImLerp(c::bg::background, dark ? ImColor(15, 15, 15) : ImColor(255, 255, 255), ImGui::GetIO().DeltaTime * 12.f);
        c::separator = ImLerp(c::separator, dark ? ImColor(22, 23, 26) : ImColor(222, 228, 244), ImGui::GetIO().DeltaTime * 12.f);

        c::accent = ImLerp(c::accent, dark ? ImColor(118, 187, 117) : ImColor(121, 131, 207), ImGui::GetIO().DeltaTime * 12.f);

        c::elements::background_hovered = ImLerp(c::elements::background_hovered, dark ? ImColor(31, 33, 38) : ImColor(197, 207, 232), ImGui::GetIO().DeltaTime * 25.f);
        c::elements::background = ImLerp(c::elements::background, dark ? ImColor(22, 23, 25) : ImColor(222, 228, 244), ImGui::GetIO().DeltaTime * 25.f);

        c::checkbox::mark = ImLerp(c::checkbox::mark, dark ? ImColor(0, 0, 0) : ImColor(255, 255, 255), ImGui::GetIO().DeltaTime * 12.f);

        c::child::background = ImLerp(c::child::background, dark ? ImColor(17, 17, 18) : ImColor(241, 243, 249), ImGui::GetIO().DeltaTime * 12.f);
        c::child::cap = ImLerp(c::child::cap, dark ? ImColor(20, 21, 23) : ImColor(228, 235, 248), ImGui::GetIO().DeltaTime * 12.f);

        c::page::text_hov = ImLerp(c::page::text_hov, dark ? ImColor(68, 71, 85) : ImColor(136, 145, 176), ImGui::GetIO().DeltaTime * 12.f);
        c::page::text = ImLerp(c::page::text, dark ? ImColor(68, 71, 85) : ImColor(136, 145, 176), ImGui::GetIO().DeltaTime * 12.f);

        c::page::background_active = ImLerp(c::page::background_active, dark ? ImColor(31, 33, 38) : ImColor(196, 205, 228), ImGui::GetIO().DeltaTime * 25.f);
        c::page::background = ImLerp(c::page::background, dark ? ImColor(22, 23, 25) : ImColor(222, 228, 244), ImGui::GetIO().DeltaTime * 25.f);

        c::text::text_active = ImLerp(c::text::text_active, dark ? ImColor(255, 255, 255) : ImColor(0, 0, 0), ImGui::GetIO().DeltaTime * 12.f);
        c::text::text_hov = ImLerp(c::text::text_hov, dark ? ImColor(68, 71, 85) : ImColor(68, 71, 81), ImGui::GetIO().DeltaTime * 12.f);
        c::text::text = ImLerp(c::text::text, dark ? ImColor(68, 71, 85) : ImColor(68, 71, 81), ImGui::GetIO().DeltaTime * 12.f);

        ImGui::GetWindowDrawList()->AddRectFilled(pos, pos + ImVec2(region), ImGui::GetColorU32(c::bg::background), c::bg::rounding);
        ImGui::GetWindowDrawList()->AddRectFilled(pos + spacing, pos + ImVec2(region.x - spacing.x, 50 + spacing.y), ImGui::GetColorU32(c::child::background), c::child::rounding);
		ImGui::GetWindowDrawList()->AddText(pos + spacing * 2, GetColorU32(c::accent), "OS-IMGUI  Modified by Cownow");

        ImGui::GetWindowDrawList()->AddImage(texture::preview_slow, pos + ImVec2(region.x - (spacing.x + 89), spacing.y), pos + ImVec2(region.x - spacing.x, 50 + spacing.y), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(c::accent, 0.6f));


        //   PushFont(font::icomoon_logo);
        //   GetWindowDrawList()->AddText(pos + ImVec2(region.x - (spacing.x + CalcTextSize("m").x) - 14, 50 - (spacing.y + CalcTextSize("m").y) + 31), GetColorU32(c::accent, 1.f), "m");
        //   PopFont();
        //
        ImGui::SetCursorPos(ImVec2(spacing.x, (50 + (spacing.y * 2))));

        tab_alpha = ImClamp(tab_alpha + (4.f * ImGui::GetIO().DeltaTime * (page == active_tab ? 1.f : -1.f)), 0.f, 1.f);
        if (tab_alpha == 0.f && tab_add == 0.f) active_tab = page;

        ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style->Alpha);

        if (active_tab == 0)
        {

            custom::BeginGroup();
            {

                custom::Child("GENERAL", ImVec2((GetContentRegionMax().x - spacing.x * 3) / 2, (GetContentRegionMax().y - (60 + spacing.y * 2) * 2) + 10), true);
                {

                    static bool popup = false;
                    if (custom::CheckboxClicked("Checkbox true", &checkbox_on)) popup = !popup;

                    if (popup) {
                        ImGui::Begin("Popupbox", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBringToFrontOnFocus);
                        {
                            custom::Child("Popupbox", ImVec2(300, 170), ImGuiWindowFlags_NoBringToFrontOnFocus);
                            {
                                custom::ColorEdit4("Color Palette", col, picker_flags);

                                custom::Separator_line();

                                custom::Combo("Combobox", &select1, items, IM_ARRAYSIZE(items), 3);
                            }
                            custom::EndChild();
                        }
                        ImGui::End();
                    }

                    custom::Separator_line();

                    custom::Checkbox("Checkbox false", &checkbox_off);

                    custom::Separator_line();

                    custom::MultiCombo("Multi Combo", multi_num, multi_items, 5);

                    custom::Separator_line();

                    custom::SliderInt("Slider Integer", &slider_int, 1, 100, "%d%%");

                    custom::Separator_line();

                    custom::SliderFloat("Slider Float", &slider_float, 0.f, 5.f, "%.3f [FL]");

                    custom::Separator_line();

                    ImGui::InputTextWithHint("Text Field", "Hello Mate :/", field, 45, NULL);

                    SetCursorPosY(2000);

                }
                custom::EndChild();
            }
            custom::EndGroup();

            ImGui::SameLine();

            custom::BeginGroup();
            {
                custom::Child("SETTINGS", ImVec2((GetContentRegionMax().x - spacing.x * 3) / 2, ((GetContentRegionMax().y - (60 + spacing.y * 2) * 2) + 10) / 2 - 10), true);
                {
                    custom::ColorEdit4("Color Palette", col, picker_flags);

                    custom::Separator_line();

                    custom::Combo("Combobox", &select1, items, IM_ARRAYSIZE(items), 3);

                }
                custom::EndChild();

                custom::Child("OTHER", ImVec2((GetContentRegionMax().x - spacing.x * 3) / 2, ((GetContentRegionMax().y - (60 + spacing.y * 2) * 2) + 10) / 2 - 10), true);
                {

                    custom::KnobFloat("Dot Slider", &knob, -1.f, 1.f, "%.1f [F]");

                    custom::Separator_line();

                    custom::Keybind("Keybind", &key, &m);

                }
                custom::EndChild();

            }
            custom::EndGroup();

        }
        else if (active_tab == 1)
        {
            static bool checkboxes[10];

            custom::BeginGroup();
            {

                custom::Child("ESP", ImVec2((GetContentRegionMax().x - spacing.x * 3) / 2, (GetContentRegionMax().y - (60 + spacing.y * 2) * 2) + 10), true);
                {

                    custom::Checkbox("Enable ESP", &checkboxes[0]);

                    custom::Separator_line();

                    custom::Checkbox("Through Walls", &checkboxes[1]);

                    custom::Separator_line();

                    custom::Combo("Bullet Tracer", &bullet_select, bullet, IM_ARRAYSIZE(bullet), 2);

                    custom::Separator_line();

                    custom::Checkbox("Dynamic Boxes", &checkboxes[2]);

                    custom::Separator_line();

                    custom::Checkbox("Dormant", &checkboxes[3]);

                    custom::Separator_line();

                    custom::Checkbox("Shared ESP", &checkboxes[4]);

                    custom::Separator_line();

                    custom::Combo("Sound ESP", &sound_select, sound, IM_ARRAYSIZE(sound), 2);


                }
                custom::EndChild();
            }
            custom::EndGroup();

            ImGui::SameLine();

            custom::BeginGroup();
            {
                custom::Child("CHAMS", ImVec2((GetContentRegionMax().x - spacing.x * 3) / 2, (GetContentRegionMax().y - (60 + spacing.y * 2) * 2) + 10), true);
                {

                    custom::Checkbox("Enable Chams", &checkboxes[5]);

                    custom::Separator_line();

                    custom::Checkbox("Through Walls", &checkboxes[6]);

                    custom::Separator_line();

                    custom::Combo("Style", &style_select, stylee, IM_ARRAYSIZE(stylee), 2);

                    custom::Separator_line();

                    custom::Checkbox("Backtrack", &checkboxes[7]);

                    custom::Separator_line();

                    custom::Combo("Style ", &style2_select, stylee2, IM_ARRAYSIZE(stylee2), 2);

                    custom::Separator_line();

                    custom::Checkbox("One Shot", &checkboxes[8]);

                    custom::Separator_line();

                    custom::Checkbox("Ragdolls", &checkboxes[9]);

                }
                custom::EndChild();
            }
            custom::EndGroup();
        }

        ImGui::PopStyleVar();

        SetCursorPos(ImVec2(spacing.x, region.y - (60 + spacing.y)));
        custom::BeginGroup();
        {

            custom::Child("Page One", ImVec2((GetContentRegionMax().x - (spacing.x * 6)) / 4 - 2, 60), false);
            {

                if (custom::ThemeButton("0", dark, ImVec2((GetContentRegionMax().x - spacing.x * 2) / 2, GetContentRegionMax().y - spacing.y)))
                {
                    dark = !dark;
                    ImGui::Notification({ ImGuiToastType_Success, 4000, dark ? "It's black mode! Finally it was added" : "This is the white mode! Finally it was added" });
                }
                SameLine();
                if (custom::Button("b", ImVec2((GetContentRegionMax().x - spacing.x * 2) / 2, GetContentRegionMax().y - spacing.y)));

            }
            custom::EndChild();

            SameLine();

            custom::SeparatorEx(ImGuiSeparatorFlags_Vertical, 2.f);

            SameLine();

            custom::Child("Page Two", ImVec2((GetContentRegionMax().x - (spacing.x * 6)) / 2, 60), false);
            {

                if (custom::Page(0 == page, "c", ImVec2((GetContentRegionMax().x - spacing.x * 4) / 4, GetContentRegionMax().y - spacing.y))) page = 0;
                SameLine();
                if (custom::Page(1 == page, "d", ImVec2((GetContentRegionMax().x - spacing.x * 4) / 4, GetContentRegionMax().y - spacing.y))) page = 1;
                SameLine();
                if (custom::Page(2 == page, "e", ImVec2((GetContentRegionMax().x - spacing.x * 4) / 4, GetContentRegionMax().y - spacing.y))) page = 2;
                SameLine();
                if (custom::Page(3 == page, "f", ImVec2((GetContentRegionMax().x - spacing.x * 4) / 4, GetContentRegionMax().y - spacing.y))) page = 3;

            }
            custom::EndChild();

            SameLine();

            custom::SeparatorEx(ImGuiSeparatorFlags_Vertical, 2.f);

            SameLine();

            custom::Child("Page Three", ImVec2((GetContentRegionMax().x - (spacing.x * 6)) / 4 - 2, 60), false);
            {
                if (custom::Button("g", ImVec2((GetContentRegionMax().x - spacing.x * 2) / 2, GetContentRegionMax().y - spacing.y)));
                SameLine();
                if (custom::Button("h", ImVec2((GetContentRegionMax().x - spacing.x * 2) / 2, GetContentRegionMax().y - spacing.y)));
            }
            custom::EndChild();

        }
        custom::EndGroup();

    }
    End();

}

#ifdef OSIMGUI_INTERNAL

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		// Entry
		Gui.Start(hModule, DrawCallBack,OSImGui::DirectXType::AUTO);
	}
	return TRUE;
}

#endif

#ifndef OSIMGUI_INTERNAL

int main()
{
	try {
		// Gui.NewWindow("WindowName", Vec2(1280, 720), DrawCallBack, false );
		Gui.AttachAnotherWindow("x64","", DrawCallBack);
	}
	catch (OSImGui::OSException& e)
	{
		std::cout << e.what() << std::endl;
	}

	system("pause");
	return 0;
}

#endif