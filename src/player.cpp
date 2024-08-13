#include "player.hpp"
using namespace bn;
namespace players{
    player::player(int fighter, sprite_ptr* sprPtr){
        this->playType=fighter;
        this->sprite = sprPtr;
        this->sprite->set_visible(true);
        if(fighter==0){
            this->sprite->set_item(sprite_items::boxer);
            this->maxWalk = 3.5;
            this->walkSpeed = 0.5;
            this->jumpPower = 3;
        }else if(fighter==1){
            this->sprite->set_item(sprite_items::wiener);
            this->maxWalk = 8;
            this->walkSpeed = 1;
            this->jumpPower = 2.5;
        }else if(fighter==2){
            this->sprite->set_item(sprite_items::hammer);
            this->maxWalk = 2;
            this->walkSpeed = 0.5;
            this->jumpPower = 2;
        }else if(fighter==3){
            this->sprite->set_item(sprite_items::bubble);
            this->maxWalk = 10;
            this->walkSpeed = 0.25;
            this->jumpPower = 4;
        }else if(fighter==4){
            this->sprite->set_item(sprite_items::rock);
            this->maxWalk = 12;
            this->walkSpeed = 1;
            this->jumpPower = 2;
        }else if(fighter==5){
            this->sprite->set_item(sprite_items::null);
            this->sprite->set_visible(false);
        }
        this->inAir = false;
        this->sprite->set_position(0,0);
        this->currentWalk=0;
    }
    void player::setRespawn(int x, int y){
        this->sprite->set_position(x,y);
        this->respawn[0]=x;
        this->respawn[0]=y;
    }
    void player::update(){
        bool wasGrounded = !this->inAir;
        // i love how butano has no translation function
        this->sprite->set_position(
            this->sprite->position().x(),
            this->sprite->position().y()+this->velocity[1]
        );
        if(!this->inAir){
            this->sprite->set_position(
                this->sprite->position().x()+this->currentWalk/2,
                this->sprite->position().y()
            );
        }else{
            this->velocity[1] += 0.25;
            this->sprite->set_position(
                this->sprite->position().x()+this->velocity[0],
                this->sprite->position().y()
            );
        };
        this->inAir = !this->arenaCol->pointIn(this->sprite->position().x(),this->sprite->position().y());
        if(!this->inAir){
            if(this->velocity[1]>0){
                this->velocity[0]=0;
                this->velocity[1]=0;
                for(int i=0;i<20;i++){
                    if(!this->arenaCol->pointIn(this->sprite->position().x(),this->sprite->position().y()-i)){
                        this->sprite->set_position(this->sprite->position().x(),this->sprite->position().y()-i+1);
                        break;
                    }
                }
            }else if(this->velocity[1].round_integer()!=0)this->inAir=true;
        }
        if(wasGrounded&&this->inAir)this->velocity[0]=this->currentWalk/2;
    }
    void player::dontWalk(){
        if(!this->inAir){
            this->currentWalk/=(fixed)1.3;
        }
    }
    void player::walk(bool left){
        fixed amount = 0;
        if(left){
            amount-=this->walkSpeed;
            this->sprite->set_horizontal_flip(true);
        }else{
            amount+=this->walkSpeed;
            this->sprite->set_horizontal_flip(false);
        }
        if(this->inAir)amount/=2;
        this->currentWalk+=amount;
        if(this->currentWalk>this->maxWalk)this->currentWalk=this->maxWalk;
        if(this->currentWalk<-this->maxWalk)this->currentWalk=-this->maxWalk;
    }
    void player::jump(){
        if(true){
            this->velocity[1] = -this->jumpPower;
            this->inAir = true;
            this->velocity[0] = this->currentWalk/2;
        }
    }
    void player::animate(){
        if(this->currentWalk.round_integer()!=0){
            switch(this->playType){
                case 0:
                    this->boxerRun->update();
                    break;
                case 1:
                    this->wienerRun->update();
                    break;
                case 2:
                    this->hammerRun->update();
                    break;
                case 3:
                    this->bubbleRun->update();
                    break;
                case 4:
                    this->rockRun->update();
                    break;
                default:
                    break;
            }
        }else{
            this->idle->update();
        }
    }
}