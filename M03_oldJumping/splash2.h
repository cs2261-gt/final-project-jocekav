
//{{BLOCK(splash2)

//======================================================================
//
//	splash2, 256x256@4, 
//	+ palette 256 entries, not compressed
//	+ 162 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 5184 + 2048 = 7744
//
//	Time-stamp: 2020-04-06, 12:04:46
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SPLASH2_H
#define GRIT_SPLASH2_H

#define splash2TilesLen 5184
extern const unsigned short splash2Tiles[2592];

#define splash2MapLen 2048
extern const unsigned short splash2Map[1024];

#define splash2PalLen 512
extern const unsigned short splash2Pal[256];

#endif // GRIT_SPLASH2_H

//}}BLOCK(splash2)
