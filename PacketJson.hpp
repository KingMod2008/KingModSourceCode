#pragma once
#include "GamePacket.hpp"
#include "nlohmann/json.hpp"
#include <string>
#include <vector>

                                                         
#include <Windows.h>

                  
using json = nlohmann::json;

                                                                         
inline std::string safe_wchar_to_utf8(const wchar_t* wstr, size_t max_len) {
    if (!wstr || wstr[0] == L'\0') {
        return "";
    }

                                                        
    size_t wstr_len = wcsnlen(wstr, max_len);
    if (wstr_len == 0) {
        return "";
    }

                              
    int size_needed = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, wstr, (int)wstr_len, NULL, 0, NULL, NULL);

    if (size_needed == 0) {
                                                                                        
        return std::string(wstr_len, '?');
    }

    std::string result;
    result.resize(size_needed);
    int converted = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, wstr, (int)wstr_len, &result[0], size_needed, NULL, NULL);

    if (converted == 0) {
                                                                                        
        return std::string(wstr_len, '?');
    }

    return result;
}

                                                                         
inline std::wstring safe_utf8_to_wchar(const std::string& utf8_str) {
    if (utf8_str.empty()) {
        return L"";
    }

                                
    int size_needed = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8_str.c_str(), (int)utf8_str.size(), NULL, 0);

    if (size_needed == 0) {
                                                                                        
        return std::wstring(utf8_str.size(), L'?');
    }

    std::wstring result;
    result.resize(size_needed);
    int converted = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8_str.c_str(), (int)utf8_str.size(), &result[0], size_needed);

    if (converted == 0) {
                                                                                        
        return std::wstring(utf8_str.size(), L'?');
    }

    return result;
}

                                               

                                 
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Vector3, x, y, z)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameRotator, pitch, yaw, roll)

                                         
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Physics, location, rotation, velocity, angular_velocity)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ScoreInfo, score, goals, own_goals, assists, saves, shots, demolitions)

                                                          
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BoxShape, length, width, height)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SphereShape, diameter)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CylinderShape, diameter, height)

                                                  
NLOHMANN_JSON_SERIALIZE_ENUM(ShapeType, {
    {ShapeType::Box, "Box"},
    {ShapeType::Sphere, "Sphere"},
    {ShapeType::Cylinder, "Cylinder"},
    })

                                                                 
    inline void to_json(json& j, const CollisionShape& p) {
    j = json{ {"type", p.type} };
    switch (p.type) {
    case ShapeType::Box:      j["shape"] = p.box;      break;
    case ShapeType::Sphere:   j["shape"] = p.sphere;   break;
    case ShapeType::Cylinder: j["shape"] = p.cylinder; break;
    }
}
inline void from_json(const json& j, CollisionShape& p) {
    j.at("type").get_to(p.type);
    switch (p.type) {
    case ShapeType::Box:      j.at("shape").get_to(p.box);      break;
    case ShapeType::Sphere:   j.at("shape").get_to(p.sphere);   break;
    case ShapeType::Cylinder: j.at("shape").get_to(p.cylinder); break;
    }
}

                                                              
inline void to_json(json& j, const Touch& p) {
    std::string mb_player_name = safe_wchar_to_utf8(p.player_name, MAX_NAME_LENGTH);

    j = json{
        {"player_name", mb_player_name},
        {"time_seconds", p.time_seconds},
        {"hit_location", p.hit_location},
        {"hit_normal", p.hit_normal},
        {"team", p.team},
        {"player_index", p.player_index}
    };
}

                                                        
inline void from_json(const json& j, Touch& p) {
    j.at("time_seconds").get_to(p.time_seconds);
    j.at("hit_location").get_to(p.hit_location);
    j.at("hit_normal").get_to(p.hit_normal);
    j.at("team").get_to(p.team);
    j.at("player_index").get_to(p.player_index);

                                                                              
    std::string mb_player_name = j.at("player_name").get<std::string>();
    std::wstring w_player_name = safe_utf8_to_wchar(mb_player_name);

                                                         
    wcsncpy_s(p.player_name, MAX_NAME_LENGTH, w_player_name.c_str(), _TRUNCATE);
}

                                  
inline void to_json(json& j, const PlayerInfo& p) {
    j = json{
        {"physics", p.physics},
        {"score_info", p.score_info},
        {"is_demolished", p.is_demolished},
        {"has_wheel_contact", p.has_wheel_contact},
        {"is_super_sonic", p.is_super_sonic},
        {"is_bot", p.is_bot},
        {"jumped", p.jumped},
        {"double_jumped", p.double_jumped},
        {"name", p.name},
        {"team", p.team},
        {"boost", p.boost},
        {"hitbox", p.hitbox},
        {"hitbox_offset", p.hitbox_offset},
        {"spawn_id", p.spawn_id}
    };
}

                       
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DropShotInfo, absorbed_force, damage_index, force_accum_recent)

                                     
inline void to_json(json& j, const BallInfo& p) {
    j = json{
        {"physics", p.physics},
        {"drop_shot_info", p.drop_shot_info},
        {"collision_shape", p.collision_shape}
    };
}
inline void from_json(const json& j, BallInfo& p) {
    j.at("physics").get_to(p.physics);
    j.at("drop_shot_info").get_to(p.drop_shot_info);
    j.at("collision_shape").get_to(p.collision_shape);
}

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BoostPadState, is_active, timer)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TileInfo, tile_state)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TeamInfo, team_index, score)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameInfo, seconds_elapsed, game_time_remaining, is_overtime, is_unlimited_time, is_round_active, is_kickoff_pause, is_match_ended, world_gravity_z, game_speed, frame_num)

                                       
inline void to_json(json& j, const GameTickPacket& p) {
    j = json{
        {"num_cars", p.num_cars},
        {"num_boost", p.num_boost},
        {"game_ball", p.game_ball},
        {"game_info", p.game_info},
        {"num_tiles", p.num_tiles},
        {"num_teams", p.num_teams},
        {"localPlayerName", p.localPlayerName},
        {"localPlayerIndex", p.localPlayerIndex},
        {"num_local_players", p.num_local_players}
    };
    j["game_cars"] = json::array();
    for (int i = 0; i < p.num_cars; ++i) j["game_cars"].push_back(p.game_cars[i]);

    j["game_boosts"] = json::array();
    for (int i = 0; i < p.num_boost; ++i) j["game_boosts"].push_back(p.game_boosts[i]);

    j["dropshot_tiles"] = json::array();
    for (int i = 0; i < p.num_tiles; ++i) j["dropshot_tiles"].push_back(p.dropshot_tiles[i]);

    j["teams"] = json::array();
    for (int i = 0; i < p.num_teams; ++i) j["teams"].push_back(p.teams[i]);

                              
    j["localPlayerIndices"] = json::array();
    for (int i = 0; i < p.num_local_players; ++i) j["localPlayerIndices"].push_back(p.localPlayerIndices[i]);

    j["localPlayerNames"] = json::array();
    for (int i = 0; i < p.num_local_players; ++i) j["localPlayerNames"].push_back(p.localPlayerNames[i]);
}

                                
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ControllerInput, Throttle, Steer, Pitch, Yaw, Roll, Jump, Boost, Handbrake, UseItem)

                                             
inline void to_json(json& j, const MultiControllerInput& p) {
    j = json{
        {"num_inputs", p.num_inputs}
    };
    j["inputs"] = json::array();
    for (int i = 0; i < p.num_inputs; ++i) j["inputs"].push_back(p.inputs[i]);
}

inline void from_json(const json& j, MultiControllerInput& p) {
    j.at("num_inputs").get_to(p.num_inputs);
    auto inputs_array = j.at("inputs");
    for (int i = 0; i < p.num_inputs && i < MAX_PLAYERS; ++i) {
        inputs_array[i].get_to(p.inputs[i]);
    }
}

                    
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BoostPad, location, is_full_boost)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GoalInfo, team_num, location, direction, width, height)

                                        
inline void to_json(json& j, const FieldInfoPacket& p) {
    j = json{
        {"num_boosts", p.num_boosts},
        {"num_goals", p.num_goals}
    };
    j["boost_pads"] = json::array();
    for (int i = 0; i < p.num_boosts; ++i) j["boost_pads"].push_back(p.boost_pads[i]);

    j["goals"] = json::array();
    for (int i = 0; i < p.num_goals; ++i) j["goals"].push_back(p.goals[i]);
}