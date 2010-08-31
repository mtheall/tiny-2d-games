// MiniWars - A stylised 2D FPS
// Copyright 2008-2009 Steve Schnepp <steve.schnepp@pwkf.org>
//
// The code is a little bit messy, but it's rather a work-in-progress than a 
// finished product. It will clean itself through the various refactorings

// Includes
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>

#include <ext/slist>
#include <list>
#include <vector>

#include "nds_utils.h"

#include "MovableSprite.h"

void flip_vram()
{
	if (front == VRAM_A) {
		front = VRAM_B;
		back = VRAM_A;
		videoSetMode(MODE_FB1);			
	} else {
		front = VRAM_A;
		back = VRAM_B;
		videoSetMode(MODE_FB0);			
	}
}

void initVideo() {
    /*
     *  Map VRAM to display a background on the main and sub screens.
     * 
     *  The vramSetMainBanks function takes four arguments, one for each of the
     *  major VRAM banks. We can use it as shorthand for assigning values to
     *  each of the VRAM bank's control registers.
     *
     *  We map banks A and B to main screen background memory. This gives us
     *  256KB, which is a healthy amount for 16-bit graphics.
     *
     *  We map bank C to sub screen background memory.
     *
     *  We map bank D to LCD. This setting is generally used for when we aren't
     *  using a particular bank.
     */
    /*vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000,
                     VRAM_B_MAIN_BG_0x06020000,
                     VRAM_C_SUB_BG_0x06200000,
                     VRAM_D_LCD);
	*/
    vramSetMainBanks(VRAM_A_LCD, VRAM_B_LCD, VRAM_C_SUB_BG, VRAM_D_SUB_SPRITE);							

	//set main display to render directly from the frame buffer
	videoSetMode(MODE_FB0);
	
    // /*  Set the video mode on the main screen. */
    /* videoSetMode(MODE_5_2D | // Set the graphics mode to Mode 5
                 DISPLAY_BG2_ACTIVE | // Enable BG2 for display
                 DISPLAY_BG3_ACTIVE); //Enable BG3 for display
*/
    /*  Set the video mode on the sub screen. */
    videoSetModeSub(MODE_5_2D | // Set the graphics mode to Mode 5
                    DISPLAY_BG3_ACTIVE); // Enable BG3 for display
}

void initBackgrounds() {
    /*  Set up affine background 3 on main as a 16-bit color background. */
    REG_BG3CNT = BG_BMP16_256x256 |
                 BG_BMP_BASE(0) | // The starting place in memory
                 BG_PRIORITY(3); // A low priority

    /*  Set the affine transformation matrix for the main screen background 3
     *  to be the identity matrix.
     */
    REG_BG3PA = 1 << 8;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 1 << 8;

    /*  Place main screen background 3 at the origin (upper left of the
     *  screen).
     */
    REG_BG3X = 0;
    REG_BG3Y = 0;

    /*  Set up affine background 2 on main as a 16-bit color background. */
    REG_BG2CNT = BG_BMP16_128x128 |
                 BG_BMP_BASE(8) | // The starting place in memory
                 BG_PRIORITY(2);  // A higher priority

    /*  Set the affine transformation matrix for the main screen background 3
     *  to be the identity matrix.
     */
    REG_BG2PA = 1 << 8;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 1 << 8;

    /*  Place main screen background 2 in an interesting place. */
    REG_BG2X = -(SCREEN_WIDTH / 2 - 32) << 8;
    REG_BG2Y = -32 << 8;

    /*  Set up affine background 3 on the sub screen as a 16-bit color
     *  background.
     */
    REG_BG3CNT_SUB = BG_BMP16_256x256 |
                     BG_BMP_BASE(0) | // The starting place in memory
                     BG_PRIORITY(3); // A low priority

    /*  Set the affine transformation matrix for the sub screen background 3
     *  to be the identity matrix.
     */
    REG_BG3PA_SUB = 1 << 8;
    REG_BG3PB_SUB = 0;
    REG_BG3PC_SUB = 0;
    REG_BG3PD_SUB = 1 << 8;

    /*
     *  Place main screen background 3 at the origin (upper left of the screen)
     */
    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;
}

typedef std::vector<MovableSprite*> particles_list;
particles_list particles;

// Function: main()
int main(int argc, char *argv[]) {
	/*  Turn on the 2D graphics core. */
	powerOn(POWER_ALL_2D);
 
	 /*  Configure the VRAM and background control registers. */
	lcdMainOnBottom(); // Place the main screen on the bottom physical screen
	initVideo(); 
	initBackgrounds(); 
	
	consoleDemoInit();
	// BG_PALETTE_SUB[255] = RGB15(31,31,31);	//by default font will be rendered with color 255
	
	// Infinite loop to keep the program running
	while (1) {
		static volatile int frame = 0;
		frame++;
		
		static touchPosition touch;
		touchRead(&touch);
		
		scanKeys();
		PA_CheckLid();


		// checkReset(held);

		// --------
		// Do stuff
		// --------
		int held = keysHeld();
		if (held & KEY_UP) {
		} else if (held & KEY_DOWN) {
		}
		
		if (held & KEY_RIGHT) {
		} else if (held & KEY_LEFT) {
		}
		
		if (held & KEY_A) {
		} else if (held & KEY_B) {
		}

		if (held & KEY_TOUCH) {
		}

		// Draws every Particle on the back screen
		for(particles_list::iterator i = particles.begin(); i != particles.end(); ++i) {
			MovableSprite* particle = *i;
			particle->draw();
		}

		// flip screens
		flip_vram();

		// erase back screen
		uint16 col = RGB15(0, 0, 0) | BIT(15);
		uint32 colcol = col | col << 16;
		swiFastCopy(&colcol, back, 192*256*2/4 | COPY_MODE_FILL);
		
		PA_CheckLid();
		swiWaitForVBlank();
	}
	
	return 0;
} // End of main()
