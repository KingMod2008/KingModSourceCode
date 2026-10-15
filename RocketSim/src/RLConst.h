#pragma once
#include "BaseInc.h"
#include "Math/Math.h"

RS_NS_START

                                        

namespace RLConst {
	constexpr float

		GRAVITY_Z = -650.f,

		ARENA_EXTENT_X = 4096,
		ARENA_EXTENT_Y = 5120,                               
		ARENA_HEIGHT = 2048,

		ARENA_EXTENT_X_HOOPS = (8900 / 3.f),
		ARENA_EXTENT_Y_HOOPS = 3581,
		ARENA_HEIGHT_HOOPS = 1820,

		ARENA_HEIGHT_DROPSHOT = 2024,
		FLOOR_HEIGHT_DROPSHOT = 1.5f,

		ARENA_COLLISION_BASE_FRICTION = 0.6f,
		ARENA_COLLISION_BASE_RESTITUTION = 0.3f,

		CAR_MASS_BT = 180.f,
		BALL_MASS_BT = CAR_MASS_BT / 6.f,                                                                                         

		CAR_COLLISION_FRICTION = 0.3f,
		CAR_COLLISION_RESTITUTION = 0.1f,

		CARBALL_COLLISION_FRICTION = 2.0f,
		CARBALL_COLLISION_RESTITUTION = 0.0f,

		CARWORLD_COLLISION_FRICTION = 0.3f,
		CARWORLD_COLLISION_RESTITUTION = 0.3f,

		CARCAR_COLLISION_FRICTION = 0.09f,
		CARCAR_COLLISION_RESTITUTION = 0.1f,

		BALL_REST_Z = 93.15f,                                                                   
		BALL_MAX_ANG_SPEED = 6.f,                                                           
		BALL_DRAG = 0.03f,                                
		BALL_FRICTION = 0.35f,
		BALL_RESTITUTION = 0.6f,                 

		                                                                                    
		BALL_HOOPS_LAUNCH_Z_VEL = 1000,                                              
		BALL_HOOPS_LAUNCH_DELAY = 0.265f,

		CAR_MAX_SPEED = 2300.f,
		BALL_MAX_SPEED = 6000.f,

		BOOST_MAX = 100.f,
		BOOST_USED_PER_SECOND = BOOST_MAX / 3,
		BOOST_MIN_TIME = 0.1f,                                       
		BOOST_ACCEL_GROUND = 2975/3.f,                                
		BOOST_ACCEL_AIR = 3175/3.f,                           
		BOOST_SPAWN_AMOUNT = BOOST_MAX / 3,

		RECHARGE_BOOST_PER_SECOND = 10,                                                        
		RECHARGE_BOOST_DELAY = 0.25,                                      

		CAR_MAX_ANG_SPEED = 5.5f,                                                          

		                                         
		SUPERSONIC_START_SPEED = 2200.f,

		                                                                                                   
		                                                    
		SUPERSONIC_MAINTAIN_MIN_SPEED = SUPERSONIC_START_SPEED - 100.f,

		                                                                                                                         
		SUPERSONIC_MAINTAIN_MAX_TIME = 1.f,

		                                                  
		                                                                        
		                                                                                                         
		POWERSLIDE_RISE_RATE = 5,
		POWERSLIDE_FALL_RATE = 2,

		THROTTLE_TORQUE_AMOUNT = CAR_MASS_BT * 400.f,
		BRAKE_TORQUE_AMOUNT = CAR_MASS_BT * (14.25f + (1.f / 3.f)),

		STOPPING_FORWARD_VEL = 25.f,                                                                    
		COASTING_BRAKE_FACTOR = 0.15f,                                              
		BRAKING_NO_THROTTLE_SPEED_THRESH = 0.01f,                                                                   
		THROTTLE_DEADZONE = 0.001f,                                               
		
		THROTTLE_AIR_ACCEL = 200/3.f,

		JUMP_ACCEL = 4375.f / 3.f,
		JUMP_IMMEDIATE_FORCE = 875.f / 3.f,
		JUMP_MIN_TIME = 0.025f,
		JUMP_RESET_TIME_PAD = (1 / 40.f),
		JUMP_MAX_TIME = 0.2f,
		DOUBLEJUMP_MAX_DELAY = 1.25f,                                                          

		                                                                                              
		FLIP_Z_DAMP_120 = 0.35f,
		FLIP_Z_DAMP_START = 0.15f,
		FLIP_Z_DAMP_END = 0.21f,
		FLIP_TORQUE_TIME = 0.65f,
		FLIP_TORQUE_MIN_TIME = 0.41f,
		FLIP_PITCHLOCK_TIME = 1.f,
		FLIP_PITCHLOCK_EXTRA_TIME = 0.3f,
		FLIP_INITIAL_VEL_SCALE = 500.f,
		FLIP_TORQUE_X = 260.f,              
		FLIP_TORQUE_Y = 224.f,                    
		FLIP_FORWARD_IMPULSE_MAX_SPEED_SCALE = 1.f,
		FLIP_SIDE_IMPULSE_MAX_SPEED_SCALE = 1.9f,
		FLIP_BACKWARD_IMPULSE_MAX_SPEED_SCALE = 2.5f,
		FLIP_BACKWARD_IMPULSE_SCALE_X = 16.f / 15.f,

		BALL_COLLISION_RADIUS_SOCCAR = 91.25f,
		BALL_COLLISION_RADIUS_HOOPS = 96.3831f,
		BALL_COLLISION_RADIUS_DROPSHOT = 100.2565f,

		SOCCAR_GOAL_SCORE_BASE_THRESHOLD_Y = 5124.25f,
		HOOPS_GOAL_SCORE_THRESHOLD_Z = 270.f,

		CAR_TORQUE_SCALE = 2 * M_PI / (1 << 16) * 1000,

		CAR_AUTOFLIP_IMPULSE = 200,
		CAR_AUTOFLIP_TORQUE = 50,
		CAR_AUTOFLIP_TIME = 0.4f,
		CAR_AUTOFLIP_NORMZ_THRESH = M_SQRT1_2,
		CAR_AUTOFLIP_ROLL_THRESH = 2.8f,

		CAR_AUTOROLL_FORCE = 100,
		CAR_AUTOROLL_TORQUE = 80,

		BALL_CAR_EXTRA_IMPULSE_Z_SCALE = 0.35f,
		BALL_CAR_EXTRA_IMPULSE_Z_SCALE_HOOPS_GROUND = BALL_CAR_EXTRA_IMPULSE_Z_SCALE * 1.55f,
		BALL_CAR_EXTRA_IMPULSE_FORWARD_SCALE = 0.65f,
		BALL_CAR_EXTRA_IMPULSE_MAXDELTAVEL_UU = 4600.f,
		BALL_CAR_EXTRA_IMPULSE_Z_SCALE_HOOPS_NORMAL_Z_THRESH = 0.1f,

		CAR_SPAWN_REST_Z = 17.f,
		CAR_RESPAWN_Z = 36.f,

		BUMP_COOLDOWN_TIME = 0.25f,
		BUMP_MIN_FORWARD_DIST = 64.5f,
		DEMO_RESPAWN_TIME = 3.f;

	                           
	constexpr Vec
		CAR_AIR_CONTROL_TORQUE = Vec(130, 95, 400),
		CAR_AIR_CONTROL_DAMPING = Vec(30, 20, 50);

	                                                                                                
	                                     
	namespace BTVehicle {
		                                                                     
		constexpr float
			SUSPENSION_FORCE_SCALE_FRONT = 36.f - (1.f / 4.f),
			SUSPENSION_FORCE_SCALE_BACK = 54.f + (1.f / 4.f) + (1.5f / 100.f),

			SUSPENSION_STIFFNESS = 500.f,
			WHEELS_DAMPING_COMPRESSION = 25.f,
			WHEELS_DAMPING_RELAXATION = 40.f,
			MAX_SUSPENSION_TRAVEL = 12.f,                                                    
			SUSPENSION_SUBTRACTION = 0.05f;
	}

	namespace Heatseeker {
		constexpr float
			INITIAL_TARGET_SPEED = 2900,                                                                          
			TARGET_SPEED_INCREMENT = 85,                                       
			MIN_SPEEDUP_INTERVAL = 1,                                            
			TARGET_Y = 5120,                             
			TARGET_Z = 320,                                  
			HORIZONTAL_BLEND = 1.45f,                                             
			VERTICAL_BLEND = 0.78f,                                         
			SPEED_BLEND = 0.3f,                                                      
			MAX_TURN_PITCH = 7000 * M_PI / (1 << 15),                                  
			MAX_SPEED = 4600,                                                                      
			WALL_BOUNCE_CHANGE_Y_THRESH = 300,                                                                          
			WALL_BOUNCE_CHANGE_Y_NORMAL = 0.5f,                                                
			WALL_BOUNCE_FORCE_SCALE = 1 / 3.f,                                          
			WALL_BOUNCE_UP_FRAC = 0.3f;                                                           

		                       
		constexpr Vec
			BALL_START_POS = Vec(-1000, -2220, 92.75f),
			BALL_START_VEL = Vec(0, -65, 650);
	}

	namespace Snowday {
		constexpr float
			PUCK_RADIUS = 114.25f,                                                                             
			PUCK_HEIGHT = 62.5f,
			PUCK_CIRCLE_POINT_AMOUNT = 20,                                                   
			PUCK_MASS_BT = 50,
			PUCK_GROUND_STICK_FORCE = 70,
			PUCK_FRICTION = 0.1f,
			PUCK_RESTITUTION = 0.3f;
	}

	namespace Dropshot {

		                                                                                   
		                                                      
		              
		                                                                                                                               
			
		constexpr float BALL_LAUNCH_Z_VEL = 985.f;
		constexpr float BALL_LAUNCH_DELAY = 0.26f;

		constexpr float MIN_DOWNWARD_SPEED_TO_DAMAGE = 250;                                          
		constexpr float MIN_CHARGE_HIT_SPEED = 500;                                                                       
		constexpr float MIN_ABSORBED_FORCE_FOR_CHARGE = 2500;                                                          
		constexpr float MIN_ABSORBED_FORCE_FOR_SUPERCHARGE = 11000;                                                   
		constexpr float MIN_DAMAGE_INTERVAL = 0.1f;                                       

		            

		constexpr int 
			NUM_TILES_PER_TEAM = 70,
			TEAM_AMOUNT = 2;

		                                                         
		constexpr Vec TILE_HEXAGON_AABB_MAX = Vec(7.6643f, 8.85f, 0.f);

		                                          
		constexpr Vec TILE_HEXAGON_VERTS_BT[6] = {
			{  0.0f,    -8.85f,  0.f},
			{  7.6643f, -4.425f, 0.f},
			{  7.6643f,  4.425f, 0.f},
			{  0.0f,     8.85f,  0.f},
			{ -7.6643f,  4.425f, 0.f},
			{ -7.6643f, -4.425f, 0.f}
		};                                                                       

		                             
		constexpr float TILE_WIDTH_X = TILE_HEXAGON_VERTS_BT[1].x * 2 * BT_TO_UU;

		                                                           
		                                                                                          
		constexpr float ROW_OFFSET_Y = (TILE_HEXAGON_VERTS_BT[3].y + TILE_HEXAGON_VERTS_BT[4].y) * BT_TO_UU;

		                                                         
		constexpr float TILE_OFFSET_Y = 2.54736f * BT_TO_UU;
		constexpr int TILES_IN_FIRST_ROW = 13;                           
		constexpr int TILES_IN_LAST_ROW = 7;
		constexpr int NUM_TILE_ROWS = TILES_IN_FIRST_ROW - TILES_IN_LAST_ROW + 1;
	}

	namespace BoostPads {
		                                                                                  
		
		constexpr float
			CYL_HEIGHT = 95,
			CYL_RAD_BIG = 208,
			CYL_RAD_SMALL = 144,

			BOX_HEIGHT = 64,
			BOX_RAD_BIG = 160,
			BOX_RAD_SMALL = 120,

			COOLDOWN_BIG = 10,
			COOLDOWN_SMALL = 4,

			BOOST_AMOUNT_BIG = 100,
			BOOST_AMOUNT_SMALL = 12;

		constexpr int
			LOCS_AMOUNT_SMALL_SOCCAR = 28,
			LOCS_AMOUNT_SMALL_HOOPS = 14,
			LOCS_AMOUNT_BIG = 6;

		constexpr Vec LOCS_SMALL_SOCCAR[LOCS_AMOUNT_SMALL_SOCCAR] = {
			{0.f,		-4240.f,	70.f },
			{-1792.f,	-4184.f,	70.f },
			{1792.f,	-4184.f,	70.f },
			{-940.f,	-3308.f,	70.f },
			{940.f,		-3308.f,	70.f },
			{0.f,		-2816.f,	70.f },
			{-3584.f,	-2484.f,	70.f },
			{3584.f,	-2484.f,	70.f },
			{-1788.f,	-2300.f,	70.f },
			{1788.f,	-2300.f,	70.f },
			{-2048.f,	-1036.f,	70.f },
			{0.f,		-1024.f,	70.f },
			{2048.f,	-1036.f,	70.f },
			{-1024.f,	0.f,		70.f },
			{1024.f,	0.f,		70.f },
			{-2048.f,	1036.f,		70.f },
			{0.f,		1024.f,		70.f },
			{2048.f,	1036.f,		70.f },
			{-1788.f,	2300.f,		70.f },
			{1788.f,	2300.f,		70.f },
			{-3584.f,	2484.f,		70.f },
			{3584.f,	2484.f,		70.f },
			{0.f,		2816.f,		70.f },
			{-940.f,	3308.f,		70.f },
			{940.f,		3308.f,		70.f },
			{-1792.f,	4184.f,		70.f },
			{1792.f,	4184.f,		70.f },
			{0.f,		4240.f,		70.f }
		};

		constexpr Vec LOCS_BIG_SOCCAR[LOCS_AMOUNT_BIG] = {
			{-3584.f,     0.f, 73.f },
			{ 3584.f,     0.f, 73.f },
			{-3072.f,  4096.f, 73.f },
			{ 3072.f,  4096.f, 73.f },
			{-3072.f, -4096.f, 73.f },
			{ 3072.f, -4096.f, 73.f }
		};

		constexpr Vec LOCS_SMALL_HOOPS[LOCS_AMOUNT_SMALL_HOOPS] = {
			                                                                                   
			                                                                                             
			{1536,	-1024, 64 },
			{-1280,	-2304, 64 },
			{0,		-2816, 64 },
			{-1536,	-1024, 64 },
			{1280,	-2304, 64 },
			{-512,	  512, 64 },
			{-1536,  1024, 64 },
			{1536,	 1024, 64 },
			{1280,	 2304, 64 },
			{0,		 2816, 64 },
			{512,	  512, 64 },
			{512,	 -512, 64 },
			{-512,	 -512, 64 },
			{-1280,	 2304, 64 }
		};

		constexpr Vec LOCS_BIG_HOOPS[LOCS_AMOUNT_BIG] = {
			{-2176,		 2944, 72 },
			{ 2176,		-2944, 72 },
			{-2176,		-2944, 72 },
			{-2432,			0, 72 },
			{ 2432,			0, 72 },
			{ 2175.99f,	 2944, 72 }
		};
	}

	constexpr int
		CAR_SPAWN_LOCATION_AMOUNT = 5,
		CAR_SPAWN_LOCATION_AMOUNT_HEATSEEKER = 4,
		CAR_RESPAWN_LOCATION_AMOUNT = 4;

	struct CarSpawnPos {
		float x, y;
		float yawAng;
	};

	                                                         
	                                 
	const static CarSpawnPos 
		CAR_SPAWN_LOCATIONS_SOCCAR[CAR_SPAWN_LOCATION_AMOUNT] = {
			{ -2048, -2560, M_PI_4 * 1 },
			{  2048, -2560, M_PI_4 * 3 },
			{  -256, -3840, M_PI_4 * 2 },
			{   256, -3840, M_PI_4 * 2 },
			{     0, -4608, M_PI_4 * 2 }
	};

	const static CarSpawnPos
		CAR_SPAWN_LOCATIONS_HEATSEEKER[CAR_SPAWN_LOCATION_AMOUNT_HEATSEEKER] = {
			{ -1000, -4620, M_PI / 2 },
			{  1000, -4620, M_PI / 2 },
			{ -2000, -4620, M_PI / 2 },
			{  2000, -4620, M_PI / 2 },
	};

	const static CarSpawnPos
		CAR_SPAWN_LOCATIONS_HOOPS[CAR_SPAWN_LOCATION_AMOUNT] = {
			{ -1536, -3072, M_PI_4 * 2 },
			{  1536, -3072, M_PI_4 * 2 },
			{  -256, -2816, M_PI_4 * 2 },
			{   256, -2816, M_PI_4 * 2 },
			{     0, -3200, M_PI_4 * 2 }
	};

	const static CarSpawnPos	
		CAR_SPAWN_LOCATIONS_DROPSHOT[CAR_SPAWN_LOCATION_AMOUNT] = {
			{ -1867, -2380, M_PI_4 * 1 },
			{  1867, -2380, M_PI_4 * 3 },
			{  -256, -3576, M_PI_4 * 2 },
			{   256, -3576, M_PI_4 * 2 },
			{     0, -4088, M_PI_4 * 2 }
	};

	                                                         
	                                 
	const static CarSpawnPos                                  
		CAR_RESPAWN_LOCATIONS_SOCCAR[CAR_RESPAWN_LOCATION_AMOUNT] = {
		{ -2304, -4608, M_PI / 2 },
		{ -2688, -4608, M_PI / 2 },
		{  2304, -4608, M_PI / 2 },
		{  2688, -4608, M_PI / 2 }
	};

	const static CarSpawnPos
		CAR_RESPAWN_LOCATIONS_HOOPS[CAR_RESPAWN_LOCATION_AMOUNT] = {
		{ -1920, -3072, M_PI / 2 },
		{ -1152, -3072, M_PI / 2 },
		{  1920, -3072, M_PI / 2 },
		{  1152, -3072, M_PI / 2 }
	};

	const static CarSpawnPos
		CAR_RESPAWN_LOCATIONS_DROPSHOT[CAR_RESPAWN_LOCATION_AMOUNT] = {
		{ -2176, -3410, M_PI / 2 },
		{ -1152, -3100, M_PI / 2 },
		{  2176, -3410, M_PI / 2 },
		{  1152, -3100, M_PI / 2 }
	};

	                           
	                                       
	const static LinearPieceCurve STEER_ANGLE_FROM_SPEED_CURVE = {
		{
			{0,		0.53356f},
			{500,	0.31930f},
			{1000,	0.18203f},
			{1500,	0.10570f},
			{1750,	0.08507f},
			{3000,	0.03454f}
		}
	};

	const static LinearPieceCurve STEER_ANGLE_FROM_SPEED_CURVE_THREEWHEEL = {
		{
			{0,		0.342473f},
			{2300,	0.034837f}
		}
	};

	                            
	                                            
	const static LinearPieceCurve POWERSLIDE_STEER_ANGLE_FROM_SPEED_CURVE = {
		{
			{0,		0.39235f},
			{2500,	0.12610f},
		}
	};

	                            
	                        
	const static LinearPieceCurve DRIVE_SPEED_TORQUE_FACTOR_CURVE = {
		{
			{0,		1.0f},
			{1400,	0.1f},
			{1410,	0.0f}
		}
	};

	const static LinearPieceCurve NON_STICKY_FRICTION_FACTOR_CURVE = {
		{
			{0,			0.1f},
			{0.7075f,	0.5f},
			{1,			1.0f}
		}
	};

	const static LinearPieceCurve LAT_FRICTION_CURVE = {
		{
			{0,	1.0f},
			{1,	0.2f},
		}
	};

	const static LinearPieceCurve LAT_FRICTION_CURVE_THREEWHEEL = {
		{
			{0,	0.30f},
			{1,	0.25f},
		}
	};

	const static LinearPieceCurve LONG_FRICTION_CURVE = {
		{
			              
		}
	};

	const static LinearPieceCurve HANDBRAKE_LAT_FRICTION_FACTOR_CURVE = {
		{
			{0,	0.1f},
		}
	};

	const static LinearPieceCurve HANDBRAKE_LONG_FRICTION_FACTOR_CURVE = {
		{
			{0,	0.5f},
			{1,	0.9f}
		}
	};

	const static LinearPieceCurve BALL_CAR_EXTRA_IMPULSE_FACTOR_CURVE = {
		{
			{     0, 0.65f},
			{ 500.f, 0.65f},
			{2300.f, 0.55f},
			{4600.f, 0.30f}
		}
	};

	const static LinearPieceCurve BUMP_VEL_AMOUNT_GROUND_CURVE = {
		{
			{0.f, (5.f / 6.f)},
			{1400.f, 1100.f},
			{2200.f, 1530.f},
		}
	};

	const static LinearPieceCurve BUMP_VEL_AMOUNT_AIR_CURVE = {
		{
			{0.f, (5.f / 6.f)},
			{1400.f, 1390.f},
			{2200.f, 1945.f},
		}
	};

	const static LinearPieceCurve BUMP_UPWARD_VEL_AMOUNT_CURVE = {
		{
			{0.f, (2.f / 6.f)},
			{1400.f, 278.f},
			{2200.f, 417.f},
		}
	};
}

RS_NS_END