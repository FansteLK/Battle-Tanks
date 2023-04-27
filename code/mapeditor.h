#ifndef HEADERFILE
#define HEADERFILE
#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"

#define DIM 26
#define TILE 26
#define TANKSIZE 52
#define BOTSIZE 52
#define BULLETSIZE 26
#define MAX 20
#define MAX_BULLETS 100

/*int doEvents(char map[][DIM], GameState *game, char tek) {
	SDL_Event event;
	double x, y;
	int posx, posy;
	int possx, possy;
	while (SDL_PollEvent(&event)){
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN: {
			if (event.button.button == SDL_BUTTON_LEFT) {
				//SDL_GetMouseState(&x, &y);
				posx = (int)x / DIM;
				posy = (int)y / DIM;
				switch (tek) {
				case 'v':
					SDL_Rect waterRect = { posx*TILE, posy*TILE, TILE, TILE };
					SDL_RenderCopy(game->renderer, game->water, NULL, &waterRect);
					map[posx][posy] = 'v';
					break;
				case 'c':
					SDL_Rect ironwallRect = { posx*TILE, posy*TILE, TILE, TILE };
					SDL_RenderCopy(game->renderer, game->ironwall, NULL, &ironwallRect);
					map[posx][posy] = 'c';
					break;
				case 'z':
					SDL_Rect wallRect = { posx*TILE, posy*TILE, TILE, TILE };
					SDL_RenderCopy(game->renderer, game->wall, NULL, &wallRect);
					map[posx][posy] = 'z';
					break;
				}

			}
		} return 0;
		case SDL_MOUSEWHEEL: {
			if (event.wheel.y < 0) {
				switch (tek) {
				case 'v': tek = 'c'; break;
				case 'z': tek = 'v'; break;
				case 'c': tek = 'z'; break;
				}
			}
			else if (event.wheel.y > 0) {
				switch (tek) {
				case 'v': tek = 'z'; break;
				case 'z': tek = 'c'; break;
				case 'c': tek = 'v'; break;
				}
				return 0;
			}
		}
		case SDL_MOUSEMOTION: {
			x = event.motion.x;
			y = event.motion.y;
			printf("%lf %lf \n", x, y);
			posx = (int)x;
			posy = (int)y;
			printf("%d %d \n", posx, posy);

			if (x < 676 && y < 676 && x>0 && y>0) {
				switch (tek) {
				case 'v':
					SDL_Rect waterRect = { x, y, TILE, TILE };
					SDL_RenderCopy(game->renderer, game->water, NULL, &waterRect);
					break;
				case 'c':
					SDL_Rect ironwallRect = { x, y, TILE, TILE };
					SDL_RenderCopy(game->renderer, game->ironwall, NULL, &ironwallRect);
					break;
				case 'z':
					SDL_Rect wallRect = { posx, posy, TILE, TILE };
					printf("ashjdgajh");
					SDL_RenderCopy(game->renderer, game->wall, NULL, &wallRect);
					printf("mmmdgajh");
					break;
				}
			}
		}
		}

	}

		if (x < 676 && y < 676 && x>0 && y>0) {
			switch (*tek) {
			case 'v':
				SDL_Rect waterRect = { x, y, TILE, TILE };
				SDL_RenderCopy(game->renderer, game->water, NULL, &waterRect);
				break;
			case 'c':
				SDL_Rect ironwallRect = { x, y, TILE, TILE };
				SDL_RenderCopy(game->renderer, game->ironwall, NULL, &ironwallRect);
				break;
			case 'z':
				SDL_Rect wallRect = { x, y, TILE, TILE };
				SDL_RenderCopy(game->renderer, game->wall, NULL, &wallRect);
				break;
			}
		}

}*/

int editmap(GameState *gamestate) {
	int cnt = 0;
	char map[][DIM] = {
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'},
	{'g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g','g'}
	};
	char tek = 'z';


	SDL_SetRenderDrawColor(gamestate->renderer, 140, 150, 40, 255);

	SDL_RenderClear(gamestate->renderer);


	SDL_SetRenderDrawColor(gamestate->renderer, 4, 0, 0, 255);
	for (int i = 0; i <= DIM; i++) {
		SDL_RenderDrawLine(gamestate->renderer, i*DIM, 0, i*DIM, DIM*DIM);
		SDL_RenderDrawLine(gamestate->renderer, 0, i*DIM, DIM*DIM, i*DIM);
	}



	SDL_Rect rect = { 676, 0, 124, 676 };
	SDL_RenderFillRect(gamestate->renderer, &rect);


	SDL_SetRenderDrawColor(gamestate->renderer, 105, 105, 105, 255);
	SDL_Rect bazicarect = { 11 * TILE + 1, 23 * TILE + 1, 4 * TILE - 1, 3 * TILE - 1 };
	SDL_RenderFillRect(gamestate->renderer, &bazicarect);

	doWord(gamestate, "active:", 690, 230, 100, 50);
	doWord(gamestate, "finish", 690, 550, 100, 50);
	doWord(gamestate, "return", 690, 616, 100, 50);

	//SDL_Rect finishlvleditorRect = { 710, 550, 70, 50 };
	//SDL_RenderCopy(gamestate->renderer, gamestate->finishlvleditor, NULL, &finishlvleditorRect);

	while (cnt < 500) {


		SDL_Event event;
		double x, y;
		int posx, posy;
		int possx, possy;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEBUTTONDOWN: {
				if (event.button.button == SDL_BUTTON_LEFT) {
					x = event.motion.x;
					y = event.motion.y;
					if (x < 790 && y < 600 && x>690 && y>550) {
						for (int i = 0; i < DIM; i++)
							for (int j = 0; j < DIM; j++) gamestate->map[i][j] = map[i][j];
						gamestate->map[12][24] = 'b';
						gamestate->map[13][24] = 'p';
						gamestate->map[12][25] = 'p';
						gamestate->map[13][25] = 'p';
						gamestate->map[11][24] = 'z';
						gamestate->map[11][25] = 'z';
						gamestate->map[14][25] = 'z';
						gamestate->map[14][24] = 'z';
						gamestate->map[11][23] = 'z';
						gamestate->map[14][23] = 'z';
						gamestate->map[12][23] = 'z';
						gamestate->map[13][23] = 'z';

						return(1);
					}
					if (x < 790 && y < 666 && x>690 && y>616) {
						return(3);
					}
					if (!(x > 286 && x < 390 && y>598)) {
						posx = (int)x / DIM;
						posy = (int)y / DIM;
						if (x < DIM*DIM && y < DIM*DIM && x>0 && y>0) {
							switch (tek) {
							case 'v':
								SDL_Rect waterRect = { posx*TILE + 1, posy*TILE + 1, TILE - 1, TILE - 1 };
								SDL_RenderCopy(gamestate->renderer, gamestate->water, NULL, &waterRect);

								map[posx][posy] = 'v';
								break;
							case 'c':
								SDL_Rect ironwallRect = { posx*TILE + 1, posy*TILE + 1, TILE - 1, TILE - 1 };
								SDL_RenderCopy(gamestate->renderer, gamestate->ironwall, NULL, &ironwallRect);
								map[posx][posy] = 'c';
								break;
							case 'z':
								SDL_Rect wallRect = { posx*TILE + 1, posy*TILE + 1, TILE - 1, TILE - 1 };
								SDL_RenderCopy(gamestate->renderer, gamestate->wall, NULL, &wallRect);
								map[posx][posy] = 'z';
								break;
							}
						}

					}
				}

				if (event.button.button == SDL_BUTTON_RIGHT) {
					x = event.motion.x;
					y = event.motion.y;

					if (x < DIM*DIM && y < DIM*DIM && x>0 && y>0) {
						posx = (int)x / DIM;
						posy = (int)y / DIM;
						SDL_SetRenderDrawColor(gamestate->renderer, 140, 150, 40, 255);
						SDL_Rect erease = { posx*TILE + 1, posy*TILE + 1, TILE - 1, TILE - 1 };
						SDL_RenderFillRect(gamestate->renderer, &erease);
						map[posx][posy] = 'g';

					}
				}



			} break;
			case SDL_MOUSEWHEEL: {
				if (event.wheel.y < 0) {
					switch (tek) {
					case 'v': tek = 'c'; break;
					case 'z': tek = 'v'; break;
					case 'c': tek = 'z'; break;
					}
				}
				else if (event.wheel.y > 0) {
					switch (tek) {
					case 'v': tek = 'z'; break;
					case 'z': tek = 'c'; break;
					case 'c': tek = 'v'; break;
					}

				}
			}break;
				/*case SDL_MOUSEMOTION: {
					x = event.motion.x;
					y = event.motion.y;
					printf("%lf %lf \n", x, y);
					posx = (int)x;
					posy = (int)y;
					printf("%d %d \n", posx, posy);

					if (x < 676 && y < 676 && x>0 && y>0) {
						switch (tek) {
						case 'v':
							//SDL_Rect waterRect = { x, y, TILE, TILE };
							//SDL_RenderCopy(gamestate->renderer, gamestate->water, NULL, &waterRect);

							break;
						case 'c':
							//SDL_Rect ironwallRect = { x, y, TILE, TILE };
							//SDL_RenderCopy(gamestate->renderer, gamestate->ironwall, NULL, &ironwallRect);
							break;
						case 'z':
							//SDL_Rect wallRect = { posx, posy, TILE, TILE };

							//SDL_RenderCopy(gamestate->renderer, gamestate->wall, NULL, &wallRect);

							break;
						}
					}
				}*/
			}

		}
		switch (tek) {
		case 'v':
			SDL_Rect waterRect = { 717, 300, TILE * 2, 2 * TILE };
			SDL_RenderCopy(gamestate->renderer, gamestate->water, NULL, &waterRect);

			break;
		case 'c':
			SDL_Rect ironwallRect = { 717, 300, 2 * TILE, 2 * TILE };
			SDL_RenderCopy(gamestate->renderer, gamestate->ironwall, NULL, &ironwallRect);
			break;
		case 'z':
			SDL_Rect wallRect = { 717, 300, 2 * TILE, 2 * TILE };

			SDL_RenderCopy(gamestate->renderer, gamestate->wall, NULL, &wallRect);

			break;
		}

		SDL_RenderPresent(gamestate->renderer);
		SDL_Delay(10);
	}



}


#endif // !HEADERFILE

