#include "raylib.h"

// Game constants
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PADDLE_WIDTH 15
#define PADDLE_HEIGHT 100
#define BALL_RADIUS 10
#define PADDLE_SPEED 400
#define BALL_SPEED 400

// Helper functions
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(val, min, max) (MAX((min), MIN((val), (max))))

// Game objects
typedef struct {
    Rectangle rect;
    int score;
    Color color;
} Paddle;

typedef struct {
    Vector2 position;
    Vector2 speed;
    float radius;
    Color color;
} Ball;

// Function declarations
void InitGame(Paddle *leftPaddle, Paddle *rightPaddle, Ball *ball);
void UpdateGame(Paddle *leftPaddle, Paddle *rightPaddle, Ball *ball, float deltaTime);
void DrawGame(Paddle *leftPaddle, Paddle *rightPaddle, Ball *ball);

int main(void) {
    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
    SetTargetFPS(60);

    // Initialize game objects
    Paddle leftPaddle, rightPaddle;
    Ball ball;
    InitGame(&leftPaddle, &rightPaddle, &ball);

    // Main game loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        
        // Update game state
        UpdateGame(&leftPaddle, &rightPaddle, &ball, deltaTime);

        // Draw game
        BeginDrawing();
        {
            ClearBackground(BLACK);
            DrawGame(&leftPaddle, &rightPaddle, &ball);
        }
        EndDrawing();
    }

    // Cleanup
    CloseWindow();
    return 0;
}

void InitGame(Paddle *leftPaddle, Paddle *rightPaddle, Ball *ball) {
    // Initialize left paddle
    leftPaddle->rect = (Rectangle){
        .x = 50,
        .y = SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2,
        .width = PADDLE_WIDTH,
        .height = PADDLE_HEIGHT
    };
    leftPaddle->score = 0;
    leftPaddle->color = WHITE;

    // Initialize right paddle
    rightPaddle->rect = (Rectangle){
        .x = SCREEN_WIDTH - 50 - PADDLE_WIDTH,
        .y = SCREEN_HEIGHT/2 - PADDLE_HEIGHT/2,
        .width = PADDLE_WIDTH,
        .height = PADDLE_HEIGHT
    };
    rightPaddle->score = 0;
    rightPaddle->color = WHITE;

    // Initialize ball
    ball->position = (Vector2){
        .x = SCREEN_WIDTH/2,
        .y = SCREEN_HEIGHT/2
    };
    ball->speed = (Vector2){
        .x = BALL_SPEED,
        .y = BALL_SPEED
    };
    ball->radius = BALL_RADIUS;
    ball->color = WHITE;
}

void UpdateGame(Paddle *leftPaddle, Paddle *rightPaddle, Ball *ball, float deltaTime) {
    // Ball movement
    ball->position.x += ball->speed.x * deltaTime;
    ball->position.y += ball->speed.y * deltaTime;

    // Paddle movement
    if (IsKeyDown(KEY_W)) {
        leftPaddle->rect.y -= PADDLE_SPEED * deltaTime;
    }
    if (IsKeyDown(KEY_S)) {
        leftPaddle->rect.y += PADDLE_SPEED * deltaTime;
    }
    if (IsKeyDown(KEY_UP)) {
        rightPaddle->rect.y -= PADDLE_SPEED * deltaTime;
    }
    if (IsKeyDown(KEY_DOWN)) {
        rightPaddle->rect.y += PADDLE_SPEED * deltaTime;
    }

    // Collision detection - paddles with top/bottom of screen
    leftPaddle->rect.y = CLAMP(leftPaddle->rect.y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
    rightPaddle->rect.y = CLAMP(rightPaddle->rect.y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);

    // Collision detection - ball with top/bottom of screen
    if (ball->position.y - ball->radius <= 0 || ball->position.y + ball->radius >= SCREEN_HEIGHT) {
        ball->speed.y *= -1;
    }
    if (ball->position.x - ball->radius <= 0 || ball->position.x + ball->radius >= SCREEN_WIDTH) {
        ball->speed.x *= -1;
    }

    // TODO: Collision detection - ball with paddles
    if (CheckCollisionCircleRec(ball->position, ball->radius, leftPaddle->rect)) {

    }
    if (CheckCollisionCircleRec(ball->position, ball->radius, rightPaddle->rect)) {

    }

    // TODO: Collision detection - ball with left/right of screen (scoring)
}

void DrawGame(Paddle *leftPaddle, Paddle *rightPaddle, Ball *ball) {
    // Draw paddles
    DrawRectangleRec(leftPaddle->rect, leftPaddle->color);
    DrawRectangleRec(rightPaddle->rect, rightPaddle->color);
    
    // Draw ball
    DrawCircleV(ball->position, ball->radius, ball->color);
    
    // Draw center line
    DrawLine(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, WHITE);
    
    // Draw scores
    DrawText(TextFormat("%d", leftPaddle->score), SCREEN_WIDTH/4, 20, 40, WHITE);
    DrawText(TextFormat("%d", rightPaddle->score), 3*SCREEN_WIDTH/4, 20, 40, WHITE);
}
