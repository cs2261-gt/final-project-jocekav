#include <stdlib.h>
#include "myLib.h"
#include "game.h"

// Variables
PIG pig;
CLOUD clouds[NUMCLOUDS];
COIN coins[NUMCOINS];
COIN coin;
WINGS wings;
extern int time;
int score;
int vOff;
int timestep = 2;
int floor;
int flag;
int topRow;
int topCol;
int ones;
int tens;
int hundreds;
int thousands;
int oldFloor;


// Initialize the game
void initGame() {

	initPig();
	initClouds();
	initCoins();
	initWings();
	drawClouds();
	drawPig();
	drawCoins();
	vOff = 0;
	flag = 0;
	score = 0;
	floor = SCREENHEIGHT - pig.height;
	oldFloor = floor;
}

// Updates the game each frame
void updateGame() {
	time++;
	updatePig();
	updateClouds();
	updateScore();
    REG_BG0VOFF = vOff;
}

//draws the game
void drawGame() {
	// draw pig
	drawPig();
	//draw clouds
	drawClouds();
	//draw coins
	drawCoins();
	//draw the wings
	drawWings();
	//draw the score
	drawScore();

	waitForVBlank();
	DMANow(3, shadowOAM, OAM, 512);
}

//update the pig's position
void updatePig() {
	//check collisions with the clouds, coins, and wings
	cloudCollisions();
	coinCollisions();
	wingsCollisions();

	//check which button the user pressed and increment velocity and direction accordingly
	if (BUTTON_HELD(BUTTON_RIGHT)) {
		pig.velx = 2;
		if (pig.screenCol + pig.width + 2 > SCREENWIDTH) {
			pig.velx = 0;
		}
	} else if (BUTTON_HELD(BUTTON_LEFT)) {
		pig.velx = -2;
		if (pig.screenCol - 2 < 0) {
			pig.velx = 0;
		}
	} 
	//update x position
	pig.screenCol += pig.velx;
	pig.velx = 0;
	
	//the pig is in the air if it is not touching the "floor"
	pig.midAir = pig.screenRow != floor;

	//if the pig jumps set the velocity, but dont allow jumping while jumping
	if (BUTTON_PRESSED(BUTTON_UP) && !pig.midAir) {
		pig.vely = -7;
		pig.midAir = 1;
		pig.timeInAir = 1;
	} 

	//if the pig is in the air, implement psuedo-gravity (ignore gravity during flight)
	if (pig.midAir && !pig.flight) {
			pig.vely = -7 + (pig.timeInAir / 2);
			pig.timeInAir++;
	}

	//if the pig is in flight, double the shift for some of the time, and count until flight is over
	if (pig.flight) {
		pig.vely = 0;
		if (wings.time > 50) {
			vOff-= 2;
			for(int i = 0; i < NUMCLOUDS; i++) {
				if (clouds[i].active) {
					clouds[i].screenRow += 2;
				}
			}
			if (coin.active) {
				coin.screenRow += 2;
			}
		} else if (wings.time < 50) {
			vOff--;
			for(int i = 0; i < NUMCLOUDS; i++) {
				if (clouds[i].active) {
					clouds[i].screenRow++;
				}
			}
			if (coin.active) {
				coin.screenRow++;
			}
		}
		if (wings.time == 0) {
			pig.flight = 0;
		}
		wings.time--;
	}
	//update y position
	pig.screenRow += pig.vely;

	//if the pig passes the floor, stop jumping (ignore during flight)
	if (pig.screenRow >= floor && !pig.flight) {
		pig.screenRow = floor;
		pig.midAir = 0;
		pig.vely = 0;
	}

	//shift screen and clouds if pig is above the 80th row
	if (pig.screenRow < 80 && oldFloor != floor) {
        vOff--;
		for(int i = 0; i < NUMCLOUDS; i++) {
			if (clouds[i].active) {
				clouds[i].screenRow++;
				topRow++;
			}
		}
		if (coin.active) {
			coin.screenRow++;
		}
		if (wings.active) {
			wings.screenRow++;
		}
		score += 1;
    }

	//check for a loss if the pig is at the bottom of the screen (only checks after first cloud jump)
	if (pig.screenRow >= (SCREENHEIGHT - pig.height) && flag) {
		loser = 1;
	}
}

//update the clouds
void updateClouds() {
	for (int i = 0; i < NUMCLOUDS; i++) {
		//if the cloud is active, but half is below the screen, deactivate
		if (clouds[i].active && ((clouds[i].screenRow + clouds[i].height/2) > SCREENHEIGHT)){
			clouds[i].active = 0;
		}
		if (clouds[i].active && (clouds[i].screenRow > 20) && clouds[i].hasCoin) {
			clouds[i].hasCoin = 0;
			addCoin(&clouds[i]);
		}
		if (clouds[i].active && (clouds[i].screenRow > 20) && clouds[i].hasWings) {
			clouds[i].hasWings = 0;
			addWings(&clouds[i]);
		}
		//activate the next cloud
		if (!clouds[i].active) {
			clouds[i].active = 1;
			clouds[i].screenRow = 0;
			clouds[i].aniState = 0;
			clouds[i].hide = 0;
			//randomly determine breaking cloud
			clouds[i].disappear = rand() % 2;
			topRow = clouds[i].screenRow;
			//randomly set x position
			clouds[i].screenCol = 20 + (rand() % 100);
			if ((clouds[i].screenCol + clouds[i].width) >= SCREENWIDTH) {
				clouds[i].screenCol = SCREENWIDTH - clouds[i].width ;
			}
			clouds[i].counter = 0;
			if (rand() % 3 == 0) {
				clouds[i].hasCoin = 1;
			}
			if (rand() % 4 == 0 && !clouds[i].hasCoin) {
				clouds[i].hasWings = 1;
			}
		}
	}
}

//add a coin to a given cloud
void addCoin(CLOUD* cloud) {
	if (!coin.active) {
		coin.active = 1;
		coin.screenRow =  cloud->screenRow - coin.height;
		coin.screenCol = cloud->screenCol + cloud->width/2;
		//randomly assign the type
		int random = rand();
			if (random % 4 == 0) {
				coin.type = GOLD;
			} else if (random % 3 == 0) {
				coin.type = SILVER;
			} else {
				coin.type = BRONZE;
			}
	}
}

//initialize the pig
void initPig() {
	pig.width = 32;
    pig.height = 32;
	pig.screenRow = SCREENHEIGHT - pig.height;
    pig.screenCol = SCREENWIDTH/2;
}

//initialize the cloud (hard code the y position for better scrolling)
void initClouds() {
	int row = 120;
	for (int i = 0; i < NUMCLOUDS; i++) {
		clouds[i].screenRow = row;
		clouds[i].screenCol = 30 + (rand() % 70);
		clouds[i].active = 1;
		clouds[i].type = XL;
		clouds[i].hide = 0;
		clouds[i].aniState = 0;
		clouds[i].aniCounter = 0;
		clouds[i].hasWings = 0;
		getCloudDim(&clouds[i]);
		row -= 50;
	}
	clouds[2].disappear = 1;
	topRow = clouds[NUMCLOUDS].screenRow;
	topCol = 40;
}

//initialize coins
void initCoins() {
	coin.height = 16;
	coin.width = 16;
	coin.active = 0;
}

//get cloud dimensions (will be used in the future)
void getCloudDim(CLOUD* cloud) {
	switch (cloud->type) {
		case XL: 
            cloud->height = 32;
			cloud->width = 64;
            break;
		case LG:
			cloud->height = 16;
			cloud->width = 32;
			break;
		case MED:
			cloud->height = 8;
			cloud->width = 32;
			break;
		case SM:
			cloud->height = 8;
			cloud->width = 16;
	}
}

//draw the pig sprite
void drawPig() {
	shadowOAM[0].attr0 = pig.screenRow | ATTR0_SQUARE;
	shadowOAM[0].attr1 = pig.screenCol | ATTR1_MEDIUM;
	shadowOAM[0].attr2 = ATTR2_TILEID(0, 0);
}

//draw the cloud sprites
void drawClouds() {
	for (int i = 0; i < NUMCLOUDS; i++) {
		if (clouds[i].active) {
			//check cloud sizes (will be used in the future)
			switch (clouds[i].type) {
				case XL: 
					//hide the breaking sprite
					if (clouds[i].hide) {
						shadowOAM[i + 1].attr0 = ATTR0_HIDE;
					} else {
						shadowOAM[i + 1].attr0 = clouds[i].screenRow | ATTR0_WIDE;
					}
					shadowOAM[i + 1].attr1 = clouds[i].screenCol | ATTR1_LARGE;
					//check anistates for breaking cloud
					if (clouds[i].aniState == 0) {
						shadowOAM[i + 1].attr2 = ATTR2_TILEID(4, 0);
					} else if (clouds[i].aniState == 1) {
						shadowOAM[i + 1].attr2 = ATTR2_TILEID(4, 4);
					} else if (clouds[i].aniState == 2) {
						shadowOAM[i + 1].attr2 = ATTR2_TILEID(4, 8);
					}
            		break;
				case LG: 
            		shadowOAM[i + 1].attr0 = clouds[i].screenRow | ATTR0_WIDE;
					shadowOAM[i + 1].attr1 = clouds[i].screenCol | ATTR1_MEDIUM;
					shadowOAM[i + 1].attr2 = ATTR2_TILEID(12, 0);
            		break;
				case MED:
					shadowOAM[i + 1].attr0 = clouds[i].screenRow | ATTR0_WIDE;
					shadowOAM[i + 1].attr1 = clouds[i].screenCol | ATTR1_SMALL;
					shadowOAM[i + 1].attr2 = ATTR2_TILEID(16, 0);
            		break;
				case SM:
					shadowOAM[i + 1].attr0 = clouds[i].screenRow | ATTR0_WIDE;
					shadowOAM[i + 1].attr1 = clouds[i].screenCol | ATTR1_TINY;
					shadowOAM[i + 1].attr2 = ATTR2_TILEID(20, 0);
            		break;
			}
		}
	}
}

//draw coin sprites
void drawCoins() {
	//only draw if active
	if (coin.active) {
			shadowOAM[2 + NUMCLOUDS].attr0 = coin.screenRow | ATTR0_SQUARE;
			shadowOAM[2 + NUMCLOUDS].attr1 = coin.screenCol | ATTR1_SMALL;
			//switch statement to find sprite id
			switch (coin.type) {
				case GOLD:
					shadowOAM[2 + NUMCLOUDS].attr2 = ATTR2_TILEID(22, 0);
					break;
				case SILVER:
					shadowOAM[2 + NUMCLOUDS].attr2 = ATTR2_TILEID(24, 0);
					break;
				case BRONZE:
					shadowOAM[2 + NUMCLOUDS].attr2 = ATTR2_TILEID(26, 0);
					break;
	} 
	} else {
		shadowOAM[2 + NUMCLOUDS].attr0 = coin.screenRow | ATTR0_HIDE;
	}
}

//check all cloud collisions
void cloudCollisions() {
	oldFloor = floor;

	if (collision(pig.screenCol, pig.screenRow + 24, pig.width, pig.height - 24, 
	clouds[0].screenCol, clouds[0].screenRow, clouds[0].width, clouds[0].height/2)
	&& !clouds[0].hide && (pig.vely >= 0)) {
		//reset the floor to the cloud
		floor = clouds[0].screenRow - 20;
		pig.cloud = 1;
		flag = 1;
		//if its a cloud that disappears increment through animation states
		if (clouds[0].disappear) {
			clouds[0].counter++;
			if (clouds[0].counter == 30) {
				clouds[0].aniState = 1;
			} else if (clouds[0].counter == 60) {
				clouds[0].aniState = 2;
			} else if (clouds[0].counter == 90) {
				clouds[0].hide = 1;
				pig.cloud = 0;
				floor = SCREENHEIGHT - pig.height;
			}
		}
	} else {
		pig.cloud = 0;
		floor = SCREENHEIGHT - pig.height;
	}

	if (collision(pig.screenCol, pig.screenRow + 24, pig.width, pig.height - 24, 
	clouds[1].screenCol, clouds[1].screenRow, clouds[1].width, clouds[1].height/2)
	&& !pig.cloud && !clouds[1].hide) {
		floor = clouds[1].screenRow - 20;
		pig.cloud = 1;
		if (clouds[1].disappear) {
			clouds[1].counter++;
			if (clouds[1].counter == 30) {
				clouds[1].aniState = 1;
			} else if (clouds[1].counter == 60) {
				clouds[1].aniState = 2;
			} else if (clouds[1].counter == 90) {
				clouds[1].hide = 1;
				pig.cloud = 0;
				floor = SCREENHEIGHT - pig.height;
			}
		}
	} else if (!pig.cloud) {
		pig.cloud = 0;
		floor = SCREENHEIGHT - pig.height;
	}

	if (collision(pig.screenCol, pig.screenRow + 24, pig.width, pig.height - 24, 
	clouds[2].screenCol, clouds[2].screenRow, clouds[2].width, clouds[2].height/2)
	&& !pig.cloud && !clouds[2].hide) {
		floor = clouds[2].screenRow - 20;
		pig.cloud = 1;
		if (clouds[2].disappear) {
			clouds[2].counter++;
			if (clouds[2].counter == 30) {
				clouds[2].aniState = 1;
			} else if (clouds[2].counter == 60) {
				clouds[2].aniState = 2;
			} else if (clouds[2].counter == 90) {
				clouds[2].hide = 1;
				pig.cloud = 0;
				floor = SCREENHEIGHT - pig.height;
			}
		}
	} else if (!pig.cloud) {
		pig.cloud = 0;
		floor = SCREENHEIGHT - pig.height;
	}

	if (collision(pig.screenCol, pig.screenRow + 24, pig.width, pig.height - 24, 
	clouds[3].screenCol, clouds[3].screenRow, clouds[3].width, clouds[3].height/2)
	&& !pig.cloud && !clouds[3].hide) {
		floor = clouds[3].screenRow - 20;
		pig.cloud = 1;
		if (clouds[3].disappear) {
			clouds[3].counter++;
			if (clouds[3].counter == 30) {
				clouds[3].aniState = 1;
			} else if (clouds[3].counter == 60) {
				clouds[3].aniState = 2;
			} else if (clouds[3].counter == 90) {
				clouds[3].hide = 1;
				pig.cloud = 0;
				floor = SCREENHEIGHT - pig.height;
			}
		}
	} else if (!pig.cloud) {
		pig.cloud = 0;
		floor = SCREENHEIGHT - pig.height;
	}

}

//check coin collisions
void coinCollisions() {
	//if the pig gets a coin deactivate it and increment the score
	if (collision(pig.screenCol, pig.screenRow, pig.width, pig.height, 
	coin.screenCol, coin.screenRow, coin.width, coin.height) && coin.active) {
		coin.active = 0;
		score += coin.type;
	}
	//if the coin reaches the bottom of the screen, deactivate
	if (coin.active && coin.screenRow + coin.height >= SCREENHEIGHT) {
		coin.active = 0;
	}
}

//calculate the number places of the score
void updateScore() {
	ones = score % 10;
	tens = (score/10) % 10;
	hundreds = (score/100) % 10;
	thousands = (score/1000) % 1000;
}

//draw the score and use the place variables for tile id
void drawScore() {
	shadowOAM[30].attr0 = 0 | ATTR0_SQUARE;
	shadowOAM[30].attr1 = 0 | ATTR1_TINY;
	shadowOAM[30].attr2 = ATTR2_TILEID(0, (thousands + 4));

	shadowOAM[31].attr0 = 0 | ATTR0_SQUARE;
	shadowOAM[31].attr1 = 8 | ATTR1_TINY;
	shadowOAM[31].attr2 = ATTR2_TILEID(0, (hundreds + 4));

	shadowOAM[32].attr0 = 0 | ATTR0_SQUARE;
	shadowOAM[32].attr1 = 16 | ATTR1_TINY;
	shadowOAM[32].attr2 = ATTR2_TILEID(0, (tens + 4));

	shadowOAM[33].attr0 = 0 | ATTR0_SQUARE;
	shadowOAM[33].attr1 = 24 | ATTR1_TINY;
	shadowOAM[33].attr2 = ATTR2_TILEID(0, (ones + 4));
}

//initialize the wing feature
void initWings() {
	wings.width = 16;
	wings.height = 16;
	wings.active = 0;
}

//draw the wings sprite
void drawWings() {
	//only draw if active
	if (wings.active) {
			shadowOAM[3 + NUMCLOUDS].attr0 = wings.screenRow | ATTR0_SQUARE;
			shadowOAM[3 + NUMCLOUDS].attr1 = wings.screenCol | ATTR1_SMALL;
			shadowOAM[3 + NUMCLOUDS].attr2 = ATTR2_TILEID(28, 0);
	} else {
		shadowOAM[3 + NUMCLOUDS].attr0 = wings.screenRow | ATTR0_HIDE;
	}
}

//checks for pig collisions with the wings
void wingsCollisions() {
	//if the pig gets wings deactivate it and set pig for flight
	if (collision(pig.screenCol, pig.screenRow, pig.width, pig.height, 
	wings.screenCol, wings.screenRow, wings.width, wings.height) && wings.active) {
		wings.active = 0;
		pig.flight = 1;
		wings.time = 350;
	}
	//if the wings reaches the bottom of the screen, deactivate
	if (wings.active && wings.screenRow + wings.height >= SCREENHEIGHT) {
		wings.active = 0;
	}
}

//similar function to addCoins, adds wings to the cloud
void addWings(CLOUD* cloud) {
	if (!wings.active &&!pig.flight) {
		wings.active = 1;
		wings.screenRow =  cloud->screenRow - coin.height;
		wings.screenCol = cloud->screenCol + cloud->width/2;
	}
}
