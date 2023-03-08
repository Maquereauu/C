// C.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_image.h>
#include <math.h>
#include <SDL.h>
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
	int i = 1;
	while (*play) {
		if (i == 0) {
			MenuSDL();
		}
		else {
			GameSDL(play);
		}
	}
}

void MenuSDL() {
}

void GameSDL(int* play) {
	int close = 0;
	int difficulty = 1;
	int* InGame = 1;
	int GameOver = 0;
	srand(time(NULL));
	int length = 10 * difficulty;
	int lengthAllCoords = length * length;
	int i;
	int j;
	Case** T = (Case**)malloc(sizeof(Case*) * length);
	for (int i = 0; i < (10 * difficulty); ++i)
	{
		T[i] = (Case*)malloc(sizeof(Case) * length);
	}
	Init(T, difficulty);
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
	SDL_Rect case_damier[10][10];
	//DAMIER
	for (i = 0; i < length; i++) {
		for (j = 0; j < length; j++) {
			case_damier[i][j].x = 100 + j * 60;
			case_damier[i][j].y = 50 + i * 60;
			case_damier[i][j].h = 60;
			case_damier[i][j].w = 60;
		}
	}

	SDL_Surface* image = IMG_Load("0.png");
	SDL_Surface* image2 = IMG_Load("test2.png");
	SDL_Surface* image3 = IMG_Load("Bomb.png");
	SDL_Surface* image4 = IMG_Load("1.png");
	SDL_Surface* image5 = IMG_Load("2.png");
	SDL_Surface* image6 = IMG_Load("3.png");
	SDL_Surface* image7 = IMG_Load("4.png");
	SDL_Surface* image8 = IMG_Load("5.png");
	SDL_Surface* image9 = IMG_Load("6.png");
	SDL_Surface* image10 = IMG_Load("7.png");
	SDL_Surface* image11 = IMG_Load("8.png");
	SDL_Surface* image12 = IMG_Load("flag.png");
	if (window == NULL) { printf("%s\n", SDL_GetError()); exit(-1); }
	//dessiner un composant 
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, image2);
	SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, image3);
	SDL_Texture* texture4 = SDL_CreateTextureFromSurface(renderer, image4);
	SDL_Texture* texture5 = SDL_CreateTextureFromSurface(renderer, image5);
	SDL_Texture* texture6 = SDL_CreateTextureFromSurface(renderer, image6);
	SDL_Texture* texture7 = SDL_CreateTextureFromSurface(renderer, image7);
	SDL_Texture* texture8 = SDL_CreateTextureFromSurface(renderer, image8);
	SDL_Texture* texture9 = SDL_CreateTextureFromSurface(renderer, image9);
	SDL_Texture* texture10 = SDL_CreateTextureFromSurface(renderer, image10);
	SDL_Texture* texture11 = SDL_CreateTextureFromSurface(renderer, image11);
	SDL_Texture* texture12 = SDL_CreateTextureFromSurface(renderer, image12);
	SDL_Event event;
	while (1) {
		//
		if (GameOver == 1) {
			if (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) { close = 1; break; }
				if (SDL_MOUSEBUTTONDOWN == event.type) {
					if (SDL_BUTTON_LEFT == event.button.button) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						if (x >= 300 && x <= 500 && y >= 450 && y <= 550) {
							for (int i = 0; i < (10 * difficulty); ++i) {
								free(T[i]);
							}
							free(T);
							SDL_DestroyRenderer(renderer);
							SDL_FreeSurface(image); //Équivalent du destroyTexture pour les surface, permet de libérer la mémoire quand on n'a plus besoin d'une surface
							IMG_Quit();
							SDL_DestroyWindow(window);
							SDL_Quit();
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
						x = (x - 100) / 60;
						y = (y - 50) / 60;
						if (x < 10 && y < 10 && x >= 0 && y >= 0) {
							T[y][x].isClicked = 1;
							if (T[y][x].bombsNearby == 0) {
								revealNear(T, y, x, difficulty);
							}
						}
					}
					else if (SDL_BUTTON_RIGHT == event.button.button) {
						int x, y;
						SDL_GetMouseState(&x, &y);
						x = (x - 100) / 60;
						y = (y - 50) / 60;
						if (x < 10 && y < 10 && x >= 0 && y >= 0) {
							T[y][x].isFlaged = 1;
						}
					}
					int verif = verifWin(T, difficulty);
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
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				if (T[i][j].isClicked == 1) {
					if (T[i][j].isBomb == 1) {
						SDL_RenderCopy(renderer, texture3, NULL, &case_damier[i][j]);
					}
					else if (T[i][j].bombsNearby > 0) {
						switch (T[i][j].bombsNearby) {
						case 1: SDL_RenderCopy(renderer, texture4, NULL, &case_damier[i][j]); break;
						case 2: SDL_RenderCopy(renderer, texture5, NULL, &case_damier[i][j]); break;
						case 3: SDL_RenderCopy(renderer, texture6, NULL, &case_damier[i][j]); break;
						case 4: SDL_RenderCopy(renderer, texture7, NULL, &case_damier[i][j]); break;
						case 5: SDL_RenderCopy(renderer, texture8, NULL, &case_damier[i][j]); break;
						case 6: SDL_RenderCopy(renderer, texture9, NULL, &case_damier[i][j]); break;
						case 7: SDL_RenderCopy(renderer, texture10, NULL, &case_damier[i][j]); break;
						case 8: SDL_RenderCopy(renderer, texture11, NULL, &case_damier[i][j]); break;
						}
					}
					else {
						SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);
					}
				}
				else if (T[i][j].isFlaged == 1) {
					SDL_RenderCopy(renderer, texture12, NULL, &case_damier[i][j]);
				}
				else if (T[i][j].isClicked == 0) {
					SDL_SetRenderDrawColor(renderer, 110, 148, 240, 255);
					SDL_RenderFillRect(renderer, &case_damier[i][j]);
				}
			}
		}
		//DAMIER-------------------
		if (!image)
		{
			printf("Erreur de chargement de l'image : %s", SDL_GetError());
			return -1;
		}
		if (GameOver == 1) {
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 150);
			SDL_RenderFillRect(renderer, &menu);
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
			SDL_RenderFillRect(renderer, &playAgainRect);
		}
		SDL_RenderPresent(renderer);
	}
	if (close) {
		for (int i = 0; i < (10 * difficulty); ++i) {
			free(T[i]);
		}
		free(T);
		SDL_DestroyRenderer(renderer);
		SDL_FreeSurface(image); //Équivalent du destroyTexture pour les surface, permet de libérer la mémoire quand on n'a plus besoin d'une surface
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
		for (int j = index; j < lengthAllCoords - 1; ++j) 
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
