#include <genesis.h>
#include <resources.h>

Sprite* player;																								// "Sprite*" is a pointer.

// ----- Variables -----
u16 ind = TILE_USER_INDEX;																					// Setting up graphics tiles into VRAM.
int anim = 0;																								// Setting up an animation controller value.

int main()																									// Initial Setup
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
	player = SPR_addSprite(&cdr_sheet, 60, 136, TILE_ATTR(PAL2, FALSE, FALSE, FALSE));						// Draws Cinder sprite at the determined position (pixels).
	SPR_setAnim(player, anim);																				// Initialising the Animation Function and setting it to an animation index represented by the anim integer (which line of sprites to play).

	// ----- Background Scroll Setup -----
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);														// Enables scrolling by planes, and how much it scrolls by.

	// ----- Repeat Every Frame -----
	while(1)
	{        



		SPR_update();																						// Updates sprites every frame.
		SYS_doVBlankProcess();																				// Refresh screen every frame.
		VDP_waitVSync();
	}
	return (0);
}
