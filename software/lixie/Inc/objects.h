#ifndef _OBJECTS_H_
#define _OBJECTS_H_

#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "lexer.h"

//The amount of objects in the game
#define OBJECT_COUNT 1
//Object States
//Null
#define OBJ_NULL 		0x00
//The item has not been acted upon
#define OBJ_UNTOUCHED 	0x01
//The object has been acted upon in the game world and is removed from play
#define OBJ_ACTED_ON 	0x02

struct obj{
	//The token that the game logic refers to the object by
	uint8_t token;
	//The current state of the object
	uint8_t state;
	//Pointer to a C string containing a human readable name
	const char* name;
	//Pointer to the C string containing the text that prints when
	//in the same room as the object and the object has not been removed from play
	const char* seen_text;
	//Pointer to the C string containing the object examine text
	const char* examine_text;
};



//Get a game object by its token
struct obj* GetObjByToken(uint8_t token);
//Initialize all the objects at the start of the game
void InitObjs();

#endif
