#include "raylib.h"
#include <time.h>
int main() {
    const int screenWidth = 480;
    const int screenHeight = 640;
    InitWindow(screenWidth, screenHeight, "Skratchpad");
    RenderTexture2D render = LoadRenderTexture(screenWidth, screenHeight);
    Vector2 cachedMousePos;
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginTextureMode(render);
            if (IsCursorOnScreen() && IsMouseButtonPressed(0)) cachedMousePos = GetMousePosition();
            if (IsCursorOnScreen() && IsMouseButtonDown(0)) {
                Vector2 mousePos = GetMousePosition();
                    DrawLineEx(cachedMousePos, mousePos, 3.0, BLACK);
                cachedMousePos = mousePos;
            } else if (IsCursorOnScreen() && IsMouseButtonDown(1)) {
                Vector2 mousePos = GetMousePosition();
                DrawLineEx(cachedMousePos, mousePos, 9.0, WHITE);
                cachedMousePos = mousePos;
            }
            if (IsKeyPressed(KEY_BACKSPACE)) ClearBackground(WHITE);
        EndTextureMode();
        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
            struct tm* time;
            char filename[30];
            char* fileptr = filename;
            fileptr = asctime(time);
            fileptr[25] = '.'; fileptr[26] = 'p'; fileptr[27] = 'n'; fileptr[28] = 'g'; fileptr[29] = '\0';
            TakeScreenshot(fileptr);
        }
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTextureRec(render.texture, (Rectangle) {0, 0, screenWidth, -screenHeight}, (Vector2) {0,0}, WHITE);
        EndDrawing();
    }
    UnloadRenderTexture(render);
    CloseWindow();
    return 0;
}
