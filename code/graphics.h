#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string.h>

#define DIM 26
#define TILE 26
#define TANKSIZE 52
#define BOTSIZE 52
#define BULLETSIZE 26
#define MAX 20
#define MAX_BULLETS 100
#define LETTER 90

typedef struct {
	int posx, posy;
	char rotation;
	int active;
	int last_shot;
	int indx;
	int tip;
	int tezina;
	int spec;
	int botspec;
	int life;
	int freez;
	int lvl;
} Tank;

typedef struct {
	int posx, posy;
	int blink;
	int active;
	char type;

} bonus;

typedef struct {
	int score;
	char ime[30];

} podatak;

typedef struct {
	int freez_state;
	char map[DIM + 1][DIM + 1];
	int changed;
	int gamelvl;
	int nivo;
	int kills;
	SDL_Renderer *renderer;
	SDL_Texture *water;
	SDL_Texture *wall;
	SDL_Texture *ironwall;
	SDL_Texture *tankLeft[4];
	SDL_Texture *tankRight[4];
	SDL_Texture *tankUp[4];
	SDL_Texture *tankDown[4];
	SDL_Texture *botLeft;
	SDL_Texture *botRight;
	SDL_Texture *botUp;
	SDL_Texture *botDown;
	SDL_Texture *botspecLeft;
	SDL_Texture *botspecRight;
	SDL_Texture *botspecUp;
	SDL_Texture *botspecDown;
	SDL_Texture *base;
	SDL_Texture *Bomb;
	SDL_Texture *Freez;
	SDL_Texture *Star;
	SDL_Texture *bulletLeft[5];
	SDL_Texture *bulletRight[5];
	SDL_Texture *bulletUp[5];
	SDL_Texture *bulletDown[5];
	SDL_Texture *Srce;
	SDL_Texture *B;
	SDL_Texture *A;
	SDL_Texture *T;
	SDL_Texture *L;
	SDL_Texture *E;
	SDL_Texture *N;
	SDL_Texture *K;
	SDL_Texture *S;
	SDL_Texture *play;
	SDL_Texture *word;
	SDL_Texture *highscore;
	SDL_Texture *emh;
	SDL_Texture *exit;
	SDL_Texture *finishlvleditor;
	SDL_Texture *editlvl;
	SDL_Texture *back;
	Tank mainTank;
	Tank bots[MAX];
	Tank bullets[MAX_BULLETS];
	bonus bonuses[MAX];
	int numberOfBonuses;
	int numberOfBots;
	int numberOfBullets;
} GameState;
void doWord(GameState *game, char *str, int x, int y, int w, int h) {

	if (TTF_Init() == -1) exit(4);
	TTF_Font *Sans = TTF_OpenFont("bahnschrift.ttf", 80);
	if (!Sans) exit(2);
	SDL_Color White = { 105, 105, 105 , 255 };
	SDL_Surface *wordSurface = TTF_RenderText_Solid(Sans, str, White);
	TTF_CloseFont(Sans);
	TTF_Quit();
	game->word = SDL_CreateTextureFromSurface(game->renderer, wordSurface);
	//SDL_Rect location = { 350, 350, 0, 0 };
	//SDL_RenderCopy(game->renderer, game->word, NULL, &location);
	SDL_Rect Message;

	Message.x = x;
	Message.y = y;
	Message.w = w;
	Message.h = h;
	SDL_RenderCopy(game->renderer, game->word, NULL, &Message);
	SDL_FreeSurface(wordSurface);
	SDL_DestroyTexture(game->word);


}
void doBack(GameState *game) {

	SDL_Surface *backSurface = NULL;
	backSurface = IMG_Load("img/back.png");

	if (backSurface == NULL) {
		printf("back");
		exit(1);
	}

	game->back = SDL_CreateTextureFromSurface(game->renderer, backSurface);
	SDL_FreeSurface(backSurface);



}
void doPlay(GameState *game) {

	SDL_Surface *playSurface = NULL;
	playSurface = IMG_Load("img/play.png");

	if (playSurface == NULL) {
		printf("play");
		exit(1);
	}

	game->play = SDL_CreateTextureFromSurface(game->renderer, playSurface);
	SDL_FreeSurface(playSurface);



}
void doEditlvl(GameState *game) {

	SDL_Surface *editSurface = NULL;
	editSurface = IMG_Load("img/mapeditor.png");

	if (editSurface == NULL) {
		printf("edit");
		exit(1);
	}

	game->editlvl = SDL_CreateTextureFromSurface(game->renderer, editSurface);
	SDL_FreeSurface(editSurface);


}
void doExit(GameState *game) {

	SDL_Surface *exitSurface = NULL;
	exitSurface = IMG_Load("img/exit.png");

	if (exitSurface == NULL) {
		printf("exit");
		exit(1);
	}

	game->exit = SDL_CreateTextureFromSurface(game->renderer, exitSurface);
	SDL_FreeSurface(exitSurface);



}
void doFinishlvleditor(GameState *game) {

	SDL_Surface *finishlvleditorSurface = NULL;
	finishlvleditorSurface = IMG_Load("img/finishlvleditor.png");

	if (finishlvleditorSurface == NULL) {
		printf("exit");
		exit(1);
	}

	game->finishlvleditor = SDL_CreateTextureFromSurface(game->renderer, finishlvleditorSurface);
	SDL_FreeSurface(finishlvleditorSurface);



}

void doemh(GameState *game) {

	SDL_Surface *emhSurface = NULL;
	emhSurface = IMG_Load("img/emh.png");

	if (emhSurface == NULL) {
		printf("emh");
		exit(1);
	}

	game->emh = SDL_CreateTextureFromSurface(game->renderer, emhSurface);
	SDL_FreeSurface(emhSurface);



}
void doHighscore(GameState *game) {

	SDL_Surface *highscoreSurface = NULL;
	highscoreSurface = IMG_Load("img/highscore.png");

	if (highscoreSurface == NULL) {
		printf("highscore");
		exit(1);
	}

	game->highscore = SDL_CreateTextureFromSurface(game->renderer, highscoreSurface);
	SDL_FreeSurface(highscoreSurface);



}

void doMenu(GameState *game) {
	SDL_Surface *bSurface = NULL;
	bSurface = IMG_Load("img/b.png");

	if (bSurface == NULL) {
		printf("bbbbb");
		exit(1);
	}

	game->B = SDL_CreateTextureFromSurface(game->renderer, bSurface);
	SDL_FreeSurface(bSurface);

	SDL_Surface *aSurface = NULL;
	aSurface = IMG_Load("img/a.png");

	if (aSurface == NULL) {
		printf("aaaaa");
		exit(1);
	}

	game->A = SDL_CreateTextureFromSurface(game->renderer, aSurface);
	SDL_FreeSurface(aSurface);


	SDL_Surface *tSurface = NULL;
	tSurface = IMG_Load("img/t.png");

	if (tSurface == NULL) {
		printf("tttt");
		exit(1);
	}

	game->T = SDL_CreateTextureFromSurface(game->renderer, tSurface);
	SDL_FreeSurface(tSurface);


	SDL_Surface *lSurface = NULL;
	lSurface = IMG_Load("img/l.png");

	if (lSurface == NULL) {
		printf("lllll");
		exit(1);
	}

	game->L = SDL_CreateTextureFromSurface(game->renderer, lSurface);
	SDL_FreeSurface(lSurface);


	SDL_Surface *eSurface = NULL;
	eSurface = IMG_Load("img/e.png");

	if (eSurface == NULL) {
		printf("eeeee");
		exit(1);
	}

	game->E = SDL_CreateTextureFromSurface(game->renderer, eSurface);
	SDL_FreeSurface(eSurface);

	SDL_Surface *nSurface = NULL;
	nSurface = IMG_Load("img/n.png");

	if (nSurface == NULL) {
		printf("nnnnn");
		exit(1);
	}

	game->N = SDL_CreateTextureFromSurface(game->renderer, nSurface);
	SDL_FreeSurface(nSurface);

	SDL_Surface *kSurface = NULL;
	kSurface = IMG_Load("img/k.png");

	if (kSurface == NULL) {
		printf("kkkkk");
		exit(1);
	}

	game->K = SDL_CreateTextureFromSurface(game->renderer, kSurface);
	SDL_FreeSurface(kSurface);

	SDL_Surface *sSurface = NULL;
	sSurface = IMG_Load("img/s.png");

	if (sSurface == NULL) {
		printf("sssss");
		exit(1);
	}

	game->S = SDL_CreateTextureFromSurface(game->renderer, sSurface);
	SDL_FreeSurface(sSurface);
}

void doWater(GameState *game) {

	SDL_Surface *waterSurface = NULL;
	waterSurface = IMG_Load("img/water.png");

	if (waterSurface == NULL) {
		printf("voda");
		exit(1);
	}

	game->water = SDL_CreateTextureFromSurface(game->renderer, waterSurface);
	SDL_FreeSurface(waterSurface);

	//SDL_Rect waterRect = { x, y, TILE, TILE };
	//SDL_RenderCopy(game->renderer, game->water, NULL, &waterRect);

}
void doWall(GameState *game) {

	SDL_Surface *wallSurface = NULL;
	wallSurface = IMG_Load("img/wall.png");

	if (wallSurface == NULL) {
		printf("zid");
		exit(1);
	}

	game->wall = SDL_CreateTextureFromSurface(game->renderer, wallSurface);
	SDL_FreeSurface(wallSurface);

	//SDL_Rect wallRect = { x, y, TILE, TILE };
	//SDL_RenderCopy(game->renderer, game->wall, NULL, &wallRect);

}

void doIronWall(GameState *game) {

	SDL_Surface *ironwallSurface = NULL;
	ironwallSurface = IMG_Load("img/ironwall.png");

	if (ironwallSurface == NULL) {
		printf("iron");
		exit(1);
	}

	game->ironwall = SDL_CreateTextureFromSurface(game->renderer, ironwallSurface);
	SDL_FreeSurface(ironwallSurface);

	//SDL_Rect ironwallRect = { x, y, TILE, TILE };
	//SDL_RenderCopy(game->renderer, game->ironwall, NULL, &ironwallRect);

}
void doBomb(GameState *game) {

	SDL_Surface *BombSurface = NULL;


	BombSurface = IMG_Load("img/Bomb.png");
	if (BombSurface == NULL) {
		printf("Bomb");
		exit(1);
	}

	game->Bomb = SDL_CreateTextureFromSurface(game->renderer, BombSurface);
	SDL_FreeSurface(BombSurface);

	//SDL_Rect tankLeftRect = { game->mainTank.posx, game->mainTank.posy, TANKSIZE, TANKSIZE };
	//SDL_RenderCopy(game->renderer, game->tankLeft, NULL, &tankLeftRect);

}
void doFreez(GameState *game) {

	SDL_Surface *FreezSurface = NULL;


	FreezSurface = IMG_Load("img/Freez.png");
	if (FreezSurface == NULL) {
		printf("Freez");
		exit(1);
	}

	game->Freez = SDL_CreateTextureFromSurface(game->renderer, FreezSurface);
	SDL_FreeSurface(FreezSurface);

	//SDL_Rect tankLeftRect = { game->mainTank.posx, game->mainTank.posy, TANKSIZE, TANKSIZE };
	//SDL_RenderCopy(game->renderer, game->tankLeft, NULL, &tankLeftRect);

}
void doStar(GameState *game) {

	SDL_Surface *StarSurface = NULL;


	StarSurface = IMG_Load("img/Star.png");
	if (StarSurface == NULL) {
		printf("Star");
		exit(1);
	}

	game->Star = SDL_CreateTextureFromSurface(game->renderer, StarSurface);
	SDL_FreeSurface(StarSurface);

	//SDL_Rect tankLeftRect = { game->mainTank.posx, game->mainTank.posy, TANKSIZE, TANKSIZE };
	//SDL_RenderCopy(game->renderer, game->tankLeft, NULL, &tankLeftRect);

}
void doSrce(GameState *game) {

	SDL_Surface *SrceSurface = NULL;


	SrceSurface = IMG_Load("img/Srce.png");
	if (SrceSurface == NULL) {
		printf("Srce");
		exit(1);
	}

	game->Srce = SDL_CreateTextureFromSurface(game->renderer, SrceSurface);
	SDL_FreeSurface(SrceSurface);

	//SDL_Rect tankLeftRect = { game->mainTank.posx, game->mainTank.posy, TANKSIZE, TANKSIZE };
	//SDL_RenderCopy(game->renderer, game->tankLeft, NULL, &tankLeftRect);

}
void doTankLeft(GameState *game) {

	SDL_Surface *tankLeftSurface = NULL;

	tankLeftSurface = IMG_Load("img/tankl4.png");
	if (tankLeftSurface == NULL) {
		printf("tenk1");
		exit(1);
	}

	game->tankLeft[3] = SDL_CreateTextureFromSurface(game->renderer, tankLeftSurface);
	SDL_FreeSurface(tankLeftSurface);

	tankLeftSurface = IMG_Load("img/tankl1.png");
	if (tankLeftSurface == NULL) {
		printf("tenk2");
		exit(1);
	}

	game->tankLeft[0] = SDL_CreateTextureFromSurface(game->renderer, tankLeftSurface);
	SDL_FreeSurface(tankLeftSurface);

	tankLeftSurface = IMG_Load("img/tankl2.png");
	if (tankLeftSurface == NULL) {
		printf("tenk3");
		exit(1);
	}

	game->tankLeft[1] = SDL_CreateTextureFromSurface(game->renderer, tankLeftSurface);
	SDL_FreeSurface(tankLeftSurface);

	tankLeftSurface = IMG_Load("img/tankl3.png");
	if (tankLeftSurface == NULL) {
		printf("tenk4");
		exit(1);
	}

	game->tankLeft[2] = SDL_CreateTextureFromSurface(game->renderer, tankLeftSurface);
	SDL_FreeSurface(tankLeftSurface);

}
void doTankRight(GameState *game) {

	SDL_Surface *tankRightSurface = NULL;

	tankRightSurface = IMG_Load("img/tankr4.png");
	if (tankRightSurface == NULL) {
		printf("tenk5");
		exit(1);
	}

	game->tankRight[3] = SDL_CreateTextureFromSurface(game->renderer, tankRightSurface);
	SDL_FreeSurface(tankRightSurface);



	tankRightSurface = IMG_Load("img/tankr1.png");
	if (tankRightSurface == NULL) {
		printf("tenk6");
		exit(1);
	}

	game->tankRight[0] = SDL_CreateTextureFromSurface(game->renderer, tankRightSurface);
	SDL_FreeSurface(tankRightSurface);


	tankRightSurface = IMG_Load("img/tankr2.png");
	if (tankRightSurface == NULL) {
		printf("tenk7");
		exit(1);
	}

	game->tankRight[1] = SDL_CreateTextureFromSurface(game->renderer, tankRightSurface);
	SDL_FreeSurface(tankRightSurface);


	tankRightSurface = IMG_Load("img/tankr3.png");
	if (tankRightSurface == NULL) {
		printf("tenk8");
		exit(1);
	}

	game->tankRight[2] = SDL_CreateTextureFromSurface(game->renderer, tankRightSurface);
	SDL_FreeSurface(tankRightSurface);


}
void doTankUp(GameState *game) {

	SDL_Surface *tankUpSurface = NULL;


	tankUpSurface = IMG_Load("img/tanku4.png");
	if (tankUpSurface == NULL) {
		printf("tenk9");
		exit(1);
	}

	game->tankUp[3] = SDL_CreateTextureFromSurface(game->renderer, tankUpSurface);
	SDL_FreeSurface(tankUpSurface);

	tankUpSurface = IMG_Load("img/tanku1.png");
	if (tankUpSurface == NULL) {
		printf("tenk10");
		exit(1);
	}

	game->tankUp[0] = SDL_CreateTextureFromSurface(game->renderer, tankUpSurface);
	SDL_FreeSurface(tankUpSurface);

	tankUpSurface = IMG_Load("img/tanku2.png");
	if (tankUpSurface == NULL) {
		printf("tenk11");
		exit(1);
	}

	game->tankUp[1] = SDL_CreateTextureFromSurface(game->renderer, tankUpSurface);
	SDL_FreeSurface(tankUpSurface);

	tankUpSurface = IMG_Load("img/tanku3.png");
	if (tankUpSurface == NULL) {
		printf("tenk12");
		exit(1);
	}

	game->tankUp[2] = SDL_CreateTextureFromSurface(game->renderer, tankUpSurface);
	SDL_FreeSurface(tankUpSurface);

}
void doTankDown(GameState *game) {

	SDL_Surface *tankDownSurface = NULL;


	tankDownSurface = IMG_Load("img/tankd4.png");
	if (tankDownSurface == NULL) {
		printf("tenk13");
		exit(1);
	}

	game->tankDown[3] = SDL_CreateTextureFromSurface(game->renderer, tankDownSurface);
	SDL_FreeSurface(tankDownSurface);


	tankDownSurface = IMG_Load("img/tankd1.png");
	if (tankDownSurface == NULL) {
		printf("tenk14");
		exit(1);
	}

	game->tankDown[0] = SDL_CreateTextureFromSurface(game->renderer, tankDownSurface);
	SDL_FreeSurface(tankDownSurface);

	tankDownSurface = IMG_Load("img/tankd2.png");
	if (tankDownSurface == NULL) {
		printf("tenk15");
		exit(1);
	}

	game->tankDown[1] = SDL_CreateTextureFromSurface(game->renderer, tankDownSurface);
	SDL_FreeSurface(tankDownSurface);

	tankDownSurface = IMG_Load("img/tankd3.png");
	if (tankDownSurface == NULL) {
		printf("tenk16");
		exit(1);
	}

	game->tankDown[2] = SDL_CreateTextureFromSurface(game->renderer, tankDownSurface);
	SDL_FreeSurface(tankDownSurface);

}

void doBotLeft(GameState *game) {

	SDL_Surface *botLeftSurface = NULL;
	
	/*switch (game->mainBot.rotation) {
	case 'l': botSurface = IMG_Load("img/botl.png"); break;
	case 'r': botSurface = IMG_Load("img/botr.png"); break;
	case 'u': botSurface = IMG_Load("img/botu.png"); break;
	case 'd': botSurface = IMG_Load("img/botd.png"); break;
	}


	if (botSurface == NULL) {
		printf("bot");
		exit(1);
	}
	*/

	botLeftSurface = IMG_Load("img/botl.png");
	if (botLeftSurface == NULL) {
		printf("bot");
		exit(1);
	}

	game->botLeft = SDL_CreateTextureFromSurface(game->renderer, botLeftSurface);
	SDL_FreeSurface(botLeftSurface);

	//SDL_Rect botLeftRect = { game->mainBot.posx, game->mainBot.posy, BOTSIZE, BOTSIZE };
	//SDL_RenderCopy(game->renderer, game->botLeft, NULL, &botLeftRect);

}
void doBotRight(GameState *game) {

	SDL_Surface *botRightSurface = NULL;

	/*switch (game->mainBot.rotation) {
	case 'l': botSurface = IMG_Load("img/botl.png"); break;
	case 'r': botSurface = IMG_Load("img/botr.png"); break;
	case 'u': botSurface = IMG_Load("img/botu.png"); break;
	case 'd': botSurface = IMG_Load("img/botd.png"); break;
	}


	if (botSurface == NULL) {
		printf("bot");
		exit(1);
	}
	*/

	botRightSurface = IMG_Load("img/botr.png");
	if (botRightSurface == NULL) {
		printf("bot");
		exit(1);
	}

	game->botRight = SDL_CreateTextureFromSurface(game->renderer, botRightSurface);
	SDL_FreeSurface(botRightSurface);

	//SDL_Rect botLeftRect = { game->mainBot.posx, game->mainBot.posy, BOTSIZE, BOTSIZE };
	//SDL_RenderCopy(game->renderer, game->botLeft, NULL, &botLeftRect);

}
void doBotUp(GameState *game) {

	SDL_Surface *botUpSurface = NULL;

	/*switch (game->mainBot.rotation) {
	case 'l': botSurface = IMG_Load("img/botl.png"); break;
	case 'r': botSurface = IMG_Load("img/botr.png"); break;
	case 'u': botSurface = IMG_Load("img/botu.png"); break;
	case 'd': botSurface = IMG_Load("img/botd.png"); break;
	}


	if (botSurface == NULL) {
		printf("bot");
		exit(1);
	}
	*/

	botUpSurface = IMG_Load("img/botu.png");
	if (botUpSurface == NULL) {
		printf("bot");
		exit(1);
	}

	game->botUp = SDL_CreateTextureFromSurface(game->renderer, botUpSurface);
	SDL_FreeSurface(botUpSurface);

	//SDL_Rect botLeftRect = { game->mainBot.posx, game->mainBot.posy, BOTSIZE, BOTSIZE };
	//SDL_RenderCopy(game->renderer, game->botLeft, NULL, &botLeftRect);

}
void doBotDown(GameState *game) {

	SDL_Surface *botDownSurface = NULL;

	/*switch (game->mainBot.rotation) {
	case 'l': botSurface = IMG_Load("img/botl.png"); break;
	case 'r': botSurface = IMG_Load("img/botr.png"); break;
	case 'u': botSurface = IMG_Load("img/botu.png"); break;
	case 'd': botSurface = IMG_Load("img/botd.png"); break;
	}


	if (botSurface == NULL) {
		printf("bot");
		exit(1);
	}
	*/

	botDownSurface = IMG_Load("img/botd.png");
	if (botDownSurface == NULL) {
		printf("bot");
		exit(1);
	}

	game->botDown = SDL_CreateTextureFromSurface(game->renderer, botDownSurface);
	SDL_FreeSurface(botDownSurface);

	//SDL_Rect botLeftRect = { game->mainBot.posx, game->mainBot.posy, BOTSIZE, BOTSIZE };
	//SDL_RenderCopy(game->renderer, game->botLeft, NULL, &botLeftRect);

}

void dospecbotLeft(GameState *game) {

	SDL_Surface *specbotLeftSurface = NULL;

	/*switch (game->mainspecbot.rotation) {
	case 'l': specbotSurface = IMG_Load("img/specbotl.png"); break;
	case 'r': specbotSurface = IMG_Load("img/specbotr.png"); break;
	case 'u': specbotSurface = IMG_Load("img/specbotu.png"); break;
	case 'd': specbotSurface = IMG_Load("img/specbotd.png"); break;
	}


	if (specbotSurface == NULL) {
		printf("specbot");
		exit(1);
	}
	*/

	specbotLeftSurface = IMG_Load("img/specbotl.png");
	if (specbotLeftSurface == NULL) {
		printf("specbot");
		exit(1);
	}

	game->botspecLeft = SDL_CreateTextureFromSurface(game->renderer, specbotLeftSurface);
	SDL_FreeSurface(specbotLeftSurface);

	//SDL_Rect specbotLeftRect = { game->mainspecbot.posx, game->mainspecbot.posy, specbotSIZE, specbotSIZE };
	//SDL_RenderCopy(game->renderer, game->specbotLeft, NULL, &specbotLeftRect);

}
void dospecbotRight(GameState *game) {

	SDL_Surface *specbotRightSurface = NULL;

	/*switch (game->mainspecbot.rotation) {
	case 'l': specbotSurface = IMG_Load("img/specbotl.png"); break;
	case 'r': specbotSurface = IMG_Load("img/specbotr.png"); break;
	case 'u': specbotSurface = IMG_Load("img/specbotu.png"); break;
	case 'd': specbotSurface = IMG_Load("img/specbotd.png"); break;
	}


	if (specbotSurface == NULL) {
		printf("specbot");
		exit(1);
	}
	*/

	specbotRightSurface = IMG_Load("img/specbotr.png");
	if (specbotRightSurface == NULL) {
		printf("specbot");
		exit(1);
	}

	game->botspecRight = SDL_CreateTextureFromSurface(game->renderer, specbotRightSurface);
	SDL_FreeSurface(specbotRightSurface);

	//SDL_Rect specbotLeftRect = { game->mainspecbot.posx, game->mainspecbot.posy, specbotSIZE, specbotSIZE };
	//SDL_RenderCopy(game->renderer, game->specbotLeft, NULL, &specbotLeftRect);

}
void dospecbotUp(GameState *game) {

	SDL_Surface *specbotUpSurface = NULL;

	/*switch (game->mainspecbot.rotation) {
	case 'l': specbotSurface = IMG_Load("img/specbotl.png"); break;
	case 'r': specbotSurface = IMG_Load("img/specbotr.png"); break;
	case 'u': specbotSurface = IMG_Load("img/specbotu.png"); break;
	case 'd': specbotSurface = IMG_Load("img/specbotd.png"); break;
	}


	if (specbotSurface == NULL) {
		printf("specbot");
		exit(1);
	}
	*/

	specbotUpSurface = IMG_Load("img/specbotu.png");
	if (specbotUpSurface == NULL) {
		printf("specbot");
		exit(1);
	}

	game->botspecUp = SDL_CreateTextureFromSurface(game->renderer, specbotUpSurface);
	SDL_FreeSurface(specbotUpSurface);

	//SDL_Rect specbotLeftRect = { game->mainspecbot.posx, game->mainspecbot.posy, specbotSIZE, specbotSIZE };
	//SDL_RenderCopy(game->renderer, game->specbotLeft, NULL, &specbotLeftRect);

}
void dospecbotDown(GameState *game) {

	SDL_Surface *specbotDownSurface = NULL;

	/*switch (game->mainspecbot.rotation) {
	case 'l': specbotSurface = IMG_Load("img/specbotl.png"); break;
	case 'r': specbotSurface = IMG_Load("img/specbotr.png"); break;
	case 'u': specbotSurface = IMG_Load("img/specbotu.png"); break;
	case 'd': specbotSurface = IMG_Load("img/specbotd.png"); break;
	}


	if (specbotSurface == NULL) {
		printf("specbot");
		exit(1);
	}
	*/

	specbotDownSurface = IMG_Load("img/specbotd.png");
	if (specbotDownSurface == NULL) {
		printf("specbot");
		exit(1);
	}

	game->botspecDown = SDL_CreateTextureFromSurface(game->renderer, specbotDownSurface);
	SDL_FreeSurface(specbotDownSurface);

	//SDL_Rect specbotLeftRect = { game->mainspecbot.posx, game->mainspecbot.posy, specbotSIZE, specbotSIZE };
	//SDL_RenderCopy(game->renderer, game->specbotLeft, NULL, &specbotLeftRect);

}


void doBase(GameState *game) {

	SDL_Surface *baseSurface = NULL;
	baseSurface = IMG_Load("img/beer.png");

	if (baseSurface == NULL) {
		printf("pivo");
		exit(1);
	}

	game->base = SDL_CreateTextureFromSurface(game->renderer, baseSurface);
	SDL_FreeSurface(baseSurface);

	//SDL_Rect baseRect = { x, y, 2 * TILE, 2 * TILE };
	//SDL_RenderCopy(game->renderer, game->base, NULL, &baseRect);

}
void doBulletRight(GameState *game) {

	SDL_Surface *bulletRightSurface = NULL;

	bulletRightSurface = IMG_Load("img/bulletr.png");
	if (bulletRightSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletRight[0] = SDL_CreateTextureFromSurface(game->renderer, bulletRightSurface);
	SDL_FreeSurface(bulletRightSurface);

	bulletRightSurface = IMG_Load("img/bulletr1.png");
	if (bulletRightSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletRight[1] = SDL_CreateTextureFromSurface(game->renderer, bulletRightSurface);
	SDL_FreeSurface(bulletRightSurface);


	bulletRightSurface = IMG_Load("img/bulletr2.png");
	if (bulletRightSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletRight[2] = SDL_CreateTextureFromSurface(game->renderer, bulletRightSurface);
	SDL_FreeSurface(bulletRightSurface);

	bulletRightSurface = IMG_Load("img/bulletr3.png");
	if (bulletRightSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletRight[3] = SDL_CreateTextureFromSurface(game->renderer, bulletRightSurface);
	SDL_FreeSurface(bulletRightSurface);

	bulletRightSurface = IMG_Load("img/botbulletr.png");
	if (bulletRightSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletRight[4] = SDL_CreateTextureFromSurface(game->renderer, bulletRightSurface);
	SDL_FreeSurface(bulletRightSurface);

}
void doBulletUp(GameState *game) {

	SDL_Surface *bulletUpSurface = NULL;

	bulletUpSurface = IMG_Load("img/bulletu.png");
	if (bulletUpSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletUp[0] = SDL_CreateTextureFromSurface(game->renderer, bulletUpSurface);
	SDL_FreeSurface(bulletUpSurface);

	bulletUpSurface = IMG_Load("img/bulletu1.png");
	if (bulletUpSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletUp[1] = SDL_CreateTextureFromSurface(game->renderer, bulletUpSurface);
	SDL_FreeSurface(bulletUpSurface);

	bulletUpSurface = IMG_Load("img/bulletu2.png");
	if (bulletUpSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletUp[2] = SDL_CreateTextureFromSurface(game->renderer, bulletUpSurface);
	SDL_FreeSurface(bulletUpSurface);

	bulletUpSurface = IMG_Load("img/bulletu3.png");
	if (bulletUpSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletUp[3] = SDL_CreateTextureFromSurface(game->renderer, bulletUpSurface);
	SDL_FreeSurface(bulletUpSurface);


	bulletUpSurface = IMG_Load("img/botbulletu.png");
	if (bulletUpSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletUp[4] = SDL_CreateTextureFromSurface(game->renderer, bulletUpSurface);
	SDL_FreeSurface(bulletUpSurface);

}

void doBulletLeft(GameState *game) {

	SDL_Surface *bulletLeftSurface = NULL;

	bulletLeftSurface = IMG_Load("img/bulletl.png");
	if (bulletLeftSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletLeft[0] = SDL_CreateTextureFromSurface(game->renderer, bulletLeftSurface);
	SDL_FreeSurface(bulletLeftSurface);

	bulletLeftSurface = IMG_Load("img/bulletl1.png");
	if (bulletLeftSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletLeft[1] = SDL_CreateTextureFromSurface(game->renderer, bulletLeftSurface);
	SDL_FreeSurface(bulletLeftSurface);


	bulletLeftSurface = IMG_Load("img/bulletl2.png");
	if (bulletLeftSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletLeft[2] = SDL_CreateTextureFromSurface(game->renderer, bulletLeftSurface);
	SDL_FreeSurface(bulletLeftSurface);

	bulletLeftSurface = IMG_Load("img/bulletl3.png");
	if (bulletLeftSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletLeft[3] = SDL_CreateTextureFromSurface(game->renderer, bulletLeftSurface);
	SDL_FreeSurface(bulletLeftSurface);

	bulletLeftSurface = IMG_Load("img/botbulletl.png");
	if (bulletLeftSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletLeft[4] = SDL_CreateTextureFromSurface(game->renderer, bulletLeftSurface);
	SDL_FreeSurface(bulletLeftSurface);


}

void doBulletDown(GameState *game) {

	SDL_Surface *bulletDownSurface = NULL;

	bulletDownSurface = IMG_Load("img/bulletd.png");
	if (bulletDownSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletDown[0] = SDL_CreateTextureFromSurface(game->renderer, bulletDownSurface);
	SDL_FreeSurface(bulletDownSurface);

	bulletDownSurface = IMG_Load("img/bulletd1.png");
	if (bulletDownSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletDown[1] = SDL_CreateTextureFromSurface(game->renderer, bulletDownSurface);
	SDL_FreeSurface(bulletDownSurface);

	bulletDownSurface = IMG_Load("img/bulletd2.png");
	if (bulletDownSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletDown[2] = SDL_CreateTextureFromSurface(game->renderer, bulletDownSurface);
	SDL_FreeSurface(bulletDownSurface);

	bulletDownSurface = IMG_Load("img/bulletd3.png");
	if (bulletDownSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletDown[3] = SDL_CreateTextureFromSurface(game->renderer, bulletDownSurface);
	SDL_FreeSurface(bulletDownSurface);


	bulletDownSurface = IMG_Load("img/botbulletd.png");
	if (bulletDownSurface == NULL) {
		printf("bullet");
		exit(1);
	}

	game->bulletDown[4] = SDL_CreateTextureFromSurface(game->renderer, bulletDownSurface);
	SDL_FreeSurface(bulletDownSurface);

}
void doRender(GameState *game) {
	SDL_SetRenderDrawColor(game->renderer, 140, 150, 40, 255);
	SDL_RenderClear(game->renderer);



	SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);
	SDL_Rect rectt = { 676, 0, 124, 676 };
	SDL_RenderFillRect(game->renderer, &rectt);

	for (int i = 0; i < DIM; i++) {

		for (int j = 0; j < DIM; j++) {
			switch (game->map[i][j]) {
			case 'v':
				SDL_Rect waterRect = { i * TILE, j * TILE, TILE, TILE };
				SDL_RenderCopy(game->renderer, game->water, NULL, &waterRect); break;
			case 'c':
				SDL_Rect ironwallRect = { i*TILE, j*TILE, TILE, TILE };
				SDL_RenderCopy(game->renderer, game->ironwall, NULL, &ironwallRect); break;
			case 'z':
				SDL_Rect wallRect = { i*TILE, j*TILE, TILE, TILE };
				SDL_RenderCopy(game->renderer, game->wall, NULL, &wallRect); break;
			case 'b':
				SDL_Rect baseRect = { i*TILE, j*TILE, 2 * TILE, 2 * TILE };
				SDL_RenderCopy(game->renderer, game->base, NULL, &baseRect); break;

			}
		}
	}

	for (int i = 0; i < MAX; i++) {
		if (game->bonuses[i].active) {
			if (game->bonuses[i].blink % 8 < 4) {
				switch (game->bonuses[i].type)
				{
				case 'b':
					SDL_Rect Bomb = { game->bonuses[i].posx, game->bonuses[i].posy, BOTSIZE, BOTSIZE };
					SDL_RenderCopy(game->renderer, game->Bomb, NULL, &Bomb);
					break;
				case 's':
					SDL_Rect Srce = { game->bonuses[i].posx, game->bonuses[i].posy, BOTSIZE, BOTSIZE };
					SDL_RenderCopy(game->renderer, game->Srce, NULL, &Srce);
					break;
				case 'f':
					SDL_Rect Freez = { game->bonuses[i].posx, game->bonuses[i].posy, BOTSIZE, BOTSIZE };
					SDL_RenderCopy(game->renderer, game->Freez, NULL, &Freez);
					break;
				case 'z':
					SDL_Rect Star = { game->bonuses[i].posx, game->bonuses[i].posy, BOTSIZE, BOTSIZE };
					SDL_RenderCopy(game->renderer, game->Star, NULL, &Star);
					break;
				}
			}
			game->bonuses[i].blink--;
			if (!game->bonuses[i].blink) game->bonuses[i].active = 0;
		}
	}

	switch (game->mainTank.rotation) {
	case 'l': SDL_Rect tankLeftRect = { game->mainTank.posx, game->mainTank.posy, TANKSIZE, TANKSIZE };
			  SDL_RenderCopy(game->renderer, game->tankLeft[game->mainTank.lvl], NULL, &tankLeftRect); break;
	case 'r':  SDL_Rect tankRightRect = { game->mainTank.posx, game->mainTank.posy, TANKSIZE, TANKSIZE };
			   SDL_RenderCopy(game->renderer, game->tankRight[game->mainTank.lvl], NULL, &tankRightRect); break;
	case 'u': SDL_Rect tankUpRect = { game->mainTank.posx, game->mainTank.posy, TANKSIZE, TANKSIZE };
			  SDL_RenderCopy(game->renderer, game->tankUp[game->mainTank.lvl], NULL, &tankUpRect); break;
	case 'd': SDL_Rect tankDownRect = { game->mainTank.posx, game->mainTank.posy, TANKSIZE, TANKSIZE };
			  SDL_RenderCopy(game->renderer, game->tankDown[game->mainTank.lvl], NULL, &tankDownRect); break;
	}


	for (int i = 0; i < MAX; i++) {
		if (game->bots[i].active)
			if (game->bots[i].botspec)
				switch (game->bots[i].rotation) {
				case 'l': SDL_Rect specbotLeftRect = { game->bots[i].posx, game->bots[i].posy, BOTSIZE, BOTSIZE };
						  SDL_RenderCopy(game->renderer, game->botspecLeft, NULL, &specbotLeftRect); break;
				case 'r':  SDL_Rect specbotRightRect = { game->bots[i].posx, game->bots[i].posy, BOTSIZE, BOTSIZE };
						   SDL_RenderCopy(game->renderer, game->botspecRight, NULL, &specbotRightRect); break;
				case 'u': SDL_Rect specbotUpRect = { game->bots[i].posx, game->bots[i].posy, BOTSIZE, BOTSIZE };
						  SDL_RenderCopy(game->renderer, game->botspecUp, NULL, &specbotUpRect); break;
				case 'd': SDL_Rect specbotDownRect = { game->bots[i].posx, game->bots[i].posy, BOTSIZE, BOTSIZE };
						  SDL_RenderCopy(game->renderer, game->botspecDown, NULL, &specbotDownRect); break;
				}
			else
				switch (game->bots[i].rotation) {
				case 'l': SDL_Rect botLeftRect = { game->bots[i].posx, game->bots[i].posy, BOTSIZE, BOTSIZE };
						  SDL_RenderCopy(game->renderer, game->botLeft, NULL, &botLeftRect); break;
				case 'r':  SDL_Rect botRightRect = { game->bots[i].posx, game->bots[i].posy, BOTSIZE, BOTSIZE };
						   SDL_RenderCopy(game->renderer, game->botRight, NULL, &botRightRect); break;
				case 'u': SDL_Rect botUpRect = { game->bots[i].posx, game->bots[i].posy, BOTSIZE, BOTSIZE };
						  SDL_RenderCopy(game->renderer, game->botUp, NULL, &botUpRect); break;
				case 'd': SDL_Rect botDownRect = { game->bots[i].posx, game->bots[i].posy, BOTSIZE, BOTSIZE };
						  SDL_RenderCopy(game->renderer, game->botDown, NULL, &botDownRect); break;
				}
	}
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (game->bullets[i].active) {
			if (game->bullets[i].indx == -1) {
				switch (game->bullets[i].rotation) {
				case 'l': SDL_Rect bulletLeftRect = { game->bullets[i].posx, game->bullets[i].posy, BULLETSIZE, BULLETSIZE };
						  SDL_RenderCopy(game->renderer, game->bulletLeft[game->mainTank.lvl], NULL, &bulletLeftRect); break;
				case 'r':  SDL_Rect bulletRightRect = { game->bullets[i].posx, game->bullets[i].posy, BULLETSIZE, BULLETSIZE };
						   SDL_RenderCopy(game->renderer, game->bulletRight[game->mainTank.lvl], NULL, &bulletRightRect); break;
				case 'u': SDL_Rect bulletUpRect = { game->bullets[i].posx, game->bullets[i].posy, BULLETSIZE, BULLETSIZE };
						  SDL_RenderCopy(game->renderer, game->bulletUp[game->mainTank.lvl], NULL, &bulletUpRect); break;
				case 'd': SDL_Rect bulletDownRect = { game->bullets[i].posx, game->bullets[i].posy, BULLETSIZE, BULLETSIZE };
						  SDL_RenderCopy(game->renderer, game->bulletDown[game->mainTank.lvl], NULL, &bulletDownRect); break;
				}
			}
			else if (game->bullets[i].indx == 1) {
				switch (game->bullets[i].rotation) {
				case 'l': SDL_Rect bulletLeftRect = { game->bullets[i].posx, game->bullets[i].posy, BULLETSIZE, BULLETSIZE };
						  SDL_RenderCopy(game->renderer, game->bulletLeft[4], NULL, &bulletLeftRect); break;
				case 'r':  SDL_Rect bulletRightRect = { game->bullets[i].posx, game->bullets[i].posy, BULLETSIZE, BULLETSIZE };
						   SDL_RenderCopy(game->renderer, game->bulletRight[4], NULL, &bulletRightRect); break;
				case 'u': SDL_Rect bulletUpRect = { game->bullets[i].posx, game->bullets[i].posy, BULLETSIZE, BULLETSIZE };
						  SDL_RenderCopy(game->renderer, game->bulletUp[4], NULL, &bulletUpRect); break;
				case 'd': SDL_Rect bulletDownRect = { game->bullets[i].posx, game->bullets[i].posy, BULLETSIZE, BULLETSIZE };
						  SDL_RenderCopy(game->renderer, game->bulletDown[4], NULL, &bulletDownRect); break;
				}
			}
		}
	}
	SDL_RenderPresent(game->renderer);

}




void Create(GameState *gameState) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Battle Tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 676, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);




	//videti za ovo

	gameState->renderer = renderer;



}
void initImages(GameState *game) {
	doWater(game);
	doWall(game);
	doIronWall(game);
	doBase(game);
	doTankLeft(game);
	doTankRight(game);
	doTankUp(game);
	doTankDown(game);
	doBotLeft(game);
	doBotRight(game);
	doBotUp(game);
	doBotDown(game);
	dospecbotDown(game);
	dospecbotLeft(game);
	dospecbotRight(game);
	dospecbotUp(game);
	doBomb(game);
	doSrce(game);
	doBulletLeft(game);
	doBulletRight(game);
	doBulletUp(game);
	doBulletDown(game);
	doMenu(game);
	doPlay(game);
	doHighscore(game);
	doemh(game);
	doExit(game);
	doStar(game);
	doFreez(game);
	doFinishlvleditor(game);
	doEditlvl(game);
	doBack(game);

}

int highscoreList(GameState *game) {
	FILE *fptr;
	podatak citanje[10];

	SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);
	SDL_RenderClear(game->renderer);
	doWord(game, "HIGHSCORE ", 100, 0, 600, 190);

	SDL_Rect backRect = { 700, 600, TILE * 4, TILE * 4 };
	SDL_RenderCopy(game->renderer, game->back, NULL, &backRect);


	if ((fptr = fopen("rezultati.bin", "rb")) == NULL) {
		printf("Error!");
		exit(1);
	}

	int n = fread(&citanje, sizeof(podatak), 10, fptr);
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		char str[10];
		int size = 5;
		sprintf(str, "%d", i + 1);
		printf("%s", str);
		doWord(game, str, 100, 190 + i * 50, 30, 30);
		doWord(game, citanje[i].ime, 140, 190 + i * 50, strlen(citanje[i].ime) * 30, 30);
		sprintf(str, "%d", citanje[i].score);
		if (citanje[i].score < 10) size = 1;
		else if (citanje[i].score < 100) size = 2;
		else if (citanje[i].score < 1000) size = 3;
		else if (citanje[i].score < 10000) size = 4;
		doWord(game, str, 550, 190 + i * 50, 30 * size, 30);
	}
	SDL_RenderPresent(game->renderer);

	SDL_Event event;
	int cnt = 0;
	while (cnt < 500) {
		SDL_PollEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				double x = event.motion.x;
				double y = event.motion.y;
				printf("%d %d\n", x, y);
				if (x > 700 && y > 600 && x < 800 && y < 676) {
					return 3;
				}
			}
		}
		SDL_Delay(10);
	}
}


int createMenu(GameState *game, int *emh) {
	int play = 0; // 1 za obicni play , 2 za edit map
	int x, y;
	//emh ---> 0 ako se bira easy (podrazumevano), 1 - medium, 2 - hard
	SDL_Event event;
	SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);

	SDL_RenderClear(game->renderer);


	SDL_Rect bRect = { 130, 53, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->B, NULL, &bRect);


	SDL_Rect aRect = { 220, 51, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->A, NULL, &aRect);


	SDL_Rect tRect = { 310, 50, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->T, NULL, &tRect);

	SDL_Rect ttRect = { 400, 50, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->T, NULL, &ttRect);

	SDL_Rect lRect = { 490, 50, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->L, NULL, &lRect);

	SDL_Rect eRect = { 580, 50, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->E, NULL, &eRect);

	SDL_Rect tttRect = { 175, 150, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->T, NULL, &tttRect);

	SDL_Rect aaRect = { 265, 151, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->A, NULL, &aaRect);

	SDL_Rect nRect = { 355, 150, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->N, NULL, &nRect);

	SDL_Rect kRect = { 445, 150, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->K, NULL, &kRect);

	SDL_Rect sRect = { 530, 150, LETTER, LETTER };
	SDL_RenderCopy(game->renderer, game->S, NULL, &sRect);

	SDL_Rect playRect = { 300, 300, 200, 70 };
	SDL_RenderCopy(game->renderer, game->play, NULL, &playRect);

	SDL_Rect highscoreRect = { 200, 380, 400, 70 };
	SDL_RenderCopy(game->renderer, game->highscore, NULL, &highscoreRect);

	SDL_Rect emhRect = { 50, 465, 700, 60 };
	SDL_RenderCopy(game->renderer, game->emh, NULL, &emhRect);

	SDL_Rect exitRect = { 735, 610, 60, 60 };
	SDL_RenderCopy(game->renderer, game->exit, NULL, &exitRect);

	SDL_Rect editRect = { 225, 538, 350, 70 };
	SDL_RenderCopy(game->renderer, game->editlvl, NULL, &editRect);
	//doWord(game);
	SDL_Rect esquare = { 22, 484, 30, 36 };
	SDL_Rect msquare = { 200, 484, 70, 36 };
	SDL_Rect hsquare = { 520, 484, 75, 36 };
	while (!play) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEBUTTONDOWN: {
				if (event.button.button == SDL_BUTTON_LEFT) {
					x = event.motion.x;
					y = event.motion.y;
					printf("%d %d\n", x, y);
					if (x > 300 && x < 500 && y>300 && y < 370) {
						play = 1;
						SDL_Rect tankRRightRect = { 270, 313, TANKSIZE / 2, TANKSIZE / 2 };
						SDL_RenderCopy(game->renderer, game->tankRight[0], NULL, &tankRRightRect);

					}
					else if (x > 60 && x < 200 && y>484 && y < 520) {
						*emh = 0;
						printf("%d\n", *emh);
						SDL_Rect tankRRRightRect = { 25, 485, TANKSIZE / 2, TANKSIZE / 2 };
						SDL_RenderCopy(game->renderer, game->tankRight[0], NULL, &tankRRRightRect);
						SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);

						SDL_RenderFillRect(game->renderer, &msquare);

						SDL_RenderFillRect(game->renderer, &hsquare);

						SDL_RenderPresent(game->renderer);
					}
					else if (x > 270 && x < 520 && y>484 && y < 520) {
						*emh = 1;
						printf("%d\n", *emh);
						SDL_Rect tankRRRRightRect = { 235, 485, TANKSIZE / 2, TANKSIZE / 2 };
						SDL_RenderCopy(game->renderer, game->tankRight[0], NULL, &tankRRRRightRect);
						SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);
						SDL_RenderFillRect(game->renderer, &esquare);
						SDL_RenderFillRect(game->renderer, &hsquare);

						SDL_RenderPresent(game->renderer);
					}
					else if (x > 596 && x < 732 && y>484 && y < 520) {
						*emh = 2;
						printf("%d\n", *emh);
						SDL_Rect tankRRRRRightRect = { 560, 485, TANKSIZE / 2, TANKSIZE / 2 };
						SDL_RenderCopy(game->renderer, game->tankRight[0], NULL, &tankRRRRRightRect);
						SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);
						SDL_RenderFillRect(game->renderer, &esquare);
						SDL_RenderFillRect(game->renderer, &msquare);

						SDL_RenderPresent(game->renderer);
					}
					else if (x > 225 && x < 575 && y>538 && y < 608) {
						play = 2;
						SDL_Rect tankRRRRRRightRect = { 200, 540, TANKSIZE / 2, TANKSIZE / 2 };
						SDL_RenderCopy(game->renderer, game->tankRight[0], NULL, &tankRRRRRRightRect);
					}
					else if (x > 200 && x < 600 && y>380 && y < 450) {
						play = 4;
					}
				}
			}
			}

		}

		SDL_RenderPresent(game->renderer);
		SDL_Delay(10);
	}

	TTF_Quit();
	return play;
}

void playMode(GameState*game) {

	SDL_SetRenderDrawColor(game->renderer, 140, 150, 40, 255);
	SDL_RenderClear(game->renderer);



		SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);
		SDL_Rect rectt = { 676, 0, 124, 676 };
		SDL_RenderFillRect(game->renderer, &rectt);

		doRender(game);

	//	doWord(game, "pause", 690, 550, 100, 50);
	//	SDL_RenderPresent(game->renderer);
	/*	SDL_Event event;
		double x, y;
		SDL_PollEvent(&event);
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				x = event.motion.x;
				y = event.motion.y;
				if (x < 790 && y < 600 && x>690 && y>550) {
					int click = 0;
					SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);
					SDL_Rect recto = { 690, 550, 100, 50 };
					SDL_RenderFillRect(game->renderer, &recto);
					doWord(game, "resume", 690, 550, 100, 50);
					doRender(game);
					SDL_RenderPresent(game->renderer);
					while (!click) {
						SDL_Event evento;




						SDL_PollEvent(&evento);
						if (evento.type == SDL_MOUSEBUTTONDOWN) {
							if (evento.button.button == SDL_BUTTON_LEFT) {
								x = evento.motion.x;
								y = evento.motion.y;
								if (x < 790 && y < 600 && x>690 && y>550)
									click = 1;
							}
						}
					}
				}
			}
		}

*/

}

void insert(GameState *game, int score) {
	SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);
	SDL_RenderClear(game->renderer);
	doWord(game, "INSERT NAME: ", 250, 150, 300, 100);

	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
	SDL_Rect nameRect = { 250, 300, 300, 75 };
	SDL_RenderFillRect(game->renderer, &nameRect);
	doWord(game, "YOUR SCORE: ", 275, 400, 250, 100);

	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
	SDL_Rect scoreRect = { 250, 550, 300, 75 };
	SDL_RenderFillRect(game->renderer, &scoreRect);

	doWord(game, "DONE", 350, 630, 100, 50);

	SDL_RenderPresent(game->renderer);
	int tastatura = 0;
	double x, y;
	int cnt = 0;
	int cntletters = 0;
	int pos = 0;

	char string[30] = "";

	int done = 0;



	SDL_StartTextInput();
	SDL_Event event;


	while (cnt < 500 && (!done)) {

		SDL_PollEvent(&event);

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			printf("b");
			if (event.button.button == SDL_BUTTON_LEFT) {

				x = event.motion.x;
				y = event.motion.y;
				if (x > 250 && x < 550 && y>300 && y < 375 && (!tastatura)) {

					tastatura = 1;
					doWord(game, "|", 253, 300, 10, 75);
					SDL_RenderPresent(game->renderer);
				}
				else if (x > 350 && x < 450 && y>630 && y < 680) {
					done = 1;
					FILE *fptr;
					podatak citanje[10];
					podatak tmp;

					if ((fptr = fopen("rezultati.bin", "rb")) == NULL) {
						printf("Error!");
						exit(1);
					}

					int n = fread(&citanje, sizeof(podatak), 10, fptr);
					fclose(fptr);
					printf("%d\n", n);
					for (int i = 0; i < n - 1; i++) {
						for (int j = i + 1; j < n; j++) {
							if (citanje[i].score < citanje[j].score) {
								tmp = citanje[i];
								citanje[i] = citanje[j];
								citanje[j] = tmp;

							}
						}
					}
					if (!(n == 10 && score <= citanje[9].score)) {
						int i = 0;
						while (score < citanje[i].score) i++;
						for (int j = n; j > i; j--) citanje[j] = citanje[j - 1];
						strcpy(citanje[i].ime, string);
						citanje[i].score = score;
					}
					if (n + 1 > 10) n = 10;
					else n = n + 1;
					printf("%d\n", n);
					for (int i = 0; i < n; i++) printf("%d %s\n", citanje[i].score, citanje[i].ime);



					FILE *ptr;
					if ((ptr = fopen("rezultati.bin", "wb")) == NULL) {
						printf("Error!");
						exit(1);
					}


					for (int i = 0; i < n; i++) {
						fwrite(&citanje[i], sizeof(podatak), 1, ptr);
					}
					fclose(ptr);
					highscoreList(game);

				}



			}
		}

		if (event.type == SDL_TEXTINPUT && cntletters < 15) {

			printf(" %s\n", event.text.text);
			strcat(string, event.text.text);
			printf(" %s\n", string);
			pos = cntletters * 20 + 252;
			cntletters++;

			SDL_Rect recto = { pos, 300, 20, 75 };
			SDL_RenderFillRect(game->renderer, &recto);
			doWord(game, event.text.text, pos, 300, 20, 75);
			doWord(game, "|", pos + 20, 300, 10, 75);
			SDL_RenderPresent(game->renderer);
		}

		if (event.type == SDL_KEYDOWN && cntletters > 0) {
			if (event.key.keysym.sym == SDLK_BACKSPACE) {
				SDL_Rect delete = { (--cntletters) * 20 + 252, 300, 40, 75 };

				SDL_RenderFillRect(game->renderer, &delete);
				doWord(game, "|", cntletters * 20 + 252, 300, 10, 75);
				string[strlen(string) - 1] = '\0';


				SDL_RenderPresent(game->renderer);
			}
		}



		SDL_Delay(70);
	}
	SDL_StopTextInput();



	system("pause");


}


#endif // !HEADER_FILE




