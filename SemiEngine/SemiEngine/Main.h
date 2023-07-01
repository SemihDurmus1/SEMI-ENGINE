#pragma once
void FrameCap();

void PlayerSecondFixPos();

void PlayerFirstFixPos();


void destroy_window(); 
int InitializeWindow(void);


void PlayerFirstKeyUp();
void PlayerFirstKeyDown();
void PlayerFirstPressControl();


void PlayerSecondKeyDown();
void PlayerSecondKeyUp();
void PlayerSecondPressControl();


void BallMove(struct ball* ball, int speedx, int speedy);


int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

SDL_Event event;

float delta_time;

int time_to_wait;

int ballx = 140;
int bally = 100;

int speed = 400;

int is_w_pressed = FALSE;
int is_s_pressed = FALSE;

int is_up_pressed = FALSE;
int is_down_pressed = FALSE;