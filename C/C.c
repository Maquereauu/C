// C.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Case {
	int isBomb;
	int bombsNearby;
	int isFlaged;
	int isClicked;
} Case;

void Init();
void ShowGrid();
int getRandom();
int verifWin();
void revealNear();

int main()
{
	srand(time(NULL));
	int playAgain = 0;
	Case EmptyCase[10][10];
	Init(EmptyCase);
	while (1) {
		ShowGrid(EmptyCase);
		int verif = verifWin(EmptyCase);
		if (verif == 1) {
			puts("Voulez vous rejouer?");
			scanf_s(" %d", &playAgain);
			if (playAgain) {
				main();
			}
			else {
				break;
			}
		}
		int playerchoicex;
		int playerchoicey;
		puts("Quelle case voulez vous decouvrir ? :");
		scanf_s("%d/%d", &playerchoicex, &playerchoicey);
		if (EmptyCase[playerchoicex][playerchoicey].isClicked != 1) {
			EmptyCase[playerchoicex][playerchoicey].isClicked = 1;
		}
		else {
			printf("merci de renseigner une case non selectionné !\n\n");

			
		}
	}

}
void Init(Case EmptyCase[10][10]){
	int x;
	int y;
	int i;
	int j;
	int BombCount = 0;
	int bombsnear = 0;
	int debug = 0;
	int debug2 = 0;
	for (x = 0; x < 10; x++) {
		for (y = 0; y < 10; y++) {
			EmptyCase[x][y].isBomb = 0;
		}
	}

	for (i = 0; i < 10; i++)
	{
		int xrand = getRandom(10);
		int yrand = getRandom(10);
		EmptyCase[xrand][yrand].isBomb = 1; 
	}

	for (x = 0; x < 10; x++) {
		for (y = 0; y < 10; y++) {
			EmptyCase[x][y].isClicked = 0;
			EmptyCase[x][y].bombsNearby = 0;
			int bombsnear = 0;
			if (EmptyCase[x][y].isBomb == 0) {
				for (i = -1; i < 2; i++) {
					for (j = -1; j < 2; j++) {
						if (0 <= (y + j) && (y + j) < 10 && 0 <= (x + i) && (x + i) < 10) {
							if (EmptyCase[x + i][y + j].isBomb == 1) {
								bombsnear++;
								EmptyCase[x][y].bombsNearby = bombsnear;
							}
						}
					}
				}
			}
		}
	}
}

void ShowGrid(Case CaseList[10][10]) {
	int x;
	int y;
	for (x = -1; x < 10; x++) {
		for (y = -1; y < 10; y++) {
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
			else if (CaseList[x][y].isClicked == 0) {
				if (CaseList[x][y].isFlaged == 1) {
					printf(" v ");
				}
				else {
					printf(" ? ");
				}
			}
			else {
				if (CaseList[x][y].isClicked == 1) {
					if (CaseList[x][y].isBomb == 1) {
						printf(" B ");
					}
					else if (CaseList[x][y].bombsNearby == 0) {
						revealNear(CaseList, x, y);
						printf(" 0 ");
					}
					else if (CaseList[x][y].bombsNearby > 0) {
						printf(" %d ", CaseList[x][y].bombsNearby);
					}
				}
			}
		}
		printf("\n");

	}
	}

int getRandom(int max) 
{
	return rand() % max;
}

//void flag(){ 
//    //input ("voulez vous mettre un drapeau :")
//    //if answer = O 
//        //return 1 en x , y 
//        
//    //else 
//        //return input ("Qu'elle case voulez vous marquer :")
//    
//}
void revealNear(Case CaseList[10][10],int casex,int casey) {
	int x = casex;
	int y = casey;
	int i;
	int j;
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if (CaseList[x + i][y + j].isBomb == 0 && CaseList[x + i][y + j].isClicked == 0) {
				if (0 <= (y + j) && (y + j) < 10 && 0 <= (x + i) && (x + i) < 10) {
					CaseList[x + i][y + j].isClicked = 1;
					if (CaseList[x + i][y + j].bombsNearby == 0) {
						revealNear(CaseList, x + i, y + j);
					}
				}
			}
		}
	}
}
int verifWin(Case CaseList[10][10]) {
	int x;
	int y;
	int casecount = 0;
	for (x = 0; x < 10; x++) {
		for (y = 0; y < 10; y++) {
			if (CaseList[x][y].isClicked == 1 && CaseList[x][y].isBomb == 1) {
				printf("Vous avez perdu !");
				return 1;
			}
			else if (CaseList[x][y].isBomb != 1 && CaseList[x][y].isClicked != 1) {
				casecount++;
			}
		}
	}
	if (casecount == 0) {
		printf("Victoire !");
		return 1;
	}

}
//int Restart(){}

//int win{
//    //si VerifWin = 0 
//        //return Win  
//    //sinon si  VerifWin != 0  & toute les case = clické (decouverte)
//        //return "Toute les case n'ont pas été decouverte "
//    //sinon si case clicked = isbomb 
//        //return "GAME OVER"
//        //print "voulez vous recommencer :"
//}



// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
