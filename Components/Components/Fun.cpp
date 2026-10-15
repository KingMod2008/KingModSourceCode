#include "../../pch.hpp"
#include "Fun.hpp"
#include "Events.hpp"
#include "Instances.hpp"
#include "Console.hpp"
#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"
#include "../../ImGui/imgui.h"
#include "../../ImGui/imgui_stdlib.h"

                        
namespace ModalState {
    static bool createmodalrn = false;
    static int createdmodaltype = 0;                           
    static std::string custommodaltitle = "";
    static std::string custommodalbody = "";
    static struct { uint8_t r, g, b, a; } custommodalcolor = {255, 255, 255, 255};
    static std::vector<std::string> banCitations;
    static std::vector<std::string> modalbuttons;
    static UGFxShell_TA* gfxshell = nullptr;
}

void Fun::QueueModal(
    int modalType,
    const std::string& title,
    const std::string& body,
    uint8_t red,
    uint8_t green,
    uint8_t blue,
    uint8_t alpha,
    const std::vector<std::string>& citations,
    const std::vector<std::string>& buttons)
{
    ModalState::createmodalrn = true;
    ModalState::createdmodaltype = modalType;
    ModalState::custommodaltitle = title;
    ModalState::custommodalbody = body;
    ModalState::custommodalcolor = { red, green, blue, alpha };
    ModalState::banCitations = citations;
    ModalState::modalbuttons = buttons.empty() ? std::vector<std::string>{ "OK" } : buttons;
}

void Fun::ShowWelcomeModal()
{
    QueueModal(2, "Welcome to KingMod",
        "KingMod is free and open source. If you paid anyone for this mod, you were scammed.\n\nSigned, rlsdk",
        255, 255, 255, 255, {}, { "OK" });
}

void Fun::HandleModalEvents()
{
    if (ModalState::createmodalrn) {
        ModalState::createmodalrn = false;

        if (!ModalState::gfxshell)
            ModalState::gfxshell = Instances.GetInstanceOf<UGFxShell_TA>();

        if (ModalState::gfxshell)
        {
            UGFxModal_X* modal = nullptr;
            
                                                              
            switch (ModalState::createdmodaltype)
            {
                case 0:             
                    modal = (UGFxModal_X*)ModalState::gfxshell->CreateModal_NoShow(UGFxModal_X::StaticClass());
                    break;
                    
                case 1:             
                    modal = (UGFxModal_X*)ModalState::gfxshell->CreateModal_NoShow(UGFxModal_Ban_TA::StaticClass());
                    break;
                    
                case 2:                   
                    modal = (UGFxModal_X*)ModalState::gfxshell->CreateModal_NoShow(UGFxModal_Warning_TA::StaticClass());
                    break;
                    
                default:
                    modal = (UGFxModal_X*)ModalState::gfxshell->CreateModal_NoShow(UGFxModal_X::StaticClass());
                    break;
            }

            if (modal)
            {
                                                                                           
                std::wstring title_ws(ModalState::custommodaltitle.begin(), ModalState::custommodaltitle.end());
                FString title(title_ws.c_str());

                std::wstring body_ws(ModalState::custommodalbody.begin(), ModalState::custommodalbody.end());
                FString body(body_ws.c_str());

                modal->SetTitle(title);
                modal->SetBody(body);

                                                                        
                if (ModalState::createdmodaltype == 1 && !ModalState::banCitations.empty())
                {
                    std::string citationsText = "\n\nCitations:\n";
                    for (size_t i = 0; i < ModalState::banCitations.size(); i++)
                    {
                        citationsText += std::to_string(i + 1) + ". " + ModalState::banCitations[i] + "\n";
                    }
                    
                                                        
                    std::string fullBody = ModalState::custommodalbody + citationsText;
                    std::wstring body_with_citations_ws(fullBody.begin(), fullBody.end());
                    FString bodyWithCitations(body_with_citations_ws.c_str());
                    modal->SetBody(bodyWithCitations);
                }

                for (const auto& button_text : ModalState::modalbuttons)
                {
                    modal->FlashAddButton(FString(std::wstring(button_text.begin(), button_text.end()).c_str()));
                }

                                 
                FASColorTransform ColorTransform;
                FLinearColor linearcolor = ModalState::gfxshell->ColorToLinearColor(
                    FColor(ModalState::custommodalcolor.r, ModalState::custommodalcolor.g, 
                           ModalState::custommodalcolor.b, ModalState::custommodalcolor.a)
                );
                ColorTransform.Multiply = linearcolor;
                if (modal->GFxPopup)
                {
                    modal->GFxPopup->SetColorTransform(ColorTransform);
                }

                                                                                 
                modal->SetCancellable(true);

                                  
                ModalState::gfxshell->ShowModalObject(modal);
            }
        }
    }
}
