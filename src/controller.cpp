#include "controller.hpp"
using namespace bn;
namespace controllers{
    controller::controller(players::player* player){
        this->playerObj = player;
    }
    void controller::update(){
        if(keypad::left_held()){
            this->playerObj->walk(true);
            return;
        }
        if(keypad::right_held()){
            this->playerObj->walk(false);
            return;
        }
        this->playerObj->dontWalk();
    }
}