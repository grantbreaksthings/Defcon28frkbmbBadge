#include "lexer.h"

//Lexically analyze the user input
//Return 0xFF and set global vars if fully understood
//Else, return the index of the first character of the not understood word
uint8_t TokenizeUserInput(char *buf, uint8_t len){
	//Clear the tokens
	memset(game_tokens, LTKN_TOKEN_NULL, MAX_TOKENS);
	uint8_t buf_index = 0;
	uint8_t token_count = 0;
	while(buf[buf_index] != '\0' && token_count < MAX_TOKENS){
		if(!strncmp(&buf[buf_index], "go", 2)){
			game_tokens[token_count] = LTKN_ACT_GO;
			buf_index = buf_index + 3;
		}
		else if(!strncmp(&buf[buf_index], "use", 3)){
			game_tokens[token_count] = LTKN_ACT_USE;
			buf_index = buf_index + 4;
		}
		else if(!strncmp(&buf[buf_index], "push", 4)){
			game_tokens[token_count] = LTKN_ACT_PUSH;
			buf_index = buf_index + 5;
		}
		else if(!strncmp(&buf[buf_index], "pull", 4)){
			game_tokens[token_count] = LTKN_ACT_PULL;
			buf_index = buf_index + 5;
		}
		else if(!strncmp(&buf[buf_index], "turn", 4)){
			game_tokens[token_count] = LTKN_ACT_TURN;
			buf_index = buf_index + 5;
		}
		else if(!strncmp(&buf[buf_index], "location", 8)){
			game_tokens[token_count] = LTKN_ACT_LOCATION;
			buf_index = buf_index + 9;
		}
		else if(!strncmp(&buf[buf_index], "say", 3)){
			game_tokens[token_count] = LTKN_ACT_SAY;
			buf_index = buf_index + 4;
		}
		else if(!strncmp(&buf[buf_index], "get", 3)){
			game_tokens[token_count] = LTKN_ACT_GET;
			buf_index = buf_index + 4;
		}
		else if(!strncmp(&buf[buf_index], "mix", 3)){
			game_tokens[token_count] = LTKN_ACT_MIX;
			buf_index = buf_index + 4;
		}
		else if(!strncmp(&buf[buf_index], "north", 5)){
			game_tokens[token_count] = LTKN_NAVD_NORTH;
			buf_index = buf_index + 6;
		}
		else if(!strncmp(&buf[buf_index], "south", 5)){
			game_tokens[token_count] = LTKN_NAVD_SOUTH;
			buf_index = buf_index + 6;
		}
		else if(!strncmp(&buf[buf_index], "east", 4)){
			game_tokens[token_count] = LTKN_NAVD_EAST;
			buf_index = buf_index + 5;
		}
		else if(!strncmp(&buf[buf_index], "west", 4)){
			game_tokens[token_count] = LTKN_NAVD_WEST;
			buf_index = buf_index + 5;
		}
		else if(!strncmp(&buf[buf_index], "up", 2)){
			game_tokens[token_count] = LTKN_NAVD_UP;
			buf_index = buf_index + 3;
		}
		else if(!strncmp(&buf[buf_index], "down", 4)){
			game_tokens[token_count] = LTKN_NAVD_DOWN;
			buf_index = buf_index + 5;
		}
		else if(!strncmp(&buf[buf_index], "left", 4)){
			game_tokens[token_count] = LTKN_TURND_LEFT;
			buf_index = buf_index + 5;
		}
		else if(!strncmp(&buf[buf_index], "right", 5)){
			game_tokens[token_count] = LTKN_TURND_RIGHT;
			buf_index = buf_index + 6;
		}
		else if(!strncmp(&buf[buf_index], "help", 4)){
			game_tokens[token_count] = LTKN_ACT_HELP;
			buf_index = buf_index + 5;
		}
		else if(!strncmp(&buf[buf_index], "inventory", 9)){
			game_tokens[token_count] = LTKN_ACT_INVENTORY;
			buf_index = buf_index + 10;
		}
		else if(!strncmp(&buf[buf_index], "examine", 7)){
			game_tokens[token_count] = LTKN_ACT_EXAMINE;
			buf_index = buf_index + 8;
		}
		else if(!strncmp(&buf[buf_index], "dial", 4)){
			game_tokens[token_count] = LTKN_OBJ_STRTDIAL;
			buf_index = buf_index + 5;
		}
		else if(!strncmp(&buf[buf_index], "paper", 5)){
			game_tokens[token_count] = LTKN_ITM_PAPER;
			buf_index = buf_index + 6;
		}
		else if(!strncmp(&buf[buf_index], "tornpaper1", 10)){
			game_tokens[token_count] = LTKN_ITM_TPAPER1;
			buf_index = buf_index + 11;
		}
		else if(!strncmp(&buf[buf_index], "tornpaper2", 10)){
			game_tokens[token_count] = LTKN_ITM_TPAPER2;
			buf_index = buf_index + 11;
		}
		else if(!strncmp(&buf[buf_index], "yggdrasil", 9)){
			game_tokens[token_count] = LTKN_CMD_YGDRSL;
			buf_index = buf_index + 10;
		}
		else if(!strncmp(&buf[buf_index], "totem", 5)){
			game_tokens[token_count] = LTKN_ITM_TOTEM;
			buf_index = buf_index + 6;
		}
		else{
			return buf_index;
		}
		token_count++;
	}
	return 0xFF;
}
