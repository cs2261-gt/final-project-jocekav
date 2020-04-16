
//{{BLOCK(pauseBg)

//======================================================================
//
//	pauseBg, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 240 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 7680 + 2048 = 10240
//
//	Time-stamp: 2020-04-08, 20:28:22
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PAUSEBG_H
#define GRIT_PAUSEBG_H

#define pauseBgTilesLen 7680
extern const unsigned short pauseBgTiles[3840];

#define pauseBgMapLen 2048
extern const unsigned short pauseBgMap[1024];

#define pauseBgPalLen 512
extern const unsigned short pauseBgPal[256];

#endif // GRIT_PAUSEBG_H

//}}BLOCK(pauseBg)
