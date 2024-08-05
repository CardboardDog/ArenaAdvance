#include "player_select.hpp"
using namespace bn;
namespace players{
    int picked[4] = {0,5,5,5};
    int wrap(int value){
        if(value<0){
            return (6-abs(value))%6;
        }
        return value%6;
        
    }
    void playerSelect(){
        fixed personSelect = 0;
        fixed spotlightSelect = 0;
        fixed targetSelect = 0;
        int direction = 0;
        int animFrame = 0;
        int flicker = 0;
        random Random;
        regular_bg_ptr nothing = regular_bg_items::black.create_bg(0,0);
        sprite_ptr spotlight = sprite_items::spotlight.create_sprite(0,0);
        sprite_ptr playerSprites[4] = {
            sprite_items::boxer.create_sprite((0-1.5)*32,20),
            sprite_items::null.create_sprite((1-1.5)*32,20),
            sprite_items::null.create_sprite(((2-1.5)*32),20),
            sprite_items::null.create_sprite((3-1.5)*32,20)
        };
        while(1){
            core::update();
            if(keypad::a_pressed())personSelect+=1;
            if(keypad::b_pressed())personSelect-=1;
            
            direction = keypad::up_pressed()-keypad::down_pressed();
            if((direction != 0)&&(wrap(picked[(int)personSelect]+direction)!=5)){
                for(int i=0;i<4;i++){
                    if((picked[i]==(wrap(picked[(int)personSelect]+direction)))&&(i!=(int)personSelect)){
                        if(direction>0){
                            direction+=1;
                        }else{
                            direction-=1;
                        }
                    }
                }
            }
            picked[(int)personSelect]+=direction;

            if((int)personSelect > 3)personSelect=3;
            if((int)personSelect < 0)personSelect=0;
            picked[(int)personSelect]=wrap(picked[(int)personSelect]);
            
            if(direction != 0){
                if(picked[(int)personSelect]==0){
                    playerSprites[(int)personSelect].set_item(sprite_items::boxer);
                    playerSprites[(int)personSelect].set_position((personSelect-1.5)*32,20);
                }else if(picked[(int)personSelect]==1){
                    playerSprites[(int)personSelect].set_item(sprite_items::bubble);
                    playerSprites[(int)personSelect].set_position((personSelect-1.5)*32,20);
                }else if(picked[(int)personSelect]==2){
                    playerSprites[(int)personSelect].set_item(sprite_items::hammer);
                    playerSprites[(int)personSelect].set_position(((personSelect-1.5)*32)+5,20);
                }else if(picked[(int)personSelect]==3){
                    playerSprites[(int)personSelect].set_item(sprite_items::rock);
                    playerSprites[(int)personSelect].set_position((personSelect-1.5)*32,20);
                }else if(picked[(int)personSelect]==4){
                    playerSprites[(int)personSelect].set_item(sprite_items::wiener);
                    playerSprites[(int)personSelect].set_position((personSelect-1.5)*32,20);
                }else if(picked[(int)personSelect]==5){
                    playerSprites[(int)personSelect].set_item(sprite_items::null);
                    playerSprites[(int)personSelect].set_position((personSelect-1.5)*32,20);
                }
            }

            targetSelect=(personSelect-1.5)*32;
            spotlightSelect += (targetSelect-spotlightSelect)/4;
            spotlight.set_position(spotlightSelect,0);

            if(keypad::start_pressed())animFrame++;

            if(animFrame!=0){
                if(animFrame<20){
                    for(int i=0;i<4;i++){
                        // sorry about this line :(
                        playerSprites[i].set_position(playerSprites[i].position().x(),20+(((animFrame+(i*3))*(animFrame+(i*3)))/4));
                    }
                }else if(animFrame == 20){
                    for(int i=0;i<4;i++){
                        playerSprites[i].set_visible(false);
                    }
                }else if(animFrame<70){
                    if(flicker==0){
                        if(Random.get_int(2)==1){
                            spotlight.set_visible(false);
                        }else{
                            spotlight.set_visible(true);
                        }
                        flicker = (70-animFrame)/6;
                    }else{
                        flicker--;
                    }
                }else{
                    spotlight.set_visible(false);
                }
                animFrame++;
            }
            if(animFrame==80){
                break;
            }
        }
    }
}