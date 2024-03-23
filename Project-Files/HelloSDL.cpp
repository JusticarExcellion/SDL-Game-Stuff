#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <stdio.h>
#include <cstdint>

#define internal static
#define global static
#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1080
typedef uint32_t uint32;
typedef uint8_t uint8;

//This is our App containing the handle to the renderer and the handle to the window
typedef struct{

	SDL_Renderer *renderer;
	SDL_Window *window;


}App;

global App app;
global bool is_Running = true;

//This initializes our SDL and sets up the window 
internal void initSDL(void){
	

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

internal 
void handleEvents(void){

	SDL_Event event;
	while(SDL_PollEvent(&event)){


		switch(event.type){


			case SDL_KEYDOWN:
				//handle what key is down here
				//We going to use scancodes because I don't want to change keyboard layouts :)
				printf("Pressed: ");

				if(event.key.keysym.scancode == SDL_SCANCODE_W) printf("W");
			
				printf("\n");

			break;


			case SDL_QUIT:

				is_Running = false;

			break;


		};


	}



}

void RenderColor(void){

	if(SDL_RenderClear(app.renderer)) printf("Failed to clear the screen: %s", SDL_GetError());

	SDL_Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.w = 200;
	rect.h = 200;

	//Technically these can fail, so error checking them might be a good idea
	SDL_SetRenderDrawColor(app.renderer, 255,255,255,255);
	SDL_RenderDrawRect(app.renderer, &rect);
	SDL_RenderFillRect(app.renderer, &rect);

	SDL_SetRenderDrawColor(app.renderer, 0,0,0,255);

	SDL_RenderPresent(app.renderer);
}


int main(int argc, char* argv[]){

	initSDL();
	//Game Loop
	//Change the game loop while condition
	while(is_Running){

		handleEvents();

		RenderColor();

	}

	//Handle any cleanup here
	//Check to see if these succeed and log them
	SDL_DestroyWindow(app.window);
	SDL_DestroyRenderer(app.renderer);

	SDL_Quit();

	return 0;
}
