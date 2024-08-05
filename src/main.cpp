#include "bn_core.h"
#include "player_select.hpp"
#include "stage_select.hpp"

int main(){
    bn::core::init();
    while(1){
        players::playerSelect();
        stages::stageSelectFade();
        stages::stageSelect();
        stages::stageSelectFadeOut();
        while(1)bn::core::update();
        bn::core::update();
    }
}