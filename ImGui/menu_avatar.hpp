#pragma once

#include <cstdint>
#include <cstddef>

struct ID3D11ShaderResourceView;

namespace menu_avatar
{
                                                                            
                                                                                
                                                                          
      
                                                                         
                                                                     
                                                                                
                         
    ID3D11ShaderResourceView* CreateTextureFromMemory(const void* data, size_t size,
                                                      int* outWidth = nullptr,
                                                      int* outHeight = nullptr);

                                                                               
                                                                              
    void Update();

                                                                 
    const char* Name();

                                                          
    int Platform();

                                          
    uint64_t SteamId();

                                                                          
                                                               
    ID3D11ShaderResourceView* Texture();

                                                                       
    void Shutdown();
}
