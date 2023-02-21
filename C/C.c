// C.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct Case {
    int isBomb;
    int bombsNearby;
    int isFlaged;
    int isClicked;
} Case;

void Init();
void ShowGrid();
int main()
{
    int c = 0;
    Case EmptyCase[10][10];
    Init(EmptyCase);
    ShowGrid(EmptyCase);
}
void Init(Case EmptyCase[10][10]) {
    int x;
    int y;
    int i;
    int j;
    int BombCount = 0;
    int bombsnear = 0;
    while (BombCount < 5) {
        for (x = 0; x < 10; x++) {
            for (y = 0; y < 10; y++) {
                int randomBomb = (rand() % 10);
                if (randomBomb == 0) {
                    EmptyCase[x][y].isBomb = 1;
                    BombCount++;
                }
                else {
                    EmptyCase[x][y].isBomb = 0;
                }

            }
        }
    }
    for (x = 0; x < 10; x++) {
        for (y = 0; y < 10; y++) {
            EmptyCase[x][y].isClicked = 0;
            if (EmptyCase[x][y].isBomb == 0) {
                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 10; j++) {
                        if (EmptyCase[i][j].isBomb == 1) {
                            bombsnear++;
                        }
                    }
                }
            }
            int bombsnear = 0;
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
                    if(y == -1){
                        printf("salut %d  ", y);
                    }
                }
                else if (y == -1) {
                    printf("%d ", x);
                }
            }else if (CaseList[x][y].isClicked == 0) {
                if (CaseList[x][y].isFlaged == 1) {
                    printf("F");
                }
                else {
                    printf(" ? ");
                }
            }
            else {
                if (CaseList[x][y].isClicked == 1) {
                    if (CaseList[x][y].bombsNearby > 0) {
                        printf("%d", CaseList[x][y].bombsNearby);
                    }
                    else if (CaseList[x][y].isBomb == 1) {
                        printf("B");
                    }
                    else {
                    }
                }
            }
        }
        printf("\n");
    }
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


//int VerifWin(){ 
//    //si case clické != isbomb 
//        //return 0 
//    //sinon 
//        //return ""
//
//}
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
