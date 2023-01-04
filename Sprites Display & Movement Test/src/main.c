#include <genesis.h>
#include <resources.h>

Sprite* player;																								// "Sprite*" is a pointer.

// ----- Variables -----
u16 ind = TILE_USER_INDEX;																					// Setting up graphics tiles into VRAM.

#define ANIM_IDLE 0
#define ANIM_WALK 1

int player_x = 60;																							// Setting up Cinder's X position.
int player_y = 136;																							// Setting up Cinder's Y position.

// ----- Controls -----
static void handleInput()
{
	u16 value = JOY_readJoypad(JOY_1);																		// This u16 value will be determined by the buttons on the controller in Port 1.
	
	if (value & BUTTON_RIGHT) {
		player_x += 3;																						// If the right d-pad button is held down, the player will move 2 pixels to the right every frame.
		SPR_setAnim(player, ANIM_WALK);
		SPR_setHFlip(player, FALSE);
	}
	else if (value & BUTTON_LEFT) {
		player_x -= 3;																						// If the left d-pad button is held down, the player will move 2 pixels to the left every frame.
		SPR_setAnim(player, ANIM_WALK);
		SPR_setHFlip(player, TRUE);
	}

	if (!(value & BUTTON_LEFT) && !(value & BUTTON_RIGHT)) {
		SPR_setAnim(player, ANIM_IDLE);
	}

	SPR_setPosition(player, player_x, player_y);															// Updates the sprite ("player") to the position ("player_x" and "player_y") stated.
}

// ----- Main Code -----
int main()
{
	// ----- Background Rendering -----
	PAL_setPalette(PAL0, bg1.palette->data, DMA);															// Assigning pallette 0 to the colours in background 1's image.
	VDP_drawImageEx(BG_B, &bg1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, -2, FALSE, TRUE);		// Draws background image on the background plane from the determined offset (tiles).
	ind += bg1.tileset->numTile;																			// Enables us to extract tiles from image without overwriting the background's existing ones.

	// ----- Foreground Rendering -----
	PAL_setPalette(PAL1, fg1.palette->data, DMA);															// Assigning pallette 1 to the colours in foreground 1's image.
	VDP_drawImageEx(BG_A, &fg1, TILE_ATTR_FULL(PAL1, TRUE, FALSE, FALSE, ind), 0, -4, FALSE, TRUE);			// Draws foreground image on the foreground plane from the determined offset (tiles).

	// ----- Sprite Rendering -----
	SPR_init();																								// Initialising Sprite Engine.
	PAL_setPalette(PAL2, cdr_sheet.palette->data, DMA);														// Assigning pallette 2 to the colours in Cinder's sprite.
	player = SPR_addSprite(&cdr_sheet, player_x, player_y, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));			// Draws Cinder sprite at the determined position (pixels), represented by "player_x" & "player_y".
	

	// ----- Background Scroll Setup -----
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);														// Enables scrolling by planes, and how much it scrolls by.

	// ----- Repeat Every Frame -----
	while(1)
	{   
		handleInput();																						// Calls the controller input function.
		SPR_update();																						// Updates sprites every frame.
		SYS_doVBlankProcess();																				// Refresh screen every frame.
	}
	return (0);
}
