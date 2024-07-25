#include <tonc.h>
#include "mode7.h"
#include "world.h"
#include "daySky.h"
#include "bgpal.h"
#define SPRITE_COUNT 30
M7_CAM m7_cam;
BG_AFFINE m7_bgaffs[SCREEN_HEIGHT+1];
M7_SPRITE m7_sprites[SPRITE_COUNT];
M7_LEVEL m7_level;
bool inventory;
u8 sort_ids[SPRITE_COUNT];
int sort_keys[SPRITE_COUNT];
const M7_CAM m7_defualt = {
    {0x0D100,0x1900,0x38800},
    0x0A00,0x2600,
    {256,0,0},{0,256,0},{0,0,256}
};
int main(){
    m7_init(
        &m7_level,&m7_cam,m7_bgaffs,m7_sprites,BG_CBB(0)|BG_SBB(22)|BG_REG_64x32|BG_PRIO(3),BG_CBB(0)|BG_SBB(24)|BG_AFF_128x128|BG_WRAP|BG_PRIO(3));
    *m7_level.camera = m7_defualt;
    //ground
    LZ77UnCompVram(bgPal,pal_bg_mem);
    LZ77UnCompVram(worldTiles,tile_mem[0]);
    LZ77UnCompVram(worldMap,se_mem[24]);
    //fog
    REG_BLDCNT = BLD_BUILD(BLD_BG2,BLD_BACKDROP,1);
    pal_bg_mem[0] = CLR_ORANGE;
    //sky
    LZ77UnCompVram(daySkyTiles,&tile_mem[0][128]);
    LZ77UnCompVram(daySkyMap,se_mem[22]);
    REG_DISPCNT = DCNT_MODE1|DCNT_BG2|DCNT_OBJ|DCNT_OBJ_1D;
    irq_init(NULL);
    irq_add(II_HBLANK,(fnptr)m7_hbl_floor);
    irq_add(II_VBLANK,NULL);
    while(1){
        VBlankIntrWait();
        m7_prep_horizon(&m7_level);
        if(m7_level.horizon>0){
            BFN_SET(REG_DISPCNT,DCNT_MODE0,DCNT_MODE);
            REG_BG2CNT = m7_level.bgcnt_sky;
            REG_BLDALPHA = 16;
        }
        m7_update_sky(&m7_level);
        m7_prep_affines(&m7_level);
    }
}