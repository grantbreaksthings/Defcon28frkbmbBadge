#ifndef _GAME_H_
#define _GAME_H_

#include "lexer.h"
#include "items.h"
#include "objects.h"
#include "rooms.h"

//Initialize the game to its default state
void InitGame();
//The main game loop
void GameLoop();
//Set the current room the player is in
void SetCurrentRoom(struct room* new_current_room);
//Get the current room the player is in
struct room* GetCurrentRoom();

//Move the player
void MovePlayer();
//Print the text (room flavortext, item flavortext, etc) associated with the current room
void PrintRoomText();
//Use an item
void UseItem();
//Push an object
void PushObject();
//Pull an object
void PullObject();
//Turn an object
void TurnObject();
void TurnObjectStateMachine(uint8_t direction);  // 0 for left, 1 for right
//Print current location of the player location
void PrintLocation();
//Say a command
void SayCommand();
//Get an item
void GetItem();
//Use an item();
void UseItem(); //Basic checker to make sure the syntax is right
void UseItemStateMachine(); //Use the item based on the current state of the game
//Mix two items();
void MixItems(); //Basic checker to make sure syntax is right
void MixItemsMixer(struct itm* itm1, struct itm* itm2); //Actually mix the items
//Print the help dialogue
void PrintHelp();
//Show the player inventory
void PrintInventory();
//Examine an item or an object
void Examine();

//All the game states
#define GSTATE_NULL					0x00
#define GSTATE_MOVING				0x01
#define GSTATE_STARTROOM_TURNDIAL1 	0x02
#define GSTATE_STARTROOM_TURNDIAL2 	0x03
#define GSTATE_STARTROOM_TURNDIAL3 	0x04
#define GSTATE_STARTROOM_TURNDIAL4 	0x05
#endif
