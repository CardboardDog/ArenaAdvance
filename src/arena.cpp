#include "arena.hpp"
using namespace bn;
#define curtainSlice(x,y) sprite_items::curtain.create_sprite(x*64,y*64)
#define curtainLayer(y) curtainSlice(0,y),curtainSlice(1,y),curtainSlice(-1,y),curtainSlice(2,y),curtainSlice(-2,y)
namespace arena{
    void battle(){
        regular_bg_ptr sky = regular_bg_items::mountains.create_bg(0,0);
        switch(stages::picked){
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
                stages::picked=0;
                break;
        }
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
        while(1){
            core::update();
        }
    }
}