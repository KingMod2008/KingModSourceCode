#pragma once
#include <string>
#include <vector>
#include <cstdint>

                                                                            
                                                                 
                                                              
namespace Notify
{
                               
    enum class Style
    {
        Info,            
        Success,          
        Warning,          
        Error,          
        Discord,            
        Custom                            
    };

                                         
    enum class Kind
    {
        Toast,                                             
        Popup                                                                    
    };

                                                              
    void Toast(const std::string& title,
               const std::string& body,
               Style style = Style::Info,
               float durationSec = 5.0f);

                                                                 
    void ToastColored(const std::string& title,
                      const std::string& body,
                      uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255,
                      float durationSec = 5.0f);

                                                                                
                                                          
    void Popup(const std::string& title,
               const std::string& body,
               Style style = Style::Info,
               const std::vector<std::string>& buttons = {},
               const std::vector<std::string>& citations = {});

    void PopupColored(const std::string& title,
                      const std::string& body,
                      uint8_t r, uint8_t g, uint8_t b, uint8_t a,
                      const std::vector<std::string>& buttons = {},
                      const std::vector<std::string>& citations = {});

                                                                            
    void Render();

                                                                             
                                                                         
    bool HasPopup();

                                           
    void Clear();
}
