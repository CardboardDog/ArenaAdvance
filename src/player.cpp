#include "player.hpp"
using namespace bn;
namespace players{
    player::player(int fighter, sprite_ptr* sprPtr){
        this->playType=fighter;
        this->sprite = sprPtr;
        this->sprite->set_visible(true);
        if(fighter==0){
            this->sprite->set_item(sprite_items::boxer);
        }else if(fighter==1){
            this->sprite->set_item(sprite_items::bubble);
        }else if(fighter==2){
            this->sprite->set_item(sprite_items::hammer);
        }else if(fighter==3){
            this->sprite->set_item(sprite_items::rock);
        }else if(fighter==4){
            this->sprite->set_item(sprite_items::wiener);
        }else if(fighter==5){
            this->sprite->set_item(sprite_items::null);
            this->sprite->set_visible(false);
        }
        this->sprite->set_position(0,0);
    }
    void player::setRespawn(int x, int y){
        this->sprite->set_position(x,y);
        this->respawn[0]=x;
        this->respawn[0]=y;
    }
}