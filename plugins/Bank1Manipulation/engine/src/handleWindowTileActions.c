#include <asm/types.h>
#include <stdint.h>
#pragma bank 255

#include "vm.h"
#include <gb/gb.h>
#include "data_manager.h"
#include "load_save.h"

union tile {
    uint8_t _tile;
    struct {
        unsigned char palette : 3;
        unsigned char bank : 1;
        unsigned char nothing : 1;
        unsigned char flip_h : 1;
        unsigned char flip_v : 1;
        unsigned char draw_over_objects : 1;
    } attr;
};

union tile_var {
    UWORD _var;
    struct {
        UBYTE b0_tile;
        UBYTE b1_tile;
    } tiles;
};

union tile_vram {
    UWORD _var;
    struct {
        uint8_t b0_tile;
        uint8_t b1_tile;
    } tiles;
};

void drawWinTileOverObjects(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t * win_tile_addr;
    union tile win_tile;
    //union tile win_tile;

    uint16_t col = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG1));
    uint16_t row =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0));

    
    VBK_REG = VBK_BANK_1;
    win_tile_addr = get_win_xy_addr(col, row);
    win_tile._tile = get_vram_byte(win_tile_addr);
    
    win_tile.attr.draw_over_objects = 1;
    
    set_vram_byte(win_tile_addr, win_tile._tile);
    VBK_REG = VBK_BANK_0;
}

void drawWinTileUnderObjects(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t * win_tile_addr;
    union tile win_tile;
    //union tile win_tile;

    uint16_t col = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG1));
    uint16_t row =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0));

    
    VBK_REG = VBK_BANK_1;
    win_tile_addr = get_win_xy_addr(col, row);
    win_tile._tile = get_vram_byte(win_tile_addr);
    
    win_tile.attr.draw_over_objects = 0;
    
    set_vram_byte(win_tile_addr, win_tile._tile);
    VBK_REG = VBK_BANK_0;
}

void setWinTileColor(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t * win_tile_addr;
    union tile win_tile;
    //union tile win_tile;

    uint16_t pal = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG2));
    uint16_t col = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG1));
    uint16_t row = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0));

    
    VBK_REG = VBK_BANK_1;
    win_tile_addr = get_win_xy_addr(col, row);
    win_tile._tile = get_vram_byte(win_tile_addr);
    
    win_tile.attr.palette = pal;
    
    set_vram_byte(win_tile_addr, win_tile._tile);
    VBK_REG = VBK_BANK_0;
}

void incrementWinTileColor(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t * win_tile_addr;
    union tile win_tile;
    //union tile win_tile;

    uint16_t col = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG1));
    uint16_t row =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0));

    
    VBK_REG = VBK_BANK_1;
    win_tile_addr = get_win_xy_addr(col, row);
    win_tile._tile = get_vram_byte(win_tile_addr);
    
    win_tile.attr.palette++;
    
    set_vram_byte(win_tile_addr, win_tile._tile);
    VBK_REG = VBK_BANK_0;
}

void decrementWinTileColor(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t * win_tile_addr;
    union tile win_tile;
    //union tile win_tile;

    uint16_t col = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG1));
    uint16_t row =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0));

    
    VBK_REG = VBK_BANK_1;
    win_tile_addr = get_win_xy_addr(col, row);
    win_tile._tile = get_vram_byte(win_tile_addr);
    
    win_tile.attr.palette--;
    
    set_vram_byte(win_tile_addr, win_tile._tile);
    VBK_REG = VBK_BANK_0;
}

void flipWinTileX(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t * win_tile_addr;
    union tile win_tile;
    //union tile win_tile;

    uint16_t col = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG1));
    uint16_t row =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0));

    
    VBK_REG = VBK_BANK_1;
    win_tile_addr = get_win_xy_addr(col, row);
    win_tile._tile = get_vram_byte(win_tile_addr);
    //win_tile._tile = get_vram_byte(win_tile_addr);
    win_tile.attr.flip_h = ~(win_tile.attr.flip_h);
    
    set_vram_byte(win_tile_addr, win_tile._tile);
    VBK_REG = VBK_BANK_0;
}

void flipWinTileY(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t * win_tile_addr;
    union tile win_tile;
    //union tile win_tile;

    uint16_t col = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG1));
    uint16_t row =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0));

    
    VBK_REG = VBK_BANK_1;
    win_tile_addr = get_win_xy_addr(col, row);
    win_tile._tile = get_vram_byte(win_tile_addr);
    //win_tile._tile = get_vram_byte(win_tile_addr);
    win_tile.attr.flip_v = ~(win_tile.attr.flip_v);
    
    set_vram_byte(win_tile_addr, win_tile._tile);
    VBK_REG = VBK_BANK_0;
}

void rotateWinTile(SCRIPT_CTX * THIS) OLDCALL BANKED {
    THIS;
    uint8_t * win_tile_addr;
    union tile win_tile;
    //union tile win_tile;

    uint16_t col = (*(uint16_t *) VM_REF_TO_PTR(FN_ARG1));
    uint16_t row =  (*(uint16_t *) VM_REF_TO_PTR(FN_ARG0));

    
    VBK_REG = VBK_BANK_1;
    win_tile_addr = get_win_xy_addr(col, row);
    win_tile._tile = get_vram_byte(win_tile_addr);
    //win_tile._tile = get_vram_byte(win_tile_addr);
    if(
        !win_tile.attr.flip_h &&
        !win_tile.attr.flip_v
    ){
        win_tile.attr.flip_h = ~(win_tile.attr.flip_h);
    } else if (
        win_tile.attr.flip_h &&
        !win_tile.attr.flip_v
    ){
        win_tile.attr.flip_v = ~(win_tile.attr.flip_v);
    } else if (
        win_tile.attr.flip_h &&
        win_tile.attr.flip_v
    ){
        win_tile.attr.flip_h = ~(win_tile.attr.flip_h);
    } else if (
        !win_tile.attr.flip_h &&
        win_tile.attr.flip_v
    ){
        win_tile.attr.flip_v = ~(win_tile.attr.flip_v);
    }
    set_vram_byte(win_tile_addr, win_tile._tile);
    VBK_REG = VBK_BANK_0;
}