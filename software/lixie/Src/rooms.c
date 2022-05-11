#include "rooms.h"
#include "usbd_cdc_if.h"

//Array of pointers to all the game rooms
struct room* game_rooms[ROOM_COUNT];

//All the game rooms
struct room rm_startroom;
struct room rm_rfciphr1;
struct room rm_rfciphr2;

//Room names
const char rm_name_startroom[] = 	"Start Room";
const char rm_name_rfciphr1[] = 	"Level0: Room1";
const char rm_name_rfciphr2[] = 	"Level0: Room2";

//Room flavor text
const char rm_flvr_startoom[] = 	"The room is blank, stark white.\r\nThere's graphite plaque that says \"aopz pz aol mpyza alza. abyu aol kphs slma, slma, ypnoa, ypnoa\"";
const char rm_flvr_rfciphr1[] = 	"The walls turn to brushed steel, the room is starkly furnished. Bright lights are inset in the ceiling. There's a door with a stenciled letters, \"VERDE\"";
const char rm_flvr_rfciphr2[] = 	"It looks a lot like the previous room, but more clutter. There's scrap metal all over the floor and file cabinets pressed against the walls.";

//Room item lists
struct itm* rm_rfciphr1_itms[1];
struct itm* rm_rfciphr2_itms[1];
//Room object lists
struct obj* rm_startroom_objs[1];

void InitRooms(){
	//Initialize the list of all the game rooms
	game_rooms[0] = &rm_startroom;
	game_rooms[1] = &rm_rfciphr1;
	game_rooms[2] = &rm_rfciphr2;

	//Init the start room
	rm_startroom.north_room = NULL;
	rm_startroom.east_room = NULL;
	rm_startroom.south_room = NULL;
	rm_startroom.west_room = NULL;
	rm_startroom.up_room = NULL;
	rm_startroom.down_room = NULL;
	rm_startroom.name = rm_name_startroom;
	rm_startroom.flavortext = rm_flvr_startoom;
	rm_startroom.items = NULL;
	rm_startroom.objects = rm_startroom_objs;
	rm_startroom.item_count = 0;
	rm_startroom.object_count = 1;
	rm_startroom.token = RTKN_STARTROOM;
	rm_startroom_objs[0] = GetObjByToken(LTKN_OBJ_STRTDIAL);

	//Init the Rail Fence Cipher Room1
	rm_rfciphr1.north_room = NULL;
	rm_rfciphr1.east_room = &rm_rfciphr2;
	rm_rfciphr1.south_room = &rm_startroom;
	rm_rfciphr1.west_room = NULL;
	rm_rfciphr1.up_room = NULL;
	rm_rfciphr1.down_room = NULL;
	rm_rfciphr1.name = rm_name_rfciphr1;
	rm_rfciphr1.flavortext = rm_flvr_rfciphr1;
	rm_rfciphr1.items = rm_rfciphr1_itms;
	rm_rfciphr1.objects = NULL;
	rm_rfciphr1.item_count = 1;
	rm_rfciphr1.object_count = 0;
	rm_rfciphr1.token = RTKN_RFCIPHR1;
	rm_rfciphr1_itms[0] = GetItmByToken(LTKN_ITM_TPAPER1);

	//Init the Rail Fence Cipher Room2
	rm_rfciphr2.north_room = NULL;
	rm_rfciphr2.east_room = NULL;
	rm_rfciphr2.south_room = NULL;
	rm_rfciphr2.west_room = &rm_rfciphr1;
	rm_rfciphr2.up_room = NULL;
	rm_rfciphr2.down_room = NULL;
	rm_rfciphr2.name = rm_name_rfciphr2;
	rm_rfciphr2.flavortext = rm_flvr_rfciphr2;
	rm_rfciphr2.items = rm_rfciphr2_itms;
	rm_rfciphr2.objects = NULL;
	rm_rfciphr2.item_count = 1;
	rm_rfciphr2.object_count = 0;
	rm_rfciphr2.token = RTKN_RFCIPHR2;
	rm_rfciphr2_itms[0] = GetItmByToken(LTKN_ITM_TPAPER2);

}

struct room* GetRoomByToken(uint8_t token){
	for(uint8_t i = 0; i < ROOM_COUNT; i++){
		if(game_rooms[i]->token == token){
			return game_rooms[i];
		}
	}
	return NULL;
}
