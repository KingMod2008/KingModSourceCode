#include "RankChanger.hpp"
#include "../Includes.hpp"

RankChangerComponent RankChanger;

RankChangerComponent::RankChangerComponent() : Component("RankChanger", "Rank changing functionality")
{
}

RankChangerComponent::~RankChangerComponent()
{
}

void RankChangerComponent::OnCreate()
{
                           
}

void RankChangerComponent::OnDestroy()
{
              
}

#pragma region Rank Editor Functions
void RankChangerComponent::ResetRank()
{
                
    UOnlineGameSkill_TA* getSkill = Instances.GetInstanceOf<UOnlineGameSkill_TA>();
    if (getSkill)
    {
        FUniqueNetId playerID;
        if (ULocalPlayer* lp = Instances.IULocalPlayer()) {
            playerID = lp->eventGetUniqueNetId();
        }
        getSkill->SyncPlayerSkill(playerID, getSkill->__EventSkillSynced__Delegate);
    }
    Console.Write("Rank has been reset");
}

void RankChangerComponent::ChangeRank()
{
                                          
    UOnlineGameSkill_TA* getSkill = Instances.GetInstanceOf<UOnlineGameSkill_TA>();
    UOnlineGamePlaylists_TA* playlists = Instances.GetInstanceOf<UOnlineGamePlaylists_TA>();

    if (playlists)
    {
                                          
        for (int i = 0; i < playlists->DownloadedPlaylists.size(); i++)
        {
            UGameSettingPlaylist_X* playlist = playlists->DownloadedPlaylists[i];
            if (playlist)
            {
                std::string playlistitle = std::string(playlist->Title.ToString() + " (" + (playlist->bRanked == 0 ? "Casual" : "Comp") + ")");

                if (playlistitle == RankChanger.selectedplaylisttoedit)
                {
                    float finalmmr = (float)(RankChanger.custommmr - 100) / 20;

                    FUniqueNetId playerID;
                    if (ULocalPlayer* lp = Instances.IULocalPlayer()) {
                        playerID = lp->eventGetUniqueNetId();
                    }
                    FUpdatedPlayerSkillRating rating;
                    rating.Tier                   = RankChanger.customrank;
                    rating.Division               = RankChanger.customrankplaylist - 1;
                    rating.MatchesPlayed          = RankChanger.matchesPlayed;
                    rating.PlacementMatchesPlayed = RankChanger.seasonalwins;
                    rating.WinStreak              = RankChanger.winStreak;
                    rating.Mu                     = finalmmr;
                    rating.Sigma                  = finalmmr;
                    rating.MMR                    = finalmmr;
                    rating.PlayerID               = playerID;
                    rating.PrevMu                 = finalmmr;
                    rating.PrevSigma              = finalmmr;
                    rating.PrevTier               = RankChanger.customrank;
                    rating.PrevDivision           = RankChanger.customrankplaylist - 1;

                    getSkill->ClientSetSkill(rating, playlist->PlaylistId);
                    getSkill->EventPlayerSkillUpdated(playerID, rating);

                    Console.Write("[Rank Editor] Changed rank for " + playlistitle);
                    break;
                }
            }
        }
    }
}

void RankChangerComponent::ChangeRankAllPlaylists()
{
    UOnlineGameSkill_TA* getSkill = Instances.GetInstanceOf<UOnlineGameSkill_TA>();
    UOnlineGamePlaylists_TA* playlists = Instances.GetInstanceOf<UOnlineGamePlaylists_TA>();
    if (!getSkill || !playlists) return;

    float finalmmr = (float)(RankChanger.custommmr - 100) / 20;
    FUniqueNetId playerID;
    if (ULocalPlayer* lp = Instances.IULocalPlayer()) {
        playerID = lp->eventGetUniqueNetId();
    }

    for (int i = 0; i < playlists->DownloadedPlaylists.size(); i++)
    {
        UGameSettingPlaylist_X* playlist = playlists->DownloadedPlaylists[i];
        if (!playlist) continue;

        FUpdatedPlayerSkillRating rating;
        rating.Tier                   = RankChanger.customrank;
        rating.Division               = RankChanger.customrankplaylist - 1;
        rating.MatchesPlayed          = RankChanger.matchesPlayed;
        rating.PlacementMatchesPlayed = RankChanger.seasonalwins;
        rating.WinStreak              = RankChanger.winStreak;
        rating.Mu                     = finalmmr;
        rating.Sigma                  = finalmmr;
        rating.MMR                    = finalmmr;
        rating.PlayerID               = playerID;
        rating.PrevMu                 = finalmmr;
        rating.PrevSigma              = finalmmr;
        rating.PrevTier               = RankChanger.customrank;
        rating.PrevDivision           = RankChanger.customrankplaylist - 1;

        getSkill->ClientSetSkill(rating, playlist->PlaylistId);
        getSkill->EventPlayerSkillUpdated(playerID, rating);
    }
    Console.Write("[Rank Editor] Applied rank to all playlists");
}

void RankChangerComponent::ApplyRewards()
{
    UOnlineGameSkill_TA* getSkill = Instances.GetInstanceOf<UOnlineGameSkill_TA>();
    if (!getSkill) return;
    FPlayerSeasonRewardProgress progress;
    FUniqueNetId playerID;
    if (ULocalPlayer* lp = Instances.IULocalPlayer()) {
        playerID = lp->eventGetUniqueNetId();
    }
    progress.PlayerID        = playerID;
    progress.SeasonLevelWins = RankChanger.rewardWins;
    progress.SeasonLevel     = RankChanger.seasonrewards;
    getSkill->SetPlayerSeasonReward(progress);
    Console.Write("[Rank Editor] Applied season rewards");
}
#pragma endregion
