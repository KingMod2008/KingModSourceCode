#include "gui_widget.hpp"
using namespace ImGui;

void c_gui::render_circle_for_horizontal_bar(ImVec2 pos, ImColor color, float alpha) {
    auto draw = GetWindowDrawList();
    draw->AddCircleFilled(pos, 6, ImColor(color.Value.x, color.Value.y, color.Value.z, alpha * GetStyle().Alpha));
}

bool c_gui::tab(const char* icon, const char* label, bool selected) {
    auto window = GetCurrentWindow();
    auto id = window->GetID(label);

    auto label_size = CalcTextSize(label, 0, 1);

    auto pos = window->DC.CursorPos;
    auto draw = window->DrawList;

    ImRect bb(pos, pos + ImVec2(GetWindowWidth(), 30));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

                                                                             
                                                                             
                                                            
    static std::unordered_map<ImGuiID, float> sel_values;
    static std::unordered_map<ImGuiID, float> hov_values;
    float& sel = sel_values.try_emplace(id, 0.f).first->second;
    float& hov = hov_values.try_emplace(id, 0.f).first->second;
    sel = ImLerp(sel, selected ? 1.f : 0.f, 0.16f);
    hov = ImLerp(hov, (hovered && !selected) ? 1.f : 0.f, 0.18f);

                                                                         
    if (hov > 0.001f)
        draw->AddRectFilled(bb.Min, bb.Max, gui.frame_active.to_im_color(0.22f * hov), 6.f);
    if (sel > 0.001f)
        draw->AddRectFilled(bb.Min, bb.Max, gui.frame_active.to_im_color(0.62f * sel), 6.f);

                                                                             
    const float pillH = (bb.GetHeight() - 12.f) * sel;
    if (pillH > 0.5f) {
        const float cy = bb.GetCenter().y;
        draw->AddRectFilled(ImVec2(bb.Min.x + 2.f, cy - pillH * 0.5f),
            ImVec2(bb.Min.x + 5.f, cy + pillH * 0.5f), gui.accent_color.to_im_color(), 2.f);
    }

                                                                                
                                                                             
    const float t = ImClamp(sel + hov, 0.f, 1.f);
    const float slide = 3.f * sel;
    const ImU32 iconCol = ColorConvertFloat4ToU32(ImLerp(gui.text_disabled.to_vec4(), gui.accent_color.to_vec4(), t));
    const ImU32 textCol = ColorConvertFloat4ToU32(ImLerp(gui.text_disabled.to_vec4(), gui.text.to_vec4(), ImClamp(sel + hov * 0.6f, 0.f, 1.f)));
    draw->AddText(ImVec2(bb.Min.x + 12 + slide, bb.GetCenter().y - label_size.y / 2), iconCol, icon);
    draw->AddText(ImVec2(bb.Min.x + 37 + slide, bb.GetCenter().y - label_size.y / 2), textCol, label);

    return pressed;
}

bool c_gui::subtab(const char* label, bool selected, int size, ImDrawFlags flags) {
    auto window = GetCurrentWindow();
    auto id = window->GetID(label);

    auto label_size = CalcTextSize(label, 0, 1);

    auto pos = window->DC.CursorPos;
    auto draw = window->DrawList;

                                                                           
                                                                              
                                                                               
    const float tabWidth = ImMax(92.0f, label_size.x + 28.0f);
    ImRect bb(pos, pos + ImVec2(tabWidth, GetWindowHeight()));
    ItemAdd(bb, id);
    ItemSize(bb, GetStyle().FramePadding.y);

    bool hovered, held;
    bool pressed = ButtonBehavior(bb, id, &hovered, &held);

    static std::unordered_map<ImGuiID, float> sel_values;
    static std::unordered_map<ImGuiID, float> hov_values;
    float& sel = sel_values.try_emplace(id, 0.f).first->second;
    float& hov = hov_values.try_emplace(id, 0.f).first->second;
    sel = ImLerp(sel, selected ? 1.f : 0.f, 0.18f);
    hov = ImLerp(hov, (hovered && !selected) ? 1.f : 0.f, 0.20f);

    if (hov > 0.001f)
        draw->AddRectFilled(bb.Min, bb.Max, gui.frame_active.to_im_color(0.35f * hov), 4, flags);
    if (sel > 0.001f)
        draw->AddRectFilled(bb.Min, bb.Max, gui.frame_active.to_im_color(0.85f * sel), 4, flags);

                                                                            
    const float underline = (bb.GetWidth() - 16.f) * sel;
    if (underline > 0.5f) {
        const float cx = bb.GetCenter().x;
        const float y = bb.Max.y - 3.f;
        draw->AddRectFilled(ImVec2(cx - underline * 0.5f, y), ImVec2(cx + underline * 0.5f, y + 2.f),
            gui.accent_color.to_im_color(), 1.f);
    }

    const ImU32 col = ColorConvertFloat4ToU32(ImLerp(gui.text_disabled.to_vec4(), gui.text.to_vec4(), ImClamp(sel + hov * 0.7f, 0.f, 1.f)));
    draw->AddText(bb.GetCenter() - label_size / 2, col, label);

    return pressed;
}

void c_gui::group_box(const char* name, ImVec2 size_arg) {
    auto window = GetCurrentWindow();
    auto pos = window->DC.CursorPos;

    BeginChild(std::string(name).append(".main").c_str(), size_arg, false, ImGuiWindowFlags_NoScrollbar);

    GetWindowDrawList()->AddRectFilled(pos + ImVec2(0, 20), pos + size_arg, gui.group_box_bg.to_im_color(), 6);
    GetWindowDrawList()->AddRect(pos + ImVec2(0, 20), pos + size_arg, gui.border.to_im_color(), 6);

    GetWindowDrawList()->AddText(pos + ImVec2(12, 0), GetColorU32(ImGuiCol_Text, 0.5f), name);

    SetCursorPos(ImVec2(12, 21));
    PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 10 });
                                                                             
                                                                            
                                                                    
    std::string innerName = std::string(name) + "##s" + std::to_string(gui.m_active_subtab[gui.m_tab]);
    BeginChild(innerName.c_str(), { size_arg.x - 24, size_arg.y - 21 }, 0, ImGuiWindowFlags_AlwaysUseWindowPadding);

    BeginGroup();

    PushStyleVar(ImGuiStyleVar_ItemSpacing, { 8, 10 });
    PushStyleVar(ImGuiStyleVar_Alpha, gui.m_anim);
}

void c_gui::end_group_box() {
    PopStyleVar(3);
    EndGroup();
    EndChild();
    EndChild();
}
