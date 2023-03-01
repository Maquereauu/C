//#include <SDL.h>
//#include <stdlib.h>
//#include <stdio.h>
//
//
//const int WIDTH = 800;
//const int HEIGHT = 600;
//const int POSITION_X = 100;
//const int POSITION_Y = 100;
//
//
//
//int main(int c, char* T[]){
//	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { printf("%s\n", SDL_GetError()); exit(-1); }
//	SDL_Window* window;
//	window = SDL_CreateWindow("Hello SDL", POSITION_X, POSITION_Y, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
//	SDL_Rect carre;
//	carre.x=100;
//	carre.y=100;
//	carre.h=100;
//	carre.w=100;
//
//
//	if (window == NULL) { printf("%s\n", SDL_GetError()); exit(-1); }
//	//dessiner un composant 
//	SDL_Event windowEvent;
//	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//
//
//	while (1) {
//	//
//		if (SDL_PollEvent(&windowEvent)) {
//			if (windowEvent.type == SDL_QUIT) { break; }
//	}
//	//SDL_Renderer
//		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
//		SDL_RenderClear(renderer);
//		
//
//		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//		SDL_RenderFillRect(renderer, &carre);
//		SDL_RenderPresent(renderer);
//
//	}
//	//SDL_Delay(5000);
//	SDL_DestroyRenderer(renderer);
//
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//
//	return 0;
//}
//
