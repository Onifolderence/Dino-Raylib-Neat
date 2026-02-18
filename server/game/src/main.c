#include <raylib.h>
#include <stdbool.h>
// #include <stdio.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define PLAYER_SPEED 10
#define PLAYER_BOXES 8
#define CHARACTER_SCALING 3
#define PLAYER_POS_Y 670
#define PLAYER_MAX_SPEED_SCALE 4

#define JUMP_HEIGHT 250

#define FPS 120

#define HEADLESS 0

typedef enum GameStage { LOGO, TITLE, GAMEPLAY, ENDING } GameStage;
typedef enum Result { LOST, WON } Result;

typedef struct Player {
    Rectangle bound;
    Vector2 pos;
    bool alive;
} Player;

typedef struct Obs {
} Obs;

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

    GameStage screen = GAMEPLAY;
    int frameCount = 0;
    int frameTotal = 0;
    float SPEED = 1.0f;

    int spriteSpeed = 10;
    int playerBox = 0;

    float scrollL0 = 0.0f;
    float scrollL1 = 0.0f;
    float scrollL2 = 0.0f;
    float scrollL3 = 0.0f;
    float scrollL4 = 0.0f;
    float scrollL5 = 0.0f;

    Player player = {0};
    player.pos = (Vector2){250, PLAYER_POS_Y};
    player.alive = 1;
    // printf("%d-%d-%d", player_run.width/8, player_jump.width/8, player_dead.width/8);
    float ethWidth = (float)player_run.width / 8;
    player.bound = (Rectangle){player.pos.x, player.pos.y, ethWidth, player_run.height};

    int jumpFlag = 0;

    float scale = (float)GetScreenWidth() / day[0].width;
    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        switch (screen) {
            case LOGO: {
                frameCount++;
            } break;

            case TITLE: {
            } break;

            case GAMEPLAY: {
                frameCount++;
                frameTotal++;

                if(SPEED <= PLAYER_MAX_SPEED_SCALE) SPEED += 0.0003f;

                scrollL0 -= 0.1 * SPEED;
                scrollL1 -= 0.5 * SPEED;
                scrollL2 -= 1 * SPEED;
                scrollL3 -= 2 * SPEED;
                scrollL4 -= 3 * SPEED;
                scrollL5 -= 4 * SPEED;

                if (frameCount > 1.25 * FPS / (PLAYER_SPEED * SPEED)) {
                    frameCount = 0;
                    playerBox++;
                    if (playerBox > PLAYER_BOXES - 1) playerBox = 0;
                }

                if (scrollL0 <= -SCREEN_WIDTH) scrollL0 = 0;
                if (scrollL1 <= -SCREEN_WIDTH) scrollL1 = 0;
                if (scrollL2 <= -SCREEN_WIDTH) scrollL2 = 0;
                if (scrollL3 <= -SCREEN_WIDTH) scrollL3 = 0;
                if (scrollL4 <= -SCREEN_WIDTH) scrollL4 = 0;
                if (scrollL5 <= -SCREEN_WIDTH) scrollL5 = 0;

                if (IsKeyPressed(KEY_SPACE) && player.pos.y == PLAYER_POS_Y) jumpFlag = 1;

                if (jumpFlag == 1 && player.pos.y >= PLAYER_POS_Y - JUMP_HEIGHT)
                    player.pos.y -= 8;
                else
                    jumpFlag = 0;

                if (jumpFlag == 0 && player.pos.y != PLAYER_POS_Y) {
                    player.pos.y += 8;
                }
                // else if(jumpflag == 1 && )

            } break;

            case ENDING: {
            } break;

            default:
                break;
        }

        BeginDrawing();
        ClearBackground((Color){19, 30, 22});

        switch (screen) {
            case LOGO: {
            } break;

            case TITLE: {
            } break;

            case GAMEPLAY: {
                DrawTextureEx(day[0], (Vector2){scrollL0, 0}, 0.0f, scale, WHITE);
                DrawTextureEx(day[0], (Vector2){scrollL0 + SCREEN_WIDTH, 0}, 0.0f, scale,
                              WHITE);

                DrawTextureEx(day[1], (Vector2){scrollL1, 0}, 0.0f, scale, WHITE);
                DrawTextureEx(day[1], (Vector2){scrollL1 + SCREEN_WIDTH, 0}, 0.0f, scale,
                              WHITE);

                DrawTextureEx(day[2], (Vector2){scrollL2, 0}, 0.0f, scale, WHITE);
                DrawTextureEx(day[2], (Vector2){scrollL2 + SCREEN_WIDTH, 0}, 0.0f, scale,
                              WHITE);

                DrawTextureEx(day[3], (Vector2){scrollL3, 0}, 0.0f, scale, WHITE);
                DrawTextureEx(day[3], (Vector2){scrollL3 + SCREEN_WIDTH, 0}, 0.0f, scale,
                              WHITE);

                DrawTextureEx(day[4], (Vector2){scrollL4, 0}, 0.0f, scale, WHITE);
                DrawTextureEx(day[4], (Vector2){scrollL4 + SCREEN_WIDTH, 0}, 0.0f, scale,
                              WHITE);

                // Player
                if (jumpFlag == 0 && player.pos.y == PLAYER_POS_Y) {
                    DrawTexturePro(player_run,
                                   (Rectangle){(float)playerBox * ethWidth, 0, (float)ethWidth,
                                               player_run.height},
                                   (Rectangle){player.pos.x, player.pos.y,
                                               (float)ethWidth * CHARACTER_SCALING,
                                               (float)player_run.height * CHARACTER_SCALING},
                                   (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
                } else {
                    DrawTexturePro(player_jump,
                                   (Rectangle){(float)playerBox * ethWidth, 0, (float)ethWidth,
                                               player_run.height},
                                   (Rectangle){player.pos.x, player.pos.y,
                                               (float)ethWidth * CHARACTER_SCALING,
                                               (float)player_run.height * CHARACTER_SCALING},
                                   (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
                }

                // DrawTextureEx(roller, (Vector2){0.0f, 0.0f}, 0.0f, 0.25, WHITE);
                DrawTexturePro(
                    roller, (Rectangle){0, 0, (float)roller.width / 10 * 3, roller.height},
                    (Rectangle){SCREEN_WIDTH + scrollL5, PLAYER_POS_Y - 15,
                                (float)roller.width / 10 * 0.2 * 3, roller.height * 0.2},
                    (Vector2){0, 0}, 0.0f, WHITE);
                // DrawTexturePro(
                //     roller, (Rectangle){(float)roller.width/10, 0, (float)roller.width / 10, roller.height},
                //     (Rectangle){SCREEN_WIDTH + scrollL5 + 50, PLAYER_POS_Y - 15,
                //                 (float)roller.width / 10 * 0.2, roller.height * 0.2},
                //     (Vector2){0, 0}, 0.0f, WHITE);

                DrawTextureEx(day[5], (Vector2){scrollL5, 0}, 0.0f, scale, WHITE);
                DrawTextureEx(day[5], (Vector2){scrollL5 + SCREEN_WIDTH, 0}, 0.0f, scale,
                              WHITE);


                DrawFPS(30, 30);
                DrawText(TextFormat("SPEED %d%%", (int)((SPEED)/PLAYER_MAX_SPEED_SCALE * 100)), 130, 30, 20, BLACK);
                DrawText(TextFormat("TIME %d", frameTotal/FPS), 260, 30, 20, BLACK);
            } break;

            case ENDING: {
            } break;

            default:
                break;
        }
        EndDrawing();
    }

    for (int i = 0; i < 6; i++) UnloadTexture(day[i]);
    UnloadTexture(player_run);
    UnloadTexture(player_jump);
    UnloadTexture(player_dead);
    UnloadTexture(roller);

    CloseWindow();
}
