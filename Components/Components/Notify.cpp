#include "Notify.hpp"
#include "../../ImGui/imgui.h"
#include "../../ImGui/hashes.hpp"                                                                  
#include <mutex>
#include <deque>
#include <algorithm>
#include <cmath>
#include <atomic>

                                                               
                             
  
                                                                   
                                                     
                                                                  
                                                     
  
                                                                 
                                                                 
                                                              
                                                                  
                                                               

namespace
{
    struct Accent { float r, g, b; };

    Accent StyleAccent(Notify::Style s)
    {
        switch (s)
        {
        case Notify::Style::Info:    return { 0.23f, 0.55f, 1.00f };
        case Notify::Style::Success: return { 0.24f, 0.80f, 0.44f };
        case Notify::Style::Warning: return { 1.00f, 0.70f, 0.15f };
        case Notify::Style::Error:   return { 0.95f, 0.28f, 0.28f };
        case Notify::Style::Discord: return { 0.35f, 0.40f, 0.95f };
        default:                     return { 0.80f, 0.80f, 0.85f };
        }
    }

    const char* StyleGlyph(Notify::Style s)
    {
        switch (s)
        {
        case Notify::Style::Success: return ICON_FA_CHECK_CIRCLE;
        case Notify::Style::Warning: return ICON_FA_EXCLAMATION_TRIANGLE;
        case Notify::Style::Error:   return ICON_FA_TIMES_CIRCLE;
        case Notify::Style::Discord: return ICON_FA_BELL;
        default:                     return ICON_FA_INFO_CIRCLE;
        }
    }

    struct ToastItem
    {
        std::string title, body;
        Accent      accent;
        std::string glyph;
        float       duration;
        float       spawn = -1.0f;                       
        float       height = 0.0f;                          
    };

    struct PopupItem
    {
        std::string              title, body;
        Accent                   accent;
        std::string              glyph;
        std::vector<std::string> buttons;
        std::vector<std::string> citations;
        float                    spawn = -1.0f;
        bool                     closing = false;
        float                    closeStart = 0.0f;
        bool                     done = false;
    };

    std::mutex             g_mutex;
    std::deque<ToastItem>  g_pendingToasts;
    std::deque<ToastItem>  g_toasts;                                  
    std::deque<PopupItem>  g_pendingPopups;
    std::deque<PopupItem>  g_popups;                                  
    std::atomic<int>       g_livePopups{0};                                                    

    float EaseOutCubic(float t)  { t = 1.0f - t; return 1.0f - t * t * t; }
    float EaseOutBack(float t)
    {
        const float c1 = 1.70158f, c3 = c1 + 1.0f;
        float x = t - 1.0f;
        return 1.0f + c3 * x * x * x + c1 * x * x;
    }
}

                                                               
                                  
                                                               

void Notify::Toast(const std::string& title, const std::string& body, Style style, float durationSec)
{
    ToastItem t;
    t.title    = title;
    t.body     = body;
    t.accent   = StyleAccent(style);
    t.glyph    = StyleGlyph(style);
    t.duration = durationSec > 0.0f ? durationSec : 5.0f;
    std::lock_guard<std::mutex> lk(g_mutex);
    g_pendingToasts.push_back(std::move(t));
}

void Notify::ToastColored(const std::string& title, const std::string& body,
                          uint8_t r, uint8_t g, uint8_t b, uint8_t      , float durationSec)
{
    ToastItem t;
    t.title    = title;
    t.body     = body;
    t.accent   = { r / 255.0f, g / 255.0f, b / 255.0f };
    t.glyph    = ICON_FA_INFO_CIRCLE;
    t.duration = durationSec > 0.0f ? durationSec : 5.0f;
    std::lock_guard<std::mutex> lk(g_mutex);
    g_pendingToasts.push_back(std::move(t));
}

void Notify::Popup(const std::string& title, const std::string& body, Style style,
                   const std::vector<std::string>& buttons,
                   const std::vector<std::string>& citations)
{
    PopupItem p;
    p.title     = title;
    p.body      = body;
    p.accent    = StyleAccent(style);
    p.glyph     = StyleGlyph(style);
    p.buttons   = buttons.empty() ? std::vector<std::string>{ "OK" } : buttons;
    p.citations = citations;
    std::lock_guard<std::mutex> lk(g_mutex);
    g_pendingPopups.push_back(std::move(p));
}

void Notify::PopupColored(const std::string& title, const std::string& body,
                          uint8_t r, uint8_t g, uint8_t b, uint8_t      ,
                          const std::vector<std::string>& buttons,
                          const std::vector<std::string>& citations)
{
    PopupItem p;
    p.title     = title;
    p.body      = body;
    p.accent    = { r / 255.0f, g / 255.0f, b / 255.0f };
    p.glyph     = ICON_FA_INFO_CIRCLE;
    p.buttons   = buttons.empty() ? std::vector<std::string>{ "OK" } : buttons;
    p.citations = citations;
    std::lock_guard<std::mutex> lk(g_mutex);
    g_pendingPopups.push_back(std::move(p));
}

void Notify::Clear()
{
    std::lock_guard<std::mutex> lk(g_mutex);
    g_pendingToasts.clear();
    g_toasts.clear();
    g_pendingPopups.clear();
    g_popups.clear();
    g_livePopups.store(0);
}

bool Notify::HasPopup()
{
    std::lock_guard<std::mutex> lk(g_mutex);
    if (!g_pendingPopups.empty())
        return true;
    return g_livePopups.load() > 0;
}

                                                               
          
                                                               

static void RenderToasts(float now)
{
    const float PAD   = 14.0f;
    const float MIN_W = 280.0f;
    const float MAX_W = 420.0f;
    const float INTRO = 0.35f;                   
    const float OUTRO = 0.45f;                     

    ImGuiIO& io = ImGui::GetIO();
    const ImGuiStyle& style = ImGui::GetStyle();

                                                                      
    float yOffset = PAD;
    int   drawIndex = 0;

    for (size_t i = 0; i < g_toasts.size(); )
    {
        ToastItem& t = g_toasts[i];
        if (t.spawn < 0.0f) t.spawn = now;
        float age = now - t.spawn;

        if (age >= t.duration + OUTRO)
        {
            g_toasts.erase(g_toasts.begin() + static_cast<long long>(i));
            continue;
        }

                            
        float alpha = 1.0f;
        if (age < INTRO)                     alpha = EaseOutCubic(age / INTRO);
        else if (age > t.duration)           alpha = 1.0f - EaseOutCubic((age - t.duration) / OUTRO);
        alpha = alpha < 0.0f ? 0.0f : (alpha > 1.0f ? 1.0f : alpha);

                                                                             
                                                                            
                               
        float glyphW = ImGui::CalcTextSize(t.glyph.c_str()).x + style.ItemSpacing.x;
        float titleW = ImGui::CalcTextSize(t.title.c_str()).x;
        float width  = titleW + glyphW + 34.0f;
        if (width < MIN_W) width = MIN_W;
        if (width > MAX_W) width = MAX_W;

                                                   
        float slideT = age < INTRO ? EaseOutCubic(age / INTRO) : 1.0f;
        float offX   = (1.0f - slideT) * (width + PAD);

        float posX = io.DisplaySize.x - width - PAD + offX;
        float posY = yOffset;

        ImGui::SetNextWindowPos(ImVec2(posX, posY), ImGuiCond_Always);
                                                              
        ImGui::SetNextWindowSizeConstraints(ImVec2(width, 0.0f), ImVec2(width, io.DisplaySize.y));
        ImGui::SetNextWindowBgAlpha(0.0f);                     

        char id[48];
        snprintf(id, sizeof(id), "##notify_toast_%d", drawIndex);

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
            ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(14.0f, 12.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10.0f);
        ImGui::Begin(id, nullptr, flags);

        ImDrawList* dl = ImGui::GetWindowDrawList();
        ImVec2 wpos = ImGui::GetWindowPos();
        ImVec2 wsz  = ImGui::GetWindowSize();

        ImU32 bg     = ImGui::GetColorU32(ImVec4(0.09f, 0.09f, 0.11f, 0.96f * alpha));
        ImU32 accent = ImGui::GetColorU32(ImVec4(t.accent.r, t.accent.g, t.accent.b, alpha));
        ImU32 border = ImGui::GetColorU32(ImVec4(t.accent.r, t.accent.g, t.accent.b, 0.55f * alpha));

        dl->AddRectFilled(wpos, ImVec2(wpos.x + wsz.x, wpos.y + wsz.y), bg, 10.0f);
        dl->AddRect(wpos, ImVec2(wpos.x + wsz.x, wpos.y + wsz.y), border, 10.0f, 0, 1.5f);
                                       
        dl->AddRectFilled(wpos, ImVec2(wpos.x + 4.0f, wpos.y + wsz.y), accent, 10.0f,
                          ImDrawFlags_RoundCornersLeft);
                                                    
        float prog = age < t.duration ? 1.0f - (age / t.duration) : 0.0f;
        dl->AddRectFilled(ImVec2(wpos.x, wpos.y + wsz.y - 2.0f),
                          ImVec2(wpos.x + wsz.x * prog, wpos.y + wsz.y), accent);

                                          
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(t.accent.r, t.accent.g, t.accent.b, alpha));
        ImGui::TextUnformatted(t.glyph.c_str());
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, alpha));
        ImGui::PushTextWrapPos(width - 14.0f);
        ImGui::TextUnformatted(t.title.c_str());
        ImGui::PopTextWrapPos();
        ImGui::PopStyleColor();

        if (!t.body.empty())
        {
            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.78f, 0.78f, 0.82f, alpha));
            ImGui::PushTextWrapPos(width - 14.0f);
            ImGui::TextUnformatted(t.body.c_str());
            ImGui::PopTextWrapPos();
            ImGui::PopStyleColor();
        }

        t.height = ImGui::GetWindowSize().y;
        ImGui::End();
        ImGui::PopStyleVar(2);

        yOffset += t.height + PAD * 0.6f;
        ++drawIndex;
        ++i;
    }
}

static void RenderPopups(float now)
{
    const float INTRO = 0.30f;
    const float OUTRO = 0.22f;

    ImGuiIO& io = ImGui::GetIO();

    for (size_t i = 0; i < g_popups.size(); )
    {
        PopupItem& p = g_popups[i];
        if (p.spawn < 0.0f) p.spawn = now;

        if (p.done)
        {
            g_popups.erase(g_popups.begin() + static_cast<long long>(i));
            g_livePopups.store(static_cast<int>(g_popups.size()));
            continue;
        }

        float alpha, scale;
        if (p.closing)
        {
            float ct = (now - p.closeStart) / OUTRO;
            if (ct >= 1.0f) { p.done = true; continue; }
            alpha = 1.0f - ct;
            scale = 1.0f - 0.06f * ct;
        }
        else
        {
            float age = now - p.spawn;
            float t   = age < INTRO ? (age / INTRO) : 1.0f;
            alpha = t;
            scale = 0.85f + 0.15f * EaseOutBack(t);
        }

                                                        
        if (i + 1 == g_popups.size())
        {
            ImDrawList* bgdl = ImGui::GetBackgroundDrawList();
            bgdl->AddRectFilled(ImVec2(0, 0), io.DisplaySize,
                                ImGui::GetColorU32(ImVec4(0, 0, 0, 0.55f * alpha)));
        }

                                                                          
                                                                  
        float baseW = ImGui::CalcTextSize(p.title.c_str()).x + 90.0f;
        if (baseW < 360.0f) baseW = 360.0f;
        if (baseW > 520.0f) baseW = 520.0f;
        float w = baseW * scale;
        ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
                                ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(w, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.0f);

        char id[48];
        snprintf(id, sizeof(id), "##notify_popup_%zu", i);

        ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav |
            ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20.0f, 18.0f));
        ImGui::Begin(id, nullptr, flags);

        ImDrawList* dl = ImGui::GetWindowDrawList();
        ImVec2 wpos = ImGui::GetWindowPos();
        ImVec2 wsz  = ImGui::GetWindowSize();

        ImU32 bg     = ImGui::GetColorU32(ImVec4(0.08f, 0.08f, 0.10f, 0.98f * alpha));
        ImU32 accent = ImGui::GetColorU32(ImVec4(p.accent.r, p.accent.g, p.accent.b, alpha));
        ImU32 border = ImGui::GetColorU32(ImVec4(p.accent.r, p.accent.g, p.accent.b, 0.75f * alpha));

        dl->AddRectFilled(wpos, ImVec2(wpos.x + wsz.x, wpos.y + wsz.y), bg, 10.0f);
        dl->AddRect(wpos, ImVec2(wpos.x + wsz.x, wpos.y + wsz.y), border, 10.0f, 0, 2.0f);
                               
        dl->AddRectFilled(wpos, ImVec2(wpos.x + wsz.x, wpos.y + 4.0f), accent, 10.0f,
                          ImDrawFlags_RoundCornersTop);

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(p.accent.r, p.accent.g, p.accent.b, alpha));
        ImGui::TextUnformatted(p.glyph.c_str());
        ImGui::PopStyleColor();
        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, alpha));
        ImGui::PushFont(nullptr);
        ImGui::PushTextWrapPos(wpos.x + wsz.x - 20.0f);
        ImGui::TextUnformatted(p.title.c_str());
        ImGui::PopTextWrapPos();
        ImGui::PopFont();
        ImGui::PopStyleColor();

        ImGui::Separator();
        ImGui::Spacing();

                                                                          
                                                                              
        const float bodyHeight = (std::min)(160.0f, io.DisplaySize.y * 0.30f);
        ImGui::BeginChild("##notify_popup_body", ImVec2(-1.0f, bodyHeight), true);
        if (!p.body.empty())
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.85f, 0.85f, 0.88f, alpha));
            ImGui::TextWrapped("%s", p.body.c_str());
            ImGui::PopStyleColor();
        }

        if (!p.citations.empty())
        {
            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(p.accent.r, p.accent.g, p.accent.b, alpha));
            ImGui::TextUnformatted("Citations:");
            ImGui::PopStyleColor();
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.75f, 0.75f, 0.78f, alpha));
            for (size_t c = 0; c < p.citations.size(); ++c)
                ImGui::TextWrapped("%zu. %s", c + 1, p.citations[c].c_str());
            ImGui::PopStyleColor();
        }
        ImGui::EndChild();

        ImGui::Spacing();
        ImGui::Spacing();

                                      
        float btnW = 96.0f;
        float spacing = ImGui::GetStyle().ItemSpacing.x;
        float total = p.buttons.size() * btnW + (p.buttons.size() - 1) * spacing;
        float startX = ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - total);
        if (startX > ImGui::GetCursorPosX()) ImGui::SetCursorPosX(startX);

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(p.accent.r * 0.5f, p.accent.g * 0.5f, p.accent.b * 0.5f, alpha));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(p.accent.r * 0.75f, p.accent.g * 0.75f, p.accent.b * 0.75f, alpha));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(p.accent.r, p.accent.g, p.accent.b, alpha));
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, alpha));
        for (size_t b = 0; b < p.buttons.size(); ++b)
        {
            if (b > 0) ImGui::SameLine();
            char blabel[128];
            snprintf(blabel, sizeof(blabel), "%s##notify_pbtn_%zu_%zu", p.buttons[b].c_str(), i, b);
            if (!p.closing && ImGui::Button(blabel, ImVec2(btnW, 0.0f)))
            {
                p.closing = true;
                p.closeStart = now;
            }
        }
        ImGui::PopStyleColor(4);

        ImGui::End();
        ImGui::PopStyleVar();
        ++i;
    }
}

void Notify::Render()
{
                                                                     
    {
        std::lock_guard<std::mutex> lk(g_mutex);
        while (!g_pendingToasts.empty())
        {
            g_toasts.push_back(std::move(g_pendingToasts.front()));
            g_pendingToasts.pop_front();
        }
        while (!g_pendingPopups.empty())
        {
            g_popups.push_back(std::move(g_pendingPopups.front()));
            g_pendingPopups.pop_front();
        }
        g_livePopups.store(static_cast<int>(g_popups.size()));
    }

    if (g_toasts.empty() && g_popups.empty())
        return;

    float now = static_cast<float>(ImGui::GetTime());
    RenderToasts(now);
    RenderPopups(now);
}
