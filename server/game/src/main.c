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
typedef enum TitleParts { START, SETUP, BUILD_BY, CREDITS } TitleParts;
typedef enum Result { LOST, WON } Result;

typedef struct Player {
    Rectangle bound;
    Vector2 pos;
    bool alive;
} Player;

typedef struct Obs {
} Obs;

#define DAY 1

int frameCount2 = 255;
void fadeOutBlack() {
    if (frameCount2 > 1) frameCount2 -= 2;
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){19, 30, 22, frameCount2});
}

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "RAYLIB_NEAT");

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

    Image background = LoadImage("server/game/assets/BACK.png");
    ImageFormat(&background, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    Texture background_img = LoadTextureFromImage(background);

    GameStage screen = LOGO;
    TitleParts part = START;
    int frameCount = 0;
    // int frameCount2 = 255;
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
                if (frameCount > 3 * FPS) {
                    screen = TITLE;
                    frameCount = 0;
                    frameCount2 = 255;
                }
            } break;

            case TITLE: {
                if (IsKeyPressed(KEY_P)) {
                    screen = GAMEPLAY;
                    frameCount2 = 255;
                }

                if (IsKeyPressed(KEY_X)) {
                    part = START;
                    frameCount2 = 255;
                }
                if (IsKeyPressed(KEY_S)) {
                    part = SETUP;
                    frameCount2 = 255;
                }
                if (IsKeyPressed(KEY_B)) {
                    part = BUILD_BY;
                    frameCount2 = 255;
                }
                if (IsKeyPressed(KEY_C)) {
                    part = CREDITS;
                    frameCount2 = 255;
                }
            } break;

            case GAMEPLAY: {
                frameCount++;
                frameTotal++;

                if (SPEED <= PLAYER_MAX_SPEED_SCALE) SPEED += 0.0003f;

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

                if (jumpFlag == 0 && player.pos.y < PLAYER_POS_Y) player.pos.y += 8;

            } break;

            case ENDING: {
            } break;

            default:
                break;
        }

        //====================================DRAWING==============================================

        BeginDrawing();
        ClearBackground((Color){19, 30, 22, 255});

        switch (screen) {
            case LOGO: {
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, LIGHTGRAY);
                char str[] = "ML Project Sem-2";

                if (frameCount % 120 <= 60)
                    DrawText(str, (SCREEN_WIDTH - MeasureText(str, 60)) / 2,
                             SCREEN_HEIGHT * 2 / 6, 60, WHITE);
                else
                    DrawText(str, (SCREEN_WIDTH - MeasureText(str, 60)) / 2,
                             SCREEN_HEIGHT * 2 / 6, 60, DARKGRAY);

                fadeOutBlack();
            } break;

            case TITLE: {
                switch (part) {
                    case START: {
                        char str_play[] = "Press P: Play";
                        char str_setup[] = "      S: Setup";
                        char str_build_by[] = "      B: Build_By";
                        char str_credit[] = "      C: Credits";

                        DrawTextureEx(background_img, (Vector2){0.0f, 0.0f}, 45.0f, 2.0f,
                                      BLUE);
                        int pos = (SCREEN_WIDTH - MeasureText(str_play, 30)) / 2;
                        int len = MeasureText(str_build_by, 30);

                        DrawRectangleGradientV((int)pos - 20 - 10, 300 - 20 - 10, len + 40,
                                               120 + 70, WHITE, DARKGRAY);
                        DrawRectangle((int)pos + 2 - 20 - 10, 300 + 2 - 20 - 10, len + 40 - 4,
                                      120 - 4 + 70, (Color){19, 30, 22, 255});

                        DrawRectangleGradientH((int)pos - 20, 300 - 20, len + 40, 120 + 70,
                                               WHITE, DARKGRAY);
                        DrawRectangle((int)pos + 2 - 20, 300 + 2 - 20, len + 40 - 4,
                                      120 - 4 + 70, (Color){19, 30, 22, 255});

                        DrawText(str_play, pos, 300, 30, WHITE);
                        DrawText(str_setup, pos, 340, 30, WHITE);
                        DrawText(str_build_by, pos, 380, 30, WHITE);
                        DrawText(str_credit, pos, 420, 30, WHITE);

                        fadeOutBlack();
                    } break;

                    case SETUP: {
                        DrawTextureRec(background_img,
                                       (Rectangle){100, 100, (float)SCREEN_WIDTH * 9 / 10,
                                                   (float)SCREEN_HEIGHT * 1 / 5},
                                       (Vector2){(float)SCREEN_WIDTH / 20, 20}, RED);
                        fadeOutBlack();
                    } break;

                    case BUILD_BY: {
                        DrawTextureRec(background_img,
                                       (Rectangle){200, 200, (float)SCREEN_WIDTH * 9 / 10,
                                                   (float)SCREEN_HEIGHT * 1 / 5},
                                       (Vector2){(float)SCREEN_WIDTH / 20, 20}, ORANGE);
                        fadeOutBlack();
                    } break;

                    case CREDITS: {
                        DrawTextureRec(background_img,
                                       (Rectangle){0, 300, (float)SCREEN_WIDTH * 9 / 10,
                                                   (float)SCREEN_HEIGHT * 1 / 5},
                                       (Vector2){(float)SCREEN_WIDTH / 20, 20}, VIOLET);
                        fadeOutBlack();
                    } break;

                    default:
                        break;
                }
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
                //     roller, (Rectangle){(float)roller.width/10, 0, (float)roller.width / 10,
                //     roller.height}, (Rectangle){SCREEN_WIDTH + scrollL5 + 50, PLAYER_POS_Y -
                //     15,
                //                 (float)roller.width / 10 * 0.2, roller.height * 0.2},
                //     (Vector2){0, 0}, 0.0f, WHITE);

                DrawTextureEx(day[5], (Vector2){scrollL5, 0}, 0.0f, scale, WHITE);
                DrawTextureEx(day[5], (Vector2){scrollL5 + SCREEN_WIDTH, 0}, 0.0f, scale,
                              WHITE);

                DrawFPS(30, 30);
                DrawText(TextFormat("SPEED %d%%",
                                    (int)((SPEED - 1) / (PLAYER_MAX_SPEED_SCALE - 1) * 100)),
                         130, 30, 20, BLACK);
                DrawText(TextFormat("TIME %d", frameTotal / FPS), 260, 30, 20, BLACK);

                fadeOutBlack();
            } break;

            case ENDING: {
                fadeOutBlack();
            } break;

            default:
                break;
        }
        EndDrawing();
    }

    for (int i = 0; i < 6; i++) UnloadTexture(day[i]);
    UnloadImage(background);
    UnloadTexture(background_img);
    UnloadTexture(player_run);
    UnloadTexture(player_jump);
    UnloadTexture(player_dead);
    UnloadTexture(roller);

    CloseWindow();
}
