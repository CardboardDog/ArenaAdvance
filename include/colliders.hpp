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

#ifndef __COLLIDERS_THING_IDK__
#define __COLLIDERS_THING_IDK__
namespace colliders{
    class arena{
        public:
            arena(int stage);
            bool pointIn(bn::fixed x, bn::fixed y);
            int cStage;
    };
}
#endif