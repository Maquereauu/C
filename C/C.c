// C.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL.h>
const int WIDTH = 800;
const int HEIGHT = 600;
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
void CatchError();

int main()
{
	int choice;
	puts("Terminal ou Graphique?");
	if (scanf_s(" %d", &choice)) {
		if (choice == 1) {
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { printf("%s\n", SDL_GetError()); exit(-1); }
			SDL_Window* window;
			window = SDL_CreateWindow("Hello SDL", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
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
			SDL_Rect back;
			back.x = 200;
			back.y = 50;
			back.h = 500;
			back.w = 400;
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

			/*SDL_Rect chiffre_0;
			SDL_Rect chiffre_1;
			SDL_Rect chiffre_2;
			SDL_Rect chiffre_3;
			SDL_Rect chiffre_4;
			SDL_Rect chiffre_5;
			SDL_Rect chiffre_6;
			SDL_Rect chiffre_7;
			SDL_Rect chiffre_8;
			SDL_Rect chiffre_9;*/











			if (window == NULL) { printf("%s\n", SDL_GetError()); exit(-1); }
			//dessiner un composant 
			SDL_Event windowEvent;
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


			while (1) {
				//
				if (SDL_PollEvent(&windowEvent)) {
					if (windowEvent.type == SDL_QUIT) { break; }
				}
				//CHIFFRE
				/*drawDigit(renderer, 0, 50, 50);
				drawDigit(renderer, 1, 70, 50);
				drawDigit(renderer, 2, 90, 50);
				drawDigit(renderer, 3, 110, 50);
				drawDigit(renderer, 4, 130, 50);
				drawDigit(renderer, 5, 50, 70);
				drawDigit(renderer, 6, 70, 70);
				drawDigit(renderer, 7, 90, 70);
				drawDigit(renderer, 8, 110, 70);
				drawDigit(renderer, 9, 130, 70);*/
				//CHIFFRE
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
				SDL_RenderPresent(renderer);

			}
			//SDL_Delay(5000);
			SDL_DestroyRenderer(renderer);

			SDL_DestroyWindow(window);
			SDL_Quit();

			return 0;
		}
		else {
			int* play = 1;
			while (play) {
				Game(&play);
			}
		}
	}
else {
	printf("merci de rentrer une valeur valide");
	}
}

void Game(int* play) {
	int difficulty;
	int* InGame = 1;
	puts("Veuillez choisir un mode de difficulté ");
	do {
		if (scanf_s(" %d", &difficulty)) {
			if (difficulty <= 0) {
				printf("Merci de renseigner une valeur supérieure à 0\n");
			}
			else if(round(difficulty)==difficulty){
				printf("mais , %d", &difficulty);
				/*break;*/
			}
		}
		else {
			printf("Merci de renseigner un nombre entier \n");
			while(getchar() != '\n');
		}
	} while (1);
	printf("%d", difficulty);
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
			printf("merci de renseigner une case non selectionné !\n\n");
		}
		int verif = verifWin(T, difficulty);
		if (verif == 1) {
			for (int i = 0; i < (10 * difficulty); ++i)
			{
				free(T[i]);
			}
			free(T);
			CatchError(play,&InGame);
			if (InGame == 0) {
				break;
			}
	
		}
		int flag = 0;
		int playerchoicex;
		int playerchoicey;
		puts("Voulez-vous découvrir une case ou bien poser un drapeau?(0/1)");
		scanf_s("%d", &flag);
		if (flag == 1) {
			puts("Quelle case voulez vous drapeauter ? :");
			scanf_s("%d/%d", &playerchoicex, &playerchoicey);
			if (T[playerchoicex][playerchoicey].isFlaged != 1) {
				T[playerchoicex][playerchoicey].isFlaged = 1;

			}
			else {
				T[playerchoicex][playerchoicey].isFlaged = 0;
			}
		}
		else {
			puts("Quelle case voulez vous decouvrir ? :");
			while (1) {
				if (scanf_s("%d/%d", &playerchoicex, &playerchoicey)) {
					if (T[playerchoicex][playerchoicey].isClicked != 1) {
						T[playerchoicex][playerchoicey].isClicked = 1;
						isError = 0;
					}
					else {
						isError = 1;
					}
				}
				else {
					printf("Merci de rentrer des coordonées valides(en nombre entier)");
					printf("%d", &difficulty);
				}
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
						printf("D  ");
					}
					else {
						printf("%d  ", y);
					}
				}
				else if (y == -1) {
					printf("%d ", x);
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
		for (int i = 0; i < (10 * difficulty); ++i)
		{
			free(T[i]);
		}
		free(T);
		return 1;
	}
	return 0;
}

void CatchError(int* play,int* InGame) {
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

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
