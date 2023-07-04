#pragma once
void FrameCap();


void destroy_window();
int InitializeWindow(void);


void PlayerFirstFixPos();
void PlayerFirstKeyUp();
void PlayerFirstKeyDown();
void PlayerFirstPressControl();


void PlayerSecondFixPos();
void PlayerSecondKeyUp();
void PlayerSecondKeyDown();
void PlayerSecondPressControl();


void RespawnBall(struct ball* ball);
void BallMove(struct ball* ball, int speedx, int speedy);


int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

SDL_Event event;

float delta_time;

int time_to_wait;

int ballSpeedX = 500;
int ballSpeedY = 500;

int playerSpeed = 600;

int is_w_pressed = FALSE;
int is_s_pressed = FALSE;

int is_up_pressed = FALSE;
int is_down_pressed = FALSE;

int rightCornerplayerFirst;

int leftCornerBall;