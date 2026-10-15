#include "PsyNetDump.hpp"
#include "../Includes.hpp"
#include <sstream>
#include <iomanip>

                                       
std::string DumpParamsHex(void* params, size_t size) {
    if (!params || size == 0) return "[null]";
    
    std::stringstream ss;
    unsigned char* bytes = static_cast<unsigned char*>(params);
    ss << "Params[" << size << " bytes]: ";
    
                                                   
    size_t dumpSize = (size > 128) ? 128 : size;
    for (size_t i = 0; i < dumpSize; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)bytes[i] << " ";
        if ((i + 1) % 16 == 0) ss << "\n                    ";
    }
    if (size > 128) ss << "... (truncated)";
    
    return ss.str();
}

                                                     
void InitializePsyNetDump()
{
                                                                         
    
                         
    Events.HookEventPost("Function ProjectX.RPC_X.RPC", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        
        UObject* caller = event.Caller();
        void* params = event.Params();
        std::string callerInfo = caller ? caller->GetFullName() : "[null]";
        std::string paramData = DumpParamsHex(params, 256);
        
        PsyNetDumper::DumpRequest("ProjectX.RPC_X.RPC", 
            "Caller: " + callerInfo + "\n                " + paramData);
    });
    
    Events.HookEventPost("Function ProjectX.RPC_X.SendRequest", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpRequest("SendRequest", DumpParamsHex(event.Params(), 256));
    });
    
                              
    Events.HookEventPost("Function ProjectX.GFxData_PsyNet_X.SendPsyNetMessage", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpRequest("SendPsyNetMessage", DumpParamsHex(event.Params(), 512));
    });
    
    Events.HookEventPost("Function ProjectX.GFxData_PsyNet_X.HandlePsyNetMessage", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpResponse("HandlePsyNetMessage", DumpParamsHex(event.Params(), 512));
    });
    
                              
    Events.HookEventPost("Function TAGame.GFxData_PsyNet_TA.HandleRewardResult", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpResponse("HandleRewardResult", DumpParamsHex(event.Params(), 512));
    });
    
    Events.HookEventPost("Function TAGame.GFxData_PsyNet_TA.HandleProductResult", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpResponse("HandleProductResult", DumpParamsHex(event.Params(), 512));
    });
    
                        
    Events.HookEventPost("Function TAGame.PRI_TA.ClientLoadoutsChanged", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpResponse("ClientLoadoutsChanged", DumpParamsHex(event.Params(), 512));
    });
    
    Events.HookEventPost("Function TAGame.PRI_TA.ClientLoadoutOnlineChanged", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpResponse("ClientLoadoutOnlineChanged", DumpParamsHex(event.Params(), 512));
    });
    
                            
    Events.HookEventPost("Function ProjectX.OnlineGameParty_X.UpdatePartyConfig", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpRequest("UpdatePartyConfig", DumpParamsHex(event.Params(), 256));
    });
    
    Events.HookEventPost("Function ProjectX.OnlineGameParty_X.SendMessage", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpRequest("Party.SendMessage", DumpParamsHex(event.Params(), 512));
    });
    
                             
    Events.HookEventPost("Function TAGame.ProductDatabase_TA.SetProductData", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpResponse("SetProductData", DumpParamsHex(event.Params(), 512));
    });
    
    Events.HookEventPost("Function TAGame.ProductDatabase_TA.AddProduct", [](const PostEvent& event) {
        if (!PsyNetDumper::IsEnabled()) return;
        PsyNetDumper::DumpResponse("AddProduct", DumpParamsHex(event.Params(), 256));
    });
    
    Console.Success("[PsyNet] Comprehensive dump hooks installed");
    Console.Write("[PsyNet] Capturing: RPC, Messages, Rewards, Loadouts, Products, Party");
    Console.Write("[PsyNet] Enable via GUI checkbox -> kingmod/psynet_dump.txt");
}
