#include <genesis.h>
#include <resources.h>

// ----- Variables -----
u16 ind = TILE_USER_INDEX;																					// Setting up graphics tiles into VRAM.
int hscroll_offeset_bg = 0;																					// Background horizontal scrolling offset value.
int hscroll_offeset_fg = 0;																					// Background horizontal scrolling offset value.

int main()
{
	// ----- Background Rendering -----
	PAL_setPalette(PAL0, bg1.palette->data, DMA);															// Assigning pallette 0 to the colours in background 1's image.
	VDP_drawImageEx(BG_B, &bg1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, -4, FALSE, TRUE);		// Draws background image on the background plane from the top-left of the screen.
	ind += bg1.tileset->numTile;																			// Enables us to extract tiles from image without overwriting the background's existing ones.

	// ----- Foreground Rendering -----
	PAL_setPalette(PAL1, fg1.palette->data, DMA);															// Assigning pallette 1 to the colours in foreground 1's image.
	VDP_drawImageEx(BG_A, &fg1, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, -4, FALSE, TRUE);		// Draws foreground image on the foreground plane from the top-left of the screen.

	// ----- Text Rendering -----
	VDP_drawText("Welcome to Freeheart Forest", 8, 13);														// Draws text at designated position.

	// ----- Background Scroll Setup -----
	VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);														// Enables scrolling by planes, and how much it scrolls by.

	// ----- Repeat Every Frame -----
	while(1)
	{        
		// ----- Background Scrolling -----
		hscroll_offeset_bg -= 1;
		VDP_setHorizontalScroll(BG_B, hscroll_offeset_bg);													// Scrolls the background plane by the assigned amount.

		// ----- Foreground Scrolling -----
		hscroll_offeset_fg -= 2;
		VDP_setHorizontalScroll(BG_A, hscroll_offeset_fg);													// Scrolls the background plane by the assigned amount.

		SYS_doVBlankProcess();																				// Refresh screen every frame.
		VDP_waitVSync();
	}
	return (0);
}
