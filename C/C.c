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
void Game();
void PlayAgain();
void SDL_Render();

int main()
{
	int choice;
	puts("Terminal ou Graphique?");
	if (scanf_s(" %d", &choice)) {
		if (choice == 1) {
			SDL_Render();
		}
		else {
			int* play = 1;
			while (play) {
				Game(&play);
			}
		}
	}
else {
	printf("Merci de rentrer une valeur valide");
	}
}

void SDL_Render() {
	int difficulty = 1;
	int* InGame = 1;
	srand(time(NULL));
	int i;
	int j;
	Case** T = (Case**)malloc(sizeof(Case*) * (10 * difficulty));
	for (int i = 0; i < (10 * difficulty); ++i)
	{
		T[i] = (Case*)malloc(sizeof(Case) * (10 * difficulty));
	}
	Init(T, difficulty);
	int length = 10 * difficulty;
	int lengthAllCoords = length * length;
	int* coordscases = (int*)malloc(sizeof(int) * lengthAllCoords);
	for (j = 0; j < lengthAllCoords; j++) {
		coordscases[j] = 0;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { printf("%s\n", SDL_GetError()); exit(-1); }
	IMG_Init(IMG_INIT_JPG);
	SDL_Window* window;
	window = SDL_CreateWindow("Démineur", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	//FLAG
	SDL_Rect carre_flag;
	carre_flag.x = 10;
	carre_flag.y = 10;
	carre_flag.h = 5;
	carre_flag.w = 5;
	SDL_Rect rectangle_flag;
	rectangle_flag.x = 10;
	rectangle_flag.y = 10;
	rectangle_flag.h = 10;
	rectangle_flag.w = -2;
	//BACK_Damier
	SDL_Rect back;
	back.x = 100;
	back.y = 50;
	back.h = 600;
	back.w = 600;
	//BOMBE 
	SDL_Rect rectangle_bomb_vertical;
	rectangle_bomb_vertical.x = 22;
	rectangle_bomb_vertical.y = 10;
	rectangle_bomb_vertical.h = 10;
	rectangle_bomb_vertical.w = 6;

	SDL_Rect rectangle_bomb_horizontal;
	rectangle_bomb_horizontal.x = 20;
	rectangle_bomb_horizontal.y = 12;
	rectangle_bomb_horizontal.h = 6;
	rectangle_bomb_horizontal.w = 10;

	SDL_Rect carre_bomb;
	carre_bomb.x = 21;
	carre_bomb.y = 11;
	carre_bomb.h = 8;
	carre_bomb.w = 8;
	SDL_Rect meche_bomb;
	meche_bomb.x = 24;
	meche_bomb.y = 8;
	meche_bomb.h = 2;
	meche_bomb.w = 2;
	SDL_Rect trait_bomb;
	trait_bomb.x = 20;
	trait_bomb.y = 14;
	trait_bomb.h = 2;
	trait_bomb.w = 10;
	SDL_Rect case_damier[10][10];
	//DAMIER
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			case_damier[i][j].x = 100 + j * 60;
			case_damier[i][j].y = 50 + i * 60;
			case_damier[i][j].h = 60;
			case_damier[i][j].w = 60;
		}
	}

	SDL_Surface* image = IMG_Load("test.png");
	SDL_Surface* image2 = IMG_Load("test2.png");
	SDL_Surface* image3 = IMG_Load("test3.jpg");
	if (window == NULL) { printf("%s\n", SDL_GetError()); exit(-1); }
	//dessiner un composant 
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, image2);
	SDL_Texture* texture3 = SDL_CreateTextureFromSurface(renderer, image3);
	SDL_Event event;
	while (1) {
		//
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { break; }
			if (SDL_MOUSEBUTTONDOWN == event.type) {
				if (SDL_BUTTON_LEFT == event.button.button) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					x = (x - 100) / 60;
					y = (y - 50) / 60;
					if (x < 10 && y < 10 && x >= 0 && y >= 0) {
						coordscases[(y * 10) + x] = 1;
					}
				}
				else if (SDL_BUTTON_RIGHT == event.button.button) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					x = (x - 100) / 60;
					y = (y - 50) / 60;
					if (x < 10 && y < 10 && x >= 0 && y >= 0) {
						coordscases[(y * 10) + x] = 2;
					}
				}
				int verif = verifWin(T, difficulty);
				if (verif == 1) {
					for (int i = 0; i < (10 * difficulty); ++i) {
						free(T[i]);
					}
					free(T);
				}
			}
		}
		//SDL_Renderer
		SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
		SDL_RenderFillRect(renderer, &back);


		//BOMBE-----------------------
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rectangle_bomb_vertical);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rectangle_bomb_horizontal);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &carre_bomb);

		SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
		SDL_RenderFillRect(renderer, &trait_bomb);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &meche_bomb);
		//BOMBE-----------------------


		//FLAG------------------------
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rectangle_flag);

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &carre_flag);
		//FLAG----------------------
		//DAMIER-------------------
		for (i = 0; i < 10; i++) {
			for (j = 0; j < 10; j++) {
				if (coordscases[(i * 10) + j] == 0) {
					SDL_SetRenderDrawColor(renderer, 110, 148, 240, 255);
					SDL_RenderFillRect(renderer, &case_damier[i][j]);
				}
				else if (coordscases[(i * 10) + j] == 1) {
					if (T[i][j].isBomb == 1) {
						SDL_RenderCopy(renderer, texture3, NULL, &case_damier[i][j]);
					}
					else if (T[i][j].bombsNearby > 0) {
						SDL_RenderCopy(renderer, texture2, NULL, &case_damier[i][j]);
					}
					else {
						SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);
					}
					/*else if (T[i][j].bombsNearby > 0) {
						switch (T[i][j].bombsNearby) {
						case 1: SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);
						case 2: SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);
						case 3: SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);
						case 4: SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);
						case 5: SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);
						case 6: SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);
						case 7: SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);
						case 8: SDL_RenderCopy(renderer, texture, NULL, &case_damier[i][j]);

						}
					}*/
				}
			}
			}
			//DAMIER-------------------
			SDL_SetRenderDrawColor(renderer, 38, 70, 147, 255);
			SDL_RenderCopy(renderer, texture, NULL, &case_damier[1][1]);
			SDL_RenderCopy(renderer, texture, NULL, &case_damier[9][9]);
			SDL_RenderCopy(renderer, texture2, NULL, &case_damier[2][2]);
			SDL_RenderCopy(renderer, texture2, NULL, &case_damier[8][8]);
			if (!image)
			{
				printf("Erreur de chargement de l'image : %s", SDL_GetError());
				return -1;
			}
			SDL_RenderPresent(renderer);
		}
		SDL_DestroyRenderer(renderer);
		SDL_FreeSurface(image); //Équivalent du destroyTexture pour les surface, permet de libérer la mémoire quand on n'a plus besoin d'une surface
		IMG_Quit();
		SDL_DestroyWindow(window);
		SDL_Quit();
		free(coordscases);
		return 0;
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

void revealNear(Case** T,int casex,int casey,int difficulty) {
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
						revealNear(T, x + i, y + j,difficulty);
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

int checkErrorInt(int max) {
	
}


void clrscr()
{
	system("@cls||clear");
}
