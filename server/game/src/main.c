#include <raylib.h>
#include <stdbool.h>
// #include <stdio.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define PLAYER_SPEED 10
#define PLAYER_BOXES 8

#define FPS 120

#define HEADLESS 0

typedef enum GameStage {LOGO, TITLE, GAMEPLAY, ENDING} GameStage;

typedef struct Player {
    Rectangle bound;
    Vector2 pos;
    bool alive;
} Player;

typedef struct Obs {} Obs;

#define DAY 1

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DINO-RAYLIB_NEAT");

    Texture player_run = LoadTexture("./server/game/assets/PLAYER/player_run.png");
    Texture player_jump = LoadTexture("./server/game/assets/PLAYER/player_jump.png");
    Texture player_dead = LoadTexture("./server/game/assets/PLAYER/player_dead.png");

    Texture roller = LoadTexture("./server/game/assets/ROLLERS/spritesheet.png");

    Texture day[] = {
        LoadTexture("server/game/assets/DAY/LAYERS/L0.png"),
        LoadTexture("server/game/assets/DAY/LAYERS/L1.png"),
        LoadTexture("server/game/assets/DAY/LAYERS/L2.png"),
        LoadTexture("server/game/assets/DAY/LAYERS/L3.png"),
        LoadTexture("server/game/assets/DAY/LAYERS/L4.png"),
        LoadTexture("server/game/assets/DAY/LAYERS/L5.png"),
    };

    int frameCount = 0;
    float SPEED = 1.0f;

    int spriteSpeed = 10;
    int playerBox = 0;

    float scrollL2 = 0.0f;
    float scrollL3 = 0.0f;
    float scrollL4 = 0.0f;
    float scrollL5 = 0.0f;

    float scale = (float)GetScreenWidth() / day[0].width;

    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        frameCount++;
        SPEED+=0.0003f;

        scrollL2 -= 1*SPEED;
        scrollL3 -= 2*SPEED;
        scrollL4 -= 3*SPEED;
        scrollL5 -= 4*SPEED;

        BeginDrawing();
        ClearBackground((Color){19, 30, 22});

        if (frameCount > 1.25 * FPS / (PLAYER_SPEED*SPEED)) {
            frameCount = 0;
            playerBox++;
            if (playerBox > PLAYER_BOXES - 1) playerBox = 0;
        }

        if (scrollL2 <= -SCREEN_WIDTH) scrollL2 = 0;
        if (scrollL3 <= -SCREEN_WIDTH) scrollL3 = 0;
        if (scrollL4 <= -SCREEN_WIDTH) scrollL4 = 0;
        if (scrollL5 <= -SCREEN_WIDTH) scrollL5 = 0;


        DrawTextureEx(day[0], (Vector2){0, 0}, 0.0f, scale, WHITE);
        DrawTextureEx(day[1], (Vector2){0, 0}, 0.0f, scale, WHITE);

        DrawTextureEx(day[2], (Vector2){scrollL2, 0}, 0.0f, scale, WHITE);
        DrawTextureEx(day[2], (Vector2){scrollL2 + SCREEN_WIDTH, 0}, 0.0f, scale, WHITE);

        DrawTextureEx(day[3], (Vector2){scrollL3, 0}, 0.0f, scale, WHITE);
        DrawTextureEx(day[3], (Vector2){scrollL3 + SCREEN_WIDTH, 0}, 0.0f, scale, WHITE);

        DrawTextureEx(day[4], (Vector2){scrollL4, 0}, 0.0f, scale, WHITE);
        DrawTextureEx(day[4], (Vector2){scrollL4 + SCREEN_WIDTH, 0}, 0.0f, scale, WHITE);

        DrawTexturePro(player_run,
                       (Rectangle){(float)playerBox*player_run.width/8, 0, (float)player_run.width / 8, player_run.height},
                       (Rectangle){90, SCREEN_HEIGHT-230, (float)player_run.width * 3 / 8,
                                   (float)player_run.height * 3},
                       (Vector2){0.0f, 0.0f}, 0.0f, WHITE);

        DrawTextureEx(day[5], (Vector2){scrollL5, 0}, 0.0f, scale, WHITE);
        DrawTextureEx(day[5], (Vector2){scrollL5 + SCREEN_WIDTH, 0}, 0.0f, scale, WHITE);

        DrawFPS(30, 30);
        EndDrawing();
    }

    for (int i=0; i < 6; i++) UnloadTexture(day[i]);
    UnloadTexture(player_run);
    UnloadTexture(player_jump);
    UnloadTexture(player_dead);
    UnloadTexture(roller);
    CloseWindow();
}
