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
#include "bn_log.h"
#include "bn_log_backend.h"
#include "bn_random.h"
#include "bn_deque.h"
#include "bn_music_actions.h"
#include "bn_sprite_actions.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_palette_actions.h"
#include "bn_sprite_affine_mat_actions.h"
#include "bn_sprite_ptr.h"

#include "bn_sprite_items_boxer.h"
#include "bn_sprite_items_wiener.h"
#include "bn_sprite_items_bubble.h"
#include "bn_sprite_items_rock.h"
#include "bn_sprite_items_hammer.h"
#include "bn_sprite_items_spotlight.h"
#include "bn_sprite_items_null.h"
#include "bn_sprite_items_curtain.h"

#include "bn_regular_bg_items_mountains.h"
#include "bn_regular_bg_items_foliage.h"
#include "bn_regular_bg_items_space.h"
#include "bn_regular_bg_items_night.h"

#include "stage_select.hpp"
#include "player_select.hpp"

#define tBoxer 0;
#define tBubble 1;
#define tHammer 2;
#define tRock 3;
#define tWiener 4;
#define tNull 5;

#ifndef __PLAYER_DEFINED__
#define __PLAYER_DEFINED__
namespace players{
    class player{
        public:
            player(int fighter, bn::sprite_ptr* sprPtr);
            void update();
            void setRespawn(int x, int y);
            void walk(bool left);
            void jump();
            void dontWalk();
            void animate();
            ~player();
            int playType;
            unsigned int falls;
            unsigned int kos;
            unsigned int damage;
            bool stunned;
            bool inAir;
            int respawn[2];
            bn::fixed velocity[2];
            bn::fixed currentWalk;
            bn::fixed maxWalk;
            bn::fixed walkSpeed;
            bn::fixed jumpPower;
            bn::sprite_animate_action<4>* boxerRun;
            bn::sprite_animate_action<4>* wienerRun;
            bn::sprite_animate_action<4>* hammerRun;
            bn::sprite_animate_action<2>* bubbleRun;
            bn::sprite_animate_action<2>* rockRun;
            bn::sprite_animate_action<2>* idle;
        private:
            bn::sprite_ptr* sprite = nullptr;
    };
}
#endif