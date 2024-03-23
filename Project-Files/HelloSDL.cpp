#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <cstdint>

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1080
typedef uint32_t uint32;
typedef uint8_t uint8;

//This is our App containing the handle to the renderer and the handle to the window
typedef struct{

	SDL_Renderer *renderer;
	SDL_Window *window;


}App;

App app;

//This initializes our 
void initSDL(void){
	

	uint32 rendererFlags = SDL_RENDERER_ACCELERATED; 
	uint32 windowFlags = 0;

	if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0){

		printf("Can't Initialize SDL: %s\n", SDL_GetError());
		exit(1);

	}
	
	app.window = SDL_CreateWindow("This is Dumb", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if(!app.window){

		printf("Failed to create window: %s\n", SDL_GetError());
		exit(1);

	}

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

	
	if(!app.renderer){

		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);

	}


}

bool GetKeyboardInput(void){

	SDL_Event event;

	while(SDL_PollEvent(&event)){


		if(event.type == SDL_QUIT) return false;

	}

	return true;

}
void RenderColor(void){

	if(SDL_RenderClear(app.renderer)) printf("Failed to clear the screen: %s", SDL_GetError());

	SDL_Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.w = 200;
	rect.h = 200;

	SDL_SetRenderDrawColor(app.renderer, 255,255,255,255);
	SDL_RenderDrawRect(app.renderer, &rect);
	SDL_RenderFillRect(app.renderer, &rect);

	SDL_SetRenderDrawColor(app.renderer, 0,0,0,255);

	SDL_RenderPresent(app.renderer);
}


int main(int argc, char* argv[]){

	initSDL();

	//Game Loop
	while(GetKeyboardInput()){


		RenderColor();

	}

	SDL_Quit();

	return 0;
}
