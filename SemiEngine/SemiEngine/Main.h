#pragma once
void FrameCap();

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

SDL_Event event;

float delta_time;

int time_to_wait;