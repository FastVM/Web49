#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

int main() {
    SetTraceLogLevel(LOG_WARNING);
    InitWindow(512, 512, "Cool Window!");
    Color color = (Color) {
        .r = 0,
        .g = 0,
        .b = 0,
        .a = 255,
    };
    float t = 0;
    while (!WindowShouldClose()) {
        t += GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircle(256, 256, (sin(t) * 0.5 + 0.5) * 50 + 25, color);
        EndDrawing();
    }
    CloseWindow();
}