#define _CRT_SECURE_NO_WARNINGS

#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "logic.h"
#include "mapeditor.h"

#define tank_speed 5


int main(int argc, char argv[]) {

	srand(time(NULL));

	GameState gamestate;
	gamestate.gamelvl = 0;
	gamestate.nivo = 1;
	Create(&gamestate);

	int score = 154;
	initImages(&gamestate);
	//insert(&gamestate, score);

	int play = createMenu(&gamestate, &gamestate.gamelvl);
	initgame(&gamestate);

	//editmap(&gamestate);

	char m[7];

	for (int i = 0; i < 7; i++) {
		m[i] = 'p';
	}
	gamestate.changed = 0;
	const a = -1;
	char d = 'u';
	while (1) {
		if (play == 1) {
			//printf("%d\n", gamestate.mainTank.lvl);
			//playMode(&gamestate);
			doRender(&gamestate);
			keypress(&m);
			for (int i = 0; i < 7; i++)
				if (m[i] != 'p') {
					while (m[6] == 'o') {
							keypress(&m);
					}
					//printf("%c ", m[i]);
					int c = do_move(&gamestate, m[i], valid_move(&gamestate, &gamestate.mainTank, m[i]));
					if (c == 10) {
						printf("kraj igre \n");
						initgame(&gamestate);
					}
				}
			
			//printf("%c\n",gamestate.mainTank.rotation);
			int c = do_move(&gamestate, 'm', valid_move(&gamestate, &gamestate.mainTank, 'n'));
			if (c == 10) {
				printf("kraj igre \n");
				initgame(&gamestate);
			}
			if (!gamestate.mainTank.life) {
				printf("Umro si \n");
				initgame(&gamestate);
			}
			if (gamestate.kills >= 10 * (gamestate.gamelvl + 1)) {
				gamestate.nivo++;
				if (gamestate.nivo > 10) gamestate.nivo = 1;
				initgame(&gamestate);
			}
			SDL_Delay(20);
		}
		else if (play == 3) play = createMenu(&gamestate, &gamestate.gamelvl);
		else if (play == 4) play = highscoreList(&gamestate);
		else play = editmap(&gamestate);
	}
}