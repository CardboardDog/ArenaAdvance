#include "bn_core.h"
#include "player_select.hpp"
#include "stage_select.hpp"
#include "arena.hpp"

int main(){
    bn::core::init();
    while(1){
        players::playerSelect();
        //stages::stageSelectFade();
        //stages::stageSelect();
        //stages::stageSelectFadeOut();
        arena::battle();
        bn::core::update();
    }
}