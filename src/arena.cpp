#include "arena.hpp"
using namespace bn;
#define curtainSlice(x,y) sprite_items::curtain.create_sprite(x*64,y*64)
#define curtainLayer(y) curtainSlice(0,y),curtainSlice(1,y),curtainSlice(-1,y),curtainSlice(2,y),curtainSlice(-2,y)
#define run4(ptr,type,speed) create_sprite_animate_action_forever(ptrPile[ptr],speed,sprite_items::type.tiles_item(),0,1,2,3)
#define runAll4(ptr) run4(ptr,boxer,8),run4(0,wiener,4),run4(0,hammer,16)
#define run2(ptr,type,speed) create_sprite_animate_action_forever(ptrPile[ptr],speed,sprite_items::type.tiles_item(),0,1)
#define runAll2(ptr) run2(ptr,bubble,32),run2(ptr,rock,4)
#define idle(ptr,type) create_sprite_animate_action_forever(ptrPile[ptr],1,sprite_items::type.tiles_item(),0,0)
#define idleAll(ptr) idle(ptr,boxer),idle(ptr,wiener),idle(ptr,hammer),idle(ptr,bubble),idle(ptr,rock)
#define jumpAll(ptr) create_sprite_animate_action_forever(ptrPile[ptr],1,sprite_items::boxer.tiles_item(),4,4),\
    create_sprite_animate_action_forever(ptrPile[ptr],1,sprite_items::wiener.tiles_item(),5,5),\
    create_sprite_animate_action_forever(ptrPile[ptr],1,sprite_items::hammer.tiles_item(),8,8),\
    create_sprite_animate_action_forever(ptrPile[ptr],1,sprite_items::bubble.tiles_item(),6,6),\
    create_sprite_animate_action_forever(ptrPile[ptr],1,sprite_items::rock.tiles_item(),2,2)                        
namespace arena{
    fixed tangent(int theta){ 
        /* 
            This was originally a pretty fast
            three-liner, but somehow it grew 
            out of control. It's not really
            the best choice when you need
            speed, but it has more features
            than my original implementation, 
            making it more versatile. oh well.
            (sorry if this function makes you
            want to bleach your eyeballs)
        */
        pair<fixed,fixed> sin_cos;
        if(theta<0)
            sin_cos = degrees_lut_sin_and_cos(360-(abs(theta)%360));
        else
            sin_cos = degrees_lut_sin_and_cos(theta%360);
        if(sin_cos.second==0)return (sin_cos.first<0)?9999:-9999; // good enough :/
        if(theta>=0)return sin_cos.first/sin_cos.second;
        return sin_cos.first/sin_cos.second;
    }
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
        sprite_ptr ptrPile[4] = {
            sprite_items::boxer.create_sprite((0-1.5)*32,20),
            sprite_items::null.create_sprite((1-1.5)*32,20),
            sprite_items::null.create_sprite(((2-1.5)*32),20),
            sprite_items::null.create_sprite((3-1.5)*32,20)
        };
        for(int i=0;i<4;i++){
            ptrPile[i].set_visible(false);
        }
        players::player* allPlayers[4] = {
            new players::player(players::picked[0],&ptrPile[0]),
            new players::player(players::picked[1],&ptrPile[1]),
            new players::player(players::picked[2],&ptrPile[2]),
            new players::player(players::picked[3],&ptrPile[3])
        };
        sprite_animate_action<4> fourRunAnims[15] = {
            runAll4(0),
            runAll4(1),
            runAll4(2),
            runAll4(3),
            runAll4(4)
        };
        sprite_animate_action<2> twoRunAnims[10] = {
            runAll2(0),
            runAll2(1),
            runAll2(2),
            runAll2(3),
            runAll2(4)
        };
        sprite_animate_action<2> idleAnims[25] = {
            idleAll(0),
            idleAll(1),
            idleAll(2),
            idleAll(3),
            idleAll(4),
        };
        sprite_animate_action<2> jumpAnims[25]{
            jumpAll(0),
            jumpAll(1),
            jumpAll(2),
            jumpAll(3),
            jumpAll(4)
        };
        for(int i=0;i<4;i++){
            allPlayers[i]->boxerRun = &fourRunAnims[i*5];
            allPlayers[i]->wienerRun = &fourRunAnims[(i*5)+1];
            allPlayers[i]->hammerRun = &fourRunAnims[(i*5)+2];
            allPlayers[i]->bubbleRun = &twoRunAnims[i*5];
            allPlayers[i]->rockRun = &twoRunAnims[(i*5)+1];
            switch(players::picked[i]){
                case 0:
                    allPlayers[i]->idle = &idleAnims[i*5];
                    allPlayers[i]->jumpAnim = &jumpAnims[i*5];
                    break;
                case 1:
                    allPlayers[i]->idle = &idleAnims[(i*5)+1];
                    allPlayers[i]->jumpAnim = &jumpAnims[(i*5)+1];
                    break;
                case 2:
                    allPlayers[i]->idle = &idleAnims[(i*5)+2];
                    allPlayers[i]->jumpAnim = &jumpAnims[(i*5)+2];
                    break;
                case 3:
                    allPlayers[i]->idle = &idleAnims[(i*5)+3];
                    allPlayers[i]->jumpAnim = &jumpAnims[(i*5)+3];
                    break;
                case 4:
                    allPlayers[i]->idle = &idleAnims[(i*5)+4];
                    allPlayers[i]->jumpAnim = &jumpAnims[(i*5)+4];
                    break;
                default:
                    break;
            }
        }
        switch(stages::picked){
            case 0:
                allPlayers[0]->setRespawn(40,40);
                allPlayers[1]->setRespawn(-20,39);
                allPlayers[2]->setRespawn(112,20);
                allPlayers[3]->setRespawn(-105,-1);
                break;
            case 1:
                allPlayers[0]->setRespawn(40,0);
                allPlayers[1]->setRespawn(-40,0);
                allPlayers[2]->setRespawn(15,-25);
                allPlayers[3]->setRespawn(-15,-24);
                break;
            case 2:
                allPlayers[0]->setRespawn(0,37);
                allPlayers[1]->setRespawn(-55,-21);
                allPlayers[2]->setRespawn(55,-21);
                allPlayers[3]->setRespawn(0,-57);
                break;
            case 3:
                allPlayers[0]->setRespawn(10,21);
                allPlayers[1]->setRespawn(-30,21);
                allPlayers[2]->setRespawn(80,-2);
                allPlayers[3]->setRespawn(-60,-29);
                break;
            default:
                allPlayers[0]->setRespawn(0,0);
                allPlayers[1]->setRespawn(0,0);
                allPlayers[2]->setRespawn(0,0);
                allPlayers[3]->setRespawn(0,0);
                return;
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
        animFrame=-50;
        sprite_ptr countDown = sprite_items::count.create_sprite(0,0);
        sprite_animate_action<3> countAnim = create_sprite_animate_action_forever(countDown,90,sprite_items::count.tiles_item(),2,1,0);
        while(animFrame<225){
            countDown.set_position(tangent(animFrame*2)*50,0);
            countAnim.update();
            core::update();
            animFrame++;
        }
        colliders::arena* arenaCollider = new colliders::arena(stages::picked);
        for(int i=0;i<4;i++)allPlayers[i]->arenaCol=arenaCollider;
        controllers::controller* playerController = new controllers::controller(allPlayers[0]);
        while(1){
            playerController->update();
            for(int i=0;i<4;i++){
                allPlayers[i]->update();
                allPlayers[i]->animate();
            }
            core::update();
        }
    }
}