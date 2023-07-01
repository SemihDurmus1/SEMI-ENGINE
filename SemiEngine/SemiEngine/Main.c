#include<stdio.h>
#include<SDL.h>
#include <SDL_main.h>
//SEMI ENGINE HEADERS
#include "./constants.h"
#include "Main.h"
#include "Objects.h"



//Methods-------------------------------------

//Generals
void destroy_window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
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
	if (!window)
	{
		fprintf(stderr, "Error while creating SDL Window.\n");
		return FALSE;
	}
	if (!renderer)
	{
		fprintf(stderr, "Error creating while SDL Renderer.\n");
		return FALSE;
	}

	return TRUE;
}

//First player
void PlayerFirstKeyDown()
{
	if (event.key.keysym.sym == SDLK_w)
		is_w_pressed = TRUE;
	else if (event.key.keysym.sym == SDLK_s)
		is_s_pressed = TRUE;
}
void PlayerFirstKeyUp()
{
	if (event.key.keysym.sym == SDLK_w)
		is_w_pressed = FALSE;
	else if (event.key.keysym.sym == SDLK_s)
		is_s_pressed = FALSE;
}
void PlayerFirstPressControl()
{
	if (is_w_pressed)
	{
		playerFirst.y -= speed * delta_time; // Yukarý hareket
	}
	if (is_s_pressed)
	{
		playerFirst.y += speed * delta_time; // Yukarý hareket
	}
}
void PlayerFirstFixPos()
{
	if (playerFirst.y + playerFirst.height >= WINDOW_HEIGHT)
	{
		playerFirst.y =  WINDOW_HEIGHT - playerFirst.height;
	}
	else if (playerFirst.y <= 0)
	{
		playerFirst.y = 0;
	}
}

//Second Player
void PlayerSecondKeyDown()
{
	if (event.key.keysym.sym == SDLK_KP_8)
		is_up_pressed = TRUE;
	else if (event.key.keysym.sym == SDLK_KP_2)
		is_down_pressed = TRUE;
}
void PlayerSecondKeyUp()
{
	if (event.key.keysym.sym == SDLK_KP_8)
		is_up_pressed = FALSE;
	else if (event.key.keysym.sym == SDLK_KP_2)
		is_down_pressed = FALSE;
}
void PlayerSecondPressControl()
{
	if (is_up_pressed)
	{
		playerSecond.y -= speed * delta_time; // Yukarý hareket
	}
	if (is_down_pressed)
	{
		playerSecond.y += speed * delta_time; // Yukarý hareket
	}
}
void PlayerSecondFixPos()
{
	if (playerSecond.y + playerSecond.height >= WINDOW_HEIGHT)
	{
		playerSecond.y = WINDOW_HEIGHT - playerSecond.height;
	}
	else if (playerSecond.y <= 0)
	{
		playerSecond.y = 0;
	}
}

//Ball
void BallMove(struct ball* ball, int speedx, int speedy)
{
	ball->x += ballx * delta_time;
	if (ball->x + ball->width >= WINDOW_WIDTH)//Sað köþe
	{
		ballx = -speedx;
	}
	else if (ball->x <= 0)//Sol Köþe
	{
		ballx = speedx * 4;
	}
	ball->y += bally * delta_time;
	if (ball->y + ball->height >= WINDOW_HEIGHT)//Aþaðý köþe
	{
		bally = -speedy;
	}
	else if (ball->y <= 0)//Yukarý köþe
	{
		bally = speedy * 2;
	}
}

//End-Methods---------------------------------



void process_input()
{
	SDL_PollEvent(&event);

	switch (event.type)
    {
        case SDL_QUIT:
            game_is_running = FALSE;
            break;

        case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) game_is_running = FALSE;

			PlayerFirstKeyDown();
			PlayerSecondKeyDown();
            break;

		case SDL_KEYUP:
			PlayerFirstKeyUp();
			PlayerSecondKeyUp();
			break;
    }
	PlayerFirstPressControl();
	PlayerSecondPressControl();
}

void setup()
{
	ball.x = 400;
	ball.y = 300;
	ball.width = 15;
	ball.height = 15;

	playerFirst.x = 20;
	playerFirst.y = 225;
	playerFirst.width = 15;
	playerFirst.height = 125;

	playerSecond.x = 765;
	playerSecond.y = 225;
	playerSecond.width = 15;
	playerSecond.height = 125;
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
	PlayerFirstFixPos();
	PlayerSecondFixPos();

	BallMove(&ball, 140, 100);


	//FRAME CAP FUNCTION. Bu fonksiyon, kareleri ard arda yüklemek yerine kareler arasýnda bekleme yapýyor
	FrameCap();
	//Delta time deðiþkenini saniye cinsinden günceller
	delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

	last_frame_time = SDL_GetTicks();

	//Ball2Move();
}


//void Ball2Move()
//{
//	ball2.x += ball2x * delta_time;
//	if (ball2.x + ball2.width >= WINDOW_WIDTH)//Sað köþe
//	{
//		ball2x = -50 * 4;
//	}
//	else if (ball2.x <= 0)//Sol Köþe
//	{
//		ball2x = 50;
//	}
//	ball2.y += ball2y * delta_time;
//	if (ball2.y + ball2.height >= WINDOW_HEIGHT)//Aþaðý köþe
//	{
//		ball2y = -100 * 2;
//	}
//	else if (ball2.y <= 0)//Yukarý köþe
//	{
//		ball2y = 100;
//	}
//}


void render()
{
	//Draw Background
	SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
	SDL_RenderClear(renderer);

	//Draw a rectangle
	SDL_Rect ball_rect = { 
		(int)ball.x,
		(int)ball.y,
		(int)ball.width,
		(int)ball.height
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_Rect playerFirst_rect = 
	{
		(int)playerFirst.x,
		(int)playerFirst.y,
		(int)playerFirst.width,
		(int)playerFirst.height
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 30, 255);
	SDL_RenderFillRect(renderer, &playerFirst_rect);

	SDL_Rect playerSecond_rect = 
	{
		(int)playerSecond.x,
		(int)playerSecond.y,
		(int)playerSecond.width,
		(int)playerSecond.height
	};
	SDL_SetRenderDrawColor(renderer, 255, 30, 30, 255);
	SDL_RenderFillRect(renderer, &playerSecond_rect);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLineF(renderer, 400, 0, 400, 600);
	SDL_RenderPresent(renderer);
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
