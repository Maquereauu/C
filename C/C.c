// C.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>
#include <math.h>
#include <SDL.h>
#include <SDL_mixer.h>
const int WIDTH = 800;
const int HEIGHT = 800;
const int POSITION_X = 100;
const int POSITION_Y = 100;

typedef struct Case {
	int isBomb;
	int bombsNearby;
	int isFlaged;
	int isClicked;
} Case;
void clrscr();
void Init();
void ShowGrid();
int getRandom();
int verifWin();
void revealNear();
void revealNearSDL();
void Game();
void PlayAgain();
void SDL_Render();
void GameSDL();
void MenuSDL();


int main()
{
	int choice;
	int* play = 1;
	puts("Terminal ou Graphique?");
	if (scanf_s(" %d", &choice)) {
		if (choice == 1) {
			SDL_Render(&play);
		}
		else {
			while (play) {
				Game(&play);
			}
		}
	}
else {
	printf("Merci de rentrer une valeur valide");
	}
}

void SDL_Render(int* play) {
	int* InMenu = 1;
	int* difficulty;
	while (*play) {
		if (InMenu == 1) {
			MenuSDL(play,&difficulty,&InMenu);
		}
		else {
			GameSDL(play,&difficulty,&InMenu);
		}
	}
}

void MenuSDL(int* play , int* difficulty, int* InMenu) {
	int close = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { printf("%s\n", SDL_GetError()); exit(-1); }
	IMG_Init(IMG_INIT_JPG);
	int init2 = Mix_Init(0);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_Music* music = Mix_LoadMUS("BeePatrol.wav");
	Mix_Chunk* sound = Mix_LoadWAV("BeePatrol.wav");
	Mix_PlayMusic(music, -1);
	SDL_Window* window;
	window = SDL_CreateWindow("Menu", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Rect back;
	back.x = 100;
	back.y = 50;
	back.h = 600;
	back.w = 600;
	SDL_Rect difficulty1;
	difficulty1.x = 125;
	difficulty1.y = 250;
	difficulty1.h = 100;
	difficulty1.w = 50;
	SDL_Rect difficulty2;
	difficulty2.x = 225;
	difficulty2.y = 250;
	difficulty2.h = 100;
	difficulty2.w = 50;
	SDL_Rect difficulty3;
	difficulty3.x = 325;
	difficulty3.y = 250;
	difficulty3.h = 100;
	difficulty3.w = 50;
	SDL_Rect difficulty4;
	difficulty4.x = 425;
	difficulty4.y = 250;
	difficulty4.h = 100;
	difficulty4.w = 50;
	SDL_Rect difficulty5;
	difficulty5.x = 525;
	difficulty5.y = 250;
	difficulty5.h = 100;
	difficulty5.w = 50;
	SDL_Rect difficulty6;
	difficulty6.x = 625;
	difficulty6.y = 250;
	difficulty6.h = 100;
	difficulty6.w = 50;
	const char* path[] =
	{
		"1.png",
		"2.png",
		"3.png",
		"4.png",
		"5.png",
		"6.png",
	};
	int texture_length = sizeof(path) / sizeof(path[0]);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_Texture*** textures = (SDL_Texture***)malloc(sizeof(SDL_Texture**) * texture_length);
	for (int i = 0; i < texture_length; ++i)
	{
		textures[i] = (SDL_Texture**)malloc(sizeof(SDL_Texture*));
	}

	for (int i = 0; i < texture_length; ++i)
	{
		SDL_Surface* image = IMG_Load(path[i]);
		textures[i] = SDL_CreateTextureFromSurface(renderer, image);
	}
	SDL_Event event;
	Mix_PlayChannel(-1, sound, -1);
	while (1) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { close = 1;*play = 0; break; }
			if (SDL_MOUSEBUTTONDOWN == event.type) {
				if (SDL_BUTTON_LEFT == event.button.button) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					if (x <= 175 && x >= 125 && y <= 350 && y >= 250) {
						*difficulty = 1;
						*InMenu = 0;
						close = 1;
						break;
					}
					else if (x <= 275 && x >= 225 && y <= 350 && y >= 250) {
						*difficulty = 2;
						*InMenu = 0;
						close = 1;
						break;
					}
					else if (x <= 375 && x >= 325 && y <= 350 && y >= 250) {
						*difficulty = 3;
						*InMenu = 0;
						close = 1;
						break;
					}
					else if (x <= 475 && x >= 425 && y <= 350 && y >= 250) {
						*difficulty = 4;
						*InMenu = 0;
						close = 1;
						break;
					}
					else if (x <= 575 && x >= 525 && y <= 350 && y >= 250) {
						*difficulty = 5;
						*InMenu = 0;
						close = 1;
						break;
					}
					else if (x <= 675 && x >= 625 && y <= 350 && y >= 250) {
						*difficulty = 6;
						*InMenu = 0;
						close = 1;
						break;
					}
				}
			}
		}
		SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer, textures[0], NULL, &difficulty1);
		SDL_RenderCopy(renderer, textures[1], NULL, &difficulty2);
		SDL_RenderCopy(renderer, textures[2], NULL, &difficulty3);
		SDL_RenderCopy(renderer, textures[3], NULL, &difficulty4);
		SDL_RenderCopy(renderer, textures[4], NULL, &difficulty5);
		SDL_RenderCopy(renderer, textures[5], NULL, &difficulty6);
		SDL_RenderPresent(renderer);
	}
		if (close) {
			Mix_FreeMusic(music);
			Mix_CloseAudio();
			SDL_DestroyRenderer(renderer);
			IMG_Quit();
			SDL_DestroyWindow(window);
			SDL_Quit();
		}
}

void GameSDL(int* play , int* difficulty , int* InMenu) {
	int close = 0;
	int* InGame = 1;
	int GameOver = 0;
	srand(time(NULL));
	int length = 10 * *difficulty;
	int i;
	int j;
	Case** T = (Case**)malloc(sizeof(Case*) * length);
	for (int i = 0; i < length; ++i)
	{
		T[i] = (Case*)malloc(sizeof(Case) * length);
	}
	Init(T, *difficulty);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { printf("%s\n", SDL_GetError()); exit(-1); }
	IMG_Init(IMG_INIT_JPG);
	SDL_Window* window;
	window = SDL_CreateWindow("Démineur", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	//BACK_Damier
	SDL_Rect back;
	back.x = 100;
	back.y = 50;
	back.h = 600;
	back.w = 600;
	SDL_Rect menu;
	menu.x = 50;
	menu.y = 25;
	menu.h = 700;
	menu.w = 700;
	SDL_Rect playAgainRect;
	playAgainRect.x = 300;
	playAgainRect.y = 450;
	playAgainRect.h = 100;
	playAgainRect.w = 200;
	SDL_Rect** case_damier = (SDL_Rect**)malloc(sizeof(SDL_Rect*) * length);
	for (int i = 0; i < length; ++i)
	{
		case_damier[i] = (SDL_Rect*)malloc(sizeof(SDL_Rect) * length);
	}
	//DAMIER
	for (i = 0; i < length; i++) {
		for (j = 0; j < length; j++) {
			case_damier[i][j].x = 100 + j * (60 / *difficulty)+1;
			case_damier[i][j].y = 50 + i * (60 / *difficulty)+1;
			case_damier[i][j].h = 58/ *difficulty;
			case_damier[i][j].w = 58/ *difficulty;
		}
	}

	const char* path[] =
	{
		"0.png",
		"Bomb.png",
		"1.png",
		"2.png",
		"3.png",
		"4.png",
		"5.png",
		"6.png",
		"7.png",
		"8.png",
		"flag.png",
		"emptycase.png",
		"playAgain.png"
	};

	int texture_length = sizeof(path) / sizeof(path[0]);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_Texture** textures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * texture_length);
	for (int i = 0; i < texture_length; ++i)
	{
		SDL_Surface* image = IMG_Load(path[i]);
		textures[i] = SDL_CreateTextureFromSurface(renderer, image);
	}
	SDL_Event event;
	while (1) {
		if (GameOver == 1) {
			for (i = 0; i < length; i++) {
				for (j = 0; j < length; j++) {
					T[i][j].isClicked = 1;
				}
			}
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) { close = 1; break; }
				if (SDL_MOUSEBUTTONDOWN == event.type) {
					if (SDL_BUTTON_LEFT == event.button.button) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (x >= 300 && x <= 500 && y >= 450 && y <= 550) {
							for (int i = 0; i < length; ++i) {
								free(T[i]);
								free(case_damier[i]);
							}
							free(T);
							free(case_damier);
							SDL_DestroyRenderer(renderer);
							IMG_Quit();
							SDL_DestroyWindow(window);
							SDL_Quit();
							*InMenu = 1;
							break;

						}
					}
				}
			}
		}
		else {
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) { close = 1; break; }
				if (SDL_MOUSEBUTTONDOWN == event.type) {
					if (SDL_BUTTON_LEFT == event.button.button) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						x = (x - 100) / (60 / *difficulty);
						y = (y - 50) / (60 / *difficulty);
						if (x < length && y < length && x >= 0 && y >= 0) {
							if (T[y][x].isFlaged != 1) {
								T[y][x].isClicked = 1;
								if (T[y][x].bombsNearby == 0) {
									revealNear(T, y, x, *difficulty);
								}
							}
						}
					}
					else if (SDL_BUTTON_RIGHT == event.button.button) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						x = (x - 100) / (60 / *difficulty);
						y = (y - 50) / (60 / *difficulty);
						if (x < length && y < length && x >= 0 && y >= 0) {
							if (T[y][x].isFlaged == 0) {
								T[y][x].isFlaged = 1;
							}
							else {
								T[y][x].isFlaged = 0;
							}
						}
					}
					int verif = verifWin(T, *difficulty);
					if (verif == 1) {
						GameOver = 1;
					}
				}
			}
		}
		//SDL_Renderer
		SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderFillRect(renderer, &back);

		//DAMIER-------------------
		for (i = 0; i < length; i++) {
			for (j = 0; j < length; j++) {
				if (T[i][j].isClicked == 1) {
					if (T[i][j].isBomb == 1) {
						SDL_RenderCopy(renderer, textures[1], NULL, &case_damier[i][j]);
					}
					else if (T[i][j].bombsNearby > 0) {
						switch (T[i][j].bombsNearby) {
						case 1: SDL_RenderCopy(renderer, textures[2], NULL, &case_damier[i][j]); break;
						case 2: SDL_RenderCopy(renderer, textures[3], NULL, &case_damier[i][j]); break;
						case 3: SDL_RenderCopy(renderer, textures[4], NULL, &case_damier[i][j]); break;
						case 4: SDL_RenderCopy(renderer, textures[5], NULL, &case_damier[i][j]); break;
						case 5: SDL_RenderCopy(renderer, textures[6], NULL, &case_damier[i][j]); break;
						case 6: SDL_RenderCopy(renderer, textures[7], NULL, &case_damier[i][j]); break;
						case 7: SDL_RenderCopy(renderer, textures[8], NULL, &case_damier[i][j]); break;
						case 8: SDL_RenderCopy(renderer, textures[9], NULL, &case_damier[i][j]); break;
						}
					}
					else {
						SDL_SetRenderDrawColor(renderer, 185, 185, 185, 255);
						SDL_RenderFillRect(renderer, &case_damier[i][j]);
					}
				}
				else if (T[i][j].isFlaged == 1) {
					SDL_RenderCopy(renderer, textures[10], NULL, &case_damier[i][j]);
				}
				else if (T[i][j].isClicked == 0) {
					SDL_RenderCopy(renderer, textures[11], NULL, &case_damier[i][j]);
				}
			}
		}
		//DAMIER-------------------
		if (GameOver == 1) {
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 150);
			SDL_RenderFillRect(renderer, &menu);
			SDL_RenderCopy(renderer, textures[12], NULL, &playAgainRect);
		}
		SDL_RenderPresent(renderer);
	}
	if (close) {
		for (int i = 0; i < length; ++i) {
			free(T[i]);
			free(case_damier[i]);
		}
		free(textures);
		free(T);
		free(case_damier);
		SDL_DestroyRenderer(renderer);
		IMG_Quit();
		SDL_DestroyWindow(window);
		SDL_Quit();
		*play = 0;
	}
}

void Game(int* play) {
	int difficulty;
	int* InGame = 1;
	puts("Veuillez choisir un mode de difficulte(1-6) ");
	do {
		if (scanf_s(" %d", &difficulty)) {
			if (difficulty <= 0) {
				printf("Merci de renseigner une valeur superieure a 0\n");
			}else if (difficulty > 6) {
				printf("Merci de renseigner une valeur inferieure a 7\n");
			}
			else {
				break;
			}
		}
		else {
			printf("Merci de renseigner un nombre entier \n");
			while(getchar() != '\n');
		}
	} while (1);
	while (getchar() != '\n');
	srand(time(NULL));
	int isError = 0;
	Case** T = (Case**)malloc(sizeof(Case*) * (10 * difficulty));
	for (int i = 0; i < (10 * difficulty); ++i)
	{
		T[i] = (Case*)malloc(sizeof(Case) * (10 * difficulty));
	}
	Init(T, difficulty);
	while (1) {
		ShowGrid(T, difficulty);
		clrscr();
		ShowGrid(T, difficulty);
		if (isError == 1) {
			printf("Merci de renseigner une case non selectionnee !\n\n");
		}
		int verif = verifWin(T, difficulty);
		if (verif == 1) {
			for (int i = 0; i < (10 * difficulty); ++i){
				free(T[i]);
			}
			free(T);
			PlayAgain(play,&InGame);
			if (InGame == 0) {
				break;
			}
	
		}
		int flag = 0;
		int playerchoicex;
		int playerchoicey;
		puts("Voulez-vous decouvrir une case ou bien poser un drapeau?(0/1)");
		while(1){
			if (scanf_s("%d", &flag)) {
				if (flag == 1) {
					while (getchar() != '\n');
					puts("Quelle case voulez vous drapeau-ter? ? :");
					while (1) {
						if (scanf_s("%d/%d", &playerchoicex, &playerchoicey)) {
							if (playerchoicex < difficulty * 10 && playerchoicey < difficulty * 10 && playerchoicex >=0 && playerchoicey>=0) {
								if (T[playerchoicex][playerchoicey].isFlaged != 1) {
									T[playerchoicex][playerchoicey].isFlaged = 1;
								}
								else {
									T[playerchoicex][playerchoicey].isFlaged = 0;
								}
								break;
							}
							else {
								printf("Merci de rentrer des coordonees valides(en nombre entier)\n");
								while (getchar() != '\n');
							}
						}
						else {
							printf("Merci de rentrer des coordonees valides(en nombre entier)\n");
							while (getchar() != '\n');
						}
					}
					break;
				}
				else if(flag==0){
					puts("Quelle case voulez vous decouvrir ? :");
					while (1) {
						if (scanf_s("%d/%d", &playerchoicex, &playerchoicey)) {
							if (playerchoicex < difficulty * 10 && playerchoicey < difficulty * 10 && playerchoicex >=0 && playerchoicey>=0) {
								if (T[playerchoicex][playerchoicey].isClicked != 1) {
									T[playerchoicex][playerchoicey].isClicked = 1;
									isError = 0;
									while (getchar() != '\n');
								}
								else {
									isError = 1;
									while (getchar() != '\n');
								}
								break;
							}
							else {
								printf("Merci de rentrer des coordonees valides(en nombre entier)\n");
								while (getchar() != '\n');
							}
						}
						else {
							printf("Merci de rentrer des coordonees valides(en nombre entier)\n");
							while (getchar() != '\n');
						}
					}
					break;
				}
				else {
					printf("Merci de rentrer 0 pour jouer ou 1 pour poser un drapeau.\n");
					while (getchar() != '\n');
				}
			}
			else {
				printf("Merci de rentrer 0 pour jouer ou 1 pour poser un drapeau.\n");
				while (getchar() != '\n');
			}
		}
	}
}


void Init(Case** T, int difficulty) {
	int x;
	int y;
	int i;
	int j;
	int k;
	int BombCount = 0;
	int bombsnear = 0;
	int debug = 0;
	int debug2 = 0;
	int length = 10 * difficulty;
	for (x = 0; x < (length); x++) {
		for (y = 0; y < (length); y++) {
			T[x][y].isBomb = 0;
			T[x][y].bombsNearby = 0;
			T[x][y].isFlaged = 0;
			T[x][y].isClicked = 0;
		}
	}
	int lengthAllCoords = length * length;
	int* coords = (int*)malloc(sizeof(int) * lengthAllCoords);
	for (j = 0; j < lengthAllCoords; j++) {
		coords[j] = j;
	}
	int bombCount = length * 2;
	for (k = 0; k < bombCount; k++){
		int rand = getRandom(lengthAllCoords);
		int index = coords[rand];
		for (int j = rand; j < lengthAllCoords - 1; ++j) 
		{
			coords[j] = coords[j + 1];
		}

		lengthAllCoords--;

		int xcoord = index / length;
		int ycoord = index % length;
		T[xcoord][ycoord].isBomb = 1;

		for (i = -1; i < 2; i++) {
			for (j = -1; j < 2; j++) {
				if (0 <= (ycoord + j) && (ycoord + j) < (length) && 0 <= (xcoord + i) && (xcoord + i) < (length)) {
					T[xcoord + i][ycoord + j].bombsNearby += 1;
				}
			}
		}
	}
	free(coords);
}


void ShowGrid(Case** T, int difficulty) {
	int x;
	int y;
	int i;
	int j;
	for (x = -1; x < (10 * difficulty); x++) {
		for (y = -1; y < (10 * difficulty); y++) {
			if (x == -1 || y == -1) {
				if (x == -1) {
					if (y == -1) {
						printf("   ");
					}
					else if(y<10){
						printf(" %d ", y);
					}
					else {
						printf("%d ", y);
					}
				}
				else if (y == -1) {
					if (x < 10) {
						printf(" %d ", x);
					}
					else {
						printf("%d ", x);
					}
				}
			}
			else if (T[x][y].isClicked == 0) {
				if (T[x][y].isFlaged == 1) {
					printf(" F ");
				}
				else {
					printf(" ? ");
				}
			}
			else {
				if (T[x][y].isClicked == 1) {
					if (T[x][y].isBomb == 1) {
						printf(" B ");
						for (i = 0; i < (10 * difficulty); i++) {
							for (j = 0; j < (10 * difficulty); j++) {
								T[i][j].isClicked = 1;
							}
						}
					}
					else if (T[x][y].bombsNearby == 0) {
						revealNear(T, x, y,difficulty);
						printf(" 0 ");
					}
					else if (T[x][y].bombsNearby > 0) {
						printf(" %d ", T[x][y].bombsNearby);
					}
				}
			}
		}
		printf("\n");

	}
	}

int getRandom(int max) 
{
	int random = rand() % max;
	return random;
}

void revealNear(Case** T, int casex, int casey, int difficulty) {
	int x = casex;
	int y = casey;
	int i;
	int j;
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (0 <= (y + j) && (y + j) < (10 * difficulty) && 0 <= (x + i) && (x + i) < (10 * difficulty)) {
				if (T[x + i][y + j].isBomb == 0 && T[x + i][y + j].isClicked == 0) {
					T[x + i][y + j].isClicked = 1;
					if (T[x + i][y + j].bombsNearby == 0) {
						revealNear(T, x + i, y + j, difficulty);
					}
				}
			}
		}
	}
}

int verifWin(Case** T, int difficulty) {
	int x;
	int y;
	int i;
	int j;
	int casecount = 0;
	for (x = 0; x < (10 * difficulty); x++) {
		for (y = 0; y < (10 * difficulty); y++) {
			if (T[x][y].isClicked == 1 && T[x][y].isBomb == 1) {
				printf("Vous avez perdu !");
				return 1;
			}
			else if (T[x][y].isBomb != 1 && T[x][y].isClicked != 1) {
				casecount++;
			}
		}
	}
	if (casecount == 0) {
		printf("Victoire !");
		return 1;
	}
	return 0;
}

void PlayAgain(int* play,int* InGame) {
	int playAgain = 0;
	puts("Voulez vous rejouer?");
	while (1) {
		if (scanf_s(" %d", &playAgain)) {
			if (playAgain) {
				*InGame = 0;
				break;
			}
			else {
				*InGame = 0;
				*play = 0;
				break;
			}
		}
		else {
			printf("Merci de rentrer un nombre entier");
		}
	}
}


void clrscr()
{
	system("@cls||clear");
}
