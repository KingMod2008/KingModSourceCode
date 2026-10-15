#include "Watermark.hpp"
#include <chrono>
#include <string>
#include <cmath>

using clock_tp = std::chrono::time_point<std::chrono::steady_clock>;

namespace
{
                                      
    clock_tp lastFrameTime = std::chrono::steady_clock::now();
    float smoothedFps = 0.0f;

    ImU32 rgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        return IM_COL32(r, g, b, a);
    }
}


namespace SilverModUI
{
    void RenderWatermark()
    {
        ImDrawList* drawList = ImGui::GetBackgroundDrawList();
        if (!drawList)
            return;

                       
        clock_tp now = std::chrono::steady_clock::now();
        float frameSeconds = std::chrono::duration<float>(now - lastFrameTime).count();
        if (frameSeconds <= 0.0f)
            frameSeconds = 0.001f;
        lastFrameTime = now;

        float instantFps = 1.0f / frameSeconds;
                           
        if (smoothedFps <= 0.01f)
            smoothedFps = instantFps;
        else
            smoothedFps = smoothedFps * 0.9f + instantFps * 0.1f;

        int fpsInt = (int)(smoothedFps + 0.5f);
        std::string text = "";

                 
        const float fontSize = 18.0f;
        const float charWidth = 9.0f;                          
        const float padding = 9.0f;
        const float x = 5.0f;
        const float y = 5.0f;
        const float bgWidth = (float)text.size() * charWidth + padding * 2.0f;
        const float bgHeight = fontSize + padding;
        const float textY = y + (bgHeight - fontSize) * 0.5f;

                     
        drawList->AddRectFilled(ImVec2(x, y), ImVec2(x + bgWidth, y + bgHeight), rgba(0, 0, 0, 180), 5.0f);

                                        
        const float animationSpeed = 6.0f;
        const float highlightWidth = 4.0f;
        float t = (float)ImGui::GetTime() * animationSpeed;
        float highlightPos = fmodf(t, (float)text.size() + highlightWidth) - highlightWidth;

                           
        const ImU32 darkCoolBase = rgba(80, 120, 160, 230);

                                  
        for (size_t i = 0; i < text.size(); ++i)
        {
            char c = text[i];
            float dist = fabsf((float)i - highlightPos);
            ImU32 color = darkCoolBase;
            if (dist < highlightWidth)
            {
                float blendFactor = dist / highlightWidth;
                float blend = 1.0f - sinf(blendFactor * (3.14159265f * 0.5f));
                int r = (int)(80.0f + blend * (120.0f - 80.0f));
                int g = (int)(120.0f + blend * (180.0f - 120.0f));
                int b = (int)(160.0f + blend * (220.0f - 160.0f));
                color = rgba((unsigned char)r, (unsigned char)g, (unsigned char)b, 230);
            }

                                                            
            char buf[2] = { c, '\0' };
            drawList->AddText(ImGui::GetFont(), fontSize, ImVec2(x + padding + (float)i * charWidth, textY), color, buf);
        }
    }
}