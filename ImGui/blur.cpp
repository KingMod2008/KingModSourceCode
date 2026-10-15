#include "blur.hpp"

#include <string.h>                    
#include <float.h>              

                                                                     
                                                                                 
                                                                                  
                                                                                 
  
                                                                    
                                                                                   
                                                                                   
                                                                                 
                                                                             
  
                                                                                  
                                                                              

using namespace ImGui;

namespace blur
{

struct BlurResources
{
    ID3D11Device*                 dev          = nullptr;
    ID3D11Texture2D*              tex[2]       = { nullptr, nullptr };
    ID3D11RenderTargetView*       rtv[2]       = { nullptr, nullptr };
    ID3D11ShaderResourceView*     srv[2]       = { nullptr, nullptr };
    ID3D11VertexShader*           vs           = nullptr;
    ID3D11PixelShader*            ps           = nullptr;
    ID3D11SamplerState*           sampler      = nullptr;
    ID3D11Buffer*                 cb           = nullptr;
    UINT                          width        = 0;
    UINT                          height       = 0;
    DXGI_FORMAT                   format       = DXGI_FORMAT_UNKNOWN;
};

static BlurResources g;

static ID3D11RenderTargetView* g_savedRTV = nullptr;
static ID3D11DepthStencilView* g_savedDSV = nullptr;

static const char* kVertexShader = R"(
struct VSOut { float4 pos : SV_Position; float2 uv : TEXCOORD0; };
VSOut main(uint id : SV_VertexID)
{
    VSOut o;
    o.uv = float2((id << 1) & 2, id & 2);
    o.pos = float4(o.uv * 2.0f - 1.0f, 0.0f, 1.0f);
    return o;
}
)";

static const char* kPixelShader = R"(
Texture2D    tex  : register(t0);
SamplerState smp  : register(s0);
cbuffer Params : register(b0) { float2 dir; float2 texel; };
static const float w[5] = { 0.227027f, 0.1945946f, 0.1216216f, 0.0540541f, 0.0162162f };
struct VSOut { float4 pos : SV_Position; float2 uv : TEXCOORD0; };
float4 main(VSOut i) : SV_Target
{
    float2 step = dir * texel;
    float4 c = tex.Sample(smp, i.uv) * w[0];
    for (int k = 1; k < 5; ++k)
    {
        float2 o = step * (float)k;
        c += tex.Sample(smp, i.uv + o) * w[k];
        c += tex.Sample(smp, i.uv - o) * w[k];
    }
    return c;
}
)";

                                                                                     
                                                        
typedef HRESULT(WINAPI* D3DCompile_t)(LPCVOID, SIZE_T, LPCSTR, const void*, void*, LPCSTR, LPCSTR, UINT, UINT, ID3DBlob**, ID3DBlob**);

static D3DCompile_t D3DCompileFn()
{
    static D3DCompile_t fn = []() -> D3DCompile_t
    {
        HMODULE m = GetModuleHandleA("d3dcompiler_47.dll");
        if (!m)
            m = LoadLibraryA("d3dcompiler_47.dll");
        return m ? reinterpret_cast<D3DCompile_t>(GetProcAddress(m, "D3DCompile")) : nullptr;
    }();
    return fn;
}

static void ReleaseResources()
{
    for (int i = 0; i < 2; ++i)
    {
        if (g.rtv[i]) { g.rtv[i]->Release(); g.rtv[i] = nullptr; }
        if (g.srv[i]) { g.srv[i]->Release(); g.srv[i] = nullptr; }
        if (g.tex[i]) { g.tex[i]->Release(); g.tex[i] = nullptr; }
    }
    if (g.sampler) { g.sampler->Release(); g.sampler = nullptr; }
    if (g.cb)      { g.cb->Release(); g.cb = nullptr; }
    if (g.ps)      { g.ps->Release(); g.ps = nullptr; }
    if (g.vs)      { g.vs->Release(); g.vs = nullptr; }
    if (g.dev)     { g.dev->Release(); g.dev = nullptr; }
    g.width = 0;
    g.height = 0;
    g.format = DXGI_FORMAT_UNKNOWN;
}

                                                                           
static ID3D11Texture2D* GetBackBuffer(ID3D11DeviceContext* ctx)
{
    ID3D11RenderTargetView* rtv = nullptr;
    ctx->OMGetRenderTargets(1, &rtv, nullptr);
    if (!rtv)
        return nullptr;
    ID3D11Resource* res = nullptr;
    rtv->GetResource(&res);
    rtv->Release();
    ID3D11Texture2D* tex = nullptr;
    if (res)
    {
        res->QueryInterface(__uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&tex));
        res->Release();
    }
    return tex;
}

static bool EnsureResources(ID3D11DeviceContext* ctx, UINT w, UINT h, DXGI_FORMAT fmt)
{
    if (g.dev && g.width == w && g.height == h && g.format == fmt)
        return true;

    ID3D11Device* dev = nullptr;
    ctx->GetDevice(&dev);
    if (!dev)
        return false;

    ReleaseResources();
    g.dev = dev;
    g.width = w;
    g.height = h;
    g.format = fmt;

    bool ok = true;
    for (int i = 0; i < 2 && ok; ++i)
    {
        D3D11_TEXTURE2D_DESC td = {};
        td.Width = w;
        td.Height = h;
        td.MipLevels = 1;
        td.ArraySize = 1;
        td.Format = fmt;
        td.SampleDesc.Count = 1;                              
        td.Usage = D3D11_USAGE_DEFAULT;
        td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
        if (FAILED(dev->CreateTexture2D(&td, nullptr, &g.tex[i])))
        {
            ok = false;
            break;
        }
        if (FAILED(dev->CreateRenderTargetView(g.tex[i], nullptr, &g.rtv[i])))
        {
            ok = false;
            break;
        }
        if (FAILED(dev->CreateShaderResourceView(g.tex[i], nullptr, &g.srv[i])))
        {
            ok = false;
            break;
        }
    }

    if (ok)
    {
        D3DCompile_t compile = D3DCompileFn();
        if (compile)
        {
            ID3DBlob* blob = nullptr;
            ID3DBlob* err = nullptr;
            if (SUCCEEDED(compile(kVertexShader, strlen(kVertexShader), "blur_vs", nullptr, nullptr, "main", "vs_5_0", 0, 0, &blob, &err)))
            {
                dev->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &g.vs);
                blob->Release();
            }
            if (err) { err->Release(); err = nullptr; }
            if (SUCCEEDED(compile(kPixelShader, strlen(kPixelShader), "blur_ps", nullptr, nullptr, "main", "ps_5_0", 0, 0, &blob, &err)))
            {
                dev->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &g.ps);
                blob->Release();
            }
            if (err) err->Release();
        }
    }

    if (ok)
    {
        D3D11_SAMPLER_DESC sd = {};
        sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sd.MaxLOD = FLT_MAX;
        if (FAILED(dev->CreateSamplerState(&sd, &g.sampler)))
            ok = false;
    }

    if (ok)
    {
        D3D11_BUFFER_DESC bd = {};
        bd.ByteWidth = sizeof(float) * 4;
        bd.Usage = D3D11_USAGE_DYNAMIC;
        bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        if (FAILED(dev->CreateBuffer(&bd, nullptr, &g.cb)))
            ok = false;
    }

    if (!ok)
    {
        ReleaseResources();
        return false;
    }
    return true;
}

                                                                                   
                                                                                  
                                                                                   
static void BlurPass(ID3D11DeviceContext* ctx, int dstIdx, float dirX, float dirY)
{
    ctx->OMSetRenderTargets(1, &g.rtv[dstIdx], nullptr);
    ctx->PSSetShader(g.ps, nullptr, 0);
    ctx->PSSetSamplers(0, 1, &g.sampler);

    struct { float dir[2]; float texel[2]; } params;
    params.dir[0] = dirX;
    params.dir[1] = dirY;
    params.texel[0] = 1.0f / (float)g.width;
    params.texel[1] = 1.0f / (float)g.height;

    D3D11_MAPPED_SUBRESOURCE map;
    if (SUCCEEDED(ctx->Map(g.cb, 0, D3D11_MAP_WRITE_DISCARD, 0, &map)))
    {
        memcpy(map.pData, &params, sizeof(params));
        ctx->Unmap(g.cb, 0);
    }
    ctx->PSSetConstantBuffers(0, 1, &g.cb);
}

static void begin_blur(const ImDrawList*, const ImDrawCmd* cmd)
{
    auto* ctx = static_cast<ID3D11DeviceContext*>(cmd->UserCallbackData);
    if (!ctx)
        return;

    ID3D11Texture2D* back = GetBackBuffer(ctx);
    if (!back)
        return;
    D3D11_TEXTURE2D_DESC bd;
    back->GetDesc(&bd);
                                               
    if (bd.SampleDesc.Count != 1)
    {
        back->Release();
        return;
    }
                                                                                       
                                                                                        
                                                                                         
    if (!g.dev || g.width != bd.Width || g.height != bd.Height || g.format != bd.Format)
    {
        back->Release();
        return;
    }

    ctx->OMGetRenderTargets(1, &g_savedRTV, &g_savedDSV);
    ctx->CopyResource(g.tex[0], back);
    back->Release();
}

static void pass_x(const ImDrawList*, const ImDrawCmd* cmd)
{
    if (auto* ctx = static_cast<ID3D11DeviceContext*>(cmd->UserCallbackData))
        BlurPass(ctx, 1, 1.f, 0.f);                            
}

static void pass_y(const ImDrawList*, const ImDrawCmd* cmd)
{
    if (auto* ctx = static_cast<ID3D11DeviceContext*>(cmd->UserCallbackData))
        BlurPass(ctx, 0, 0.f, 1.f);                          
}

static void end_blur(const ImDrawList*, const ImDrawCmd* cmd)
{
    auto* ctx = static_cast<ID3D11DeviceContext*>(cmd->UserCallbackData);
    if (!ctx)
        return;

                                                                         
    if (g_savedRTV || g_savedDSV)
    {
        ctx->OMSetRenderTargets(1, &g_savedRTV, g_savedDSV);
        if (g_savedRTV) { g_savedRTV->Release(); g_savedRTV = nullptr; }
        if (g_savedDSV) { g_savedDSV->Release(); g_savedDSV = nullptr; }
    }

                                                                  
    ID3D11ShaderResourceView* null_srv[1] = { nullptr };
    ID3D11SamplerState* null_samp[1] = { nullptr };
    ctx->PSSetShaderResources(0, 1, null_srv);
    ctx->PSSetSamplers(0, 1, null_samp);
    ctx->PSSetShader(nullptr, nullptr, 0);
}

}                  

void blur::Shutdown()
{
                                                                           
                                                                        
    ReleaseResources();
    if (g_savedRTV) { g_savedRTV->Release(); g_savedRTV = nullptr; }
    if (g_savedDSV) { g_savedDSV->Release(); g_savedDSV = nullptr; }
    device = nullptr;
}

void draw_blur(ImDrawList* drawList)
{
    if (!blur::enabled)
        return;

    auto* ctx = blur::device;
    if (!ctx)
        return;

    ID3D11Texture2D* back = blur::GetBackBuffer(ctx);
    if (!back)
        return;
    D3D11_TEXTURE2D_DESC bd;
    back->GetDesc(&bd);
    back->Release();
    if (bd.SampleDesc.Count != 1)
        return;
    if (!blur::EnsureResources(ctx, bd.Width, bd.Height, bd.Format))
        return;

    const ImTextureID srv0 = (ImTextureID)blur::g.srv[0];
    const ImTextureID srv1 = (ImTextureID)blur::g.srv[1];
    const ImVec2 full(0.f, 0.f);
    const ImVec2 size((float)blur::g.width, (float)blur::g.height);

    drawList->AddCallback(blur::begin_blur, blur::device);
                                                                                  
                                                                                
                                                                               
                                                                               
                                                                       
    for (int i = 0; i < 3; ++i)
    {
        drawList->AddCallback(blur::pass_x, blur::device);                
        drawList->AddImage(srv0, full, size);                                       
        drawList->AddCallback(blur::pass_y, blur::device);                
        drawList->AddImage(srv1, full, size);                                       
    }
    drawList->AddCallback(blur::end_blur, blur::device);
    drawList->AddCallback(ImDrawCallback_ResetRenderState, 0);
    drawList->AddImageRounded(srv0, full, size, full, size, IM_COL32(255, 255, 255, 255), 7.f);
}
