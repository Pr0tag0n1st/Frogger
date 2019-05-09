#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
//constants: variables that shouldn't change once the game starts
const float FPS = 60;
const int SCREEN_W = 900;
const int SCREEN_H = 900;
const int BOUNCER_SIZE = 30;
int gridsize = 30;

//enumeration to help you remember what numbers represent which directions
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

//bool collision(int x, int y, int map[30][60], int offset);

int map[30][60] = {
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,	0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,	0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,	0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
	0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
	0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,	0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,
	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,
	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,	0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,
	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
};



int main(){

	int scores[5];
	int highscores[5];
	ifstream scoreread;
	int num;
	scoreread.open("HISCORE.txt");
	bool dead = false;
	for (int i = 0; i < 5; i++) {
		scoreread >> num;
		scores[i] = num;
		cout << scores[i] << endl;
	}
	scoreread.close();

	int tempscore;
	ofstream scoresave;
	scoresave.open("HISCORE.txt");


	for (int i = 0; i < 30; i++) {
		cout << endl;
		for (int j = 0; j < 60; j++)
			cout << map[i][j];
	}
	int jumptimer = 0;
	int score = 0;
	int lives = 3;
	int offset = 0;
	int speed = 1;
	//set up allegro
	al_init();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_init_primitives_addon();
	//set up game screen, event queue, and timer
	ALLEGRO_BITMAP *road = al_load_bitmap("Road.png");
	ALLEGRO_BITMAP *grass = al_load_bitmap("Grass.png");
	ALLEGRO_BITMAP *frog = al_load_bitmap("FROG.png");
	ALLEGRO_BITMAP *froglife = al_load_bitmap("FROGLIFE.png");
	ALLEGRO_BITMAP *trees = al_load_bitmap("Trees.png");
	ALLEGRO_BITMAP *green = al_load_bitmap("greencar.png");
	ALLEGRO_BITMAP *blue = al_load_bitmap("bluecar.png");
	ALLEGRO_BITMAP *dino = al_load_bitmap("DinoStudios.jpg");
	ALLEGRO_DISPLAY *display = al_create_display(SCREEN_W, SCREEN_H);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_FONT *typeface = al_create_builtin_font();

	al_start_timer(timer);
	//position of player
	int xPos = SCREEN_W / 2;
	int yPos = SCREEN_H - BOUNCER_SIZE;
	//game variables
	bool key[4] = { false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop

	al_convert_mask_to_alpha(green, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(blue, al_map_rgb(255, 255, 255));
	al_convert_mask_to_alpha(frog, al_map_rgb(0, 0, 0));
	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	dino = al_load_bitmap("DinoStudios.jpg");
	al_draw_bitmap(dino, 0, 0, 0);
	al_flip_display();
	al_rest(0.5);
	for (int i = 255; i > 0; i -= 5) {
		al_draw_tinted_bitmap(dino, al_map_rgb(i, i, i), 0, 0, 0);
		al_flip_display();
		al_rest(0.05);
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_textf(typeface, al_map_rgb(255, 255, 255), 400, 400, 0, "Top 5 Scores:");
	al_rest(0.5);
	al_flip_display();
	for (int i = 0; i < 5; i++) {

		al_draw_textf(typeface, al_map_rgb(255, 255, 255), 400, 450 + i * 50, 0, "%d", scores[i]);
		al_rest(0.25);
		al_flip_display();

	}
	al_rest(1);

	while (!doexit)//game loop!
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {


			//lose
			/*if (collision(xPos, yPos, map, offset) == 1) {
				cout << "dead" << endl;
				xPos = SCREEN_W / 2;
				yPos = SCREEN_H - BOUNCER_SIZE;
			}*/
			if (yPos % (gridsize * 2) == 0) {
				if (map[(yPos / gridsize)][((xPos - offset) / gridsize)+30] == 1) {
					cout << "dead green" << endl;
					lives--;
					xPos = SCREEN_W / 2;
					yPos = SCREEN_H - BOUNCER_SIZE;
				}
			}
			else 
				if (map[(yPos / gridsize)][((xPos + offset) / gridsize)] == 1) {
					cout << "dead blue" << endl;
					lives--;
					xPos = SCREEN_W / 2;
					yPos = SCREEN_H - BOUNCER_SIZE;
				}
			//win
			if (map[(yPos / gridsize)][(xPos) / gridsize] == 2) {
				cout << "You win" << endl;
				xPos = SCREEN_W / 2;
				yPos = SCREEN_H - BOUNCER_SIZE;
				score++;
			}

			


			//map scroll
			if (score < 5)
				speed = score+1;

			offset += speed;
			if (offset > SCREEN_W)
				offset = 0;

			//move algorithm
			jumptimer--;


			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP] && yPos > 0 && jumptimer <= 0) {
				yPos -= 30;
				jumptimer = 10;
			}
			if (key[KEY_DOWN] && yPos < SCREEN_H - BOUNCER_SIZE && jumptimer <= 0) {
				yPos += 30;
				jumptimer = 10;
			}
			if (key[KEY_LEFT] && xPos > 0 && jumptimer <= 0) {
				xPos -= 30;
				jumptimer = 10;
			}
			if (key[KEY_RIGHT] && xPos < SCREEN_W - BOUNCER_SIZE && jumptimer <= 0) {
				xPos += 30;
				jumptimer = 10;
			}
			redraw = true;

			//gameover
			if (lives <= 0)
				break;

			//true victory
			if (score >= 10)
				break;
		}
		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;

			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}
		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			//	(without this things smear)
			al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing
			for (int i = 0; i < 30; i++)
				for (int j = 0; j < 30; j++) {
					al_draw_bitmap(road, (i * gridsize), j * gridsize, 0);
					if (map[j][i] == 2)
						al_draw_bitmap(grass, (i*gridsize), (j*gridsize, 0), 0);
					else if (map[j][i] == 3)
						al_draw_filled_rectangle((i*gridsize), j * gridsize, (i * gridsize) + gridsize, (j * gridsize) + gridsize, al_map_rgb(120, 120, 120));
				}



			for (int i = 0; i < 30; i++) {
				if (i % 2 == 0) {
					for (int j = -30; j < 30; j++)
						if (map[i][j + 30] == 1)//green
							al_draw_bitmap(green, (j*gridsize) + offset, i*gridsize, 0);

				}
				else {
					for (int j = 0; j < 60; j++)
						if (map[i][j] == 1)//blue
							//al_draw_filled_rectangle((j * gridsize) - offset, (i * gridsize), (j * gridsize + gridsize) - offset, (i * gridsize + gridsize), al_map_rgb(80, 80, 200));
							al_draw_bitmap(blue, (j*gridsize) - offset, i*gridsize, 0);
				}
			}


			al_draw_textf(typeface, al_map_rgb(255, 255, 255), gridsize, SCREEN_H - gridsize, 1, "Score: %d", score);
			al_draw_textf(typeface, al_map_rgb(255, 255, 255), gridsize, SCREEN_H - (gridsize / 2), 1, "Lives: ");
			for (int i = lives; i > 0; i--)
				al_draw_bitmap(froglife, gridsize + (i * 15), SCREEN_H - (gridsize / 2), 1);

			al_draw_bitmap(frog, xPos, yPos, 0); //draw the player
			al_flip_display(); //flip everything from memory to gamescreen
		}//end render

	}//end game loop
	//clean up memory
	//game end screen
	score += lives * 3;
	if (lives <= 0) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(typeface, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 3, 1, "GAME OVER");
		al_flip_display();
		al_rest(2.0);
		for (int i = 0; i < 5; i++) {
			if (score > scores[i]) {
				tempscore = scores[i];
				highscores[i] = score;
				score = tempscore;
			}
			else
				highscores[i] = scores[i];
		}

		al_draw_textf(typeface, al_map_rgb(255, 255, 255), 400, 400, 0, "Top 5 Scores:");
		for (int i = 0; i < 5; i++) {
			al_draw_textf(typeface, al_map_rgb(255, 255, 255), 400, 450 + i * 50, 0, "%d", highscores[i]);
			al_rest(0.25);
			al_flip_display();
		}
		al_rest(1);
		al_flip_display();
		for (int i = 0; i < 5; i++) {
			scoresave << highscores[i] << endl;;
		}
	}
	if (score >= 10) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		for (int i = 0; i < gridsize; i++) {
			for (int j = 0; j < gridsize; j++) {
				al_draw_bitmap(grass, (i*gridsize), (j*gridsize), 0);
			}
		}
		al_draw_filled_rectangle(SCREEN_W / 4, SCREEN_H / 4, (3 * SCREEN_W) / 4, (3 * SCREEN_H) / 4, al_map_rgb(100, 200, 100));
		al_draw_text(typeface, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 3, 1, "YOU WIN");
		al_flip_display();
		al_rest(2.0);
		for (int i = 0; i < 5; i++) {
			if (score > scores[i]) {
				tempscore = scores[i];
				highscores[i] = score;
				score = tempscore;
			}
			else
				highscores[i] = scores[i];
		}

		al_draw_textf(typeface, al_map_rgb(255, 255, 255), 400, 400, 0, "Top 5 Scores:");
		for (int i = 0; i < 5; i++) {
			al_draw_textf(typeface, al_map_rgb(255, 255, 255), 400, 450 + i * 50, 0, "%d", highscores[i]);
			al_rest(0.25);
			al_flip_display();
		}
		al_rest(1);
		al_flip_display();
		for (int i = 0; i < 5; i++) {
			scoresave << highscores[i] << endl;;
		}
	}
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}

//bool collision(int x, int y, int map[30][60], int offset) {
//	if ((map[((y + (BOUNCER_SIZE / 2)) / gridsize)][((x + offset) / gridsize)] == 1) ||
//		(map[((y + (BOUNCER_SIZE / 2)) / gridsize)][((x + gridsize + offset) / gridsize)] == 1) ||
//		(map[((y + (BOUNCER_SIZE / 2)) / gridsize)][((x - offset) / gridsize)] == 1) ||
//		(map[((y + (BOUNCER_SIZE / 2)) / gridsize)][((x + gridsize - offset) / gridsize)] == 1))
//	{
//		cout << "hit" << endl;
//		return 1;
//	}
//
//	else
//		return 0;
//			}

//			}
//}