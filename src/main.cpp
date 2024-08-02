#include "bn_core.h"
#include "player_select.hpp"

int main(){
    bn::core::init();
    while(1){
        players::playerSelect();
        bn::core::update();
    }
}