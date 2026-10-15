#pragma once
#include <cstdint>                                                       
#include <cwchar>                
#include "RLSDK/SDK_HEADERS/SdkHeaders.hpp"

                                                                                      
                                                       
                                                                                      

constexpr int MAX_NAME_LENGTH = 32;                                                 
constexpr int MAX_PLAYERS = 10;
constexpr int MAX_BOOSTS = 50;
constexpr int MAX_TILES = 200;
constexpr int MAX_TEAMS = 2;
constexpr int MAX_GOALS = 200;

                                                                                      
                                                                     
                                                                                      

                                                                              
                                           
#pragma pack(push, 4)

struct Vector3 {
    float x;
    float y;
    float z;
};

                       
struct GameRotator {
    float pitch;
    float yaw;
    float roll;
};

struct Physics {
    Vector3 location;
    GameRotator rotation;
    Vector3 velocity;
    Vector3 angular_velocity;
};

struct Touch {
    wchar_t player_name[MAX_NAME_LENGTH];
    float time_seconds;
    Vector3 hit_location;
    Vector3 hit_normal;
    int32_t team;
    int32_t player_index;
};

struct ScoreInfo {
    int32_t score;
    int32_t goals;
    int32_t own_goals;
    int32_t assists;
    int32_t saves;
    int32_t shots;
    int32_t demolitions;
};

struct BoxShape {
    float length;
    float width;
    float height;
};

struct SphereShape {
    float diameter;
};

struct CylinderShape {
    float diameter;
    float height;
};

enum class ShapeType : int32_t {
    Box = 0,
    Sphere = 1,
    Cylinder = 2
};

struct CollisionShape {
    ShapeType type;
    union {
        BoxShape box;
        SphereShape sphere;
        CylinderShape cylinder;
    };
};

struct PlayerInfo {
    Physics physics;
    ScoreInfo score_info;
    bool is_demolished;
    bool has_wheel_contact;
    bool is_super_sonic;
    bool is_bot;
    bool jumped;
    bool double_jumped;
                                             
    std::string name;             
    uint8_t team;
    int32_t boost;
    BoxShape hitbox;
    Vector3 hitbox_offset;
    int32_t spawn_id;
    APRI_TA* PRI;
};

struct DropShotInfo {
    float absorbed_force;
    int32_t damage_index;
    float force_accum_recent;
};

struct BallInfo {
    Physics physics;
    Touch latest_touch;
    DropShotInfo drop_shot_info;
    CollisionShape collision_shape;
};

struct BoostPadState {
    bool is_active;
    float timer;
};

struct TileInfo {
    int32_t tile_state;
};

struct TeamInfo {
    int32_t team_index;
    int32_t score;
};

struct GameInfo {
    float seconds_elapsed;
    float game_time_remaining;
    bool is_overtime;
    bool is_unlimited_time;
    bool is_round_active;
    bool is_kickoff_pause;
    bool is_match_ended;
    float world_gravity_z;
    float game_speed;
    int32_t frame_num;
};

struct GameTickPacket {
    PlayerInfo game_cars[MAX_PLAYERS];
    int32_t num_cars;
    BoostPadState game_boosts[MAX_BOOSTS];
    int32_t num_boost;
    BallInfo game_ball;
    GameInfo game_info;
    TileInfo dropshot_tiles[MAX_TILES];
    int32_t num_tiles;
    TeamInfo teams[MAX_TEAMS];
    int32_t num_teams;
    std::string localPlayerName;
    int32_t localPlayerIndex;
                              
    int32_t localPlayerIndices[MAX_PLAYERS];
    std::string localPlayerNames[MAX_PLAYERS];
    int32_t num_local_players;
};

                                

struct BoostPad {
    Vector3 location;
    bool is_full_boost;
};

struct GoalInfo {
    uint8_t team_num;
    Vector3 location;
    Vector3 direction;
    float width;
    float height;
};

struct ControllerInput {
    float Throttle;
    float Steer;
    float Pitch;
    float Yaw;
    float Roll;
    bool Jump;
    bool Boost;
    bool Handbrake;
    bool UseItem;
};

                                               
struct MultiControllerInput {
    ControllerInput inputs[MAX_PLAYERS];
    int32_t num_inputs;
};

struct FieldInfoPacket {
    BoostPad boost_pads[MAX_BOOSTS];
    int32_t num_boosts;
    GoalInfo goals[MAX_GOALS];
    int32_t num_goals;
};

                          
#pragma pack(pop)