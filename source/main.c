#include <tonc.h>
#include "mode7.h"
#include "world.h"
#include "daySky.h"
#include "tree.h"
#include "newWorld.h"
#include "bg.h"
#include "obj.h"
#include "objpal.h"
#include <limits.h>
#define SPRITE_COUNT 20
M7_CAM m7_cam;
BG_AFFINE m7_bgaffs[SCREEN_HEIGHT+1];
M7_SPRITE m7_sprites[SPRITE_COUNT];
M7_LEVEL m7_level;
bool inventory;
u8 sort_ids[SPRITE_COUNT];
int sort_keys[SPRITE_COUNT];
IWRAM_CODE void id_sort_shell(int keys[], u8 ids[], int count);
const M7_CAM m7_defualt = {
    {0x0D100,0x1900,0x38800},
    0x0A00,0x2600,
    {256,0,0},{0,256,0},{0,0,256}
};
void move_player(){
    key_poll();
    M7_CAM *cam = m7_level.camera;
    VECTOR dir = {0,0,0};
    dir.z = 520*key_tri_fire();
    m7_rotate(
        cam,
        cam->phi+(320*key_tri_horz()),
        cam->theta+(320*key_tri_vert())
    );
    m7_translate_local(cam,&dir);
}
void setup_environment(){
    LZ77UnCompVram(objPal,pal_obj_mem);
    LZ77UnCompVram(treeTiles,&tile_mem[4][16]);
    M7_SPRITE *sprite = m7_level.sprites;
    for(int i=0;i<SPRITE_COUNT;i++){
        sprite->pos = spritesPos[i];
        sprite->anchor.x = 16;
        sprite->anchor.y = 30;
        obj_set_attr(&sprite->obj,ATTR0_SQUARE|ATTR0_AFF_DBL,ATTR1_SIZE_32|ATTR1_AFF_ID(i+8),0x4410);
        sprite->phi = 0;
        sprite->obj_id = i+8;
        sprite->aff_id = i+8;
        sprite->tiles = NULL;
        sprite++;
    }
    for (int i=0;i<SPRITE_COUNT;i++){
        sort_ids[i] = i;
    }
}
void simulate_environment(){
    M7_SPRITE* sprite = m7_level.sprites;
    for(int i=0;i<SPRITE_COUNT;i++){
        m7_prep_sprite(&m7_level,&sprite[i]);
        if(BFN_GET2(sprite[i].obj.attr0,ATTR0_MODE)!=ATTR0_HIDE){
            sort_keys[i] = sprite[i].pos2.z;
        }else{
            sort_keys[i] = INT_MAX;
        }
    }
    id_sort_shell(sort_keys,sort_ids,SPRITE_COUNT);
    for(int i=0;i<SPRITE_COUNT;i++){
        obj_copy(&oam_mem[i],&sprite[sort_ids[i]].obj,1);
    }
}
int main(){
    m7_init(
        &m7_level,&m7_cam,m7_bgaffs,m7_sprites,BG_CBB(0)|BG_SBB(22)|BG_4BPP|BG_REG_64x32|BG_PRIO(3),BG_CBB(0)|BG_SBB(24)|BG_AFF_128x128|BG_WRAP|BG_PRIO(3));
    *m7_level.camera = m7_defualt;
    //ground
    LZ77UnCompVram(bgPal,pal_bg_mem);
    LZ77UnCompVram(worldTiles,tile_mem[0]);
    LZ77UnCompVram(worldMap,se_mem[24]);
    //fog
    REG_BLDCNT = BLD_BUILD(BLD_BG2,BLD_BACKDROP,1);
    pal_bg_mem[0] = CLR_SKYBLUE;
    //sky
    LZ77UnCompVram(daySkyTiles,&tile_mem[0][128]);
    LZ77UnCompVram(daySkyMap,se_mem[22]);
    //trees
    oam_init(oam_mem,128);
    setup_environment();
    //gba mode 1/setup
    REG_DISPCNT = DCNT_MODE1|DCNT_BG2|DCNT_OBJ|DCNT_OBJ_1D;
    irq_init(NULL);
    irq_add(II_HBLANK,(fnptr)m7_hbl_floor);
    irq_add(II_VBLANK,NULL);
    while(1){
        VBlankIntrWait();
        move_player();
        m7_prep_horizon(&m7_level);
        if(m7_level.horizon>0){
            BFN_SET(REG_DISPCNT,DCNT_MODE0,DCNT_MODE);
            REG_BG2CNT = m7_level.bgcnt_sky;
            REG_BLDALPHA = 16;
        }
        m7_update_sky(&m7_level);
        simulate_environment();
        m7_prep_affines(&m7_level);
    }
}