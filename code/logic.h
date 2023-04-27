
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdlib.h>
#include "graphics.h"
#include <math.h>
#include <string.h>

#define num 26
#define big_num 676
#define bullet_speed 15 
#define blink_period 250

int max_bot_speed = 3;
int main_tank_speed = 5;
int freez_period = 300;
int fire_rate_main = 40;
int fire_rate_bot = 40;
int spec_bot_speed = 6;
int spec_bot_fire_rate = 80;


typedef struct {
	int glx, gly, dlx, dly, gdx, gdy, ddx, ddy, usx, usy, dsx, dsy, lsx, lsy, rsx, rsy;
}cords;

typedef struct {
	char map[num][num];
}struktura;

void koordinate(Tank *mainTank, char dir, cords *a, int indx) {
	int nx = mainTank->posx, ny = mainTank->posy;

	if (indx == -1) {
		switch (dir) {
		case 'u':
			ny -= main_tank_speed;
			break;
		case 'd':
			ny += main_tank_speed;
			break;
		case 'l':
			nx -= main_tank_speed;
			break;
		case 'r':
			nx += main_tank_speed;
		}
	}
	else {
		int a = 1;
		if (mainTank->botspec) a = 2;

		switch (dir) {
		case 'u':
			ny -= a*max_bot_speed;
			break;
		case 'd':
			ny += a*max_bot_speed;
			break;
		case 'l':
			nx -= a*max_bot_speed;
			break;
		case 'r':
			nx += a*max_bot_speed;
		}
	}
	a->glx = nx + 1, a->gly = ny + 1;
	a->gdx = nx + 2 * num - 1, a->gdy = ny + 1;
	a->dlx = nx + 2, a->dly = ny + 2 * num - 2;
	a->ddx = nx + 2 * num - 2, a->ddy = ny + 2 * num - 2;
	a->usx = a->glx + num, a->usy = a->gly;
	a->dsx = a->dlx + num, a->dsy = a->dly;
	a->lsx = a->glx, a->lsy = a->gly + num;
	a->rsx = a->gdx, a->rsy = a->gdy + num;

}


int not_in_bound(int x) {
	if (x < 0) return 1;
	if (x > big_num) return 2;
	return 0;
}


int in_bound_bullet(cords a) {
	if (a.glx < -50) return 0;
	if (a.glx > big_num + 50) return 0;
	if (a.gly < -50) return 0;
	if (a.gly > big_num + 50) return 0;
	if (a.dlx < -50) return 0;
	if (a.dlx < -50) return 0;
	if (a.dly > big_num + 50) return 0;
	if (a.dly < -50) return 0;
	if (a.gdx > big_num + 50) return 0;
	if (a.gdx < -50) return 0;
	if (a.gdy > big_num + 50) return 0;
	if (a.gdy < -50) return 0;
	if (a.ddx < -50) return 0;
	if (a.ddx > big_num + 50) return 0;
	if (a.ddy < -50) return 0;
	if (a.ddy > big_num + 50) return 0;
	return 1;
}


int bounds(Tank *mainTank, char dir, int indx) {
	cords x;
	koordinate(mainTank, dir, &x, indx);
	switch (not_in_bound(x.glx)) {
	case 1:
		mainTank->posx = 0;
		mainTank->posy = x.gly - 1;
		return 0;
	case 2:
		mainTank->posx = big_num - 2 * num;
		mainTank->posy = x.gly - 1;
		return 0;
	}
	switch (not_in_bound(x.gly)) {
	case 1:
		mainTank->posx = x.glx - 1;
		mainTank->posy = 0;
		return 0;
	case 2:
		mainTank->posx = x.glx - 1;
		mainTank->posy = big_num - 2 * num;
		return 0;
	}
	switch (not_in_bound(x.gdx)) {
	case 1:
		mainTank->posx = 0;
		mainTank->posy = x.gly - 1;
		return 0;
	case 2:
		mainTank->posx = big_num - 2 * num;
		mainTank->posy = x.gly - 1;
		return 0;
	}
	switch (not_in_bound(x.gdy)) {
	case 1:
		mainTank->posx = x.glx - 1;
		mainTank->posy = 0;
		return 0;
	case 2:
		mainTank->posx = x.glx - 1;
		mainTank->posy = big_num - 2 * num;
		return 0;
	}
	switch (not_in_bound(x.dlx)) {
	case 1:
		mainTank->posx = 0;

		return 0;
	case 2:
		mainTank->posx = big_num - 2 * num;

		return 0;
	}
	switch (not_in_bound(x.dly)) {
	case 1:

		mainTank->posy = 0;
		return 0;
	case 2:

		mainTank->posy = big_num - 2 * num;
		return 0;
	}
	switch (not_in_bound(x.ddx)) {
	case 1:
		mainTank->posx = 0;

		return 0;
	case 2:
		mainTank->posx = big_num - 2 * num;

		return 0;

	}
	switch (x.ddy) {
	case 1:
		mainTank->posx = x.glx;
		mainTank->posy = 0;
		return 0;
	case 2:
		mainTank->posx = x.glx;
		mainTank->posy = big_num - 2 * num;
		return 0;
	}
	return 1;
}

int bounds_bullet(Tank *m, char dir, int indx) {
	cords a;
	koordinate(m, dir, &a, indx);
	return (in_bound_bullet(a));
}



int walls(GameState *m, Tank *mainTank, char dir, int indx) {
	cords x;
	koordinate(mainTank, dir, &x, mainTank->indx);

	int p, q;
	switch (dir)
	{
	case 'u':
		p = x.glx / num;
		q = (x.gly - 1) / num;
		if (m->map[p][q] != 'g') {
			mainTank->posy = (q + 1) * num + 1;
			return 0;
		}
		p = x.gdx / num;
		q = (x.gdy - 1) / num;
		if (m->map[p][q] != 'g') {
			mainTank->posy = (q + 1) * num + 1;
			return 0;
		}
		p = x.usx / num;
		q = x.usy / num;
		if (m->map[p][q] != 'g') {
			mainTank->posy = (q + 1) * num + 1;
			return 0;
		}
		break;
	case 'd':
		p = x.dlx / num;
		q = (x.dly + 1) / num;

		if (m->map[p][q] != 'g') {
			mainTank->posy = (q - 2) * num - 1;
			return 0;
		}
		p = x.ddx / num;
		q = (x.ddy + 1) / num;
		if (m->map[p][q] != 'g') {
			mainTank->posy = (q - 2) * num - 1;
			return 0;
		}
		p = x.dsx / num;
		q = (x.dsy + 1) / num;

		if (m->map[p][q] != 'g') {
			mainTank->posy = (q - 2) * num - 1;
			return 0;
		}
		break;
	case 'l':
		p = (x.glx - 1) / num;
		q = x.gly / num;
		if (m->map[p][q] != 'g') {
			mainTank->posx = (p + 1) * num;
			return 0;
		}
		p = (x.dlx - 1) / num;
		q = x.dly / num;
		if (m->map[p][q] != 'g') {
			mainTank->posx = (p + 1) * num;
			return 0;
		}
		p = (x.lsx - 1) / num;
		q = x.lsy / num;
		if (m->map[p][q] != 'g') {
			mainTank->posx = (p + 1) * num;
			return 0;
		}
		break;
	case 'r':
		p = (x.gdx + 1) / num;
		q = x.gdy / num;
		if (m->map[p][q] != 'g') {
			mainTank->posx = (p - 2) * num - 1;
			return 0;
		}
		p = (x.ddx + 1) / num;
		q = x.ddy / num;
		if (m->map[p][q] != 'g') {
			mainTank->posx = (p - 2) * num - 1;
			return 0;
		}

		p = (x.rsx + 1) / num;
		q = x.rsy / num;
		if (m->map[p][q] != 'g') {
			mainTank->posx = (p - 2) * num - 1;
			return 0;
		}
		break;
	}

	if (indx == -1) return main_tank_speed;
	if (mainTank->botspec) return spec_bot_speed;
	return max_bot_speed;
}

int tank_inter(int x, int y, Tank *t) {
	return x >= t->posx && x <= t->posx + 2 * num && y >= t->posy && y <= t->posy + 2 * num;
}


int tank_tank(Tank *t1, Tank *t2, char dir, int indx) {
	if (t1->posx == t2->posx && t1->posy == t2->posy) return 1;
	int nx = t1->posx, ny = t1->posy;
	if (indx == -1) {
		switch (dir) {
		case 'u':
			ny -= main_tank_speed;
			break;
		case 'd':
			ny += main_tank_speed;
			break;
		case 'l':
			nx -= main_tank_speed;
			break;
		case 'r':
			nx += main_tank_speed;
		}
	}
	else {
		int a = 1;
		if (t1->botspec) a = 2;
		switch (dir) {
		case 'u':
			ny -= a*max_bot_speed;
			break;
		case 'd':
			ny += a*max_bot_speed;
			break;
		case 'l':
			nx -= a*max_bot_speed;
			break;
		case 'r':
			nx += a*max_bot_speed;
		}
	}
	if (tank_inter(nx, ny, t2)) return 0;
	if (tank_inter(nx + 2 * num, ny, t2)) return 0;
	if (tank_inter(nx, ny + 2 * num, t2)) return 0;
	if (tank_inter(nx + 2 * num, ny + 2 * num, t2)) return 0;
	return 1;
}

int valid_move(GameState *m, Tank *t, char dir) {
	int indx = 1;
	if (t->posx == m->mainTank.posx && t->posy == m->mainTank.posy) indx = -1;
	if (t->rotation != dir && dir != 'n' && dir != 's') return main_tank_speed;
	if (dir == 'n') return 0;
	if (dir == 's') return 0;

	if (!bounds(t, dir, indx)) return 0;

	for (int i = 0; i < m->numberOfBots; i++) {
		if (m->bots[i].active && !tank_tank(t, &m->bots[i], dir, indx)) {
			return 0;
		}
	}
	if (!tank_tank(t, &m->mainTank, dir, indx)) return 0;
	return walls(m, t, dir, indx);

}

void create_bullet(Tank *b, char dir, int p, int q) {
	switch (dir) {
	case 'u':
		b->posx = p + num / 2;
		b->posy = q - 6;
		break;
	case 'd':
		b->posx = p + num / 2;
		b->posy = q + num + 15;
		break;
	case 'l':
		b->posx = p - 6;
		b->posy = q + num / 2;
		break;
	case 'r':
		b->posx = p + num + 15;
		b->posy = q + num / 2;
	}
}

int new_bullet(GameState *m, Tank *mainTank, char pos) {
	if (mainTank->indx == -1) {
		mainTank->last_shot = fire_rate_main;
	}
	else
		if (mainTank->botspec)
			mainTank->last_shot = spec_bot_fire_rate;
		else
			mainTank->last_shot = fire_rate_bot;
	int i = 0;
	int p = 0;
	while (i < MAX_BULLETS && m->bullets[i].active) i++;
	if (i < MAX_BULLETS) {

		p = 1;
		m->bullets[i].active = 1;
		m->bullets[i].indx = mainTank->indx;
		m->bullets[i].rotation = mainTank->rotation;
		m->bullets[i].spec = 0;
		if (mainTank->rotation == 'u' || mainTank->rotation == 'd')
			switch (pos) {
			case 'm':
				create_bullet(&m->bullets[i], mainTank->rotation, mainTank->posx, mainTank->posy);
				break;
			case 'l':
				create_bullet(&m->bullets[i], mainTank->rotation, mainTank->posx - 13, mainTank->posy);
				break;
			case 'r':
				create_bullet(&m->bullets[i], mainTank->rotation, mainTank->posx + 15, mainTank->posy);
				break;

			}
		else
			switch (pos) {
			case 'm':
				create_bullet(&m->bullets[i], mainTank->rotation, mainTank->posx, mainTank->posy);
				break;
			case 'l':
				create_bullet(&m->bullets[i], mainTank->rotation, mainTank->posx, mainTank->posy - 13);
				break;
			case 'r':
				create_bullet(&m->bullets[i], mainTank->rotation, mainTank->posx, mainTank->posy + 15);
				break;

			}
	}
	if (p) return 1;
	return 0;
}

void destroy(Tank *b) {
	b->posx = -400;
	b->posy = -400;
	b->active = 0;
}

int bullet_gameover(Tank *t, int p, int q) {
	if (p >= 12 && p <= 13 && q >= 23 && q <= 25) {
		destroy(t);
		printf("kraj igre\n");
		return 1;
	}
	return 0;
}

void bull(GameState *m, int i, int p, int q) {
	if (p < 26 && q < 26 && p >= 0 && q >= 0) {
		if (m->map[p][q] == 'z') {
			m->map[p][q] = 'g';
			destroy(&m->bullets[i]);
		}
		if (m->map[p][q] == 'c') {
			if (m->bullets[i].indx == m->mainTank.indx && m->mainTank.lvl == 3) {
				m->map[p][q] = 'g';
			}
			destroy(&m->bullets[i]);
		}
	}
}



int bullet_tank(Tank *b, Tank *t) {
	if (tank_inter(b->posx + 7, b->posy, t)) {
		if (b->indx == t->indx) {
			destroy(b);
			return 1;
		}
		else {
			destroy(b);
			destroy(t);
			return 0;
		}
	}
	if (tank_inter(b->posx + 20, b->posy, t)) {
		if (b->indx == t->indx) {
			destroy(b);
			return 1;
		}
		else {
			destroy(b);
			destroy(t);
			return 0;
		}
	}
	if (tank_inter(b->posx + num / 2, b->posy, t)) {
		if (b->indx == t->indx) {
			destroy(b);
			return 1;
		}
		else {
			destroy(b);
			destroy(t);
			return 0;
		}
	}
	if (tank_inter(b->posx, b->posy + 7, t)) {
		if (b->indx == t->indx) {
			destroy(b);
			return 1;
		}
		else {
			destroy(b);
			destroy(t);
			return 0;
		}
	}
	if (tank_inter(b->posx + 7, b->posy + 20, t)) {
		if (b->indx == t->indx) {
			destroy(b);
			return 1;
		}
		else {
			destroy(b);
			destroy(t);
			return 0;
		}
	}
	if (tank_inter(b->posx + 7, b->posy + num / 2, t)) {
		if (b->indx == t->indx) {
			destroy(b);
			return 1;
		}
		else {
			destroy(b);
			destroy(t);
			return 0;
		}
	}
	return 1;
}

int bullet_inter(GameState *m, int i) {
	int p, q;
	switch (m->bullets[i].rotation)
	{
	case 'u':
		p = (m->bullets[i].posx + num / 2) / num;
		q = m->bullets[i].posy / num;
		bull(m, i, p, q);
		p = (m->bullets[i].posx + 20) / num;
		q = m->bullets[i].posy / num;
		bull(m, i, p, q);
		p = (m->bullets[i].posx + 7) / num;
		q = m->bullets[i].posy / num;
		bull(m, i, p, q);
		if (bullet_gameover(&m->bullets[i], p, q)) return 10;
		break;
	case 'd':
		p = (m->bullets[i].posx + num / 2) / num;
		q = (m->bullets[i].posy + num - 10) / num;
		bull(m, i, p, q);
		p = (m->bullets[i].posx + 20) / num;
		q = (m->bullets[i].posy + num - 10) / num;
		bull(m, i, p, q);
		p = (m->bullets[i].posx + 7) / num;
		q = (m->bullets[i].posy + num - 10) / num;
		bull(m, i, p, q);
		if (bullet_gameover(&m->bullets[i], p, q)) return 10;
		break;

	case 'l':
		p = m->bullets[i].posx / num;
		q = (m->bullets[i].posy + num / 2) / num;
		bull(m, i, p, q);
		p = m->bullets[i].posx / num;
		q = (m->bullets[i].posy + 20) / num;
		bull(m, i, p, q);
		p = m->bullets[i].posx / num;
		q = (m->bullets[i].posy + 7) / num;
		bull(m, i, p, q);
		if (bullet_gameover(&m->bullets[i], p, q)) return 10;
		break;
	case 'r':
		p = (m->bullets[i].posx + num - 10) / num;
		q = (m->bullets[i].posy + num / 2) / num;
		bull(m, i, p, q);
		p = (m->bullets[i].posx + num - 10) / num;
		q = (m->bullets[i].posy + 20) / num;
		bull(m, i, p, q);
		p = (m->bullets[i].posx + num - 10) / num;
		q = (m->bullets[i].posy + 7) / num;
		bull(m, i, p, q);
		if (bullet_gameover(&m->bullets[i], p, q)) return 10;
		break;
	}
	return 0;
}


int tank_bonus(Tank *t, bonus *b) {
	if (tank_inter(b->posx, b->posy, t)) return 1;
	if (tank_inter(b->posx + 2 * num, b->posy, t)) return 1;
	if (tank_inter(b->posx, b->posy + 2 * num, t)) return 1;
	if (tank_inter(b->posx + 2 * num, b->posy + 2 * num, t)) return 1;
	return 0;
}

void do_bomb(GameState *m) {
	m->freez_state = 0;
	m->numberOfBots = 0;
	for (int j = 0; j < MAX; j++) {
		if (m->bots[j].active) {
			destroy(&m->bots[j]);
			m->kills++;
		}
		if (m->bonuses[j].active) m->bonuses[j].active = 0;
	}
}

void do_srce(GameState *m) {
	m->mainTank.life++;
}

void do_star(GameState *m) {
	if (m->mainTank.lvl < 3)
		m->mainTank.lvl++;
	if (m->mainTank.lvl > 0) {
		main_tank_speed = 7;
	}
}

void do_freez(GameState *m) {
	m->freez_state = 1;
	for (int i = 0; i < MAX; i++)
		if (m->bots[i].active)
			m->bots[i].freez += freez_period;
}


void do_move_tank_main(GameState *m, Tank *t, char dir, int move) {
	if (!t->active) return;
	if (dir == 'p') return;
	if (move) printf("%d\n", move);
	if (t->rotation != dir && dir != 'n' && dir != 's' && dir != 'm') t->rotation = dir;
	else if (dir == 's' && t->last_shot == 0) {
		if (t->lvl != 2)
			new_bullet(m, t, 'm');
		else {
			new_bullet(m, t, 'l');
			new_bullet(m, t, 'r');
		}
	}
	else {
		if (t->last_shot != 0) {
			t->last_shot--;
		}
		int nx = t->posx, ny = t->posy;
		switch (dir) {
		case 'u':
			ny -= move;
			break;
		case 'd':
			ny += move;
			break;
		case 'l':
			nx -= move;
			break;
		case 'r':
			nx += move;
		}
		t->posx = nx;
		t->posy = ny;
	}

	for (int i = 0; i < MAX; i++) {
		if (m->bonuses[i].active) {
			if (tank_bonus(t, &m->bonuses[i])) {
				m->bonuses[i].active = 0;
				m->numberOfBonuses--;
				switch (m->bonuses[i].type)
				{
					case 'b':
						do_bomb(m);
						break;
					case 's':
						do_srce(m);
						break;
					case 'z':
						do_star(m);
						break;
					case 'f':
						do_freez(m);
						break;
				}
			}
		}
	}

}
void do_move_tank(GameState *m, Tank *t, char dir, int move) {
	if (!t->freez) {
		m->freez_state = 0;
		if (!t->active) return;
		if (t->rotation != dir && dir != 'n' && dir != 's' && dir != 'm') t->rotation = dir;
		else if (dir == 's' && t->last_shot == 0) {
			new_bullet(m, t, 'm');
		}
		else {
			if (t->last_shot != 0) {
				t->last_shot--;
			}
			int nx = t->posx, ny = t->posy;
			switch (dir) {
			case 'u':
				ny -= move;
				break;
			case 'd':
				ny += move;
				break;
			case 'l':
				nx -= move;
				break;
			case 'r':
				nx += move;
			}
			t->posx = nx;
			t->posy = ny;
		}
	}
	else
		t->freez--;
}
void createScreen(GameState *game) {
	SDL_SetRenderDrawColor(game->renderer, 4, 0, 0, 255);
	SDL_RenderClear(game->renderer);
	doWord(game, "LEVEL", 100, 150, 600, 200);
	char str[5];
	sprintf(str, "%d", game->nivo);
	doWord(game, str, 350, 400, 100, 200);
	SDL_RenderPresent(game->renderer);
	SDL_Delay(3000);
}

void initgame(GameState *gamestate) {

	struktura citanje;

	FILE *ptr;
	char ime[15];
	createScreen(gamestate);
	switch (gamestate->nivo)
	{
	case 1:
		strcpy(ime, "nivo1.bin");
		break;
	case 2:
		strcpy(ime, "nivo2.bin");
		break;
	case 3:
		strcpy(ime, "nivo3.bin");
		break;
	case 4:
		strcpy(ime, "nivo4.bin");
		break;
	case 5:
		strcpy(ime, "nivo5.bin");
		break;
	case 6:
		strcpy(ime, "nivo6.bin");
		break;
	case 7:
		strcpy(ime, "nivo7.bin");
		break;
	case 8:
		strcpy(ime, "nivo8.bin");
		break;
	case 9:
		strcpy(ime, "nivo9.bin");
		break;
	case 10:
		strcpy(ime, "nivo10.bin");
		break;
	}
	if ((ptr = fopen(ime, "rb")) == NULL) {
		printf("Error!");
		exit(1);
	}
	for (int i = 0; i < DIM; i++)
		fread(&citanje, sizeof(struktura), 1, ptr);
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) gamestate->map[i][j] = citanje.map[j][i];
		putchar('\n');
	}
	fclose(ptr);


	for (int i = 0; i < MAX_BULLETS; i++) {
		gamestate->bullets[i].active = 0;
	};
	for (int i = 0; i < MAX; i++) {
		gamestate->bots[i].active = 0;
	};
	gamestate->kills = 0;
	gamestate->freez_state = 0;
	gamestate->mainTank.life = 4;
	gamestate->mainTank.posx = 370;
	gamestate->mainTank.posy = 600;
	gamestate->mainTank.rotation = 'u';
	gamestate->mainTank.last_shot = 0;
	gamestate->mainTank.indx = -1;
	gamestate->mainTank.lvl = 0;
	main_tank_speed = 5;
	fire_rate_bot = 40;
	fire_rate_main = 40;

	for (int i = 0; i < MAX; i++) {
		gamestate->bots[i].last_shot = 0;
	}

	gamestate->numberOfBots = 0;
	gamestate->numberOfBullets = 1;
	for (int i = 0; i < MAX; i++) {
		gamestate->bonuses[i].active = 0;
	}
	gamestate->numberOfBonuses = 0;



}

void keypress(char *m) {
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				m[0] = 'u';
				break;
			case SDLK_DOWN:
				m[1] = 'd';
				break;
			case SDLK_LEFT:
				m[2] = 'l';
				break;
			case SDLK_RIGHT:
				m[3] = 'r';
				break;
			case SDLK_SPACE:
				m[4] = 's';
				break;
			case SDLK_p:
				if (m[6] == 'o')
					m[6] = 'p';
				else
					m[6] = 'o';
				break;
			default:
				m[5] = 'n';
				break;
			}
		}
		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				m[0] = 'p';
				break;
			case SDLK_DOWN:
				m[1] = 'p';
				break;
			case SDLK_LEFT:
				m[2] = 'p';
				break;
			case SDLK_RIGHT:
				m[3] = 'p';
				break;
			case SDLK_SPACE:
				m[4] = 'p';
				break;
			default:
				m[5] = 'p';
				break;
			}
		}
	}
	return 'n';
}


char move_bot(Tank *bot, Tank bots[], GameState *game)
{
	if (bot->active==1)
	{
	/*if(bot->tezina==4)
	{
		if(bot->posy<=388)
		{
			char d;
			int r = rand();
			r = r % 10;
			if (walls(game, bot, bot->rotation, 1) == 0)
			{

				r = rand();

				r = r % 10;

				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{

						if (bot->posx <= game->mainTank.posx)
						{
							bot->rotation = 'r';

							return 'r';
						}
						else
						{
							bot->rotation = 'l';

							return 'l';
						}
					}
					else
					{
						if (bot->posy <= game->mainTank.posy) {
							bot->rotation = 'd';

							return 'd';
						}
						else
						{
							bot->rotation = 'u';

							return 'u';
						}
					}
				}
				else
				{
					char c4;
					int k = 0;
					while (k == 0) {
						r = rand();
						r = r % 4;

						switch (r)
						{
						case 1: bot->rotation = 'u'; c4 = 'u'; break;

						case 2:; bot->rotation = 'd'; c4 = 'd'; break;
						case 3:bot->rotation = 'l'; c4 = 'l'; break;
						case 0: bot->rotation = 'r'; c4 = 'r'; break;

						}

						if (valid_move(&game, &bot, c4) != 0)
						{

							k = 1;
						}

					}

					return c4;
				}
			}
			if (bounds(bot, bot->rotation, 1) == 0)
			{
				r = rand();
				r = r % 10;
				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{

						if (bot->posx <= game->mainTank.posx)
						{
							bot->rotation = 'r';

							return 'r';
						}
						else
						{
							bot->rotation = 'l';

							return 'l';
						}
					}
					else
					{
						char c4;
						int k = 0;
						while (k == 0) {
							r = rand();
							r = r % 4;

							switch (r)
							{
							case 1: bot->rotation = 'u'; c4 = 'u'; break;

							case 2:; bot->rotation = 'd'; c4 = 'd'; break;
							case 3:bot->rotation = 'l'; c4 = 'l'; break;
							case 0: bot->rotation = 'r'; c4 = 'r'; break;

							}

							if (valid_move(&game, &bot, c4) != 0)
							{

								k = 1;
							}

						}

						return c4;
					}
				}
			}
			for (int i = 0; i < MAX; i++) {

				if (bots[i].active == 1) {

					if (tank_tank(bot, &bots[i], bot->rotation, 1) == 0) {

						r = rand();
						r = r % 10;
						if (r < 8)
						{

							if ((bot->rotation == 'd') || (bot->rotation == 'u'))
							{

								if (bot->posx <= game->mainTank.posx)
								{
									bot->rotation = 'r';

									return 'r';
								}
								else
								{
									bot->rotation = 'l';

									return 'l';
								}
							}
							else
							{
								char c4;
								int k = 0;
								while (k == 0) {
									r = rand();
									r = r % 4;

									switch (r)
									{
									case 1: bot->rotation = 'u'; c4 = 'u'; break;

									case 2:; bot->rotation = 'd'; c4 = 'd'; break;
									case 3:bot->rotation = 'l'; c4 = 'l'; break;
									case 0: bot->rotation = 'r'; c4 = 'r'; break;

									}

									if (valid_move(&game, &bot, c4) != 0)
									{

										k = 1;
									}

								}

								return c4;

							}
						}
					}

				}
				if (tank_tank(bot, &game->mainTank, bot->rotation, 1) == 0)
				{


					r = rand();
					r = r % 10;
					if (r < 8)
					{

						if ((bot->rotation == 'd') || (bot->rotation == 'u'))
						{

							if (bot->posx <= game->mainTank.posx)
							{
								bot->rotation = 'r';

								return 'r';
							}
							else
							{
								bot->rotation = 'l';

								return 'l';
							}
						}
						else
						{
							r = rand();
							r = r % 4;
							switch (r)
							{
							case 1: bot->rotation = 'u'; return'u';

							case 2:; bot->rotation = 'd'; return 'd';
							case 3:bot->rotation = 'l'; return 'l';
							case 0: bot->rotation = 'r'; return 'r';
							}

						}
					}

				}
			}
			if ((bot->posx == game->mainTank.posx) || (bot->posx == game->mainTank.posx - 1) || (bot->posx == game->mainTank.posx - 3) || (bot->posx == game->mainTank.posx + 3) || (bot->posx == game->mainTank.posx + 1) || (bot->posx == game->mainTank.posx - 2) || (bot->posx == game->mainTank.posx + 2))
			{

				r = rand() % 3;

				if (r == 1) {

					if ((game->mainTank.rotation == 'u') || (game->mainTank.rotation == 'd'))
					{

						if (bot->posy <= game->mainTank.posy)
						{
							if (valid_move(&game, &bot, 'd') != 0)
							{
								bot->rotation = 'd';

								return 'd';
							}
						}
						else
						{
							if (valid_move(&game, &bot, 'u') != 0)
							{
								bot->rotation = 'u';

								return 'u';
							}
						}
					}
					else return bot->rotation;
				}
			}
			if ((bot->posy == game->mainTank.posy) || (bot->posy == game->mainTank.posy - 1) || (bot->posy == game->mainTank.posy - 3) || (bot->posy == game->mainTank.posy + 13) || (bot->posy == game->mainTank.posy + 1) || (bot->posy == game->mainTank.posy - 2) || (bot->posy == game->mainTank.posy + 2))
			{

				r = rand() % 3;

				if (r == 1) {
					if ((game->mainTank.rotation == 'r') || (game->mainTank.rotation == 'l'))
					{
						if (bot->posx <= game->mainTank.posx)
						{
							if (valid_move(&game, &bot, 'r') != 0)
							{
								bot->rotation = 'r';

								return 'r';
							}
						}
						else
						{
							if (valid_move(&game, &bot, 'l') != 0)
							{
								bot->rotation = 'l';

								return 'l';
							}
						}
					}
				}
				else return bot->rotation;
			}

			
		}
		else
		{

			char d;
			int r = rand();
			r = r % 10;
			if (walls(game, bot, bot->rotation, 1) == 0)
			{

				r = rand();

				r = r % 10;

				if (r < 9)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{

						if (bot->posx <= 388)
						{
							bot->rotation = 'r';

							return 'r';
						}
						else
						{
							bot->rotation = 'l';

							return 'l';
						}
					}
					else
					{

						bot->rotation = 'd';

						return 'd';
					}
				}
				else
				{

					char c4;
					int k = 0;
					while (k == 0) {
						r = rand();
						r = r % 4;

						switch (r)
						{
						case 1: bot->rotation = 'u'; c4 = 'u'; break;

						case 2:; bot->rotation = 'd'; c4 = 'd'; break;
						case 3:bot->rotation = 'l'; c4 = 'l'; break;
						case 0: bot->rotation = 'r'; c4 = 'r'; break;

						}

						if (valid_move(&game, &bot, c4) != 0)
						{

							k = 1;
						}

					}

					return c4;
				}
			}
			if (bounds(bot, bot->rotation, 1) == 0)
			{
				r = rand();
				r = r % 10;
				if (r < 9)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{
						if (bot->posx <= 380)
						{
							bot->rotation = 'r';
							return 'r';
						}
						else
						{
							bot->rotation = 'l';
							return 'l';
						}
					}
					else
					{


						bot->rotation = 'd';
						return 'd';
					}
				}
				else
				{

					char c4;
					int k = 0;
					while (k == 0) {
						r = rand();
						r = r % 4;

						switch (r)
						{
						case 1: bot->rotation = 'u'; c4 = 'u'; break;

						case 2:; bot->rotation = 'd'; c4 = 'd'; break;
						case 3:bot->rotation = 'l'; c4 = 'l'; break;
						case 0: bot->rotation = 'r'; c4 = 'r'; break;

						}

						if (valid_move(&game, &bot, c4) != 0)
						{

							k = 1;
						}

					}

					return c4;
				}
			}
			for (int i = 0; i < MAX; i++) {

				if (bots[i].active == 1) {

					if (tank_tank(bot, &bots[i], bot->rotation, 1) == 0) {

						r = rand();
						r = r % 10;
						if (r < 9)
						{

							if ((bot->rotation == 'd') || (bot->rotation == 'u'))
							{
								if (bot->posx <= 380)
								{
									bot->rotation = 'r';
									return 'r';
								}
								else
								{
									bot->rotation = 'l';
									return 'l';
								}
							}
							else
							{

								bot->rotation = 'd';
								return 'd';
							}
						}
						else
						{
							char c4;
							int k = 0;
							while (k == 0) {
								r = rand();
								r = r % 4;

								switch (r)
								{
								case 1: bot->rotation = 'u'; c4 = 'u'; break;

								case 2:; bot->rotation = 'd'; c4 = 'd'; break;
								case 3:bot->rotation = 'l'; c4 = 'l'; break;
								case 0: bot->rotation = 'r'; c4 = 'r'; break;

								}

								if (valid_move(&game, &bot, c4) != 0)
								{

									k = 1;
								}

							}

							return c4;

						}
					}
				}

			}
			if (tank_tank(bot, &game->mainTank, bot->rotation, 1) == 0)
			{


				r = rand();
				r = r % 10;
				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{
						if (bot->posx <= 380)
						{
							bot->rotation = 'r';
							return 'r';
						}
						else
						{
							bot->rotation = 'l';
							return 'l';
						}
					}
					else
					{



						bot->rotation = 'd';
						return 'd';
					}
				}
				else
				{
					r = rand();
					r = r % 4;
					switch (r)
					{
					case 1: bot->rotation = 'u'; return'u';

					case 2:; bot->rotation = 'd'; return 'd';
					case 3:bot->rotation = 'l'; return 'l';
					case 0: bot->rotation = 'r'; return 'r';
					}

				}
			}

			if ((bot->posx == game->mainTank.posx) || (bot->posx == game->mainTank.posx - 1) || (bot->posx == game->mainTank.posx - 3) || (bot->posx == game->mainTank.posx + 3) || (bot->posx == game->mainTank.posx + 1) || (bot->posx == game->mainTank.posx - 2) || (bot->posx == game->mainTank.posx + 2))
			{

				r = rand() % 3;

				if (r == 1) {

					if ((game->mainTank.rotation == 'u') || (game->mainTank.rotation == 'd'))
					{

						if (bot->posx <= 388)
						{
							if (valid_move(&game, &bot, 'r') != 0)
							{
								bot->rotation = 'r';

								return 'r';
							}

						}
						else
						{
							if (valid_move(&game, &bot, 'l') != 0)
							{
								bot->rotation = 'l';

								return 'l';
							}
						}
					}
					else return bot->rotation;
				}
			}
			if ((bot->posy == game->mainTank.posy) || (bot->posy == game->mainTank.posy - 1) || (bot->posy == game->mainTank.posy - 3) || (bot->posy == game->mainTank.posy + 13) || (bot->posy == game->mainTank.posy + 1) || (bot->posy == game->mainTank.posy - 2) || (bot->posy == game->mainTank.posy + 2))
			{

				r = rand() % 3;

				if (r == 1) {
					if ((game->mainTank.rotation == 'r') || (game->mainTank.rotation == 'l'))
					{
						if (valid_move(&game, &bot, 'd') != 0)
						{
							bot->rotation = 'd';

							return 'd';
						}
						else if (valid_move(&game, &bot, 'u') != 0) {
							bot->rotation = 'u';

							return 'u';
						}

					}
				}
				else return bot->rotation;
			}
			
		}
		return bot->rotation;
	}*/
      if (bot->tip == 0) {
	if (bot->tezina == 1) {
			char d;
			int r = rand();
			r = r % 10;
			if (walls(game, bot, bot->rotation, 1) == 0)
			{

				r = rand();

				r = r % 10;

				if (r < 7)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{

						if (bot->posx <= 388)
						{
							bot->rotation = 'r';

							return 'r';
						}
						else
						{
							bot->rotation = 'l';

							return 'l';
						}
					}
					else
					{

						bot->rotation = 'd';

						return 'd';
					}
				}
				else
				{
					r = rand();
					r = r % 4;
					switch (r)
					{
					case 0:bot->rotation = 'u'; return 'u';
					case 1:  bot->rotation = 'l'; return'l';

					case 2: bot->rotation = 'r'; return 'r';
					case 3:bot->rotation = 'd'; return 'd';

					}

				}
			}
			if (bounds(bot, bot->rotation, 1) == 0)
			{
				r = rand();
				r = r % 10;
				if (r < 7)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{
						if (bot->posx <= 380)
						{
							bot->rotation = 'r';
							return 'r';
						}
						else
						{
							bot->rotation = 'l';
							return 'l';
						}
					}
					else
					{


						bot->rotation = 'd';
						return 'd';
					}
				}
				else
				{
					r = rand();
					r = r % 4;
					switch (r)
					{
					case 1: bot->rotation = 'u'; return'u';

					case 2:bot->rotation = 'd'; return 'd';
					case 3:bot->rotation = 'l'; return 'l';
					case 0: bot->rotation = 'r'; return 'r';
					}

				}
			}
			for (int i = 0; i < MAX; i++) {

				if (bots[i].active == 1) {

					if (tank_tank(bot, &bots[i], bot->rotation, 1) == 0) {

						r = rand();
						r = r % 10;
						if (r < 8)
						{

							if ((bot->rotation == 'd') || (bot->rotation == 'u'))
							{
								if (bot->posx <= 380)
								{
									bot->rotation = 'r';
									return 'r';
								}
								else
								{
									bot->rotation = 'l';
									return 'l';
								}
							}
							else
							{

								bot->rotation = 'd';
								return 'd';
							}
						}
						else
						{
							r = rand();
							r = r % 4;
							switch (r)
							{
							case 1: bot->rotation = 'u'; return'u';

							case 2: bot->rotation = 'd'; return 'd';
							case 3:bot->rotation = 'l'; return 'l';
							case 0: bot->rotation = 'r'; return 'r';
							}

						}
					}
				}

			}
			if (tank_tank(bot, &game->mainTank, bot->rotation, 1) == 0)
			{


				r = rand();
				r = r % 10;
				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{
						if (bot->posx <= 380)
						{
							bot->rotation = 'r';
							return 'r';
						}
						else
						{
							bot->rotation = 'l';
							return 'l';
						}
					}
					else
					{



						bot->rotation = 'd';
						return 'd';
					}
				}
				else
				{
					r = rand();
					r = r % 4;
					switch (r)
					{
					case 1: bot->rotation = 'u'; return'u';

					case 2: bot->rotation = 'd'; return 'd';
					case 3:bot->rotation = 'l'; return 'l';
					case 0: bot->rotation = 'r'; return 'r';
					}

				}
			}
			return bot->rotation;

		}
	if (bot->tezina==2)
		{
			char d;
			int r = rand();
			r = r % 10;
			if (walls(game, bot, bot->rotation, 1) == 0)
			{

				r = rand();

				r = r % 10;

				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{

						if (bot->posx <= 388)
						{
							bot->rotation = 'r';

							return 'r';
						}
						else
						{
							bot->rotation = 'l';

							return 'l';
						}
					}
					else

					{

						bot->rotation = 'd';

						return 'd';
					}
				}
				else

				{
					char c4;
					int k = 0;
					while (k == 0) {
						r = rand();
						r = r % 4;
						
						switch (r)
						{
						case 1: bot->rotation = 'u'; c4 = 'u'; break;

						case 2:bot->rotation = 'd'; c4 = 'd'; break;
						case 3:bot->rotation = 'l'; c4 = 'l'; break;
						case 0: bot->rotation = 'r'; c4 = 'r'; break;
							
						}
					
						if (valid_move(&game, &bot, c4) !=0)
						{
							k = 1;
						}

					}
					
					return c4;

				}
			}
			if (bounds(bot, bot->rotation, 1) == 0)
			{
				r = rand();
				r = r % 10;
				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{
						if (bot->posx <= 380)
						{
							bot->rotation = 'r';
							return 'r';
						}
						else
						{
							bot->rotation = 'l';
							return 'l';
						}
					}
					else
					{


						bot->rotation = 'd';
						return 'd';
					}
				}
				else
				{
					char c4;
					int k = 0;
					while (k == 0) {
						r = rand();
						r = r % 4;

						switch (r)
						{
						case 1: bot->rotation = 'u'; c4 = 'u'; break;

						case 2: bot->rotation = 'd'; c4 = 'd'; break;
						case 3:bot->rotation = 'l'; c4 = 'l'; break;
						case 0: bot->rotation = 'r'; c4 = 'r'; break;

						}

						if (valid_move(&game, &bot, c4) != 0)
						{
						
							k = 1;
						}

					}

					return c4;
				}
			}
			for (int i = 0; i < MAX; i++) {

				if (bots[i].active == 1) {

					if (tank_tank(bot, &bots[i], bot->rotation, 1) == 0) {

						r = rand();
						r = r % 10;
						if (r < 8)
						{

							if ((bot->rotation == 'd') || (bot->rotation == 'u'))
							{
								if (bot->posx <= 380)
								{
									bot->rotation = 'r';
									return 'r';
								}
								else
								{
									bot->rotation = 'l';
									return 'l';
								}
							}
							else
							{

								bot->rotation = 'd';
								return 'd';
							}
						}
						else
						{
							r = rand();
							r = r % 4;
							switch (r)
							{
							case 1: bot->rotation = 'u'; return'u';

							case 2: bot->rotation = 'd'; return 'd';
							case 3:bot->rotation = 'l'; return 'l';
							case 0: bot->rotation = 'r'; return 'r';
							}

						}
					}
				}

			}
			if (tank_tank(bot, &game->mainTank, bot->rotation, 1) == 0)
			{


				r = rand();
				r = r % 10;
				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{
						if (bot->posx <= 380)
						{
							bot->rotation = 'r';
							return 'r';
						}
						else
						{
							bot->rotation = 'l';
							return 'l';
						}
					}
					else
					{



						bot->rotation = 'd';
						return 'd';
					}
				}
				else
				{
					char c4;
					int k = 0;
					while (k == 0) {
						r = rand();
						r = r % 4;

						switch (r)
						{
						case 1: bot->rotation = 'u'; c4 = 'u'; break;

						case 2: bot->rotation = 'd'; c4 = 'd'; break;
						case 3:bot->rotation = 'l'; c4 = 'l'; break;
						case 0: bot->rotation = 'r'; c4 = 'r'; break;

						}

						if (valid_move(&game, &bot, c4) != 0)
						{
							k = 1;
						}

					}

					return c4;

				}
			}
			return bot->rotation;
		}
	if (bot ->tezina==3)
		{ 
			char d;
			int r = rand();
			r = r % 10;
			if (walls(game, bot, bot->rotation, 1) == 0)
			{

				r = rand();

				r = r % 10;

				if (r < 9)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{

						if (bot->posx <= 388)
						{
							bot->rotation = 'r';

							return 'r';
						}
						else
						{
							bot->rotation = 'l';

							return 'l';
						}
					}
					else
					{

						bot->rotation = 'd';

						return 'd';
					}
				}
				else
				{

					char c4;
					int k = 0;
					while (k == 0) {
						r = rand();
						r = r % 4;

						switch (r)
						{
						case 1: bot->rotation = 'u'; c4 = 'u'; break;

						case 2: bot->rotation = 'd'; c4 = 'd'; break;
						case 3:bot->rotation = 'l'; c4 = 'l'; break;
						case 0: bot->rotation = 'r'; c4 = 'r'; break;

						}

						if (valid_move(&game, &bot, c4) != 0)
						{
						
							k = 1;
						}

					}

					return c4;
				}
			}
			if (bounds(bot, bot->rotation, 1) == 0)
			{
				r = rand();
				r = r % 10;
				if (r < 9)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{
						if (bot->posx <= 380)
						{
							bot->rotation = 'r';
							return 'r';
						}
						else
						{
							bot->rotation = 'l';
							return 'l';
						}
					}
					else
					{


						bot->rotation = 'd';
						return 'd';
					}
				}
				else
				{
					int c4;
					
					int k = 0;
					while (k == 0) {
						r = rand();
						r = r % 4;

						switch (r)
						{
						case 1: bot->rotation = 'u'; c4 = 'u'; break;

						case 2: bot->rotation = 'd'; c4 = 'd'; break;
						case 3:bot->rotation = 'l'; c4 = 'l'; break;
						case 0: bot->rotation = 'r'; c4 = 'r'; break;

						}

						if (valid_move(&game, &bot, c4) != 0)
						{
					
							k = 1;
						}

					}

					return c4;
				}
			}
			for (int i = 0; i < MAX; i++) {

				if (bots[i].active == 1) {

					if (tank_tank(bot, &bots[i], bot->rotation, 1) == 0) {

						r = rand();
						r = r % 10;
						if (r < 9)
						{

							if ((bot->rotation == 'd') || (bot->rotation == 'u'))
							{
								if (bot->posx <= 380)
								{
									bot->rotation = 'r';
									return 'r';
								}
								else
								{
									bot->rotation = 'l';
									return 'l';
								}
							}
							else
							{

								bot->rotation = 'd';
								return 'd';
							}
						}
						else
						{
							char c4;
							int k = 0;
							while (k == 0) {
								r = rand();
								r = r % 4;

								switch (r)
								{
								case 1: bot->rotation = 'u'; c4 = 'u'; break;

								case 2: bot->rotation = 'd'; c4 = 'd'; break;
								case 3:bot->rotation = 'l'; c4 = 'l'; break;
								case 0: bot->rotation = 'r'; c4 = 'r'; break;

								}

								if (valid_move(&game, &bot, c4) != 0)
								{
									
									k = 1;
								}

							}

							return c4;

						}
					}
				}

			}
			if (tank_tank(bot, &game->mainTank, bot->rotation, 1) == 0)
			{


				r = rand();
				r = r % 10;
				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{
						if (bot->posx <= 380)
						{
							bot->rotation = 'r';
							return 'r';
						}
						else
						{
							bot->rotation = 'l';
							return 'l';
						}
					}
					else
					{



						bot->rotation = 'd';
						return 'd';
					}
				}
				else
				{
					r = rand();
					r = r % 4;
					switch (r)
					{
					case 1: bot->rotation = 'u'; return'u';

					case 2: bot->rotation = 'd'; return 'd';
					case 3:bot->rotation = 'l'; return 'l';
					case 0: bot->rotation = 'r'; return 'r';
					}

				}
			}

			if ((bot->posx == game->mainTank.posx) || (bot->posx == game->mainTank.posx - 1) || (bot->posx == game->mainTank.posx - 3) || (bot->posx == game->mainTank.posx + 3) || (bot->posx == game->mainTank.posx + 1) || (bot->posx == game->mainTank.posx - 2) || (bot->posx == game->mainTank.posx + 2))
			{

				r = rand() % 3;

				if (r == 1) {

					if ((game->mainTank.rotation == 'u') || (game->mainTank.rotation == 'd'))
					{

						if (bot->posx <= 388)
						{
							if (valid_move(&game,&bot, 'r') != 0)
							{
								bot->rotation = 'r';

								return 'r';
							}
						
						}
						else
						{
							if (valid_move(&game, &bot, 'l') != 0)
							{
								bot->rotation = 'l';

								return 'l';
							}
						}
					}
					else return bot->rotation;
				}
			}
			if ((bot->posy == game->mainTank.posy) || (bot->posy == game->mainTank.posy - 1) || (bot->posy == game->mainTank.posy - 3) || (bot->posy == game->mainTank.posy + 13) || (bot->posy == game->mainTank.posy + 1) || (bot->posy == game->mainTank.posy - 2) || (bot->posy == game->mainTank.posy + 2))
			{

				r = rand() % 3;

				if (r == 1) {
					if ((game->mainTank.rotation == 'r') || (game->mainTank.rotation == 'l'))
					{
						if (valid_move(&game,&bot,'d')!=0)
						{
							bot->rotation = 'd';

							return 'd';
						}
						else if (valid_move(&game, &bot, 'u') != 0) {
							bot->rotation = 'u';

							return 'u';
						}
					
					}
				}
				else return bot->rotation;
			}
			return bot->rotation;
		}
	}
	else if (bot->tip == 1)
{
if (bot->tezina == 1)
{

	char d;
	int r = rand();
	r = r % 10;
	if (walls(game, bot, bot->rotation, 1) == 0)
	{

		r = rand();

		r = r % 10;

		if (r < 8)
		{

			if ((bot->rotation == 'd') || (bot->rotation == 'u'))
			{

				if (bot->posx <= game->mainTank.posx)
				{
					bot->rotation = 'r';

					return 'r';
				}
				else
				{
					bot->rotation = 'l';

					return 'l';
				}
			}
			else
			{
				if (bot->posy <= game->mainTank.posy) {
					bot->rotation = 'd';

					return 'd';
				}
				else
				{
					bot->rotation = 'u';

					return 'u';
				}
			}
		}
		else
		{
			r = rand();
			r = r % 4;
			switch (r)
			{
			case 0:bot->rotation = 'u'; return 'u';
			case 1:  bot->rotation = 'l'; return'l';

			case 2: bot->rotation = 'r'; return 'r';
			case 3:bot->rotation = 'd'; return 'd';

			}

		}
	}
	if (bounds(bot, bot->rotation, 1) == 0)
	{
		r = rand();
		r = r % 10;
		if (r < 8)
		{

			if ((bot->rotation == 'd') || (bot->rotation == 'u'))
			{

				if (bot->posx <= game->mainTank.posx)
				{
					bot->rotation = 'r';

					return 'r';
				}
				else
				{
					bot->rotation = 'l';

					return 'l';
				}
			}
			else
			{
				r = rand();
				r = r % 4;
				switch (r)
				{
				case 1: bot->rotation = 'u'; return'u';

				case 2: bot->rotation = 'd'; return 'd';
				case 3:bot->rotation = 'l'; return 'l';
				case 0: bot->rotation = 'r'; return 'r';
				}

			}
		}
	}
	for (int i = 0; i < MAX; i++) {

		if (bots[i].active == 1) {

			if (tank_tank(bot, &bots[i], bot->rotation, 1) == 0) {

				r = rand();
				r = r % 10;
				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{

						if (bot->posx <= game->mainTank.posx)
						{
							bot->rotation = 'r';

							return 'r';
						}
						else
						{
							bot->rotation = 'l';

							return 'l';
						}
					}
					else
					{
						r = rand();
						r = r % 4;
						switch (r)
						{
						case 1: bot->rotation = 'u'; return'u';

						case 2: bot->rotation = 'd'; return 'd';
						case 3:bot->rotation = 'l'; return 'l';
						case 0: bot->rotation = 'r'; return 'r';
						}

					}
				}
			}

		}
		if (tank_tank(bot, &game->mainTank, bot->rotation, 1) == 0)
		{


			r = rand();
			r = r % 10;
			if (r < 8)
			{

				if ((bot->rotation == 'd') || (bot->rotation == 'u'))
				{

					if (bot->posx <= game->mainTank.posx)
					{
						bot->rotation = 'r';

						return 'r';
					}
					else
					{
						bot->rotation = 'l';

						return 'l';
					}
				}
				else
				{
					r = rand();
					r = r % 4;
					switch (r)
					{
					case 1: bot->rotation = 'u'; return'u';

					case 2: bot->rotation = 'd'; return 'd';
					case 3:bot->rotation = 'l'; return 'l';
					case 0: bot->rotation = 'r'; return 'r';
					}

				}
			}

		}
	}
	return bot->rotation;
}
if (bot->tezina == 2)
{

	char d;
	int r;
	if (walls(game, bot, bot->rotation, 1) == 0)
	{

		r = rand();

		r = r % 10;

		if (r < 8)
		{
			
			if ((bot->rotation == 'd') || (bot->rotation == 'u'))
			{

				if (bot->posx <= game->mainTank.posx)
				{
					bot->rotation = 'r';

					return 'r';
				}
				else
				{
					bot->rotation = 'l';

					return 'l';
				}
			}
			else
			{
				if (bot->posy <= game->mainTank.posy) {
					bot->rotation = 'd';

					return 'd';
				}
				else
				{
					bot->rotation = 'u';

					return 'u';
				}
			}
		}
		else
		{
			char c4;
			int k = 0;
			while (k == 0) {
				r = rand();
				r = r % 4;

				switch (r)
				{
				case 1: bot->rotation = 'u'; c4 = 'u'; break;

				case 2: bot->rotation = 'd'; c4 = 'd'; break;
				case 3:bot->rotation = 'l'; c4 = 'l'; break;
				case 0: bot->rotation = 'r'; c4 = 'r'; break;

				}

				if (valid_move(&game, &bot, c4) != 0)
				{
				
					k = 1;
				}

			}

			return c4;
		}
	}
	if (bounds(bot, bot->rotation, 1) == 0)
	{
		r = rand();
		r = r % 10;
		if (r < 8)
		{

			if ((bot->rotation == 'd') || (bot->rotation == 'u'))
			{

				if (bot->posx <= game->mainTank.posx)
				{
					bot->rotation = 'r';

					return 'r';
				}
				else
				{
					bot->rotation = 'l';

					return 'l';
				}
			}
			else
			{
				char c4;
				int k = 0;
				while (k == 0) {
					r = rand();
					r = r % 4;

					switch (r)
					{
					case 1: bot->rotation = 'u'; c4 = 'u'; break;

					case 2: bot->rotation = 'd'; c4 = 'd'; break;
					case 3:bot->rotation = 'l'; c4 = 'l'; break;
					case 0: bot->rotation = 'r'; c4 = 'r'; break;

					}

					if (valid_move(&game, &bot, c4) != 0)
					{
					
						k = 1;
					}

				}

				return c4;
			}
		}
	}
	for (int i = 0; i < MAX; i++) {

		if (bots[i].active == 1) {

			if (tank_tank(bot, &bots[i], bot->rotation, 1) == 0) {

				r = rand();
				r = r % 10;
				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{

						if (bot->posx <= game->mainTank.posx)
						{
							bot->rotation = 'r';

							return 'r';
						}
						else
						{
							bot->rotation = 'l';

							return 'l';
						}
					}
					else
					{
						char c4;
						int k = 0;
						while (k == 0) {
							r = rand();
							r = r % 4;

							switch (r)
							{
							case 1: bot->rotation = 'u'; c4 = 'u'; break;

							case 2: bot->rotation = 'd'; c4 = 'd'; break;
							case 3:bot->rotation = 'l'; c4 = 'l'; break;
							case 0: bot->rotation = 'r'; c4 = 'r'; break;

							}

							if (valid_move(&game, &bot, c4) != 0)
							{
							
								k = 1;
							}

						}

						return c4;

					}
				}
			}

		}
		if (tank_tank(bot, &game->mainTank, bot->rotation, 1) == 0)
		{


			r = rand();
			r = r % 10;
			if (r < 8)
			{

				if ((bot->rotation == 'd') || (bot->rotation == 'u'))
				{

					if (bot->posx <= game->mainTank.posx)
					{
						bot->rotation = 'r';

						return 'r';
					}
					else
					{
						bot->rotation = 'l';

						return 'l';
					}
				}
				else
				{
					r = rand();
					r = r % 4;
					switch (r)
					{
					case 1: bot->rotation = 'u'; return'u';

					case 2: bot->rotation = 'd'; return 'd';
					case 3:bot->rotation = 'l'; return 'l';
					case 0: bot->rotation = 'r'; return 'r';
					}

				}
			}

		}
	}
	if ((bot->posx == game->mainTank.posx) || (bot->posx == game->mainTank.posx - 1) || (bot->posx == game->mainTank.posx - 3) || (bot->posx == game->mainTank.posx + 3) || (bot->posx == game->mainTank.posx + 1) || (bot->posx == game->mainTank.posx - 2) || (bot->posx == game->mainTank.posx + 2))
	 {

		r = rand() % 6;

		if (r == 1) {

			if ((game->mainTank.rotation == 'u') || (game->mainTank.rotation == 'd'))
			{

				if (bot->posy <= game->mainTank.posy)
				{
					if (valid_move(&game, &bot, 'd') != 0)
					{
						bot->rotation = 'd';

						return 'd';
					}
				}
				else
				{
					if (valid_move(&game, &bot, 'u') != 0)
					{
						bot->rotation = 'u';

						return 'u';
					}
				}
			}
		
			
			else  if ((game->mainTank.rotation == 'l') || (game->mainTank.rotation == 'r'))
			{
				r = rand() % 2;
				if (r) {
					if (bot->posx <= game->mainTank.posx)
					{
						if (valid_move(&game, &bot, 'r') != 0)
						{
							bot->rotation = 'r';

							return 'r';
						}
					}
					else
					{
						if (valid_move(&game, &bot, 'l') != 0)
						{
							bot->rotation = 'l';

							return 'l';
						}
					}

				}
			}
			
		}
		else return bot->rotation;
	}
	if ((bot->posy == game->mainTank.posy) || (bot->posy == game->mainTank.posy - 1) || (bot->posy == game->mainTank.posy - 3) || (bot->posy == game->mainTank.posy + 13) || (bot->posy == game->mainTank.posy + 1) || (bot->posy == game->mainTank.posy - 2) || (bot->posy == game->mainTank.posy + 2))
	{

		r = rand() % 6;

		if (r == 1) {
			if ((game->mainTank.rotation == 'r') || (game->mainTank.rotation == 'l'))
			{
				if (bot->posx <= game->mainTank.posx)
				{
					if (valid_move(&game, &bot, 'r') != 0)
					{
						bot->rotation = 'r';

						return 'r';
					}
				}
				else
				{
					if (valid_move(&game, &bot, 'l') != 0)
					{
						bot->rotation = 'l';

						return 'l';
					}
				}
			}
			else  if ((game->mainTank.rotation == 'l') || (game->mainTank.rotation == 'r'))
			{
				r = rand() % 2;
				if (r) {
					if (bot->posx <= game->mainTank.posx)
					{
						if (valid_move(&game, &bot, 'r') != 0)
						{
							bot->rotation = 'r';

							return 'r';
						}
					}
					else
					{
						if (valid_move(&game, &bot, 'l') != 0)
						{
							bot->rotation = 'l';

							return 'l';
						}
					}

				}
			}
		}
		
		else return bot->rotation;
	}
	return	bot->rotation;
}
if (bot->tezina == 3)
{
	char d;
	int r = rand();
	r = r % 10;
	if (walls(game, bot, bot->rotation, 1) == 0)
	{

		r = rand();

		r = r % 10;

		if (r < 8)
		{

			if ((bot->rotation == 'd') || (bot->rotation == 'u'))
			{

				if (bot->posx <= game->mainTank.posx)
				{
					bot->rotation = 'r';

					return 'r';
				}
				else
				{
					bot->rotation = 'l';

					return 'l';
				}
			}
			else
			{
				if (bot->posy <= game->mainTank.posy) {
					bot->rotation = 'd';

					return 'd';
				}
				else
				{
					bot->rotation = 'u';

					return 'u';
				}
			}
		}
		else
		{
			char c4;
			int k = 0;
			while (k == 0) {
				r = rand();
				r = r % 4;

				switch (r)
				{
				case 1: bot->rotation = 'u'; c4 = 'u'; break;

				case 2: bot->rotation = 'd'; c4 = 'd'; break;
				case 3:bot->rotation = 'l'; c4 = 'l'; break;
				case 0: bot->rotation = 'r'; c4 = 'r'; break;

				}

				if (valid_move(&game, &bot, c4) != 0)
				{

					k = 1;
				}

			}

			return c4;
		}
	}
	if (bounds(bot, bot->rotation, 1) == 0)
	{
		r = rand();
		r = r % 10;
		if (r < 8)
		{

			if ((bot->rotation == 'd') || (bot->rotation == 'u'))
			{

				if (bot->posx <= game->mainTank.posx)
				{
					bot->rotation = 'r';

					return 'r';
				}
				else
				{
					bot->rotation = 'l';

					return 'l';
				}
			}
			else
			{
				char c4;
				int k = 0;
				while (k == 0) {
					r = rand();
					r = r % 4;

					switch (r)
					{
					case 1: bot->rotation = 'u'; c4 = 'u'; break;

					case 2:; bot->rotation = 'd'; c4 = 'd'; break;
					case 3:bot->rotation = 'l'; c4 = 'l'; break;
					case 0: bot->rotation = 'r'; c4 = 'r'; break;

					}

					if (valid_move(&game, &bot, c4) != 0)
					{

						k = 1;
					}

				}

				return c4;
			}
		}
	}
	for (int i = 0; i < MAX; i++) {

		if (bots[i].active == 1) {

			if (tank_tank(bot, &bots[i], bot->rotation, 1) == 0) {

				r = rand();
				r = r % 10;
				if (r < 8)
				{

					if ((bot->rotation == 'd') || (bot->rotation == 'u'))
					{

						if (bot->posx <= game->mainTank.posx)
						{
							bot->rotation = 'r';

							return 'r';
						}
						else
						{
							bot->rotation = 'l';

							return 'l';
						}
					}
					else
					{
						char c4;
						int k = 0;
						while (k == 0) {
							r = rand();
							r = r % 4;

							switch (r)
							{
							case 1: bot->rotation = 'u'; c4 = 'u'; break;

							case 2: bot->rotation = 'd'; c4 = 'd'; break;
							case 3:bot->rotation = 'l'; c4 = 'l'; break;
							case 0: bot->rotation = 'r'; c4 = 'r'; break;

							}

							if (valid_move(&game, &bot, c4) != 0)
							{

								k = 1;
							}

						}

						return c4;

					}
				}
			}

		}
		if (tank_tank(bot, &game->mainTank, bot->rotation, 1) == 0)
		{


			r = rand();
			r = r % 10;
			if (r < 8)
			{

				if ((bot->rotation == 'd') || (bot->rotation == 'u'))
				{

					if (bot->posx <= game->mainTank.posx)
					{
						bot->rotation = 'r';

						return 'r';
					}
					else
					{
						bot->rotation = 'l';

						return 'l';
					}
				}
				else
				{
					r = rand();
					r = r % 4;
					switch (r)
					{
					case 1: bot->rotation = 'u'; return'u';

					case 2: bot->rotation = 'd'; return 'd';
					case 3:bot->rotation = 'l'; return 'l';
					case 0: bot->rotation = 'r'; return 'r';
					}

				}
			}

		}
	}
	if ((bot->posx == game->mainTank.posx) || (bot->posx == game->mainTank.posx - 1) || (bot->posx == game->mainTank.posx - 3) || (bot->posx == game->mainTank.posx + 3) || (bot->posx == game->mainTank.posx + 1) || (bot->posx == game->mainTank.posx - 2) || (bot->posx == game->mainTank.posx + 2))
	{

		r = rand() % 3;

		if (r == 1) {

			if ((game->mainTank.rotation == 'u') || (game->mainTank.rotation == 'd'))
			{

				if (bot->posy <= game->mainTank.posy)
				{
					if (valid_move(&game, &bot, 'd') != 0)
					{
						bot->rotation = 'd';

						return 'd';
					}
				}
				else
				{
					if (valid_move(&game, &bot, 'u') != 0)
					{
						bot->rotation = 'u';

						return 'u';
					}
				}
			}
			else  if ((game->mainTank.rotation == 'l') || (game->mainTank.rotation == 'r'))
			{
				r = rand() % 2;
				if (r) {
					if (bot->posx <= game->mainTank.posx)
					{
						if (valid_move(&game, &bot, 'r') != 0)
						{
							bot->rotation = 'r';

							return 'r';
						}
					}
					else
					{
						if (valid_move(&game, &bot, 'l') != 0)
						{
							bot->rotation = 'l';

							return 'l';
						}
					}

				}
			}

		}
		else return bot->rotation;
	}
	 if ((bot->posy == game->mainTank.posy) || (bot->posy == game->mainTank.posy - 1) || (bot->posy == game->mainTank.posy - 3) || (bot->posy == game->mainTank.posy + 13) || (bot->posy == game->mainTank.posy + 1) || (bot->posy == game->mainTank.posy - 2) || (bot->posy == game->mainTank.posy + 2))
	{

		r = rand() % 3;

		if (r == 1)
		{
			if ((game->mainTank.rotation == 'r') || (game->mainTank.rotation == 'l'))
			{
				if (bot->posx <= game->mainTank.posx)
				{
					if (valid_move(&game, &bot, 'r') != 0)
					{
						bot->rotation = 'r';

						return 'r';
					}
				}
				else
				{
					if (valid_move(&game, &bot, 'l') != 0)
					{
						bot->rotation = 'l';

						return 'l';
					}
				}
			}
		
		else  if ((game->mainTank.rotation == 'l') || (game->mainTank.rotation == 'r'))
		{
			r = rand() % 2;
			if (r) 
			{
				if (bot->posx <= game->mainTank.posx)
				{
					if (valid_move(&game, &bot, 'r') != 0)
					{
						bot->rotation = 'r';

						return 'r';
					}
				}
				else
				{
					if (valid_move(&game, &bot, 'l') != 0)
					{
						bot->rotation = 'l';

						return 'l';
					}
				}

			}
		}

	}

	return	bot->rotation;
 
}
else return bot->rotation;
}
}

    }
}
int new_Bot(GameState *m) {
	if (m->freez_state) return 1;
	int i = 0;
	for (i = 0; i < MAX; i++) {
		if (!m->bots[i].active) break;
	}
	if (i == MAX) return 0;
	int a = rand() % 2;
	int p = 0, q = 0, s = 0;
	for (int j = 0; j < MAX; j++) {
		if (m->bots[j].active) {
			if (m->bots[j].posx < 100 && m->bots[j].posy < 100)
				p = 1;
			else
				if (m->bots[j].posx > 550 && m->bots[j].posy < 100)
					q = 1;
		}
	}
	if (a) {
		if (!p) {
			m->bots[i].posx = 0;
			m->bots[i].posy = 0;
			s = 1;
		}
		else
			if (!q)
			{
				m->bots[i].posx = 620;
				m->bots[i].posy = 0;
				s = 1;
			}
	}
	else {
		if (!q) {
			m->bots[i].posx = 620;
			m->bots[i].posy = 0;
			s = 1;
		}
		else
			if (!p) {
				m->bots[i].posx = 0;
				m->bots[i].posy = 0;
				s = 1;
			}
	}
	if (s) {
		a = rand() % 10;
		int d = m->gamelvl;
		m->bots[i].active = 1;
		if (a < 2) {
			m->bots[i].botspec = 1;
			m->bots[i].tip = 1;
			m->bots[i].tezina = d + 1;
			m->bots[i].freez = 0;
			m->bots[i].lvl = 0;
			m->bots[i].indx = 1;
		}
		else {
			m->bots[i].botspec = 0;
			m->bots[i].indx = 1;
			a = rand() % 2;
			m->bots[i].tip = a;
			m->bots[i].tezina = d + 1;
			m->bots[i].freez = 0;
			m->bots[i].lvl = 0;
		}
		a = rand() % 4;
		switch (a)
		{
		case 0:
			m->bots[i].rotation = 'd';
			break;
		case 1:
			m->bots[i].rotation = 'u';
			break;
		case 2:
			m->bots[i].rotation = 'l';
			break;
		case 3:
			m->bots[i].rotation = 'r';
			break;

		}
		a = rand() % 10;
		if (a <= 2)
			m->bots[i].spec = 1;
		else 
			m->bots[i].spec = 0;
		if (tank_tank(&m->bots[i], &m->mainTank, m->bots[i].rotation, 1))
			m->numberOfBots++;
		else {
			destroy(&m->bots[i]);
		}
		return 1;
	}
	return 0;
}


int new_bonus(int p, int q, GameState *m) {
	int i = 0;
	for (i = 0; i < MAX; i++) {
		if (!m->bonuses[i].active) break;
	}
	if (i == MAX) return 0;
	m->bonuses[i].active = 1;
	m->bonuses[i].posx = p;
	m->bonuses[i].posy = q;
	m->bonuses[i].blink = blink_period;
	int a = rand() % 4;
	switch (a)
	{
		case 0:
			m->bonuses[i].type = 's';
			break;
		case 1:
			m->bonuses[i].type = 'z';
			break;
		case 2:
			m->bonuses[i].type = 'b';
			break;
		case 3:
			m->bonuses[i].type = 'f';
	}
	m->numberOfBonuses++;
	return 1;
}


// ukoliko do_move vrati 10 onda je metak pogodio pivo i to se smatra krajem igre
int do_move(GameState *m, char dir, int move) {
	
	do_move_tank_main(m, &m->mainTank, dir, move);

	if (dir == 'm') {
		for (int i = 0; i < MAX; i++) {
			if (m->bots[i].active) {
				do_move_tank(m, &m->bots[i], move_bot(&m->bots[i], &m->bots, m), valid_move(m, &m->bots[i], m->bots[i].rotation));
				do_move_tank(m, &m->bots[i], 's', valid_move(m, &m->bots[i], 's'));
			}
		}
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (m->bullets[i].active) {
				switch (m->bullets[i].rotation) {
				case 'u':
					m->bullets[i].posy -= bullet_speed;
					break;
				case 'd':
					m->bullets[i].posy += bullet_speed;
					break;
				case 'l':
					m->bullets[i].posx -= bullet_speed;
					break;
				case 'r':
					m->bullets[i].posx += bullet_speed;
				}
				if (!bounds_bullet(&m->bullets[i], m->bullets[i].rotation, i)) destroy(&m->bullets[i]);

				if (m->bullets[i].active) {
					if (bullet_inter(m, i) == 10) return 10;
				}

				for (int j = 0; j < MAX; j++) {
					if (m->bots[j].active) {
						if (m->bots[j].active) {
							int p = m->bots[j].posx;
							int q = m->bots[j].posy;
							if (!bullet_tank(&m->bullets[i], &m->bots[j])) {
								m->kills++;
								if (m->bots[j].spec)
									if (!new_bonus(p, q, m)) printf("nema mesta za novi bonus\n");
								m->numberOfBots--;
							}
						}
						if (!bullet_tank(&m->bullets[i], &m->mainTank)) {
							m->mainTank.life--;
							if (m->mainTank.life < 0) m->mainTank.life == 0;
							m->mainTank.active = 1;
							m->mainTank.posx = 100;
							m->mainTank.posy = 500;
							m->mainTank.rotation = 'r';
							m->mainTank.last_shot = 0;
							m->mainTank.indx = -1;
						}
					}
				}
			}
		}
		if (!m->numberOfBots)
			m->freez_state = 0;
		if (m->numberOfBots < 4)
			new_Bot(m);
		return 1;
	}
}
/*char move_tenk(Tank *tenk, Tank bots[], GameState *game)
{
	int min;
	int mini;
	char direkcija;
	 min = 700;
	int mini = -1;
	int mind = 2;
	int maxy;
	maxy = 0;
	int raz1, raz2;
	
	for(int i=0;i<MAX;i++)
	{
		if (tenk->posy > maxy) maxy = tenk->posy;

		 raz1 =abs(tenk->posx - bots[i].posx);
		 raz2 = abs(tenk->posy - bots[i].posy);
		 if (raz1 < min) 
		 {
			 min = raz1;
			 mini = i;
			 mind = 1;
		 }
		 if (raz2 < min)
		 {
			 min = raz2;
			 mini = i;
			 mind = 0;
		 }
	}
	if(mind==0)
	{
		if(tenk->posx<bots[mini].posx)
		{
			direkcija = 'r';
		}
		else
		{
			direkcija = 'l';
		}
	}
	else
	{
		if (tenk->posy < maxy) {
			return 'd';
		}
		if (tenk->posy < bots[mini].posy)
		{
			direkcija = 'd';
		}
		else
		{
			direkcija = 'u';
		}
	}
	if (valid_move(&game,&tenk,direkcija)
	{ 
		return direkcija;
	}

	else
	{
		if(mind==0){
			if (tenk->posy < bots[mini].posy)
			{
				direkcija = 'd';
			}
			else
			{
				direkcija = 'u';
			}
			return direkcija;
		}
		else
		{
			if (tenk->posy < bots[mini].posy)
			{
				direkcija = 'd';
			}
			else
			{
				direkcija = 'u';
			}
			return direkcija;
		}
	}
}*/
