#pragma once

//client request
#define CLIENT_PLAYER_NONE	0x01
#define CLIENT_PLAYER_LEFT 0x02
#define CLIENT_PLAYER_RIGHT 0x04
#define CLIENT_PLAYER_SHOT 0x08
#define CLIENT_PLAYER_DRONE 0x10

//actvalue
//char info type
#define PLAYER_STATE 0x01
#define SPAWN_PLAYER_BULLET 0x02
#define ERASE_PLAYER_BULLET 0x03
#define SPAWN_PLAYER_DRONE 0x04
#define ERASE_PLAYER_DRONE 0x05
#define OVER_WINDOW_PLAYER_DRONE 0x08
#define PLAYER_BULLET_COLLISION 0x12
#define PLAYER_DRONE_COLLISION 0x14
#define PLAYER_DRONE_AND_ENEMY_BULLET 0x24
#define ENEMY_PLAYER_STATE 0x10
#define SPAWN_ENEMY_BULLET 0x20
#define ERASE_ENEMY_BULLET 0x30
#define SPAWN_ENEMY_DRONE 0x40
#define ERASE_ENEMY_DRONE 0x50
#define ENEMY_BULLET_COLLISION 0x21
#define ENEMY_DRONE_COLLISION 0x41
#define ENEMY_DRONE_AND_PLAYER_BULLET 0x42
#define OVER_WINDOW_ENEMY_DRONE 0x80
#define SCENE_CHANGE 0xfe
#define UNCONNECT 0xff

#pragma pack(1)
struct ActValue
{
	unsigned char infoType;
	unsigned char infoOption;
	unsigned short pointX;
	ActValue() :infoType(0), infoOption(0), pointX(0) {}
	void init() { infoType = 0; infoOption = 0; pointX = 0; }
};
#pragma pack()











