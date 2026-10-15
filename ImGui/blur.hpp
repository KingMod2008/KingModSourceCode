#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <windows.h>
#include <d3d11.h>
#include "imgui.h"
#include "imgui_internal.h"

namespace blur
{
                                                                     
    inline ID3D11DeviceContext* device = nullptr;

                                                                              
                                                                     
    inline bool enabled = true;

                                                                            
                                     
    void Shutdown();
}

                                                                              
                                                                           
extern void draw_blur(ImDrawList* drawList);
