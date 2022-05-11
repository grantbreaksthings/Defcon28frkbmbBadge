#include "game.h"
#include "lexer.h"
#include "rooms.h"
#include "items.h"
#include "usbd_cdc_if.h"

//Pointer to the current game room
struct room* current_room;

//The current game state
uint16_t current_state;

// TODO Totem stuff
//The totem states
uint8_t totem_state;
//The highest unlocked totem level
uint8_t totem_level;

//Output buffer for the game
#define GAME_OUTPUT_BUFFER_SIZE 512
char game_output_buffer[GAME_OUTPUT_BUFFER_SIZE];

void InitGame(){
	InitItms();
	InitObjs();
	InitRooms();
	totem_state = 0;
	totem_level = 0;
	current_room = GetRoomByToken(RTKN_STARTROOM);
	current_state = GSTATE_MOVING;
}

void PrintBadInput(char* ins, uint8_t index){
	ClearTxBuffer();
	strncpy(UserTxBufferFS, "Invalid input: ", 15);
	uint8_t i = 0;
	while(	(i < APP_TX_DATA_SIZE - 18) &&
			(ins[i + index] != '\0') &&
			(ins[i + index] != ' ')){
		UserTxBufferFS[i + 15] = ins[i + index];
		i++;
	}
	UserTxBufferFS[i + 16] = '\r';
	UserTxBufferFS[i + 17] = '\n';
	CDC_Transmit_FS(UserTxBufferFS, i + 18);
}

void GameLoop(){
	  uint8_t ret = 0;
	  if(CheckUserDataReady()){
		  ret = TokenizeUserInput(GetUserDataBuf(), GetUserDataSize());
		  if(ret != 0xFF){
			  PrintBadInput(GetUserDataBuf(), ret);
			  ClearUserDataBuf();
		  }
		  else{
			  if(game_tokens[0] == LTKN_ACT_GO){
				  MovePlayer();
			  }
			  else if(game_tokens[0] == LTKN_ACT_LOCATION){
				  PrintLocation();
			  }
			  else if(game_tokens[0] == LTKN_ACT_GET){
				  GetItem();
			  }
			  else if(game_tokens[0] == LTKN_ACT_INVENTORY){
				  PrintInventory();
			  }
			  else if(game_tokens[0] == LTKN_ACT_EXAMINE){
				  Examine();
			  }
			  else if(game_tokens[0] == LTKN_ACT_USE){
				  UseItem();
			  }
			  else if(game_tokens[0] == LTKN_ACT_MIX){
				  MixItems();
			  }
			  else if(game_tokens[0] == LTKN_ACT_HELP){
				  PrintHelp();
			  }
			  else if(game_tokens[0] == LTKN_ACT_TURN){
				  TurnObject();
			  }
			  else if(game_tokens[0] == LTKN_TOKEN_NULL){
				  PrintRoomText();
			  }
			  else{
				  PrintToConsole("You can't perform that action.\0");
			  }
		  }
		  ClearUserDataBuf();
	  }
	  else{
		  //MISRA
	  }
}

void PrintLocation(){
	char tmp[100];
	memset(tmp, '\0', 100);
	snprintf(tmp, 100, "You are in %s", current_room->name);
	PrintStrToConsole(tmp);
	if(current_room->north_room != NULL){
		snprintf(tmp, 100, "To the north is %s", current_room->north_room->name);
		PrintStrToConsole(tmp);
		memset(tmp, '\0', 100);
	}
	if(current_room->east_room != NULL){
		snprintf(tmp, 100, "To the east is %s", current_room->east_room->name);
		PrintStrToConsole(tmp);
		memset(tmp, '\0', 100);
	}
	if(current_room->south_room != NULL){
		snprintf(tmp, 100, "To the south is %s", current_room->south_room->name);
		PrintStrToConsole(tmp);
		memset(tmp, '\0', 100);
	}
	if(current_room->west_room != NULL){
		snprintf(tmp, 100, "To the west is %s", current_room->west_room->name);
		PrintStrToConsole(tmp);
		memset(tmp, '\0', 100);
	}
	if(current_room->up_room != NULL){
		snprintf(tmp, 100, "Above you is %s", current_room->up_room->name);
		PrintStrToConsole(tmp);
		memset(tmp, '\0', 100);
	}
	if(current_room->down_room != NULL){
		snprintf(tmp, 100, "Below you is %s", current_room->down_room->name);
		PrintStrToConsole(tmp);
		memset(tmp, '\0', 100);
	}
}

void PrintInventory(){
	for(uint8_t i = 0; i < ITEM_COUNT; i++){
		if(game_itms[i]->state == ITM_IN_INVENTORY){
			PrintStrToConsole(game_itms[i]->name);
		}
	}
}

void PrintHelp(){
	PrintToConsole(
		"go (north, south, east, west, up, down)\r\n"
			"\tMove in a given direction\r\n"
		"use (item) (object)\r\n"
			"\tUse an item on an object\r\n"
		"push (object)\r\n"
			"\tPush an object\r\n"
		"pull (object)\r\n"
			"\tPull an object\r\n"
		"turn (object) (left, right)\r\n"
			"\tTurn an object left or right\r\n"
		"location\r\n"
			"\tPrint your current location\r\n"
		"say (command)\r\n"
			"\tSay something out loud\r\n"
		"get (item)\r\n"
			"\tPick up an item\r\n"
		"mix (item) (item)\r\n"
			"\tMix two different items in your inventory\r\n"
		"examine (item)\r\n"
			"\tExamine an item in your inventory\r\n\0"
		"inventory\r\n"
			"\tView your current inventory\r\n"
	);
	//Need to split into two calls
	//USB Transmit is asynchronous, so wait 1ms for the data to transfer
	//TODO: Get rid of the dumb delay, poll the USB status somehow
	HAL_Delay(1);
	PrintToConsole(
		"help\r\n"
			"\tSee this dialogue\r\n\0");
}

void Examine(){
	// TODO: Haven't tested this with items
	// Try to examine an item first
	struct itm* ex_itm = GetItmByToken(game_tokens[1]);
	if(ex_itm != NULL){
		if(ex_itm->state == ITM_IN_INVENTORY){
			PrintStrToConsole(ex_itm->examine_text);
			return;
		}
	}
	// If item didn't work, try to examine an object
	struct obj* ex_obj = GetObjByToken(game_tokens[1]);
	if(ex_obj != NULL){
		// Make sure that object is in this room before printing
		for(uint8_t i = 0; i < current_room->object_count; i++){
			if(current_room->objects[i] == ex_obj){
				PrintStrToConsole(ex_obj->examine_text);
				return;
			}
		}
	}
	// If neither worked, it's invalid
	PrintToConsole("You can't examine that.\0");
}

void GetItem(){
	for(uint8_t i = 0; i < current_room->item_count; i++){
		if(game_tokens[1] == current_room->items[i]->token){
			if(current_room->items[i]->state == ITM_NOT_PICKED_UP){
				current_room->items[i]->state = ITM_IN_INVENTORY;
				PrintToConsole("You got it\0");
				return;
			}
		}
	}
	PrintToConsole("You can't get that.\0");
}

void MovePlayer(){
	if(game_tokens[1] <= 0x15 && game_tokens[1] >= 0x10){
		if(game_tokens[1] == LTKN_NAVD_NORTH){
			if(current_room->north_room != 0x00){
				current_room = current_room->north_room;
			}
			else{
				PrintToConsole("You can't go north.\0");
				return;
			}
		}
		else if(game_tokens[1] == LTKN_NAVD_EAST){
			if(current_room->east_room != 0x00){
				current_room = current_room->east_room;
			}
			else{
				PrintToConsole("You can't go east.\0");
				return;
			}
		}
		else if(game_tokens[1] == LTKN_NAVD_SOUTH){
			if(current_room->south_room != 0x00){
				current_room = current_room->south_room;
			}
			else{
				PrintToConsole("You can't go south.\0");
				return;
			}
		}
		else if(game_tokens[1] == LTKN_NAVD_WEST){
			if(current_room->west_room != 0x00){
				current_room = current_room->west_room;
			}
			else{
				PrintToConsole("You can't go west.\0");
				return;
			}
		}
		else if(game_tokens[1] == LTKN_NAVD_UP){
			if(current_room->up_room != 0x00){
				current_room = current_room->up_room;
			}
			else{
				PrintToConsole("You can't go up.\0");
				return;
			}
		}
		else if(game_tokens[1] == LTKN_NAVD_DOWN){
			if(current_room->down_room != 0x00){
				current_room = current_room->down_room;
			}
			else{
				PrintToConsole("You can't go down.\0");
				return;
			}
		}
		PrintRoomText();
		current_state = GSTATE_MOVING;
	}
	else{
		PrintToConsole("You can't go that way\0");
	}
}

void PrintRoomText(){
	PrintStrToConsole(current_room->flavortext);
	for(uint8_t i = 0; i < current_room->item_count; i++){
		if(current_room->items[i]->state == ITM_NOT_PICKED_UP){
			PrintStrToConsole(current_room->items[i]->seen_text);
		}
	}
	for(uint8_t i = 0; i < current_room->object_count; i++){
		if(current_room->objects[i]->state != OBJ_ACTED_ON){
			PrintStrToConsole(current_room->objects[i]->seen_text);
		}
	}
}

void MixItems(){
	struct itm* itm1 = GetItmByToken(game_tokens[1]);
	struct itm* itm2 = GetItmByToken(game_tokens[2]);
	//Make sure the tokens are both actually items
	if(itm1 && itm2){
		//Make sure the items are in the players inventory
		if((itm1->state == ITM_IN_INVENTORY) &&
				itm2->state == ITM_IN_INVENTORY){
			return MixItemsMixer(itm1, itm2);
		}
	}
	else{
		PrintToConsole("You can't mix those.\0");
		return;
	}
}

void MixItemsMixer(struct itm* itm1, struct itm* itm2){
	//Mix testitm1 and testitm2 together to make a testitm
	if(((itm1->token == LTKN_ITM_TPAPER1) && (itm2->token == LTKN_ITM_TPAPER2)) ||
	   ((itm1->token == LTKN_ITM_TPAPER2) && (itm2->token == LTKN_ITM_TPAPER1))){
		//Remove the two items from player inventory
		itm1->state = ITM_USED_UP;
		itm2->state = ITM_USED_UP;
		//Put testitm in the players inventory
		GetItmByToken(LTKN_ITM_PAPER)->state = ITM_IN_INVENTORY;
		PrintToConsole("You match up the tear marks on the slips of paper to make a full sheet of paper (paper).\0");
		return;
	}
	else{
		PrintToConsole("You can't mix those.\0");
		return;
	}
}

void UseItem(){
	//Make sure the item exists
	struct itm* useitem = GetItmByToken(game_tokens[1]);
	if(useitem == NULL){
		PrintToConsole("You can't use that item.\0");
		return;
	}
	//Make sure the item is in the players inventory
	if(useitem->state != ITM_IN_INVENTORY){
		PrintToConsole("You can't use that item.\0");
		return;
	}
	//Make sure the object the item is being used on exists
	struct obj* useobj = GetObjByToken(game_tokens[2]);
	if(useobj == NULL){
		PrintToConsole("You can't use that on that object.\0");
		return;
	}
	//Make sure the object that item is being used on is in the current room
	for(uint8_t i = 0; i < current_room->object_count; i++){
		if(useobj == current_room->objects[i]){
			UseItemStateMachine();
			return;
		}
	}
	PrintToConsole("You can't use that on that object.\0");
	return;
}

void UseItemStateMachine(){
	/*	Keep this as reference
	 * 	//Use a test item on a test object, unlocks the final room
	 *
	if(game_tokens[1] == LTKN_ITM_TEST && game_tokens[2] == LTKN_OBJ_TEST){
		//Link the two rooms
		GetRoomByToken(RTKN_TESTSTART)->up_room = GetRoomByToken(RTKN_TESTUP);
		GetRoomByToken(RTKN_TESTUP)->down_room = GetRoomByToken(RTKN_TESTSTART);
		//Change the flavor test of the start room
		GetRoomByToken(RTKN_TESTSTART)->flavortext = rm_flvr_teststart_up_unlocked;
		//Set the item as used
		GetItmByToken(game_tokens[1])->state = ITM_USED_UP;
		//Print some text
		PrintToConsole("You hear something click in the start room\0");
	}
	else{
		PrintToConsole("You can't use that.\0");
	}
	*/
}

void TurnObject(){
	// Make sure it's being turned in a valid direction
	uint8_t direction;
	if(game_tokens[2] == LTKN_TURND_LEFT){
		direction = 0;
	}
	else if (game_tokens[2] == LTKN_TURND_RIGHT){
		direction = 1;
	}
	else if (game_tokens[3] == LTKN_TOKEN_NULL){
		PrintToConsole("Please specify a direction to turn (left or right).\0");
		return;
	}
	else{
		PrintToConsole("You can't turn that in that direction.\0");
		return;
	}
	struct obj* ex_obj = GetObjByToken(game_tokens[1]);
	// Make sure the object is in the room first
	if(ex_obj != NULL){
		for(uint8_t i = 0; i < current_room->object_count; i++){
			// If the item is in the room and it can be interacted with, then enter the
			// turn state machine
			if(current_room->objects[i] == ex_obj &&
					current_room->objects[i]->state == OBJ_UNTOUCHED){
				TurnObjectStateMachine(direction);
				return;
			}
		}
	}
	PrintToConsole("You can't turn that.\0");
}

// Left is 0, right is 1
void TurnObjectStateMachine(uint8_t direction){
	// If in the start room, turn the start dial
	if(current_room->token == RTKN_STARTROOM){
		PrintToConsole("You turn the dial with a clunk.\0");
		switch(current_state){
			case GSTATE_MOVING:{
				if(direction == 0){
					current_state = GSTATE_STARTROOM_TURNDIAL1;
				}
				else{
					current_state = GSTATE_MOVING;
				}
				break;
			}
			case GSTATE_STARTROOM_TURNDIAL1:{
				if(direction == 0){
					current_state = GSTATE_STARTROOM_TURNDIAL2;
				}
				else{
					current_state = GSTATE_MOVING;
				}
				break;
			}
			case GSTATE_STARTROOM_TURNDIAL2:{
				if(direction == 1){
					current_state = GSTATE_STARTROOM_TURNDIAL3;
				}
				else{
					current_state = GSTATE_MOVING;
				}
				break;
			}
			case GSTATE_STARTROOM_TURNDIAL3:{
				if(direction == 1){
					PrintToConsole("The dial sticks in place. The door to the next room opens to the north\0");
					// Remove the dial from play
					current_room->objects[0]->state = OBJ_ACTED_ON;
					// Open the door to the rail cipher rooms
					current_room->north_room = GetRoomByToken(RTKN_RFCIPHR1);
					current_state = GSTATE_MOVING;
				}
				else{
					current_state = GSTATE_MOVING;
				}
				break;
			}
		}
	}
}
