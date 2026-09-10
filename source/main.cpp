#include <nds.h>
#include <stdio.h>

typedef struct {
    int x, y;
    int speed;
} Player;

typedef struct {
    int x, y;
    bool active;
} Laser;

int main(void) {
    videoSetMode(MODE_5_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankB(VRAM_B_MAIN_SPRITE);
    vramSetBankC(VRAM_C_SUB_BG);

    consoleInit(NULL, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);

    Player p = {120, 150, 3};
    Laser lasers[8];
    for(int i = 0; i < 8; i++) lasers[i].active = false;

    int score = 0;
    int energy = 100;

    iprintf("\x1b[0;2H=== CYBER QUEST DSI ===");
    iprintf("\x1b[2;2HCroix: Bouger | A: Tir");
    iprintf("\x1b[3;2HTactile: TP le vaisseau !");

    touchPosition touch;

    while(1) {
        scanKeys();
        int keys = keysHeld();
        int down = keysDown();

        if(keys & KEY_LEFT && p.x > 8)  p.x -= p.speed;
        if(keys & KEY_RIGHT && p.x < 224) p.x += p.speed;
        if(keys & KEY_UP && p.y > 20)   p.y -= p.speed;
        if(keys & KEY_DOWN && p.y < 176) p.y += p.speed;

        if(down & KEY_A) {
            for(int i = 0; i < 8; i++) {
                if(!lasers[i].active) {
                    lasers[i].x = p.x + 6;
                    lasers[i].y = p.y;
                    lasers[i].active = true;
                    break;
                }
            }
        }

        touchRead(&touch);
        if(keys & KEY_TOUCH) {
            if(touch.px > 0 && touch.px < 256 && touch.py > 0 && touch.py < 192) {
                p.x = touch.px;
                p.y = touch.py;
                score += 5;
            }
        }

        for(int i = 0; i < 8; i++) {
            if(lasers[i].active) {
                lasers[i].y -= 6;
                if(lasers[i].y < 0) lasers[i].active = false;
            }
        }

        iprintf("\x1b[16;2HScore: %d     ", score);
        iprintf("\x1b[17;2HEnergie: %d%%   ", energy);
        iprintf("\x1b[19;2HCoords: X=%3d Y=%3d", p.x, p.y);

        swiWaitForVBlank();
    }
    return 0;
}
