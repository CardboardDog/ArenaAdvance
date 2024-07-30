#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_blending.h"
#include "bn_bg_palettes.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprites_mosaic.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_builder.h"
#include "bn_sprites_actions.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_first_attributes.h"
#include "bn_sprite_third_attributes.h"
#include "bn_sprite_position_hbe_ptr.h"
#include "bn_sprite_first_attributes_hbe_ptr.h"
#include "bn_sprite_third_attributes_hbe_ptr.h"
#include "bn_sprite_affine_second_attributes.h"
#include "bn_sprite_regular_second_attributes.h"
#include "bn_sprite_affine_second_attributes_hbe_ptr.h"
#include "bn_sprite_regular_second_attributes_hbe_ptr.h"

#include "bn_sprite_items_boxer.h"
#include "bn_sprite_items_wiener.h"
#include "bn_sprite_items_bubble.h"
#include "bn_sprite_items_rock.h"
#include "bn_sprite_items_hammer.h"
#include "bn_regular_bg_items_mountains.h"

namespace{
    void test_scene(){
        bn::sprite_ptr boxer = bn::sprite_items::boxer.create_sprite(0,0);
        bn::sprite_ptr wiener = bn::sprite_items::wiener.create_sprite(-20,0);
        bn::sprite_ptr hammer = bn::sprite_items::hammer.create_sprite(25,0);
        bn::sprite_ptr bubble = bn::sprite_items::bubble.create_sprite(-40,0);
        bn::sprite_ptr rock = bn::sprite_items::rock.create_sprite(40,0);

        bn::sprite_animate_action<4> boxer_run = bn::create_sprite_animate_action_forever(boxer,8,bn::sprite_items::boxer.tiles_item(),0,1,2,3);
        bn::sprite_animate_action<4> wiener_run = bn::create_sprite_animate_action_forever(wiener,4,bn::sprite_items::wiener.tiles_item(),0,1,2,3);
        bn::sprite_animate_action<4> hammer_run = bn::create_sprite_animate_action_forever(hammer,16,bn::sprite_items::hammer.tiles_item(),1,2,3,4);
        bn::sprite_animate_action<2> bubble_run = bn::create_sprite_animate_action_forever(bubble,32,bn::sprite_items::bubble.tiles_item(),0,1);
        bn::sprite_animate_action<2> rock_run = bn::create_sprite_animate_action_forever(rock,4,bn::sprite_items::rock.tiles_item(),0,1);
        
        bn::regular_bg_ptr mountains = bn::regular_bg_items::mountains.create_bg(0,0);

        while(1){
            boxer_run.update();
            wiener_run.update();
            hammer_run.update();
            bubble_run.update();
            rock_run.update();
            bn::core::update();
            boxer.set_visible(true);
        }
    }
}

int main(){
    bn::core::init();
    while(1){
        test_scene();
        bn::core::update();
    }
}