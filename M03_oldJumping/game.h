// CLOUD Struct
typedef struct {
	int type;
	int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
	int height;
	int width;
	int velx;
	int vely;
	int aniCounter;
    int aniState;
	int curFrame;
    int numFrames;
    int active;
	int disappear;
    int hide;
    int counter;
    int hasCoin;
    int hasWings;
} CLOUD;


// PIG Struct
typedef struct {
	int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int velx;
    int vely;
	int midAir;
	int timeInAir;
    int width;
    int height;
    int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;
    int hide;
    int cloud;
    int flight;
} PIG;

typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int height;
    int width;
    int active;
    int hide;
    int type;
} COIN;

typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int height;
    int width;
    int active;
    int hide;
    int time;
} WINGS;

//Enum for cloud size 
enum {XL, LG, MED, SM};

//Enume for coins
enum {GOLD = 15, SILVER = 10, BRONZE = 5};

// Constants
#define GROUND 100
#define NUMCLOUDS 3
#define NUMCOINS 2

// Variables
extern PIG pig;
extern CLOUD clouds[NUMCLOUDS];
extern COIN coins[NUMCOINS];
extern COIN coin;
extern WINGS wings;
extern int loser;
extern int vOff;


// Prototypes
void initGame();
void updateGame();
void drawGame();
void initPig();
void initClouds();
void drawPig();
void drawClouds();
void updatePig();
void updateClouds();
void cloudCollisions();
void getCloudDim();
void drawScore();
void updateScore();
void coinCollisions();
void drawCoins();
void initCoins();
void addCoin(CLOUD* cloud);
void initWings();
void drawWings();
void addWings(CLOUD* cloud);
void wingsCollisions();

