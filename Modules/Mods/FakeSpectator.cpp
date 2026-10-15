#include "FakeSpectator.hpp"
#include "../../Components/Components/Events.hpp"
#include "../../Components/Components/Instances.hpp"

namespace FakeSpectator
{
	static APRI_TA* g_FakePRI = nullptr;
	static const char* kFakeName = "[Admin]KingMod";

	                                                                         
	                                                                       
	                                                                     
	static bool g_Enabled = false;

	void SetEnabled(bool enabled)
	{
		g_Enabled = enabled;
		if (!g_Enabled)
			Remove();
	}

	bool IsEnabled()
	{
		return g_Enabled;
	}

	APRI_TA* Get()
	{
		return g_FakePRI;
	}

	bool IsFake(APRI_TA* pri)
	{
		return pri && pri == g_FakePRI;
	}

	bool Create(AGameEvent_Soccar_TA* gameEvent)
	{
		if (!g_Enabled)
			return false;

		if (!gameEvent)
			return false;

		if (gameEvent->bDeleteMe)
			return false;

		if (g_FakePRI && !g_FakePRI->bDeleteMe)
			return true;

		g_FakePRI = nullptr;

		AActor* spawned = gameEvent->Spawn(
			APRI_TA::StaticClass(),
			gameEvent,
			FName(),
			FVector(),
			FRotator(),
			nullptr,
			true
		);

		if (!spawned)
			return false;

		if (!spawned->IsA<APRI_TA>())
		{
			spawned->Destroy();
			return false;
		}

		APRI_TA* pri =
			static_cast<APRI_TA*>(spawned);

		pri->eventSetPlayerName(
			FString(kFakeName)
		);

		pri->OldName =
			FString(kFakeName);

		pri->bIsSpectator = true;
		pri->bOnlySpectator = true;

		pri->bWaitingPlayer = false;
		pri->bReadyToPlay = true;

		pri->bBot = true;

		pri->bIsInactive = false;
		pri->bTimedOut = false;

		pri->Team = nullptr;
		pri->Car = nullptr;

		pri->GameEvent = gameEvent;
		pri->ReplicatedGameEvent = gameEvent;

		pri->bAdmin = true;
		pri->bMatchAdmin = true;

		pri->Score = 0;
		pri->MatchScore = 0;

		pri->MatchGoals = 0;
		pri->MatchAssists = 0;
		pri->MatchSaves = 0;
		pri->MatchShots = 0;
		pri->MatchDemolishes = 0;

		                                                                         
		                                                                       
		                                                                     
		                                                                          
		                                                                          
		                                                                          
		                                                                       
		FUniqueNetId fakeId = {};
		                                                                         
		                                                                         
		                                                                           
		                                                                       
		fakeId.Uid = 0x011000014B696E67ULL;                                             
		fakeId.Platform = EOnlinePlatform::OnlinePlatform_Steam;

		pri->SetUniqueId(fakeId);                                                                
		pri->UniqueId = fakeId;                                                                    
		pri->PlayerID = 0x4B4D;                                                            

		gameEvent->AddPRI(pri);

		pri->bForceNetUpdate = true;                                                        

		g_FakePRI = pri;

		                                                                         
		                                                                         
		                                                                         
		                                                                         
		                                                                        
		                                                              
		if (AGFxHUD_TA* hud = Instances.GetInstanceOf<AGFxHUD_TA>())
		{
			try { hud->HandlePlayerAdded(gameEvent, pri); } catch (...) {}
			try { hud->UpdatePRIData(); } catch (...) {}
		}

		return true;
	}

	void Remove()
	{
		APRI_TA* pri = g_FakePRI;

		g_FakePRI = nullptr;

		if (!pri)
			return;

		if (pri->bDeleteMe)
			return;

		AGameEvent_TA* gameEvent =
			pri->GameEvent;

		if (gameEvent &&
			!gameEvent->bDeleteMe)
		{
			gameEvent->RemovePRI(pri);
		}

		if (!pri->bDeleteMe)
		{
			pri->Destroy();
		}


	}
}
