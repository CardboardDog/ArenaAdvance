#include "stage_select.hpp"
using namespace bn;
#define curtainSlice(x,y) sprite_items::curtain.create_sprite(x*64,y*64)
#define curtainLayer(y) curtainSlice(0,y),curtainSlice(1,y),curtainSlice(-1,y),curtainSlice(2,y),curtainSlice(-2,y)
namespace stages{
    int picked = 0;
    void stageSelectFade(){
        regular_bg_ptr sky = regular_bg_items::mountains.create_bg(0,0);
        camera_ptr curtainCam = camera_ptr::create(0,0);
        sprite_ptr sprites[] = {
            curtainLayer(-1),
            curtainLayer(0),
            curtainLayer(1)
        };
        for(int i=0;i<15;i++)sprites[i].set_camera(curtainCam);
        int animFrame = 0;
        while(1){
            curtainCam.set_position(0,animFrame);
            animFrame+=3;
            core::update();
            if(animFrame>210){
                break;
            }
        }
    }
    void stageSelect(){
        int goingUp = 0;
        int animFrame = 0;
        regular_bg_ptr sky = regular_bg_items::mountains.create_bg(0,0);
        camera_ptr curtainCam = camera_ptr::create(0,0);
        sprite_ptr sprites[] = {
            curtainLayer(-1),
            curtainLayer(0),
            curtainLayer(1)
        };
        for(int i=0;i<15;i++)sprites[i].set_camera(curtainCam);
        curtainCam.set_position(0,190);
        while(1){
            if(keypad::up_pressed()){
                if(animFrame==0){
                    animFrame = 1;
                    goingUp = 0;
                }
                picked++;
            }
            if(keypad::down_pressed()){
                if(animFrame==0){
                    animFrame = 1;
                    goingUp = 0;
                }
                picked--;
            }
            if(picked>3)picked=0;
            if(picked<0)picked=3;
            if((animFrame!=0) && !goingUp){
                curtainCam.set_position(0,190+animFrame);
                animFrame-=12;
            }else if((animFrame!=0) && goingUp){
                curtainCam.set_position(0,190+animFrame);
                animFrame+=12;
                switch(picked){
                    case 0:
                        sky.set_item(regular_bg_items::mountains);
                        break;
                    case 1:
                        sky.set_item(regular_bg_items::foliage);
                        break;
                    case 2:
                        sky.set_item(regular_bg_items::space);
                        break;
                    case 3:
                        sky.set_item(regular_bg_items::night);
                        break;
                    default:
                        picked=0;
                        break;
                }
            }
            if(!goingUp && (animFrame<-190)){
                goingUp=1;
            }else if(goingUp && (animFrame>2)){
                animFrame = 0;
                goingUp = 0;
            }
            if(keypad::start_pressed())break;
            core::update();
        }
    }
    void stageSelectFadeOut(){
        regular_bg_ptr sky = regular_bg_items::mountains.create_bg(0,0);
        switch(picked){
            case 0:
                sky.set_item(regular_bg_items::mountains);
                break;
            case 1:
                sky.set_item(regular_bg_items::foliage);
                break;
            case 2:
                sky.set_item(regular_bg_items::space);
                break;
            case 3:
                sky.set_item(regular_bg_items::night);
                break;
            default:
                picked=0;
                break;
        }
        camera_ptr curtainCam = camera_ptr::create(0,0);
        sprite_ptr sprites[] = {
            curtainLayer(-1),
            curtainLayer(0),
            curtainLayer(1)
        };
        for(int i=0;i<15;i++)sprites[i].set_camera(curtainCam);
        int animFrame = -190;
        while(1){
            curtainCam.set_position(0,animFrame);
            animFrame+=3;
            core::update();
            if(animFrame>0){
                break;
            }
        }
    }
}