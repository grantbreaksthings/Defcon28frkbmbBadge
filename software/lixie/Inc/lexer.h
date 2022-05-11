#ifndef _LEXER_H_
#define _LEXER_H_

#include "stdint.h"
#include "stdio.h"
#include "string.h"

//The amount of tokens the user can input
#define MAX_TOKENS 		3

//Lexer Tokens
//Actions (0x00 to 0x0F)
#define LTKN_TOKEN_NULL		0x00
#define LTKN_ACT_GO 		0x01
#define LTKN_ACT_USE 		0x02
#define LTKN_ACT_PUSH		0x03
#define LTKN_ACT_PULL		0x04
#define LTKN_ACT_TURN		0x05
#define LTKN_ACT_LOCATION	0x06
#define LTKN_ACT_SAY		0x07
#define LTKN_ACT_GET		0x08
#define LTKN_ACT_MIX		0x09
#define LTKN_ACT_HELP		0x0A
#define LTKN_ACT_INVENTORY	0x0B
#define LTKN_ACT_EXAMINE	0x0C

//Noun tokens (0x10 to 0x1F)
//Nav directions
#define LTKN_NAVD_NORTH		0x10
#define LTKN_NAVD_SOUTH		0x11
#define LTKN_NAVD_EAST		0x12
#define LTKN_NAVD_WEST		0x13
#define LTKN_NAVD_UP		0x14
#define LTKN_NAVD_DOWN		0x15
//Turn directions
#define LTKN_TURND_LEFT		0x16
#define LTKN_TURND_RIGHT	0x17

//Objects (0x20 to 0x4F)
#define LTKN_OBJ_STRTDIAL	0x20

//Items (0x50 to 0x7F)
#define LTKN_ITM_PAPER		0x50
#define LTKN_ITM_TPAPER1	0x51
#define LTKN_ITM_TPAPER2	0x52
#define LTKN_ITM_TOTEM		0x53

//Commands (0x80 to 0xAF)
#define LTKN_CMD_YGDRSL		0x80

uint8_t game_tokens[MAX_TOKENS];

//Take input from a user and turn it into tokens
uint8_t TokenizeUserInput(char *buf, uint8_t len);
#endif
