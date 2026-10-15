#pragma once
#include "../Component.hpp"
#include <vector>
#include <string>

class RankChangerComponent : public Component
{
public:
    RankChangerComponent();
    ~RankChangerComponent() override;

public:
    void OnCreate() override;
    void OnDestroy() override;

                              
    void ResetRank();
    void ChangeRank();
    void ChangeRankAllPlaylists();
    void ApplyRewards();

public:
                            
    int custommmr = 100;
    int customrank = 1;
    int seasonrewards = 1;
    int customrankplaylist = 1;
    int seasonalwins = 10;
    int matchesPlayed = 100;
    int winStreak = 0;
    int rewardWins = 0;

    FUniqueNetId netid;
    std::vector<std::string> PlaylistsForRankEditing;
    std::string selectedplaylisttoedit;
};

extern class RankChangerComponent RankChanger;
