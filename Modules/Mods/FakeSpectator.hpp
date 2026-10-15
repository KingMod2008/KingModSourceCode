#pragma once
#include "../Module.hpp"
#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"

namespace FakeSpectator
{
	                                                                          
	                                                                            
	                                                                        
	                                                                            
	void SetEnabled(bool enabled);
	bool IsEnabled();

	bool Create(AGameEvent_Soccar_TA* gameEvent);
	void Remove();

	APRI_TA* Get();
	bool IsFake(APRI_TA* pri);
}
