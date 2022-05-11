#include "objects.h"

//Object Names
const char obj_startroomdial_name[] = "Dial (dial)";
//Object seen text
const char obj_startroomdial_seen[] = "A large, silver dial is set in the wall";
//Object examine text
const char obj_startroomdial_examine[] = "There are wires running from it to the door";
//Game objects
struct obj obj_startroomdial;
//Array of all the game objects
struct obj* game_objs[OBJECT_COUNT];


void InitObjs(){
	// Initialize the dial in the first room
	obj_startroomdial.token = LTKN_OBJ_STRTDIAL;
	obj_startroomdial.state = OBJ_UNTOUCHED;
	obj_startroomdial.name = obj_startroomdial_name;
	obj_startroomdial.seen_text = obj_startroomdial_seen;
	obj_startroomdial.examine_text = obj_startroomdial_examine;
	game_objs[0] = &obj_startroomdial;
}

struct obj* GetObjByToken(uint8_t token){
	for(uint8_t i = 0; i < OBJECT_COUNT; i++){
		if(game_objs[i]->token == token){
			return game_objs[i];
		}
	}
	return NULL;
}
