
//{{BLOCK(gameBg)

//======================================================================
//
//	gameBg, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 28 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 896 + 2048 = 3456
//
//	Time-stamp: 2020-04-06, 12:12:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GAMEBG_H
#define GRIT_GAMEBG_H

#define gameBgTilesLen 896
extern const unsigned short gameBgTiles[448];

#define gameBgMapLen 2048
extern const unsigned short gameBgMap[1024];

#define gameBgPalLen 512
extern const unsigned short gameBgPal[256];

#endif // GRIT_GAMEBG_H

//}}BLOCK(gameBg)
