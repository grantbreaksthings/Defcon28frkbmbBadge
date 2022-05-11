#include "items.h"

//Item Names
const char itm_totem_name[] = "Totem (totem)";
const char itm_paper_name[] = "Paper (paper)";
const char itm_tpaper1_name[] = "Torn Paper 1 (tornpaper1)";
const char itm_tpaper2_name[] = "Torn Paper 2 (tornpaper2)";
//Item seen textTest Item
const char itm_blank_seen[] = ""; //MISRA
const char itm_tpaper1_seen[] = "A torn scrap of paper rests on the floor (tornpaper1)";
const char itm_tpaper2_seen[] = "There's a ragged piece of paper on top of the filing cabinet (tornpaper2)";
//Item examine text
const char itm_totem_exmn[] = "It was given to you at the start of the challenge. Change its color with the \"totem (color)\" command";
const char itm_tpaper1_exmn[] = 	"It says y u t t m a m n p l t c l r u l c g e n y a i g g d a i";
const char itm_tpaper2_exmn[] = 	"It says  o r o e c n a i u a e o o . n o k r e b s y n y g r s l";
const char itm_paper_exmn[] =  		"It says y u t t m a m n p l t c l r u l c g e n y a i g g d a i \r\n"
		                            "         o r o e c n a i u a e o o . n o k r e b s y n y g r s l";

//Game items
struct itm itm_totem;
struct itm itm_paper;
struct itm itm_tpaper1;
struct itm itm_tpaper2;

void InitItms(){

	itm_paper.token = LTKN_ITM_PAPER;
	itm_paper.state = ITM_NOT_PICKED_UP;
	itm_paper.name = itm_paper_name;
	itm_paper.seen_text = itm_blank_seen;
	itm_paper.examine_text = itm_paper_exmn;

	itm_tpaper1.token = LTKN_ITM_TPAPER1;
	itm_tpaper1.state = ITM_NOT_PICKED_UP;
	itm_tpaper1.name = itm_tpaper1_name;
	itm_tpaper1.seen_text = itm_tpaper1_seen;
	itm_tpaper1.examine_text = itm_tpaper1_exmn;

	itm_tpaper2.token = LTKN_ITM_TPAPER2;
	itm_tpaper2.state = ITM_NOT_PICKED_UP;
	itm_tpaper2.name = itm_tpaper2_name;
	itm_tpaper2.seen_text = itm_tpaper2_seen;
	itm_tpaper2.examine_text = itm_tpaper2_exmn;

	itm_totem.token = LTKN_ITM_TOTEM;
	itm_totem.state = ITM_IN_INVENTORY;
	itm_totem.name = itm_totem_name;
	itm_totem.seen_text = itm_blank_seen;
	itm_tpaper2.examine_text = itm_totem_exmn;

	game_itms[0] = &itm_paper;
	game_itms[1] = &itm_tpaper1;
	game_itms[2] = &itm_tpaper2;
}

struct itm* GetItmByToken(uint8_t token){
	for(uint8_t i = 0; i < ITEM_COUNT; i++){
		if(game_itms[i]->token == token){
			return game_itms[i];
		}
	}
	return NULL;
}
