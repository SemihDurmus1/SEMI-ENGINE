#include<stdio.h>
#include<SDL.h>
#include <SDL_main.h>
//My Headers
#include "./constants.h"
#include "Main.h"
#include "Objects.h"


int InitializeWindow(void)
{
	//Init error control
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error initializing SDL.\n");
		return FALSE;
	}

	//create window
	window = SDL_CreateWindow(
		"SEMI ENGINE",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);
	renderer = SDL_CreateRenderer(window, -1, 0);

	//Render and window controls
	if(!window)
	{
		fprintf(stderr, "Error while creating SDL Window.\n");
		return FALSE;
	}
	if(!renderer)
	{
		fprintf(stderr, "Error creating while SDL Renderer.\n");
		return FALSE;
	}

	return TRUE;
}


void process_input()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		game_is_running = FALSE;
		break;

	case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_ESCAPE)
			game_is_running = FALSE;
		break;
	}
}

void setup()
{
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 15;

	ball2.x = 20;
	ball2.y = 20;
	ball2.width = 15;
	ball2.height = 15;
}

void FrameCap()
{
	time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(time_to_wait);
	}
}
void update()
{
	//FRAME CAP FUNCTION. Bu fonksiyon, kareleri ard arda y�klemek yerine kareler aras�nda bekleme yap�yor
	FrameCap();
	//Delta time de�i�kenini saniye cinsinden g�nceller
	delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

	last_frame_time = SDL_GetTicks();

	ball.x += 70 * delta_time;
	ball.y += 50 * delta_time;

	ball2.x += 10 * delta_time;
	ball2.y += 50 * delta_time;
}

void render()
{
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	//Draw a rectangle
	SDL_Rect ball_rect = { 
		(int)ball.x,
		(int)ball.y,
		(int)ball.width,
		(int)ball.height
	};
	SDL_Rect ball2_rect = {
	(int)ball2.x,
	(int)ball2.y,
	(int)ball2.width,
	(int)ball2.height
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball_rect);
	SDL_RenderFillRect(renderer, &ball2_rect);
	 
	//SDL_RenderDrawLineF(renderer, 400, 0, 400, 600);
	SDL_RenderPresent(renderer);
}

void destroy_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


int main(int argc, char* args[])
{
	printf("Hayvan gibi oyun motoru\n");

	game_is_running = InitializeWindow();

	setup();

	while (game_is_running)
	{
		process_input();
		update();
		render();
	}

	destroy_window();


	return FALSE;
}
