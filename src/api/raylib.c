#include "../interp/interp.h"
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
static web49_interp_data_t web49_api_runtime_InitWindow(web49_interp_t interp) {
  web49_interp_data_t ret;
  InitWindow(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (const char *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_WindowShouldClose(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) WindowShouldClose(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CloseWindow(web49_interp_t interp) {
  web49_interp_data_t ret;
  CloseWindow(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsWindowReady(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsWindowReady(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsWindowFullscreen(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsWindowFullscreen(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsWindowHidden(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsWindowHidden(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsWindowMinimized(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsWindowMinimized(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsWindowMaximized(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsWindowMaximized(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsWindowFocused(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsWindowFocused(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsWindowResized(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsWindowResized(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsWindowState(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsWindowState(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetWindowState(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetWindowState(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ClearWindowState(web49_interp_t interp) {
  web49_interp_data_t ret;
  ClearWindowState(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ToggleFullscreen(web49_interp_t interp) {
  web49_interp_data_t ret;
  ToggleFullscreen(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_MaximizeWindow(web49_interp_t interp) {
  web49_interp_data_t ret;
  MaximizeWindow(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_MinimizeWindow(web49_interp_t interp) {
  web49_interp_data_t ret;
  MinimizeWindow(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_RestoreWindow(web49_interp_t interp) {
  web49_interp_data_t ret;
  RestoreWindow(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetWindowIcon(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetWindowIcon(
    *(Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetWindowTitle(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetWindowTitle(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetWindowPosition(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetWindowPosition(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetWindowMonitor(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetWindowMonitor(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetWindowMinSize(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetWindowMinSize(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetWindowSize(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetWindowSize(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetWindowOpacity(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetWindowOpacity(
    (float) interp.locals[0].f32
  );
  return ret;
}
// returns ptr: GetWindowHandle
static web49_interp_data_t web49_api_runtime_GetScreenWidth(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetScreenWidth(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetScreenHeight(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetScreenHeight(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetRenderWidth(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetRenderWidth(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetRenderHeight(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetRenderHeight(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMonitorCount(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetMonitorCount(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetCurrentMonitor(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetCurrentMonitor(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMonitorPosition(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetMonitorPosition(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMonitorWidth(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetMonitorWidth(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMonitorHeight(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetMonitorHeight(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMonitorPhysicalWidth(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetMonitorPhysicalWidth(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMonitorPhysicalHeight(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetMonitorPhysicalHeight(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMonitorRefreshRate(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetMonitorRefreshRate(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetWindowPosition(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetWindowPosition(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetWindowScaleDPI(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetWindowScaleDPI(
  );
  return ret;
}
// returns ptr: GetMonitorName
static web49_interp_data_t web49_api_runtime_SetClipboardText(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetClipboardText(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
// returns ptr: GetClipboardText
static web49_interp_data_t web49_api_runtime_EnableEventWaiting(web49_interp_t interp) {
  web49_interp_data_t ret;
  EnableEventWaiting(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DisableEventWaiting(web49_interp_t interp) {
  web49_interp_data_t ret;
  DisableEventWaiting(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SwapScreenBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  SwapScreenBuffer(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_PollInputEvents(web49_interp_t interp) {
  web49_interp_data_t ret;
  PollInputEvents(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_WaitTime(web49_interp_t interp) {
  web49_interp_data_t ret;
  WaitTime(
    (double) interp.locals[0].f64
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ShowCursor(web49_interp_t interp) {
  web49_interp_data_t ret;
  ShowCursor(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_HideCursor(web49_interp_t interp) {
  web49_interp_data_t ret;
  HideCursor(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsCursorHidden(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsCursorHidden(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_EnableCursor(web49_interp_t interp) {
  web49_interp_data_t ret;
  EnableCursor(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DisableCursor(web49_interp_t interp) {
  web49_interp_data_t ret;
  DisableCursor(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsCursorOnScreen(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsCursorOnScreen(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ClearBackground(web49_interp_t interp) {
  web49_interp_data_t ret;
  ClearBackground(
    *(Color *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_BeginDrawing(web49_interp_t interp) {
  web49_interp_data_t ret;
  BeginDrawing(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_EndDrawing(web49_interp_t interp) {
  web49_interp_data_t ret;
  EndDrawing(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_BeginMode2D(web49_interp_t interp) {
  web49_interp_data_t ret;
  BeginMode2D(
    *(Camera2D *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_EndMode2D(web49_interp_t interp) {
  web49_interp_data_t ret;
  EndMode2D(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_BeginMode3D(web49_interp_t interp) {
  web49_interp_data_t ret;
  BeginMode3D(
    *(Camera3D *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_EndMode3D(web49_interp_t interp) {
  web49_interp_data_t ret;
  EndMode3D(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_BeginTextureMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  BeginTextureMode(
    *(RenderTexture2D *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_EndTextureMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  EndTextureMode(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_BeginShaderMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  BeginShaderMode(
    *(Shader *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_EndShaderMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  EndShaderMode(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_BeginBlendMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  BeginBlendMode(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_EndBlendMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  EndBlendMode(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_BeginScissorMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  BeginScissorMode(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_EndScissorMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  EndScissorMode(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_BeginVrStereoMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  BeginVrStereoMode(
    *(VrStereoConfig *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_EndVrStereoMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  EndVrStereoMode(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadVrStereoConfig(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(VrStereoConfig *) &interp.memory[interp.locals[0].i32_u] = LoadVrStereoConfig(
    *(VrDeviceInfo *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadVrStereoConfig(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadVrStereoConfig(
    *(VrStereoConfig *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadShader(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Shader *) &interp.memory[interp.locals[0].i32_u] = LoadShader(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadShaderFromMemory(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Shader *) &interp.memory[interp.locals[0].i32_u] = LoadShaderFromMemory(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetShaderLocation(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetShaderLocation(
    *(Shader *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetShaderLocationAttrib(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetShaderLocationAttrib(
    *(Shader *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetShaderValue(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetShaderValue(
    *(Shader *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (const void *) &interp.memory[interp.locals[2].i32_u],
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetShaderValueV(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetShaderValueV(
    *(Shader *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (const void *) &interp.memory[interp.locals[2].i32_u],
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetShaderValueMatrix(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetShaderValueMatrix(
    *(Shader *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    *(Matrix *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetShaderValueTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetShaderValueTexture(
    *(Shader *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    *(Texture2D *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadShader(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadShader(
    *(Shader *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMouseRay(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Ray *) &interp.memory[interp.locals[0].i32_u] = GetMouseRay(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Camera *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetCameraMatrix(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Matrix *) &interp.memory[interp.locals[0].i32_u] = GetCameraMatrix(
    *(Camera *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetCameraMatrix2D(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Matrix *) &interp.memory[interp.locals[0].i32_u] = GetCameraMatrix2D(
    *(Camera2D *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetWorldToScreen(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetWorldToScreen(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Camera *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetScreenToWorld2D(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetScreenToWorld2D(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Camera2D *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetWorldToScreenEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetWorldToScreenEx(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Camera *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetWorldToScreen2D(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetWorldToScreen2D(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Camera2D *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetTargetFPS(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetTargetFPS(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetFPS(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetFPS(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetFrameTime(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.f32 = (float) GetFrameTime(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetTime(web49_interp_t interp) {
  web49_interp_data_t ret;
  GetTime(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetRandomValue(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetRandomValue(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetRandomSeed(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetRandomSeed(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_TakeScreenshot(web49_interp_t interp) {
  web49_interp_data_t ret;
  TakeScreenshot(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetConfigFlags(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetConfigFlags(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
// is variadic: TraceLog
static web49_interp_data_t web49_api_runtime_SetTraceLogLevel(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetTraceLogLevel(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
// returns ptr: MemAlloc
// returns ptr: MemRealloc
static web49_interp_data_t web49_api_runtime_MemFree(web49_interp_t interp) {
  web49_interp_data_t ret;
  MemFree(
    (void *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_OpenURL(web49_interp_t interp) {
  web49_interp_data_t ret;
  OpenURL(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
// is callback: SetTraceLogCallback
// is callback: SetLoadFileDataCallback
// is callback: SetSaveFileDataCallback
// is callback: SetLoadFileTextCallback
// is callback: SetSaveFileTextCallback
// returns ptr: LoadFileData
static web49_interp_data_t web49_api_runtime_UnloadFileData(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadFileData(
    (unsigned char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SaveFileData(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) SaveFileData(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (void *) &interp.memory[interp.locals[1].i32_u],
    (unsigned int) interp.locals[2].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ExportDataAsCode(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) ExportDataAsCode(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (unsigned int) interp.locals[1].i32_u,
    (const char *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
// returns ptr: LoadFileText
static web49_interp_data_t web49_api_runtime_UnloadFileText(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadFileText(
    (char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SaveFileText(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) SaveFileText(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_FileExists(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) FileExists(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DirectoryExists(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) DirectoryExists(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsFileExtension(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsFileExtension(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetFileLength(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetFileLength(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
// returns ptr: GetFileExtension
// returns ptr: GetFileName
// returns ptr: GetFileNameWithoutExt
// returns ptr: GetDirectoryPath
// returns ptr: GetPrevDirectoryPath
// returns ptr: GetWorkingDirectory
// returns ptr: GetApplicationDirectory
static web49_interp_data_t web49_api_runtime_ChangeDirectory(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) ChangeDirectory(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsPathFile(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsPathFile(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadDirectoryFiles(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(FilePathList *) &interp.memory[interp.locals[0].i32_u] = LoadDirectoryFiles(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadDirectoryFilesEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(FilePathList *) &interp.memory[interp.locals[0].i32_u] = LoadDirectoryFilesEx(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u],
    (bool) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadDirectoryFiles(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadDirectoryFiles(
    *(FilePathList *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsFileDropped(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsFileDropped(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadDroppedFiles(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(FilePathList *) &interp.memory[interp.locals[0].i32_u] = LoadDroppedFiles(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadDroppedFiles(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadDroppedFiles(
    *(FilePathList *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetFileModTime(web49_interp_t interp) {
  web49_interp_data_t ret;
  GetFileModTime(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
// returns ptr: CompressData
// returns ptr: DecompressData
// returns ptr: EncodeDataBase64
// returns ptr: DecodeDataBase64
static web49_interp_data_t web49_api_runtime_IsKeyPressed(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsKeyPressed(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsKeyDown(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsKeyDown(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsKeyReleased(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsKeyReleased(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsKeyUp(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsKeyUp(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetExitKey(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetExitKey(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetKeyPressed(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetKeyPressed(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetCharPressed(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetCharPressed(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsGamepadAvailable(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsGamepadAvailable(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
// returns ptr: GetGamepadName
static web49_interp_data_t web49_api_runtime_IsGamepadButtonPressed(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsGamepadButtonPressed(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsGamepadButtonDown(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsGamepadButtonDown(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsGamepadButtonReleased(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsGamepadButtonReleased(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsGamepadButtonUp(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsGamepadButtonUp(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGamepadButtonPressed(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetGamepadButtonPressed(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGamepadAxisCount(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetGamepadAxisCount(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGamepadAxisMovement(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.f32 = (float) GetGamepadAxisMovement(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetGamepadMappings(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) SetGamepadMappings(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsMouseButtonPressed(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsMouseButtonPressed(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsMouseButtonDown(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsMouseButtonDown(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsMouseButtonReleased(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsMouseButtonReleased(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsMouseButtonUp(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsMouseButtonUp(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMouseX(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetMouseX(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMouseY(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetMouseY(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMousePosition(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetMousePosition(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMouseDelta(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetMouseDelta(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetMousePosition(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetMousePosition(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetMouseOffset(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetMouseOffset(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetMouseScale(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetMouseScale(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMouseWheelMove(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.f32 = (float) GetMouseWheelMove(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMouseWheelMoveV(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetMouseWheelMoveV(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetMouseCursor(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetMouseCursor(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetTouchX(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetTouchX(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetTouchY(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetTouchY(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetTouchPosition(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetTouchPosition(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetTouchPointId(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetTouchPointId(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetTouchPointCount(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetTouchPointCount(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetGesturesEnabled(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetGesturesEnabled(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsGestureDetected(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsGestureDetected(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGestureDetected(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetGestureDetected(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGestureHoldDuration(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.f32 = (float) GetGestureHoldDuration(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGestureDragVector(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetGestureDragVector(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGestureDragAngle(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.f32 = (float) GetGestureDragAngle(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGesturePinchVector(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = GetGesturePinchVector(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGesturePinchAngle(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.f32 = (float) GetGesturePinchAngle(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetCameraMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetCameraMode(
    *(Camera *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UpdateCamera(web49_interp_t interp) {
  web49_interp_data_t ret;
  UpdateCamera(
    (Camera *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetCameraPanControl(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetCameraPanControl(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetCameraAltControl(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetCameraAltControl(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetCameraSmoothZoomControl(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetCameraSmoothZoomControl(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetCameraMoveControls(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetCameraMoveControls(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s,
    (int) interp.locals[5].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetShapesTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetShapesTexture(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawPixel(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawPixel(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawPixelV(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawPixelV(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawLine(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawLine(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawLineV(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawLineV(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawLineEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawLineEx(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawLineBezier(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawLineBezier(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawLineBezierQuad(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawLineBezierQuad(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawLineBezierCubic(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawLineBezierCubic(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[3].i32_u],
    (float) interp.locals[4].f32,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawLineStrip(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawLineStrip(
    (Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCircle(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCircle(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCircleSector(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCircleSector(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCircleSectorLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCircleSectorLines(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCircleGradient(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCircleGradient(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32,
    *(Color *) &interp.memory[interp.locals[3].i32_u],
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCircleV(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCircleV(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCircleLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCircleLines(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawEllipse(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawEllipse(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawEllipseLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawEllipseLines(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRing(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRing(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (float) interp.locals[4].f32,
    (int) interp.locals[5].i32_s,
    *(Color *) &interp.memory[interp.locals[6].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRingLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRingLines(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (float) interp.locals[4].f32,
    (int) interp.locals[5].i32_s,
    *(Color *) &interp.memory[interp.locals[6].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangle(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangle(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangleV(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangleV(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangleRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangleRec(
    *(Rectangle *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectanglePro(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectanglePro(
    *(Rectangle *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangleGradientV(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangleGradientV(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u],
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangleGradientH(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangleGradientH(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u],
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangleGradientEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangleGradientEx(
    *(Rectangle *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u],
    *(Color *) &interp.memory[interp.locals[3].i32_u],
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangleLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangleLines(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangleLinesEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangleLinesEx(
    *(Rectangle *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangleRounded(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangleRounded(
    *(Rectangle *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (int) interp.locals[2].i32_s,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRectangleRoundedLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRectangleRoundedLines(
    *(Rectangle *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (int) interp.locals[2].i32_s,
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTriangle(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTriangle(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTriangleLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTriangleLines(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTriangleFan(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTriangleFan(
    (Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTriangleStrip(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTriangleStrip(
    (Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawPoly(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawPoly(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawPolyLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawPolyLines(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawPolyLinesEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawPolyLinesEx(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (float) interp.locals[4].f32,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionRecs(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionRecs(
    *(Rectangle *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionCircles(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionCircles(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionCircleRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionCircleRec(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    *(Rectangle *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionPointRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionPointRec(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionPointCircle(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionPointCircle(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionPointTriangle(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionPointTriangle(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionLines(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[3].i32_u],
    (Vector2 *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionPointLine(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionPointLine(
    *(Vector2 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetCollisionRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Rectangle *) &interp.memory[interp.locals[0].i32_u] = GetCollisionRec(
    *(Rectangle *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadImage(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = LoadImage(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadImageRaw(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = LoadImageRaw(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadImageAnim(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = LoadImageAnim(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (int *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadImageFromMemory(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = LoadImageFromMemory(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const unsigned char *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadImageFromTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = LoadImageFromTexture(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadImageFromScreen(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = LoadImageFromScreen(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadImage(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadImage(
    *(Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ExportImage(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) ExportImage(
    *(Image *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ExportImageAsCode(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) ExportImageAsCode(
    *(Image *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenImageColor(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = GenImageColor(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenImageGradientV(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = GenImageGradientV(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    *(Color *) &interp.memory[interp.locals[2].i32_u],
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenImageGradientH(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = GenImageGradientH(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    *(Color *) &interp.memory[interp.locals[2].i32_u],
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenImageGradientRadial(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = GenImageGradientRadial(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32,
    *(Color *) &interp.memory[interp.locals[3].i32_u],
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenImageChecked(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = GenImageChecked(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u],
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenImageWhiteNoise(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = GenImageWhiteNoise(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenImageCellular(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = GenImageCellular(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageCopy(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = ImageCopy(
    *(Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageFromImage(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = ImageFromImage(
    *(Image *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageText(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = ImageText(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageTextEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = ImageTextEx(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageFormat(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageFormat(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageToPOT(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageToPOT(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageCrop(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageCrop(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageAlphaCrop(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageAlphaCrop(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageAlphaClear(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageAlphaClear(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageAlphaMask(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageAlphaMask(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Image *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageAlphaPremultiply(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageAlphaPremultiply(
    (Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageResize(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageResize(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageResizeNN(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageResizeNN(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageResizeCanvas(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageResizeCanvas(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageMipmaps(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageMipmaps(
    (Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDither(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDither(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageFlipVertical(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageFlipVertical(
    (Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageFlipHorizontal(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageFlipHorizontal(
    (Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageRotateCW(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageRotateCW(
    (Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageRotateCCW(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageRotateCCW(
    (Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageColorTint(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageColorTint(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageColorInvert(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageColorInvert(
    (Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageColorGrayscale(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageColorGrayscale(
    (Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageColorContrast(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageColorContrast(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageColorBrightness(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageColorBrightness(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageColorReplace(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageColorReplace(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
// returns ptr: LoadImageColors
// returns ptr: LoadImagePalette
static web49_interp_data_t web49_api_runtime_UnloadImageColors(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadImageColors(
    (Color *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadImagePalette(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadImagePalette(
    (Color *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetImageAlphaBorder(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Rectangle *) &interp.memory[interp.locals[0].i32_u] = GetImageAlphaBorder(
    *(Image *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetImageColor(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Color *) &interp.memory[interp.locals[0].i32_u] = GetImageColor(
    *(Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageClearBackground(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageClearBackground(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawPixel(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawPixel(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawPixelV(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawPixelV(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawLine(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawLine(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawLineV(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawLineV(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawCircle(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawCircle(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawCircleV(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawCircleV(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawRectangle(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawRectangle(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawRectangleV(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawRectangleV(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawRectangleRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawRectangleRec(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawRectangleLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawRectangleLines(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDraw(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDraw(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Image *) &interp.memory[interp.locals[1].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[2].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[3].i32_u],
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawText(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawText(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ImageDrawTextEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  ImageDrawTextEx(
    (Image *) &interp.memory[interp.locals[0].i32_u],
    *(Font *) &interp.memory[interp.locals[1].i32_u],
    (const char *) &interp.memory[interp.locals[2].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[3].i32_u],
    (float) interp.locals[4].f32,
    (float) interp.locals[5].f32,
    *(Color *) &interp.memory[interp.locals[6].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Texture2D *) &interp.memory[interp.locals[0].i32_u] = LoadTexture(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadTextureFromImage(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Texture2D *) &interp.memory[interp.locals[0].i32_u] = LoadTextureFromImage(
    *(Image *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadTextureCubemap(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(TextureCubemap *) &interp.memory[interp.locals[0].i32_u] = LoadTextureCubemap(
    *(Image *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadRenderTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(RenderTexture2D *) &interp.memory[interp.locals[0].i32_u] = LoadRenderTexture(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadTexture(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadRenderTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadRenderTexture(
    *(RenderTexture2D *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UpdateTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  UpdateTexture(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    (const void *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UpdateTextureRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  UpdateTextureRec(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u],
    (const void *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenTextureMipmaps(web49_interp_t interp) {
  web49_interp_data_t ret;
  GenTextureMipmaps(
    (Texture2D *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetTextureFilter(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetTextureFilter(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetTextureWrap(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetTextureWrap(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTexture(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextureV(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextureV(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextureEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextureEx(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextureRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextureRec(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextureQuad(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextureQuad(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[3].i32_u],
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextureTiled(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextureTiled(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[2].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[3].i32_u],
    (float) interp.locals[4].f32,
    (float) interp.locals[5].f32,
    *(Color *) &interp.memory[interp.locals[6].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTexturePro(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTexturePro(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[2].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[3].i32_u],
    (float) interp.locals[4].f32,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextureNPatch(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextureNPatch(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(NPatchInfo *) &interp.memory[interp.locals[1].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[2].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[3].i32_u],
    (float) interp.locals[4].f32,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTexturePoly(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTexturePoly(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    (Vector2 *) &interp.memory[interp.locals[2].i32_u],
    (Vector2 *) &interp.memory[interp.locals[3].i32_u],
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_Fade(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Color *) &interp.memory[interp.locals[0].i32_u] = Fade(
    *(Color *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ColorToInt(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) ColorToInt(
    *(Color *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ColorNormalize(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector4 *) &interp.memory[interp.locals[0].i32_u] = ColorNormalize(
    *(Color *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ColorFromNormalized(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Color *) &interp.memory[interp.locals[0].i32_u] = ColorFromNormalized(
    *(Vector4 *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ColorToHSV(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector3 *) &interp.memory[interp.locals[0].i32_u] = ColorToHSV(
    *(Color *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ColorFromHSV(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Color *) &interp.memory[interp.locals[0].i32_u] = ColorFromHSV(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ColorAlpha(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Color *) &interp.memory[interp.locals[0].i32_u] = ColorAlpha(
    *(Color *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ColorAlphaBlend(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Color *) &interp.memory[interp.locals[0].i32_u] = ColorAlphaBlend(
    *(Color *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetColor(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Color *) &interp.memory[interp.locals[0].i32_u] = GetColor(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetPixelColor(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Color *) &interp.memory[interp.locals[0].i32_u] = GetPixelColor(
    (void *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetPixelColor(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetPixelColor(
    (void *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetPixelDataSize(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetPixelDataSize(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetFontDefault(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Font *) &interp.memory[interp.locals[0].i32_u] = GetFontDefault(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadFont(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Font *) &interp.memory[interp.locals[0].i32_u] = LoadFont(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadFontEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Font *) &interp.memory[interp.locals[0].i32_u] = LoadFontEx(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int *) &interp.memory[interp.locals[2].i32_u],
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadFontFromImage(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Font *) &interp.memory[interp.locals[0].i32_u] = LoadFontFromImage(
    *(Image *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadFontFromMemory(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Font *) &interp.memory[interp.locals[0].i32_u] = LoadFontFromMemory(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const unsigned char *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int *) &interp.memory[interp.locals[4].i32_u],
    (int) interp.locals[5].i32_s
  );
  return ret;
}
// returns ptr: LoadFontData
static web49_interp_data_t web49_api_runtime_GenImageFontAtlas(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Image *) &interp.memory[interp.locals[0].i32_u] = GenImageFontAtlas(
    (const GlyphInfo *) &interp.memory[interp.locals[0].i32_u],
    (Rectangle **) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s,
    (int) interp.locals[5].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadFontData(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadFontData(
    (GlyphInfo *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadFont(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadFont(
    *(Font *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ExportFontAsCode(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) ExportFontAsCode(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawFPS(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawFPS(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawText(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawText(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextEx(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32,
    (float) interp.locals[4].f32,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextPro(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextPro(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[3].i32_u],
    (float) interp.locals[4].f32,
    (float) interp.locals[5].f32,
    (float) interp.locals[6].f32,
    *(Color *) &interp.memory[interp.locals[7].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextCodepoint(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextCodepoint(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    *(Vector2 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTextCodepoints(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTextCodepoints(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (const int *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    *(Vector2 *) &interp.memory[interp.locals[3].i32_u],
    (float) interp.locals[4].f32,
    (float) interp.locals[5].f32,
    *(Color *) &interp.memory[interp.locals[6].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_MeasureText(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) MeasureText(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_MeasureTextEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Vector2 *) &interp.memory[interp.locals[0].i32_u] = MeasureTextEx(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGlyphIndex(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetGlyphIndex(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGlyphInfo(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(GlyphInfo *) &interp.memory[interp.locals[0].i32_u] = GetGlyphInfo(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetGlyphAtlasRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Rectangle *) &interp.memory[interp.locals[0].i32_u] = GetGlyphAtlasRec(
    *(Font *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
// returns ptr: LoadCodepoints
static web49_interp_data_t web49_api_runtime_UnloadCodepoints(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadCodepoints(
    (int *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetCodepointCount(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetCodepointCount(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetCodepoint(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetCodepoint(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (int *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
// returns ptr: CodepointToUTF8
// returns ptr: TextCodepointsToUTF8
static web49_interp_data_t web49_api_runtime_TextCopy(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) TextCopy(
    (char *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_TextIsEqual(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) TextIsEqual(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_TextLength(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) TextLength(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
// returns ptr: TextFormat
// is variadic: TextFormat
// returns ptr: TextSubtext
// returns ptr: TextReplace
// returns ptr: TextInsert
// returns ptr: TextJoin
// returns ptr: TextSplit
static web49_interp_data_t web49_api_runtime_TextAppend(web49_interp_t interp) {
  web49_interp_data_t ret;
  TextAppend(
    (char *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u],
    (int *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_TextFindIndex(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) TextFindIndex(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
// returns ptr: TextToUpper
// returns ptr: TextToLower
// returns ptr: TextToPascal
static web49_interp_data_t web49_api_runtime_TextToInteger(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) TextToInteger(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawLine3D(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawLine3D(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawPoint3D(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawPoint3D(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCircle3D(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCircle3D(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    *(Vector3 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTriangle3D(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTriangle3D(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[2].i32_u],
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawTriangleStrip3D(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawTriangleStrip3D(
    (Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCube(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCube(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCubeV(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCubeV(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCubeWires(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCubeWires(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCubeWiresV(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCubeWiresV(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCubeTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCubeTexture(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (float) interp.locals[4].f32,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCubeTextureRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCubeTextureRec(
    *(Texture2D *) &interp.memory[interp.locals[0].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[1].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32,
    (float) interp.locals[4].f32,
    (float) interp.locals[5].f32,
    *(Color *) &interp.memory[interp.locals[6].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawSphere(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawSphere(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawSphereEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawSphereEx(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawSphereWires(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawSphereWires(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCylinder(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCylinder(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCylinderEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCylinderEx(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCylinderWires(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCylinderWires(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawCylinderWiresEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawCylinderWiresEx(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32,
    (int) interp.locals[4].i32_s,
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawPlane(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawPlane(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[1].i32_u],
    *(Color *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawRay(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawRay(
    *(Ray *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawGrid(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawGrid(
    (int) interp.locals[0].i32_s,
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadModel(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Model *) &interp.memory[interp.locals[0].i32_u] = LoadModel(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadModelFromMesh(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Model *) &interp.memory[interp.locals[0].i32_u] = LoadModelFromMesh(
    *(Mesh *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadModel(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadModel(
    *(Model *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadModelKeepMeshes(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadModelKeepMeshes(
    *(Model *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetModelBoundingBox(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(BoundingBox *) &interp.memory[interp.locals[0].i32_u] = GetModelBoundingBox(
    *(Model *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawModel(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawModel(
    *(Model *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawModelEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawModelEx(
    *(Model *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32,
    *(Vector3 *) &interp.memory[interp.locals[4].i32_u],
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawModelWires(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawModelWires(
    *(Model *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32,
    *(Color *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawModelWiresEx(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawModelWiresEx(
    *(Model *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32,
    *(Vector3 *) &interp.memory[interp.locals[4].i32_u],
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawBoundingBox(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawBoundingBox(
    *(BoundingBox *) &interp.memory[interp.locals[0].i32_u],
    *(Color *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawBillboard(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawBillboard(
    *(Camera *) &interp.memory[interp.locals[0].i32_u],
    *(Texture2D *) &interp.memory[interp.locals[1].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32,
    *(Color *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawBillboardRec(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawBillboardRec(
    *(Camera *) &interp.memory[interp.locals[0].i32_u],
    *(Texture2D *) &interp.memory[interp.locals[1].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[2].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[3].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[4].i32_u],
    *(Color *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawBillboardPro(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawBillboardPro(
    *(Camera *) &interp.memory[interp.locals[0].i32_u],
    *(Texture2D *) &interp.memory[interp.locals[1].i32_u],
    *(Rectangle *) &interp.memory[interp.locals[2].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[3].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[4].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[5].i32_u],
    *(Vector2 *) &interp.memory[interp.locals[6].i32_u],
    (float) interp.locals[7].f32,
    *(Color *) &interp.memory[interp.locals[8].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UploadMesh(web49_interp_t interp) {
  web49_interp_data_t ret;
  UploadMesh(
    (Mesh *) &interp.memory[interp.locals[0].i32_u],
    (bool) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UpdateMeshBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  UpdateMeshBuffer(
    *(Mesh *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (const void *) &interp.memory[interp.locals[2].i32_u],
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadMesh(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadMesh(
    *(Mesh *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawMesh(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawMesh(
    *(Mesh *) &interp.memory[interp.locals[0].i32_u],
    *(Material *) &interp.memory[interp.locals[1].i32_u],
    *(Matrix *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_DrawMeshInstanced(web49_interp_t interp) {
  web49_interp_data_t ret;
  DrawMeshInstanced(
    *(Mesh *) &interp.memory[interp.locals[0].i32_u],
    *(Material *) &interp.memory[interp.locals[1].i32_u],
    (const Matrix *) &interp.memory[interp.locals[2].i32_u],
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ExportMesh(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) ExportMesh(
    *(Mesh *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMeshBoundingBox(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(BoundingBox *) &interp.memory[interp.locals[0].i32_u] = GetMeshBoundingBox(
    *(Mesh *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshTangents(web49_interp_t interp) {
  web49_interp_data_t ret;
  GenMeshTangents(
    (Mesh *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshPoly(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshPoly(
    (int) interp.locals[0].i32_s,
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshPlane(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshPlane(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshCube(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshCube(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshSphere(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshSphere(
    (float) interp.locals[0].f32,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshHemiSphere(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshHemiSphere(
    (float) interp.locals[0].f32,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshCylinder(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshCylinder(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshCone(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshCone(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshTorus(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshTorus(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshKnot(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshKnot(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshHeightmap(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshHeightmap(
    *(Image *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GenMeshCubicmap(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Mesh *) &interp.memory[interp.locals[0].i32_u] = GenMeshCubicmap(
    *(Image *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
// returns ptr: LoadMaterials
static web49_interp_data_t web49_api_runtime_LoadMaterialDefault(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Material *) &interp.memory[interp.locals[0].i32_u] = LoadMaterialDefault(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadMaterial(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadMaterial(
    *(Material *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetMaterialTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetMaterialTexture(
    (Material *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    *(Texture2D *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetModelMeshMaterial(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetModelMeshMaterial(
    (Model *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
// returns ptr: LoadModelAnimations
static web49_interp_data_t web49_api_runtime_UpdateModelAnimation(web49_interp_t interp) {
  web49_interp_data_t ret;
  UpdateModelAnimation(
    *(Model *) &interp.memory[interp.locals[0].i32_u],
    *(ModelAnimation *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadModelAnimation(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadModelAnimation(
    *(ModelAnimation *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadModelAnimations(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadModelAnimations(
    (ModelAnimation *) &interp.memory[interp.locals[0].i32_u],
    (unsigned int) interp.locals[1].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsModelAnimationValid(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsModelAnimationValid(
    *(Model *) &interp.memory[interp.locals[0].i32_u],
    *(ModelAnimation *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionSpheres(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionSpheres(
    *(Vector3 *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32,
    *(Vector3 *) &interp.memory[interp.locals[2].i32_u],
    (float) interp.locals[3].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionBoxes(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionBoxes(
    *(BoundingBox *) &interp.memory[interp.locals[0].i32_u],
    *(BoundingBox *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CheckCollisionBoxSphere(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) CheckCollisionBoxSphere(
    *(BoundingBox *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetRayCollisionSphere(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(RayCollision *) &interp.memory[interp.locals[0].i32_u] = GetRayCollisionSphere(
    *(Ray *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetRayCollisionBox(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(RayCollision *) &interp.memory[interp.locals[0].i32_u] = GetRayCollisionBox(
    *(Ray *) &interp.memory[interp.locals[0].i32_u],
    *(BoundingBox *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetRayCollisionMesh(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(RayCollision *) &interp.memory[interp.locals[0].i32_u] = GetRayCollisionMesh(
    *(Ray *) &interp.memory[interp.locals[0].i32_u],
    *(Mesh *) &interp.memory[interp.locals[1].i32_u],
    *(Matrix *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetRayCollisionTriangle(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(RayCollision *) &interp.memory[interp.locals[0].i32_u] = GetRayCollisionTriangle(
    *(Ray *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[2].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetRayCollisionQuad(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(RayCollision *) &interp.memory[interp.locals[0].i32_u] = GetRayCollisionQuad(
    *(Ray *) &interp.memory[interp.locals[0].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[1].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[2].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[3].i32_u],
    *(Vector3 *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_InitAudioDevice(web49_interp_t interp) {
  web49_interp_data_t ret;
  InitAudioDevice(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_CloseAudioDevice(web49_interp_t interp) {
  web49_interp_data_t ret;
  CloseAudioDevice(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsAudioDeviceReady(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsAudioDeviceReady(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetMasterVolume(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetMasterVolume(
    (float) interp.locals[0].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadWave(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Wave *) &interp.memory[interp.locals[0].i32_u] = LoadWave(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadWaveFromMemory(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Wave *) &interp.memory[interp.locals[0].i32_u] = LoadWaveFromMemory(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const unsigned char *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadSound(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Sound *) &interp.memory[interp.locals[0].i32_u] = LoadSound(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadSoundFromWave(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Sound *) &interp.memory[interp.locals[0].i32_u] = LoadSoundFromWave(
    *(Wave *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UpdateSound(web49_interp_t interp) {
  web49_interp_data_t ret;
  UpdateSound(
    *(Sound *) &interp.memory[interp.locals[0].i32_u],
    (const void *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadWave(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadWave(
    *(Wave *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadSound(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadSound(
    *(Sound *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ExportWave(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) ExportWave(
    *(Wave *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ExportWaveAsCode(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) ExportWaveAsCode(
    *(Wave *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_PlaySound(web49_interp_t interp) {
  web49_interp_data_t ret;
  PlaySound(
    *(Sound *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_StopSound(web49_interp_t interp) {
  web49_interp_data_t ret;
  StopSound(
    *(Sound *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_PauseSound(web49_interp_t interp) {
  web49_interp_data_t ret;
  PauseSound(
    *(Sound *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ResumeSound(web49_interp_t interp) {
  web49_interp_data_t ret;
  ResumeSound(
    *(Sound *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_PlaySoundMulti(web49_interp_t interp) {
  web49_interp_data_t ret;
  PlaySoundMulti(
    *(Sound *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_StopSoundMulti(web49_interp_t interp) {
  web49_interp_data_t ret;
  StopSoundMulti(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetSoundsPlaying(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) GetSoundsPlaying(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsSoundPlaying(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsSoundPlaying(
    *(Sound *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetSoundVolume(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetSoundVolume(
    *(Sound *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetSoundPitch(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetSoundPitch(
    *(Sound *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetSoundPan(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetSoundPan(
    *(Sound *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_WaveCopy(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Wave *) &interp.memory[interp.locals[0].i32_u] = WaveCopy(
    *(Wave *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_WaveCrop(web49_interp_t interp) {
  web49_interp_data_t ret;
  WaveCrop(
    (Wave *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_WaveFormat(web49_interp_t interp) {
  web49_interp_data_t ret;
  WaveFormat(
    (Wave *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
// returns ptr: LoadWaveSamples
static web49_interp_data_t web49_api_runtime_UnloadWaveSamples(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadWaveSamples(
    (float *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadMusicStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Music *) &interp.memory[interp.locals[0].i32_u] = LoadMusicStream(
    (const char *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadMusicStreamFromMemory(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Music *) &interp.memory[interp.locals[0].i32_u] = LoadMusicStreamFromMemory(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const unsigned char *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadMusicStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadMusicStream(
    *(Music *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_PlayMusicStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  PlayMusicStream(
    *(Music *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsMusicStreamPlaying(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsMusicStreamPlaying(
    *(Music *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UpdateMusicStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  UpdateMusicStream(
    *(Music *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_StopMusicStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  StopMusicStream(
    *(Music *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_PauseMusicStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  PauseMusicStream(
    *(Music *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ResumeMusicStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  ResumeMusicStream(
    *(Music *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SeekMusicStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  SeekMusicStream(
    *(Music *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetMusicVolume(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetMusicVolume(
    *(Music *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetMusicPitch(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetMusicPitch(
    *(Music *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetMusicPan(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetMusicPan(
    *(Music *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMusicTimeLength(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.f32 = (float) GetMusicTimeLength(
    *(Music *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_GetMusicTimePlayed(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.f32 = (float) GetMusicTimePlayed(
    *(Music *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_LoadAudioStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(AudioStream *) &interp.memory[interp.locals[0].i32_u] = LoadAudioStream(
    (unsigned int) interp.locals[0].i32_u,
    (unsigned int) interp.locals[1].i32_u,
    (unsigned int) interp.locals[2].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UnloadAudioStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  UnloadAudioStream(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_UpdateAudioStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  UpdateAudioStream(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u],
    (const void *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsAudioStreamProcessed(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsAudioStreamProcessed(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_PlayAudioStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  PlayAudioStream(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_PauseAudioStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  PauseAudioStream(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_ResumeAudioStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  ResumeAudioStream(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_IsAudioStreamPlaying(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) IsAudioStreamPlaying(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_StopAudioStream(web49_interp_t interp) {
  web49_interp_data_t ret;
  StopAudioStream(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetAudioStreamVolume(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetAudioStreamVolume(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetAudioStreamPitch(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetAudioStreamPitch(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetAudioStreamPan(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetAudioStreamPan(
    *(AudioStream *) &interp.memory[interp.locals[0].i32_u],
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_SetAudioStreamBufferSizeDefault(web49_interp_t interp) {
  web49_interp_data_t ret;
  SetAudioStreamBufferSizeDefault(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
// is callback: SetAudioStreamCallback
// is callback: AttachAudioStreamProcessor
// is callback: DetachAudioStreamProcessor
static web49_interp_data_t web49_api_runtime_rlMatrixMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlMatrixMode(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlPushMatrix(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlPushMatrix(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlPopMatrix(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlPopMatrix(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadIdentity(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlLoadIdentity(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlTranslatef(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlTranslatef(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlRotatef(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlRotatef(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlScalef(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlScalef(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlMultMatrixf(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlMultMatrixf(
    (float *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlFrustum(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlFrustum(
    (double) interp.locals[0].f64,
    (double) interp.locals[1].f64,
    (double) interp.locals[2].f64,
    (double) interp.locals[3].f64,
    (double) interp.locals[4].f64,
    (double) interp.locals[5].f64
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlOrtho(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlOrtho(
    (double) interp.locals[0].f64,
    (double) interp.locals[1].f64,
    (double) interp.locals[2].f64,
    (double) interp.locals[3].f64,
    (double) interp.locals[4].f64,
    (double) interp.locals[5].f64
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlViewport(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlViewport(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlBegin(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlBegin(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnd(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnd(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlVertex2i(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlVertex2i(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlVertex2f(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlVertex2f(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlVertex3f(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlVertex3f(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlTexCoord2f(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlTexCoord2f(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlNormal3f(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlNormal3f(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlColor4ub(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlColor4ub(
    (unsigned char) interp.locals[0].i32_u,
    (unsigned char) interp.locals[1].i32_u,
    (unsigned char) interp.locals[2].i32_u,
    (unsigned char) interp.locals[3].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlColor3f(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlColor3f(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlColor4f(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlColor4f(
    (float) interp.locals[0].f32,
    (float) interp.locals[1].f32,
    (float) interp.locals[2].f32,
    (float) interp.locals[3].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableVertexArray(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) rlEnableVertexArray(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableVertexArray(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableVertexArray(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableVertexBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableVertexBuffer(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableVertexBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableVertexBuffer(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableVertexBufferElement(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableVertexBufferElement(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableVertexBufferElement(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableVertexBufferElement(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableVertexAttribute(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableVertexAttribute(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableVertexAttribute(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableVertexAttribute(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlActiveTextureSlot(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlActiveTextureSlot(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableTexture(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableTexture(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableTextureCubemap(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableTextureCubemap(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableTextureCubemap(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableTextureCubemap(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlTextureParameters(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlTextureParameters(
    (unsigned int) interp.locals[0].i32_u,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableShader(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableShader(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableShader(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableShader(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableFramebuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableFramebuffer(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableFramebuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableFramebuffer(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlActiveDrawBuffers(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlActiveDrawBuffers(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableColorBlend(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableColorBlend(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableColorBlend(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableColorBlend(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableDepthTest(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableDepthTest(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableDepthTest(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableDepthTest(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableDepthMask(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableDepthMask(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableDepthMask(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableDepthMask(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableBackfaceCulling(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableBackfaceCulling(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableBackfaceCulling(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableBackfaceCulling(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableScissorTest(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableScissorTest(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableScissorTest(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableScissorTest(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlScissor(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlScissor(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableWireMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableWireMode(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableWireMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableWireMode(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetLineWidth(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetLineWidth(
    (float) interp.locals[0].f32
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetLineWidth(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.f32 = (float) rlGetLineWidth(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableSmoothLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableSmoothLines(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableSmoothLines(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableSmoothLines(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlEnableStereoRender(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlEnableStereoRender(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDisableStereoRender(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDisableStereoRender(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlIsStereoRenderEnabled(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) rlIsStereoRenderEnabled(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlClearColor(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlClearColor(
    (unsigned char) interp.locals[0].i32_u,
    (unsigned char) interp.locals[1].i32_u,
    (unsigned char) interp.locals[2].i32_u,
    (unsigned char) interp.locals[3].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlClearScreenBuffers(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlClearScreenBuffers(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlCheckErrors(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlCheckErrors(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetBlendMode(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetBlendMode(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetBlendFactors(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetBlendFactors(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlglInit(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlglInit(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlglClose(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlglClose(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadExtensions(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlLoadExtensions(
    (void *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetVersion(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) rlGetVersion(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetFramebufferWidth(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetFramebufferWidth(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetFramebufferWidth(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) rlGetFramebufferWidth(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetFramebufferHeight(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetFramebufferHeight(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetFramebufferHeight(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) rlGetFramebufferHeight(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetTextureIdDefault(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlGetTextureIdDefault(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetShaderIdDefault(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlGetShaderIdDefault(
  );
  return ret;
}
// returns ptr: rlGetShaderLocsDefault
static web49_interp_data_t web49_api_runtime_rlLoadRenderBatch(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlLoadRenderBatch(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUnloadRenderBatch(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUnloadRenderBatch(
    *(rlRenderBatch *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDrawRenderBatch(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDrawRenderBatch(
    (rlRenderBatch *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetRenderBatchActive(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetRenderBatchActive(
    (rlRenderBatch *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDrawRenderBatchActive(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDrawRenderBatchActive(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlCheckRenderBatchLimit(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) rlCheckRenderBatchLimit(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetTexture(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadVertexArray(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadVertexArray(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadVertexBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadVertexBuffer(
    (const void *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (bool) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadVertexBufferElement(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadVertexBufferElement(
    (const void *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (bool) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUpdateVertexBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUpdateVertexBuffer(
    (unsigned int) interp.locals[0].i32_u,
    (const void *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUpdateVertexBufferElements(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUpdateVertexBufferElements(
    (unsigned int) interp.locals[0].i32_u,
    (const void *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUnloadVertexArray(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUnloadVertexArray(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUnloadVertexBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUnloadVertexBuffer(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetVertexAttribute(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetVertexAttribute(
    (unsigned int) interp.locals[0].i32_u,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (bool) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s,
    (const void *) &interp.memory[interp.locals[5].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetVertexAttributeDivisor(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetVertexAttributeDivisor(
    (unsigned int) interp.locals[0].i32_u,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetVertexAttributeDefault(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetVertexAttributeDefault(
    (int) interp.locals[0].i32_s,
    (const void *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDrawVertexArray(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDrawVertexArray(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDrawVertexArrayElements(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDrawVertexArrayElements(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (const void *) &interp.memory[interp.locals[2].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDrawVertexArrayInstanced(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDrawVertexArrayInstanced(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlDrawVertexArrayElementsInstanced(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlDrawVertexArrayElementsInstanced(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (const void *) &interp.memory[interp.locals[2].i32_u],
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadTexture(
    (const void *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadTextureDepth(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadTextureDepth(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s,
    (bool) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadTextureCubemap(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadTextureCubemap(
    (const void *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUpdateTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUpdateTexture(
    (unsigned int) interp.locals[0].i32_u,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s,
    (int) interp.locals[5].i32_s,
    (const void *) &interp.memory[interp.locals[6].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetGlTextureFormats(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlGetGlTextureFormats(
    (int) interp.locals[0].i32_s,
    (unsigned int *) &interp.memory[interp.locals[1].i32_u],
    (unsigned int *) &interp.memory[interp.locals[2].i32_u],
    (unsigned int *) &interp.memory[interp.locals[3].i32_u]
  );
  return ret;
}
// returns ptr: rlGetPixelFormatName
static web49_interp_data_t web49_api_runtime_rlUnloadTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUnloadTexture(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGenTextureMipmaps(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlGenTextureMipmaps(
    (unsigned int) interp.locals[0].i32_u,
    (int) interp.locals[1].i32_s,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int *) &interp.memory[interp.locals[4].i32_u]
  );
  return ret;
}
// returns ptr: rlReadTexturePixels
// returns ptr: rlReadScreenPixels
static web49_interp_data_t web49_api_runtime_rlLoadFramebuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadFramebuffer(
    (int) interp.locals[0].i32_s,
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlFramebufferAttach(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlFramebufferAttach(
    (unsigned int) interp.locals[0].i32_u,
    (unsigned int) interp.locals[1].i32_u,
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s,
    (int) interp.locals[4].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlFramebufferComplete(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) rlFramebufferComplete(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUnloadFramebuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUnloadFramebuffer(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadShaderCode(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadShaderCode(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlCompileShader(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlCompileShader(
    (const char *) &interp.memory[interp.locals[0].i32_u],
    (int) interp.locals[1].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadShaderProgram(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadShaderProgram(
    (unsigned int) interp.locals[0].i32_u,
    (unsigned int) interp.locals[1].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUnloadShaderProgram(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUnloadShaderProgram(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetLocationUniform(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) rlGetLocationUniform(
    (unsigned int) interp.locals[0].i32_u,
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetLocationAttrib(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_s = (int32_t) rlGetLocationAttrib(
    (unsigned int) interp.locals[0].i32_u,
    (const char *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetUniform(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetUniform(
    (int) interp.locals[0].i32_s,
    (const void *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetUniformMatrix(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetUniformMatrix(
    (int) interp.locals[0].i32_s,
    *(Matrix *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetUniformSampler(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetUniformSampler(
    (int) interp.locals[0].i32_s,
    (unsigned int) interp.locals[1].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetShader(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetShader(
    (unsigned int) interp.locals[0].i32_u,
    (int *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadComputeShaderProgram(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadComputeShaderProgram(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlComputeShaderDispatch(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlComputeShaderDispatch(
    (unsigned int) interp.locals[0].i32_u,
    (unsigned int) interp.locals[1].i32_u,
    (unsigned int) interp.locals[2].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadShaderBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  ret.i32_u = (uint32_t) rlLoadShaderBuffer(
    (unsigned long long) interp.locals[0].i64_u,
    (const void *) &interp.memory[interp.locals[1].i32_u],
    (int) interp.locals[2].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUnloadShaderBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUnloadShaderBuffer(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlUpdateShaderBufferElements(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlUpdateShaderBufferElements(
    (unsigned int) interp.locals[0].i32_u,
    (const void *) &interp.memory[interp.locals[1].i32_u],
    (unsigned long long) interp.locals[2].i64_u,
    (unsigned long long) interp.locals[3].i64_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetShaderBufferSize(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlGetShaderBufferSize(
    (unsigned int) interp.locals[0].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlReadShaderBufferElements(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlReadShaderBufferElements(
    (unsigned int) interp.locals[0].i32_u,
    (void *) &interp.memory[interp.locals[1].i32_u],
    (unsigned long long) interp.locals[2].i64_u,
    (unsigned long long) interp.locals[3].i64_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlBindShaderBuffer(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlBindShaderBuffer(
    (unsigned int) interp.locals[0].i32_u,
    (unsigned int) interp.locals[1].i32_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlCopyBuffersElements(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlCopyBuffersElements(
    (unsigned int) interp.locals[0].i32_u,
    (unsigned int) interp.locals[1].i32_u,
    (unsigned long long) interp.locals[2].i64_u,
    (unsigned long long) interp.locals[3].i64_u,
    (unsigned long long) interp.locals[4].i64_u
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlBindImageTexture(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlBindImageTexture(
    (unsigned int) interp.locals[0].i32_u,
    (unsigned int) interp.locals[1].i32_u,
    (unsigned int) interp.locals[2].i32_u,
    (int) interp.locals[3].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetMatrixModelview(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Matrix *) &interp.memory[interp.locals[0].i32_u] = rlGetMatrixModelview(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetMatrixProjection(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Matrix *) &interp.memory[interp.locals[0].i32_u] = rlGetMatrixProjection(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetMatrixTransform(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Matrix *) &interp.memory[interp.locals[0].i32_u] = rlGetMatrixTransform(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetMatrixProjectionStereo(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Matrix *) &interp.memory[interp.locals[0].i32_u] = rlGetMatrixProjectionStereo(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlGetMatrixViewOffsetStereo(web49_interp_t interp) {
  web49_interp_data_t ret;
  *(Matrix *) &interp.memory[interp.locals[0].i32_u] = rlGetMatrixViewOffsetStereo(
    (int) interp.locals[0].i32_s
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetMatrixProjection(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetMatrixProjection(
    *(Matrix *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetMatrixModelview(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetMatrixModelview(
    *(Matrix *) &interp.memory[interp.locals[0].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetMatrixProjectionStereo(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetMatrixProjectionStereo(
    *(Matrix *) &interp.memory[interp.locals[0].i32_u],
    *(Matrix *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlSetMatrixViewOffsetStereo(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlSetMatrixViewOffsetStereo(
    *(Matrix *) &interp.memory[interp.locals[0].i32_u],
    *(Matrix *) &interp.memory[interp.locals[1].i32_u]
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadDrawCube(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlLoadDrawCube(
  );
  return ret;
}
static web49_interp_data_t web49_api_runtime_rlLoadDrawQuad(web49_interp_t interp) {
  web49_interp_data_t ret;
  rlLoadDrawQuad(
  );
  return ret;
}
web49_env_func_t web49_api_import_raylib(const char *name) {
  if (!strcmp(name, "InitWindow")) {
    return &web49_api_runtime_InitWindow;
  }
  if (!strcmp(name, "WindowShouldClose")) {
    return &web49_api_runtime_WindowShouldClose;
  }
  if (!strcmp(name, "CloseWindow")) {
    return &web49_api_runtime_CloseWindow;
  }
  if (!strcmp(name, "IsWindowReady")) {
    return &web49_api_runtime_IsWindowReady;
  }
  if (!strcmp(name, "IsWindowFullscreen")) {
    return &web49_api_runtime_IsWindowFullscreen;
  }
  if (!strcmp(name, "IsWindowHidden")) {
    return &web49_api_runtime_IsWindowHidden;
  }
  if (!strcmp(name, "IsWindowMinimized")) {
    return &web49_api_runtime_IsWindowMinimized;
  }
  if (!strcmp(name, "IsWindowMaximized")) {
    return &web49_api_runtime_IsWindowMaximized;
  }
  if (!strcmp(name, "IsWindowFocused")) {
    return &web49_api_runtime_IsWindowFocused;
  }
  if (!strcmp(name, "IsWindowResized")) {
    return &web49_api_runtime_IsWindowResized;
  }
  if (!strcmp(name, "IsWindowState")) {
    return &web49_api_runtime_IsWindowState;
  }
  if (!strcmp(name, "SetWindowState")) {
    return &web49_api_runtime_SetWindowState;
  }
  if (!strcmp(name, "ClearWindowState")) {
    return &web49_api_runtime_ClearWindowState;
  }
  if (!strcmp(name, "ToggleFullscreen")) {
    return &web49_api_runtime_ToggleFullscreen;
  }
  if (!strcmp(name, "MaximizeWindow")) {
    return &web49_api_runtime_MaximizeWindow;
  }
  if (!strcmp(name, "MinimizeWindow")) {
    return &web49_api_runtime_MinimizeWindow;
  }
  if (!strcmp(name, "RestoreWindow")) {
    return &web49_api_runtime_RestoreWindow;
  }
  if (!strcmp(name, "SetWindowIcon")) {
    return &web49_api_runtime_SetWindowIcon;
  }
  if (!strcmp(name, "SetWindowTitle")) {
    return &web49_api_runtime_SetWindowTitle;
  }
  if (!strcmp(name, "SetWindowPosition")) {
    return &web49_api_runtime_SetWindowPosition;
  }
  if (!strcmp(name, "SetWindowMonitor")) {
    return &web49_api_runtime_SetWindowMonitor;
  }
  if (!strcmp(name, "SetWindowMinSize")) {
    return &web49_api_runtime_SetWindowMinSize;
  }
  if (!strcmp(name, "SetWindowSize")) {
    return &web49_api_runtime_SetWindowSize;
  }
  if (!strcmp(name, "SetWindowOpacity")) {
    return &web49_api_runtime_SetWindowOpacity;
  }
  if (!strcmp(name, "GetScreenWidth")) {
    return &web49_api_runtime_GetScreenWidth;
  }
  if (!strcmp(name, "GetScreenHeight")) {
    return &web49_api_runtime_GetScreenHeight;
  }
  if (!strcmp(name, "GetRenderWidth")) {
    return &web49_api_runtime_GetRenderWidth;
  }
  if (!strcmp(name, "GetRenderHeight")) {
    return &web49_api_runtime_GetRenderHeight;
  }
  if (!strcmp(name, "GetMonitorCount")) {
    return &web49_api_runtime_GetMonitorCount;
  }
  if (!strcmp(name, "GetCurrentMonitor")) {
    return &web49_api_runtime_GetCurrentMonitor;
  }
  if (!strcmp(name, "GetMonitorPosition")) {
    return &web49_api_runtime_GetMonitorPosition;
  }
  if (!strcmp(name, "GetMonitorWidth")) {
    return &web49_api_runtime_GetMonitorWidth;
  }
  if (!strcmp(name, "GetMonitorHeight")) {
    return &web49_api_runtime_GetMonitorHeight;
  }
  if (!strcmp(name, "GetMonitorPhysicalWidth")) {
    return &web49_api_runtime_GetMonitorPhysicalWidth;
  }
  if (!strcmp(name, "GetMonitorPhysicalHeight")) {
    return &web49_api_runtime_GetMonitorPhysicalHeight;
  }
  if (!strcmp(name, "GetMonitorRefreshRate")) {
    return &web49_api_runtime_GetMonitorRefreshRate;
  }
  if (!strcmp(name, "GetWindowPosition")) {
    return &web49_api_runtime_GetWindowPosition;
  }
  if (!strcmp(name, "GetWindowScaleDPI")) {
    return &web49_api_runtime_GetWindowScaleDPI;
  }
  if (!strcmp(name, "SetClipboardText")) {
    return &web49_api_runtime_SetClipboardText;
  }
  if (!strcmp(name, "EnableEventWaiting")) {
    return &web49_api_runtime_EnableEventWaiting;
  }
  if (!strcmp(name, "DisableEventWaiting")) {
    return &web49_api_runtime_DisableEventWaiting;
  }
  if (!strcmp(name, "SwapScreenBuffer")) {
    return &web49_api_runtime_SwapScreenBuffer;
  }
  if (!strcmp(name, "PollInputEvents")) {
    return &web49_api_runtime_PollInputEvents;
  }
  if (!strcmp(name, "WaitTime")) {
    return &web49_api_runtime_WaitTime;
  }
  if (!strcmp(name, "ShowCursor")) {
    return &web49_api_runtime_ShowCursor;
  }
  if (!strcmp(name, "HideCursor")) {
    return &web49_api_runtime_HideCursor;
  }
  if (!strcmp(name, "IsCursorHidden")) {
    return &web49_api_runtime_IsCursorHidden;
  }
  if (!strcmp(name, "EnableCursor")) {
    return &web49_api_runtime_EnableCursor;
  }
  if (!strcmp(name, "DisableCursor")) {
    return &web49_api_runtime_DisableCursor;
  }
  if (!strcmp(name, "IsCursorOnScreen")) {
    return &web49_api_runtime_IsCursorOnScreen;
  }
  if (!strcmp(name, "ClearBackground")) {
    return &web49_api_runtime_ClearBackground;
  }
  if (!strcmp(name, "BeginDrawing")) {
    return &web49_api_runtime_BeginDrawing;
  }
  if (!strcmp(name, "EndDrawing")) {
    return &web49_api_runtime_EndDrawing;
  }
  if (!strcmp(name, "BeginMode2D")) {
    return &web49_api_runtime_BeginMode2D;
  }
  if (!strcmp(name, "EndMode2D")) {
    return &web49_api_runtime_EndMode2D;
  }
  if (!strcmp(name, "BeginMode3D")) {
    return &web49_api_runtime_BeginMode3D;
  }
  if (!strcmp(name, "EndMode3D")) {
    return &web49_api_runtime_EndMode3D;
  }
  if (!strcmp(name, "BeginTextureMode")) {
    return &web49_api_runtime_BeginTextureMode;
  }
  if (!strcmp(name, "EndTextureMode")) {
    return &web49_api_runtime_EndTextureMode;
  }
  if (!strcmp(name, "BeginShaderMode")) {
    return &web49_api_runtime_BeginShaderMode;
  }
  if (!strcmp(name, "EndShaderMode")) {
    return &web49_api_runtime_EndShaderMode;
  }
  if (!strcmp(name, "BeginBlendMode")) {
    return &web49_api_runtime_BeginBlendMode;
  }
  if (!strcmp(name, "EndBlendMode")) {
    return &web49_api_runtime_EndBlendMode;
  }
  if (!strcmp(name, "BeginScissorMode")) {
    return &web49_api_runtime_BeginScissorMode;
  }
  if (!strcmp(name, "EndScissorMode")) {
    return &web49_api_runtime_EndScissorMode;
  }
  if (!strcmp(name, "BeginVrStereoMode")) {
    return &web49_api_runtime_BeginVrStereoMode;
  }
  if (!strcmp(name, "EndVrStereoMode")) {
    return &web49_api_runtime_EndVrStereoMode;
  }
  if (!strcmp(name, "LoadVrStereoConfig")) {
    return &web49_api_runtime_LoadVrStereoConfig;
  }
  if (!strcmp(name, "UnloadVrStereoConfig")) {
    return &web49_api_runtime_UnloadVrStereoConfig;
  }
  if (!strcmp(name, "LoadShader")) {
    return &web49_api_runtime_LoadShader;
  }
  if (!strcmp(name, "LoadShaderFromMemory")) {
    return &web49_api_runtime_LoadShaderFromMemory;
  }
  if (!strcmp(name, "GetShaderLocation")) {
    return &web49_api_runtime_GetShaderLocation;
  }
  if (!strcmp(name, "GetShaderLocationAttrib")) {
    return &web49_api_runtime_GetShaderLocationAttrib;
  }
  if (!strcmp(name, "SetShaderValue")) {
    return &web49_api_runtime_SetShaderValue;
  }
  if (!strcmp(name, "SetShaderValueV")) {
    return &web49_api_runtime_SetShaderValueV;
  }
  if (!strcmp(name, "SetShaderValueMatrix")) {
    return &web49_api_runtime_SetShaderValueMatrix;
  }
  if (!strcmp(name, "SetShaderValueTexture")) {
    return &web49_api_runtime_SetShaderValueTexture;
  }
  if (!strcmp(name, "UnloadShader")) {
    return &web49_api_runtime_UnloadShader;
  }
  if (!strcmp(name, "GetMouseRay")) {
    return &web49_api_runtime_GetMouseRay;
  }
  if (!strcmp(name, "GetCameraMatrix")) {
    return &web49_api_runtime_GetCameraMatrix;
  }
  if (!strcmp(name, "GetCameraMatrix2D")) {
    return &web49_api_runtime_GetCameraMatrix2D;
  }
  if (!strcmp(name, "GetWorldToScreen")) {
    return &web49_api_runtime_GetWorldToScreen;
  }
  if (!strcmp(name, "GetScreenToWorld2D")) {
    return &web49_api_runtime_GetScreenToWorld2D;
  }
  if (!strcmp(name, "GetWorldToScreenEx")) {
    return &web49_api_runtime_GetWorldToScreenEx;
  }
  if (!strcmp(name, "GetWorldToScreen2D")) {
    return &web49_api_runtime_GetWorldToScreen2D;
  }
  if (!strcmp(name, "SetTargetFPS")) {
    return &web49_api_runtime_SetTargetFPS;
  }
  if (!strcmp(name, "GetFPS")) {
    return &web49_api_runtime_GetFPS;
  }
  if (!strcmp(name, "GetFrameTime")) {
    return &web49_api_runtime_GetFrameTime;
  }
  if (!strcmp(name, "GetTime")) {
    return &web49_api_runtime_GetTime;
  }
  if (!strcmp(name, "GetRandomValue")) {
    return &web49_api_runtime_GetRandomValue;
  }
  if (!strcmp(name, "SetRandomSeed")) {
    return &web49_api_runtime_SetRandomSeed;
  }
  if (!strcmp(name, "TakeScreenshot")) {
    return &web49_api_runtime_TakeScreenshot;
  }
  if (!strcmp(name, "SetConfigFlags")) {
    return &web49_api_runtime_SetConfigFlags;
  }
  if (!strcmp(name, "SetTraceLogLevel")) {
    return &web49_api_runtime_SetTraceLogLevel;
  }
  if (!strcmp(name, "MemFree")) {
    return &web49_api_runtime_MemFree;
  }
  if (!strcmp(name, "OpenURL")) {
    return &web49_api_runtime_OpenURL;
  }
  if (!strcmp(name, "UnloadFileData")) {
    return &web49_api_runtime_UnloadFileData;
  }
  if (!strcmp(name, "SaveFileData")) {
    return &web49_api_runtime_SaveFileData;
  }
  if (!strcmp(name, "ExportDataAsCode")) {
    return &web49_api_runtime_ExportDataAsCode;
  }
  if (!strcmp(name, "UnloadFileText")) {
    return &web49_api_runtime_UnloadFileText;
  }
  if (!strcmp(name, "SaveFileText")) {
    return &web49_api_runtime_SaveFileText;
  }
  if (!strcmp(name, "FileExists")) {
    return &web49_api_runtime_FileExists;
  }
  if (!strcmp(name, "DirectoryExists")) {
    return &web49_api_runtime_DirectoryExists;
  }
  if (!strcmp(name, "IsFileExtension")) {
    return &web49_api_runtime_IsFileExtension;
  }
  if (!strcmp(name, "GetFileLength")) {
    return &web49_api_runtime_GetFileLength;
  }
  if (!strcmp(name, "ChangeDirectory")) {
    return &web49_api_runtime_ChangeDirectory;
  }
  if (!strcmp(name, "IsPathFile")) {
    return &web49_api_runtime_IsPathFile;
  }
  if (!strcmp(name, "LoadDirectoryFiles")) {
    return &web49_api_runtime_LoadDirectoryFiles;
  }
  if (!strcmp(name, "LoadDirectoryFilesEx")) {
    return &web49_api_runtime_LoadDirectoryFilesEx;
  }
  if (!strcmp(name, "UnloadDirectoryFiles")) {
    return &web49_api_runtime_UnloadDirectoryFiles;
  }
  if (!strcmp(name, "IsFileDropped")) {
    return &web49_api_runtime_IsFileDropped;
  }
  if (!strcmp(name, "LoadDroppedFiles")) {
    return &web49_api_runtime_LoadDroppedFiles;
  }
  if (!strcmp(name, "UnloadDroppedFiles")) {
    return &web49_api_runtime_UnloadDroppedFiles;
  }
  if (!strcmp(name, "GetFileModTime")) {
    return &web49_api_runtime_GetFileModTime;
  }
  if (!strcmp(name, "IsKeyPressed")) {
    return &web49_api_runtime_IsKeyPressed;
  }
  if (!strcmp(name, "IsKeyDown")) {
    return &web49_api_runtime_IsKeyDown;
  }
  if (!strcmp(name, "IsKeyReleased")) {
    return &web49_api_runtime_IsKeyReleased;
  }
  if (!strcmp(name, "IsKeyUp")) {
    return &web49_api_runtime_IsKeyUp;
  }
  if (!strcmp(name, "SetExitKey")) {
    return &web49_api_runtime_SetExitKey;
  }
  if (!strcmp(name, "GetKeyPressed")) {
    return &web49_api_runtime_GetKeyPressed;
  }
  if (!strcmp(name, "GetCharPressed")) {
    return &web49_api_runtime_GetCharPressed;
  }
  if (!strcmp(name, "IsGamepadAvailable")) {
    return &web49_api_runtime_IsGamepadAvailable;
  }
  if (!strcmp(name, "IsGamepadButtonPressed")) {
    return &web49_api_runtime_IsGamepadButtonPressed;
  }
  if (!strcmp(name, "IsGamepadButtonDown")) {
    return &web49_api_runtime_IsGamepadButtonDown;
  }
  if (!strcmp(name, "IsGamepadButtonReleased")) {
    return &web49_api_runtime_IsGamepadButtonReleased;
  }
  if (!strcmp(name, "IsGamepadButtonUp")) {
    return &web49_api_runtime_IsGamepadButtonUp;
  }
  if (!strcmp(name, "GetGamepadButtonPressed")) {
    return &web49_api_runtime_GetGamepadButtonPressed;
  }
  if (!strcmp(name, "GetGamepadAxisCount")) {
    return &web49_api_runtime_GetGamepadAxisCount;
  }
  if (!strcmp(name, "GetGamepadAxisMovement")) {
    return &web49_api_runtime_GetGamepadAxisMovement;
  }
  if (!strcmp(name, "SetGamepadMappings")) {
    return &web49_api_runtime_SetGamepadMappings;
  }
  if (!strcmp(name, "IsMouseButtonPressed")) {
    return &web49_api_runtime_IsMouseButtonPressed;
  }
  if (!strcmp(name, "IsMouseButtonDown")) {
    return &web49_api_runtime_IsMouseButtonDown;
  }
  if (!strcmp(name, "IsMouseButtonReleased")) {
    return &web49_api_runtime_IsMouseButtonReleased;
  }
  if (!strcmp(name, "IsMouseButtonUp")) {
    return &web49_api_runtime_IsMouseButtonUp;
  }
  if (!strcmp(name, "GetMouseX")) {
    return &web49_api_runtime_GetMouseX;
  }
  if (!strcmp(name, "GetMouseY")) {
    return &web49_api_runtime_GetMouseY;
  }
  if (!strcmp(name, "GetMousePosition")) {
    return &web49_api_runtime_GetMousePosition;
  }
  if (!strcmp(name, "GetMouseDelta")) {
    return &web49_api_runtime_GetMouseDelta;
  }
  if (!strcmp(name, "SetMousePosition")) {
    return &web49_api_runtime_SetMousePosition;
  }
  if (!strcmp(name, "SetMouseOffset")) {
    return &web49_api_runtime_SetMouseOffset;
  }
  if (!strcmp(name, "SetMouseScale")) {
    return &web49_api_runtime_SetMouseScale;
  }
  if (!strcmp(name, "GetMouseWheelMove")) {
    return &web49_api_runtime_GetMouseWheelMove;
  }
  if (!strcmp(name, "GetMouseWheelMoveV")) {
    return &web49_api_runtime_GetMouseWheelMoveV;
  }
  if (!strcmp(name, "SetMouseCursor")) {
    return &web49_api_runtime_SetMouseCursor;
  }
  if (!strcmp(name, "GetTouchX")) {
    return &web49_api_runtime_GetTouchX;
  }
  if (!strcmp(name, "GetTouchY")) {
    return &web49_api_runtime_GetTouchY;
  }
  if (!strcmp(name, "GetTouchPosition")) {
    return &web49_api_runtime_GetTouchPosition;
  }
  if (!strcmp(name, "GetTouchPointId")) {
    return &web49_api_runtime_GetTouchPointId;
  }
  if (!strcmp(name, "GetTouchPointCount")) {
    return &web49_api_runtime_GetTouchPointCount;
  }
  if (!strcmp(name, "SetGesturesEnabled")) {
    return &web49_api_runtime_SetGesturesEnabled;
  }
  if (!strcmp(name, "IsGestureDetected")) {
    return &web49_api_runtime_IsGestureDetected;
  }
  if (!strcmp(name, "GetGestureDetected")) {
    return &web49_api_runtime_GetGestureDetected;
  }
  if (!strcmp(name, "GetGestureHoldDuration")) {
    return &web49_api_runtime_GetGestureHoldDuration;
  }
  if (!strcmp(name, "GetGestureDragVector")) {
    return &web49_api_runtime_GetGestureDragVector;
  }
  if (!strcmp(name, "GetGestureDragAngle")) {
    return &web49_api_runtime_GetGestureDragAngle;
  }
  if (!strcmp(name, "GetGesturePinchVector")) {
    return &web49_api_runtime_GetGesturePinchVector;
  }
  if (!strcmp(name, "GetGesturePinchAngle")) {
    return &web49_api_runtime_GetGesturePinchAngle;
  }
  if (!strcmp(name, "SetCameraMode")) {
    return &web49_api_runtime_SetCameraMode;
  }
  if (!strcmp(name, "UpdateCamera")) {
    return &web49_api_runtime_UpdateCamera;
  }
  if (!strcmp(name, "SetCameraPanControl")) {
    return &web49_api_runtime_SetCameraPanControl;
  }
  if (!strcmp(name, "SetCameraAltControl")) {
    return &web49_api_runtime_SetCameraAltControl;
  }
  if (!strcmp(name, "SetCameraSmoothZoomControl")) {
    return &web49_api_runtime_SetCameraSmoothZoomControl;
  }
  if (!strcmp(name, "SetCameraMoveControls")) {
    return &web49_api_runtime_SetCameraMoveControls;
  }
  if (!strcmp(name, "SetShapesTexture")) {
    return &web49_api_runtime_SetShapesTexture;
  }
  if (!strcmp(name, "DrawPixel")) {
    return &web49_api_runtime_DrawPixel;
  }
  if (!strcmp(name, "DrawPixelV")) {
    return &web49_api_runtime_DrawPixelV;
  }
  if (!strcmp(name, "DrawLine")) {
    return &web49_api_runtime_DrawLine;
  }
  if (!strcmp(name, "DrawLineV")) {
    return &web49_api_runtime_DrawLineV;
  }
  if (!strcmp(name, "DrawLineEx")) {
    return &web49_api_runtime_DrawLineEx;
  }
  if (!strcmp(name, "DrawLineBezier")) {
    return &web49_api_runtime_DrawLineBezier;
  }
  if (!strcmp(name, "DrawLineBezierQuad")) {
    return &web49_api_runtime_DrawLineBezierQuad;
  }
  if (!strcmp(name, "DrawLineBezierCubic")) {
    return &web49_api_runtime_DrawLineBezierCubic;
  }
  if (!strcmp(name, "DrawLineStrip")) {
    return &web49_api_runtime_DrawLineStrip;
  }
  if (!strcmp(name, "DrawCircle")) {
    return &web49_api_runtime_DrawCircle;
  }
  if (!strcmp(name, "DrawCircleSector")) {
    return &web49_api_runtime_DrawCircleSector;
  }
  if (!strcmp(name, "DrawCircleSectorLines")) {
    return &web49_api_runtime_DrawCircleSectorLines;
  }
  if (!strcmp(name, "DrawCircleGradient")) {
    return &web49_api_runtime_DrawCircleGradient;
  }
  if (!strcmp(name, "DrawCircleV")) {
    return &web49_api_runtime_DrawCircleV;
  }
  if (!strcmp(name, "DrawCircleLines")) {
    return &web49_api_runtime_DrawCircleLines;
  }
  if (!strcmp(name, "DrawEllipse")) {
    return &web49_api_runtime_DrawEllipse;
  }
  if (!strcmp(name, "DrawEllipseLines")) {
    return &web49_api_runtime_DrawEllipseLines;
  }
  if (!strcmp(name, "DrawRing")) {
    return &web49_api_runtime_DrawRing;
  }
  if (!strcmp(name, "DrawRingLines")) {
    return &web49_api_runtime_DrawRingLines;
  }
  if (!strcmp(name, "DrawRectangle")) {
    return &web49_api_runtime_DrawRectangle;
  }
  if (!strcmp(name, "DrawRectangleV")) {
    return &web49_api_runtime_DrawRectangleV;
  }
  if (!strcmp(name, "DrawRectangleRec")) {
    return &web49_api_runtime_DrawRectangleRec;
  }
  if (!strcmp(name, "DrawRectanglePro")) {
    return &web49_api_runtime_DrawRectanglePro;
  }
  if (!strcmp(name, "DrawRectangleGradientV")) {
    return &web49_api_runtime_DrawRectangleGradientV;
  }
  if (!strcmp(name, "DrawRectangleGradientH")) {
    return &web49_api_runtime_DrawRectangleGradientH;
  }
  if (!strcmp(name, "DrawRectangleGradientEx")) {
    return &web49_api_runtime_DrawRectangleGradientEx;
  }
  if (!strcmp(name, "DrawRectangleLines")) {
    return &web49_api_runtime_DrawRectangleLines;
  }
  if (!strcmp(name, "DrawRectangleLinesEx")) {
    return &web49_api_runtime_DrawRectangleLinesEx;
  }
  if (!strcmp(name, "DrawRectangleRounded")) {
    return &web49_api_runtime_DrawRectangleRounded;
  }
  if (!strcmp(name, "DrawRectangleRoundedLines")) {
    return &web49_api_runtime_DrawRectangleRoundedLines;
  }
  if (!strcmp(name, "DrawTriangle")) {
    return &web49_api_runtime_DrawTriangle;
  }
  if (!strcmp(name, "DrawTriangleLines")) {
    return &web49_api_runtime_DrawTriangleLines;
  }
  if (!strcmp(name, "DrawTriangleFan")) {
    return &web49_api_runtime_DrawTriangleFan;
  }
  if (!strcmp(name, "DrawTriangleStrip")) {
    return &web49_api_runtime_DrawTriangleStrip;
  }
  if (!strcmp(name, "DrawPoly")) {
    return &web49_api_runtime_DrawPoly;
  }
  if (!strcmp(name, "DrawPolyLines")) {
    return &web49_api_runtime_DrawPolyLines;
  }
  if (!strcmp(name, "DrawPolyLinesEx")) {
    return &web49_api_runtime_DrawPolyLinesEx;
  }
  if (!strcmp(name, "CheckCollisionRecs")) {
    return &web49_api_runtime_CheckCollisionRecs;
  }
  if (!strcmp(name, "CheckCollisionCircles")) {
    return &web49_api_runtime_CheckCollisionCircles;
  }
  if (!strcmp(name, "CheckCollisionCircleRec")) {
    return &web49_api_runtime_CheckCollisionCircleRec;
  }
  if (!strcmp(name, "CheckCollisionPointRec")) {
    return &web49_api_runtime_CheckCollisionPointRec;
  }
  if (!strcmp(name, "CheckCollisionPointCircle")) {
    return &web49_api_runtime_CheckCollisionPointCircle;
  }
  if (!strcmp(name, "CheckCollisionPointTriangle")) {
    return &web49_api_runtime_CheckCollisionPointTriangle;
  }
  if (!strcmp(name, "CheckCollisionLines")) {
    return &web49_api_runtime_CheckCollisionLines;
  }
  if (!strcmp(name, "CheckCollisionPointLine")) {
    return &web49_api_runtime_CheckCollisionPointLine;
  }
  if (!strcmp(name, "GetCollisionRec")) {
    return &web49_api_runtime_GetCollisionRec;
  }
  if (!strcmp(name, "LoadImage")) {
    return &web49_api_runtime_LoadImage;
  }
  if (!strcmp(name, "LoadImageRaw")) {
    return &web49_api_runtime_LoadImageRaw;
  }
  if (!strcmp(name, "LoadImageAnim")) {
    return &web49_api_runtime_LoadImageAnim;
  }
  if (!strcmp(name, "LoadImageFromMemory")) {
    return &web49_api_runtime_LoadImageFromMemory;
  }
  if (!strcmp(name, "LoadImageFromTexture")) {
    return &web49_api_runtime_LoadImageFromTexture;
  }
  if (!strcmp(name, "LoadImageFromScreen")) {
    return &web49_api_runtime_LoadImageFromScreen;
  }
  if (!strcmp(name, "UnloadImage")) {
    return &web49_api_runtime_UnloadImage;
  }
  if (!strcmp(name, "ExportImage")) {
    return &web49_api_runtime_ExportImage;
  }
  if (!strcmp(name, "ExportImageAsCode")) {
    return &web49_api_runtime_ExportImageAsCode;
  }
  if (!strcmp(name, "GenImageColor")) {
    return &web49_api_runtime_GenImageColor;
  }
  if (!strcmp(name, "GenImageGradientV")) {
    return &web49_api_runtime_GenImageGradientV;
  }
  if (!strcmp(name, "GenImageGradientH")) {
    return &web49_api_runtime_GenImageGradientH;
  }
  if (!strcmp(name, "GenImageGradientRadial")) {
    return &web49_api_runtime_GenImageGradientRadial;
  }
  if (!strcmp(name, "GenImageChecked")) {
    return &web49_api_runtime_GenImageChecked;
  }
  if (!strcmp(name, "GenImageWhiteNoise")) {
    return &web49_api_runtime_GenImageWhiteNoise;
  }
  if (!strcmp(name, "GenImageCellular")) {
    return &web49_api_runtime_GenImageCellular;
  }
  if (!strcmp(name, "ImageCopy")) {
    return &web49_api_runtime_ImageCopy;
  }
  if (!strcmp(name, "ImageFromImage")) {
    return &web49_api_runtime_ImageFromImage;
  }
  if (!strcmp(name, "ImageText")) {
    return &web49_api_runtime_ImageText;
  }
  if (!strcmp(name, "ImageTextEx")) {
    return &web49_api_runtime_ImageTextEx;
  }
  if (!strcmp(name, "ImageFormat")) {
    return &web49_api_runtime_ImageFormat;
  }
  if (!strcmp(name, "ImageToPOT")) {
    return &web49_api_runtime_ImageToPOT;
  }
  if (!strcmp(name, "ImageCrop")) {
    return &web49_api_runtime_ImageCrop;
  }
  if (!strcmp(name, "ImageAlphaCrop")) {
    return &web49_api_runtime_ImageAlphaCrop;
  }
  if (!strcmp(name, "ImageAlphaClear")) {
    return &web49_api_runtime_ImageAlphaClear;
  }
  if (!strcmp(name, "ImageAlphaMask")) {
    return &web49_api_runtime_ImageAlphaMask;
  }
  if (!strcmp(name, "ImageAlphaPremultiply")) {
    return &web49_api_runtime_ImageAlphaPremultiply;
  }
  if (!strcmp(name, "ImageResize")) {
    return &web49_api_runtime_ImageResize;
  }
  if (!strcmp(name, "ImageResizeNN")) {
    return &web49_api_runtime_ImageResizeNN;
  }
  if (!strcmp(name, "ImageResizeCanvas")) {
    return &web49_api_runtime_ImageResizeCanvas;
  }
  if (!strcmp(name, "ImageMipmaps")) {
    return &web49_api_runtime_ImageMipmaps;
  }
  if (!strcmp(name, "ImageDither")) {
    return &web49_api_runtime_ImageDither;
  }
  if (!strcmp(name, "ImageFlipVertical")) {
    return &web49_api_runtime_ImageFlipVertical;
  }
  if (!strcmp(name, "ImageFlipHorizontal")) {
    return &web49_api_runtime_ImageFlipHorizontal;
  }
  if (!strcmp(name, "ImageRotateCW")) {
    return &web49_api_runtime_ImageRotateCW;
  }
  if (!strcmp(name, "ImageRotateCCW")) {
    return &web49_api_runtime_ImageRotateCCW;
  }
  if (!strcmp(name, "ImageColorTint")) {
    return &web49_api_runtime_ImageColorTint;
  }
  if (!strcmp(name, "ImageColorInvert")) {
    return &web49_api_runtime_ImageColorInvert;
  }
  if (!strcmp(name, "ImageColorGrayscale")) {
    return &web49_api_runtime_ImageColorGrayscale;
  }
  if (!strcmp(name, "ImageColorContrast")) {
    return &web49_api_runtime_ImageColorContrast;
  }
  if (!strcmp(name, "ImageColorBrightness")) {
    return &web49_api_runtime_ImageColorBrightness;
  }
  if (!strcmp(name, "ImageColorReplace")) {
    return &web49_api_runtime_ImageColorReplace;
  }
  if (!strcmp(name, "UnloadImageColors")) {
    return &web49_api_runtime_UnloadImageColors;
  }
  if (!strcmp(name, "UnloadImagePalette")) {
    return &web49_api_runtime_UnloadImagePalette;
  }
  if (!strcmp(name, "GetImageAlphaBorder")) {
    return &web49_api_runtime_GetImageAlphaBorder;
  }
  if (!strcmp(name, "GetImageColor")) {
    return &web49_api_runtime_GetImageColor;
  }
  if (!strcmp(name, "ImageClearBackground")) {
    return &web49_api_runtime_ImageClearBackground;
  }
  if (!strcmp(name, "ImageDrawPixel")) {
    return &web49_api_runtime_ImageDrawPixel;
  }
  if (!strcmp(name, "ImageDrawPixelV")) {
    return &web49_api_runtime_ImageDrawPixelV;
  }
  if (!strcmp(name, "ImageDrawLine")) {
    return &web49_api_runtime_ImageDrawLine;
  }
  if (!strcmp(name, "ImageDrawLineV")) {
    return &web49_api_runtime_ImageDrawLineV;
  }
  if (!strcmp(name, "ImageDrawCircle")) {
    return &web49_api_runtime_ImageDrawCircle;
  }
  if (!strcmp(name, "ImageDrawCircleV")) {
    return &web49_api_runtime_ImageDrawCircleV;
  }
  if (!strcmp(name, "ImageDrawRectangle")) {
    return &web49_api_runtime_ImageDrawRectangle;
  }
  if (!strcmp(name, "ImageDrawRectangleV")) {
    return &web49_api_runtime_ImageDrawRectangleV;
  }
  if (!strcmp(name, "ImageDrawRectangleRec")) {
    return &web49_api_runtime_ImageDrawRectangleRec;
  }
  if (!strcmp(name, "ImageDrawRectangleLines")) {
    return &web49_api_runtime_ImageDrawRectangleLines;
  }
  if (!strcmp(name, "ImageDraw")) {
    return &web49_api_runtime_ImageDraw;
  }
  if (!strcmp(name, "ImageDrawText")) {
    return &web49_api_runtime_ImageDrawText;
  }
  if (!strcmp(name, "ImageDrawTextEx")) {
    return &web49_api_runtime_ImageDrawTextEx;
  }
  if (!strcmp(name, "LoadTexture")) {
    return &web49_api_runtime_LoadTexture;
  }
  if (!strcmp(name, "LoadTextureFromImage")) {
    return &web49_api_runtime_LoadTextureFromImage;
  }
  if (!strcmp(name, "LoadTextureCubemap")) {
    return &web49_api_runtime_LoadTextureCubemap;
  }
  if (!strcmp(name, "LoadRenderTexture")) {
    return &web49_api_runtime_LoadRenderTexture;
  }
  if (!strcmp(name, "UnloadTexture")) {
    return &web49_api_runtime_UnloadTexture;
  }
  if (!strcmp(name, "UnloadRenderTexture")) {
    return &web49_api_runtime_UnloadRenderTexture;
  }
  if (!strcmp(name, "UpdateTexture")) {
    return &web49_api_runtime_UpdateTexture;
  }
  if (!strcmp(name, "UpdateTextureRec")) {
    return &web49_api_runtime_UpdateTextureRec;
  }
  if (!strcmp(name, "GenTextureMipmaps")) {
    return &web49_api_runtime_GenTextureMipmaps;
  }
  if (!strcmp(name, "SetTextureFilter")) {
    return &web49_api_runtime_SetTextureFilter;
  }
  if (!strcmp(name, "SetTextureWrap")) {
    return &web49_api_runtime_SetTextureWrap;
  }
  if (!strcmp(name, "DrawTexture")) {
    return &web49_api_runtime_DrawTexture;
  }
  if (!strcmp(name, "DrawTextureV")) {
    return &web49_api_runtime_DrawTextureV;
  }
  if (!strcmp(name, "DrawTextureEx")) {
    return &web49_api_runtime_DrawTextureEx;
  }
  if (!strcmp(name, "DrawTextureRec")) {
    return &web49_api_runtime_DrawTextureRec;
  }
  if (!strcmp(name, "DrawTextureQuad")) {
    return &web49_api_runtime_DrawTextureQuad;
  }
  if (!strcmp(name, "DrawTextureTiled")) {
    return &web49_api_runtime_DrawTextureTiled;
  }
  if (!strcmp(name, "DrawTexturePro")) {
    return &web49_api_runtime_DrawTexturePro;
  }
  if (!strcmp(name, "DrawTextureNPatch")) {
    return &web49_api_runtime_DrawTextureNPatch;
  }
  if (!strcmp(name, "DrawTexturePoly")) {
    return &web49_api_runtime_DrawTexturePoly;
  }
  if (!strcmp(name, "Fade")) {
    return &web49_api_runtime_Fade;
  }
  if (!strcmp(name, "ColorToInt")) {
    return &web49_api_runtime_ColorToInt;
  }
  if (!strcmp(name, "ColorNormalize")) {
    return &web49_api_runtime_ColorNormalize;
  }
  if (!strcmp(name, "ColorFromNormalized")) {
    return &web49_api_runtime_ColorFromNormalized;
  }
  if (!strcmp(name, "ColorToHSV")) {
    return &web49_api_runtime_ColorToHSV;
  }
  if (!strcmp(name, "ColorFromHSV")) {
    return &web49_api_runtime_ColorFromHSV;
  }
  if (!strcmp(name, "ColorAlpha")) {
    return &web49_api_runtime_ColorAlpha;
  }
  if (!strcmp(name, "ColorAlphaBlend")) {
    return &web49_api_runtime_ColorAlphaBlend;
  }
  if (!strcmp(name, "GetColor")) {
    return &web49_api_runtime_GetColor;
  }
  if (!strcmp(name, "GetPixelColor")) {
    return &web49_api_runtime_GetPixelColor;
  }
  if (!strcmp(name, "SetPixelColor")) {
    return &web49_api_runtime_SetPixelColor;
  }
  if (!strcmp(name, "GetPixelDataSize")) {
    return &web49_api_runtime_GetPixelDataSize;
  }
  if (!strcmp(name, "GetFontDefault")) {
    return &web49_api_runtime_GetFontDefault;
  }
  if (!strcmp(name, "LoadFont")) {
    return &web49_api_runtime_LoadFont;
  }
  if (!strcmp(name, "LoadFontEx")) {
    return &web49_api_runtime_LoadFontEx;
  }
  if (!strcmp(name, "LoadFontFromImage")) {
    return &web49_api_runtime_LoadFontFromImage;
  }
  if (!strcmp(name, "LoadFontFromMemory")) {
    return &web49_api_runtime_LoadFontFromMemory;
  }
  if (!strcmp(name, "GenImageFontAtlas")) {
    return &web49_api_runtime_GenImageFontAtlas;
  }
  if (!strcmp(name, "UnloadFontData")) {
    return &web49_api_runtime_UnloadFontData;
  }
  if (!strcmp(name, "UnloadFont")) {
    return &web49_api_runtime_UnloadFont;
  }
  if (!strcmp(name, "ExportFontAsCode")) {
    return &web49_api_runtime_ExportFontAsCode;
  }
  if (!strcmp(name, "DrawFPS")) {
    return &web49_api_runtime_DrawFPS;
  }
  if (!strcmp(name, "DrawText")) {
    return &web49_api_runtime_DrawText;
  }
  if (!strcmp(name, "DrawTextEx")) {
    return &web49_api_runtime_DrawTextEx;
  }
  if (!strcmp(name, "DrawTextPro")) {
    return &web49_api_runtime_DrawTextPro;
  }
  if (!strcmp(name, "DrawTextCodepoint")) {
    return &web49_api_runtime_DrawTextCodepoint;
  }
  if (!strcmp(name, "DrawTextCodepoints")) {
    return &web49_api_runtime_DrawTextCodepoints;
  }
  if (!strcmp(name, "MeasureText")) {
    return &web49_api_runtime_MeasureText;
  }
  if (!strcmp(name, "MeasureTextEx")) {
    return &web49_api_runtime_MeasureTextEx;
  }
  if (!strcmp(name, "GetGlyphIndex")) {
    return &web49_api_runtime_GetGlyphIndex;
  }
  if (!strcmp(name, "GetGlyphInfo")) {
    return &web49_api_runtime_GetGlyphInfo;
  }
  if (!strcmp(name, "GetGlyphAtlasRec")) {
    return &web49_api_runtime_GetGlyphAtlasRec;
  }
  if (!strcmp(name, "UnloadCodepoints")) {
    return &web49_api_runtime_UnloadCodepoints;
  }
  if (!strcmp(name, "GetCodepointCount")) {
    return &web49_api_runtime_GetCodepointCount;
  }
  if (!strcmp(name, "GetCodepoint")) {
    return &web49_api_runtime_GetCodepoint;
  }
  if (!strcmp(name, "TextCopy")) {
    return &web49_api_runtime_TextCopy;
  }
  if (!strcmp(name, "TextIsEqual")) {
    return &web49_api_runtime_TextIsEqual;
  }
  if (!strcmp(name, "TextLength")) {
    return &web49_api_runtime_TextLength;
  }
  if (!strcmp(name, "TextAppend")) {
    return &web49_api_runtime_TextAppend;
  }
  if (!strcmp(name, "TextFindIndex")) {
    return &web49_api_runtime_TextFindIndex;
  }
  if (!strcmp(name, "TextToInteger")) {
    return &web49_api_runtime_TextToInteger;
  }
  if (!strcmp(name, "DrawLine3D")) {
    return &web49_api_runtime_DrawLine3D;
  }
  if (!strcmp(name, "DrawPoint3D")) {
    return &web49_api_runtime_DrawPoint3D;
  }
  if (!strcmp(name, "DrawCircle3D")) {
    return &web49_api_runtime_DrawCircle3D;
  }
  if (!strcmp(name, "DrawTriangle3D")) {
    return &web49_api_runtime_DrawTriangle3D;
  }
  if (!strcmp(name, "DrawTriangleStrip3D")) {
    return &web49_api_runtime_DrawTriangleStrip3D;
  }
  if (!strcmp(name, "DrawCube")) {
    return &web49_api_runtime_DrawCube;
  }
  if (!strcmp(name, "DrawCubeV")) {
    return &web49_api_runtime_DrawCubeV;
  }
  if (!strcmp(name, "DrawCubeWires")) {
    return &web49_api_runtime_DrawCubeWires;
  }
  if (!strcmp(name, "DrawCubeWiresV")) {
    return &web49_api_runtime_DrawCubeWiresV;
  }
  if (!strcmp(name, "DrawCubeTexture")) {
    return &web49_api_runtime_DrawCubeTexture;
  }
  if (!strcmp(name, "DrawCubeTextureRec")) {
    return &web49_api_runtime_DrawCubeTextureRec;
  }
  if (!strcmp(name, "DrawSphere")) {
    return &web49_api_runtime_DrawSphere;
  }
  if (!strcmp(name, "DrawSphereEx")) {
    return &web49_api_runtime_DrawSphereEx;
  }
  if (!strcmp(name, "DrawSphereWires")) {
    return &web49_api_runtime_DrawSphereWires;
  }
  if (!strcmp(name, "DrawCylinder")) {
    return &web49_api_runtime_DrawCylinder;
  }
  if (!strcmp(name, "DrawCylinderEx")) {
    return &web49_api_runtime_DrawCylinderEx;
  }
  if (!strcmp(name, "DrawCylinderWires")) {
    return &web49_api_runtime_DrawCylinderWires;
  }
  if (!strcmp(name, "DrawCylinderWiresEx")) {
    return &web49_api_runtime_DrawCylinderWiresEx;
  }
  if (!strcmp(name, "DrawPlane")) {
    return &web49_api_runtime_DrawPlane;
  }
  if (!strcmp(name, "DrawRay")) {
    return &web49_api_runtime_DrawRay;
  }
  if (!strcmp(name, "DrawGrid")) {
    return &web49_api_runtime_DrawGrid;
  }
  if (!strcmp(name, "LoadModel")) {
    return &web49_api_runtime_LoadModel;
  }
  if (!strcmp(name, "LoadModelFromMesh")) {
    return &web49_api_runtime_LoadModelFromMesh;
  }
  if (!strcmp(name, "UnloadModel")) {
    return &web49_api_runtime_UnloadModel;
  }
  if (!strcmp(name, "UnloadModelKeepMeshes")) {
    return &web49_api_runtime_UnloadModelKeepMeshes;
  }
  if (!strcmp(name, "GetModelBoundingBox")) {
    return &web49_api_runtime_GetModelBoundingBox;
  }
  if (!strcmp(name, "DrawModel")) {
    return &web49_api_runtime_DrawModel;
  }
  if (!strcmp(name, "DrawModelEx")) {
    return &web49_api_runtime_DrawModelEx;
  }
  if (!strcmp(name, "DrawModelWires")) {
    return &web49_api_runtime_DrawModelWires;
  }
  if (!strcmp(name, "DrawModelWiresEx")) {
    return &web49_api_runtime_DrawModelWiresEx;
  }
  if (!strcmp(name, "DrawBoundingBox")) {
    return &web49_api_runtime_DrawBoundingBox;
  }
  if (!strcmp(name, "DrawBillboard")) {
    return &web49_api_runtime_DrawBillboard;
  }
  if (!strcmp(name, "DrawBillboardRec")) {
    return &web49_api_runtime_DrawBillboardRec;
  }
  if (!strcmp(name, "DrawBillboardPro")) {
    return &web49_api_runtime_DrawBillboardPro;
  }
  if (!strcmp(name, "UploadMesh")) {
    return &web49_api_runtime_UploadMesh;
  }
  if (!strcmp(name, "UpdateMeshBuffer")) {
    return &web49_api_runtime_UpdateMeshBuffer;
  }
  if (!strcmp(name, "UnloadMesh")) {
    return &web49_api_runtime_UnloadMesh;
  }
  if (!strcmp(name, "DrawMesh")) {
    return &web49_api_runtime_DrawMesh;
  }
  if (!strcmp(name, "DrawMeshInstanced")) {
    return &web49_api_runtime_DrawMeshInstanced;
  }
  if (!strcmp(name, "ExportMesh")) {
    return &web49_api_runtime_ExportMesh;
  }
  if (!strcmp(name, "GetMeshBoundingBox")) {
    return &web49_api_runtime_GetMeshBoundingBox;
  }
  if (!strcmp(name, "GenMeshTangents")) {
    return &web49_api_runtime_GenMeshTangents;
  }
  if (!strcmp(name, "GenMeshPoly")) {
    return &web49_api_runtime_GenMeshPoly;
  }
  if (!strcmp(name, "GenMeshPlane")) {
    return &web49_api_runtime_GenMeshPlane;
  }
  if (!strcmp(name, "GenMeshCube")) {
    return &web49_api_runtime_GenMeshCube;
  }
  if (!strcmp(name, "GenMeshSphere")) {
    return &web49_api_runtime_GenMeshSphere;
  }
  if (!strcmp(name, "GenMeshHemiSphere")) {
    return &web49_api_runtime_GenMeshHemiSphere;
  }
  if (!strcmp(name, "GenMeshCylinder")) {
    return &web49_api_runtime_GenMeshCylinder;
  }
  if (!strcmp(name, "GenMeshCone")) {
    return &web49_api_runtime_GenMeshCone;
  }
  if (!strcmp(name, "GenMeshTorus")) {
    return &web49_api_runtime_GenMeshTorus;
  }
  if (!strcmp(name, "GenMeshKnot")) {
    return &web49_api_runtime_GenMeshKnot;
  }
  if (!strcmp(name, "GenMeshHeightmap")) {
    return &web49_api_runtime_GenMeshHeightmap;
  }
  if (!strcmp(name, "GenMeshCubicmap")) {
    return &web49_api_runtime_GenMeshCubicmap;
  }
  if (!strcmp(name, "LoadMaterialDefault")) {
    return &web49_api_runtime_LoadMaterialDefault;
  }
  if (!strcmp(name, "UnloadMaterial")) {
    return &web49_api_runtime_UnloadMaterial;
  }
  if (!strcmp(name, "SetMaterialTexture")) {
    return &web49_api_runtime_SetMaterialTexture;
  }
  if (!strcmp(name, "SetModelMeshMaterial")) {
    return &web49_api_runtime_SetModelMeshMaterial;
  }
  if (!strcmp(name, "UpdateModelAnimation")) {
    return &web49_api_runtime_UpdateModelAnimation;
  }
  if (!strcmp(name, "UnloadModelAnimation")) {
    return &web49_api_runtime_UnloadModelAnimation;
  }
  if (!strcmp(name, "UnloadModelAnimations")) {
    return &web49_api_runtime_UnloadModelAnimations;
  }
  if (!strcmp(name, "IsModelAnimationValid")) {
    return &web49_api_runtime_IsModelAnimationValid;
  }
  if (!strcmp(name, "CheckCollisionSpheres")) {
    return &web49_api_runtime_CheckCollisionSpheres;
  }
  if (!strcmp(name, "CheckCollisionBoxes")) {
    return &web49_api_runtime_CheckCollisionBoxes;
  }
  if (!strcmp(name, "CheckCollisionBoxSphere")) {
    return &web49_api_runtime_CheckCollisionBoxSphere;
  }
  if (!strcmp(name, "GetRayCollisionSphere")) {
    return &web49_api_runtime_GetRayCollisionSphere;
  }
  if (!strcmp(name, "GetRayCollisionBox")) {
    return &web49_api_runtime_GetRayCollisionBox;
  }
  if (!strcmp(name, "GetRayCollisionMesh")) {
    return &web49_api_runtime_GetRayCollisionMesh;
  }
  if (!strcmp(name, "GetRayCollisionTriangle")) {
    return &web49_api_runtime_GetRayCollisionTriangle;
  }
  if (!strcmp(name, "GetRayCollisionQuad")) {
    return &web49_api_runtime_GetRayCollisionQuad;
  }
  if (!strcmp(name, "InitAudioDevice")) {
    return &web49_api_runtime_InitAudioDevice;
  }
  if (!strcmp(name, "CloseAudioDevice")) {
    return &web49_api_runtime_CloseAudioDevice;
  }
  if (!strcmp(name, "IsAudioDeviceReady")) {
    return &web49_api_runtime_IsAudioDeviceReady;
  }
  if (!strcmp(name, "SetMasterVolume")) {
    return &web49_api_runtime_SetMasterVolume;
  }
  if (!strcmp(name, "LoadWave")) {
    return &web49_api_runtime_LoadWave;
  }
  if (!strcmp(name, "LoadWaveFromMemory")) {
    return &web49_api_runtime_LoadWaveFromMemory;
  }
  if (!strcmp(name, "LoadSound")) {
    return &web49_api_runtime_LoadSound;
  }
  if (!strcmp(name, "LoadSoundFromWave")) {
    return &web49_api_runtime_LoadSoundFromWave;
  }
  if (!strcmp(name, "UpdateSound")) {
    return &web49_api_runtime_UpdateSound;
  }
  if (!strcmp(name, "UnloadWave")) {
    return &web49_api_runtime_UnloadWave;
  }
  if (!strcmp(name, "UnloadSound")) {
    return &web49_api_runtime_UnloadSound;
  }
  if (!strcmp(name, "ExportWave")) {
    return &web49_api_runtime_ExportWave;
  }
  if (!strcmp(name, "ExportWaveAsCode")) {
    return &web49_api_runtime_ExportWaveAsCode;
  }
  if (!strcmp(name, "PlaySound")) {
    return &web49_api_runtime_PlaySound;
  }
  if (!strcmp(name, "StopSound")) {
    return &web49_api_runtime_StopSound;
  }
  if (!strcmp(name, "PauseSound")) {
    return &web49_api_runtime_PauseSound;
  }
  if (!strcmp(name, "ResumeSound")) {
    return &web49_api_runtime_ResumeSound;
  }
  if (!strcmp(name, "PlaySoundMulti")) {
    return &web49_api_runtime_PlaySoundMulti;
  }
  if (!strcmp(name, "StopSoundMulti")) {
    return &web49_api_runtime_StopSoundMulti;
  }
  if (!strcmp(name, "GetSoundsPlaying")) {
    return &web49_api_runtime_GetSoundsPlaying;
  }
  if (!strcmp(name, "IsSoundPlaying")) {
    return &web49_api_runtime_IsSoundPlaying;
  }
  if (!strcmp(name, "SetSoundVolume")) {
    return &web49_api_runtime_SetSoundVolume;
  }
  if (!strcmp(name, "SetSoundPitch")) {
    return &web49_api_runtime_SetSoundPitch;
  }
  if (!strcmp(name, "SetSoundPan")) {
    return &web49_api_runtime_SetSoundPan;
  }
  if (!strcmp(name, "WaveCopy")) {
    return &web49_api_runtime_WaveCopy;
  }
  if (!strcmp(name, "WaveCrop")) {
    return &web49_api_runtime_WaveCrop;
  }
  if (!strcmp(name, "WaveFormat")) {
    return &web49_api_runtime_WaveFormat;
  }
  if (!strcmp(name, "UnloadWaveSamples")) {
    return &web49_api_runtime_UnloadWaveSamples;
  }
  if (!strcmp(name, "LoadMusicStream")) {
    return &web49_api_runtime_LoadMusicStream;
  }
  if (!strcmp(name, "LoadMusicStreamFromMemory")) {
    return &web49_api_runtime_LoadMusicStreamFromMemory;
  }
  if (!strcmp(name, "UnloadMusicStream")) {
    return &web49_api_runtime_UnloadMusicStream;
  }
  if (!strcmp(name, "PlayMusicStream")) {
    return &web49_api_runtime_PlayMusicStream;
  }
  if (!strcmp(name, "IsMusicStreamPlaying")) {
    return &web49_api_runtime_IsMusicStreamPlaying;
  }
  if (!strcmp(name, "UpdateMusicStream")) {
    return &web49_api_runtime_UpdateMusicStream;
  }
  if (!strcmp(name, "StopMusicStream")) {
    return &web49_api_runtime_StopMusicStream;
  }
  if (!strcmp(name, "PauseMusicStream")) {
    return &web49_api_runtime_PauseMusicStream;
  }
  if (!strcmp(name, "ResumeMusicStream")) {
    return &web49_api_runtime_ResumeMusicStream;
  }
  if (!strcmp(name, "SeekMusicStream")) {
    return &web49_api_runtime_SeekMusicStream;
  }
  if (!strcmp(name, "SetMusicVolume")) {
    return &web49_api_runtime_SetMusicVolume;
  }
  if (!strcmp(name, "SetMusicPitch")) {
    return &web49_api_runtime_SetMusicPitch;
  }
  if (!strcmp(name, "SetMusicPan")) {
    return &web49_api_runtime_SetMusicPan;
  }
  if (!strcmp(name, "GetMusicTimeLength")) {
    return &web49_api_runtime_GetMusicTimeLength;
  }
  if (!strcmp(name, "GetMusicTimePlayed")) {
    return &web49_api_runtime_GetMusicTimePlayed;
  }
  if (!strcmp(name, "LoadAudioStream")) {
    return &web49_api_runtime_LoadAudioStream;
  }
  if (!strcmp(name, "UnloadAudioStream")) {
    return &web49_api_runtime_UnloadAudioStream;
  }
  if (!strcmp(name, "UpdateAudioStream")) {
    return &web49_api_runtime_UpdateAudioStream;
  }
  if (!strcmp(name, "IsAudioStreamProcessed")) {
    return &web49_api_runtime_IsAudioStreamProcessed;
  }
  if (!strcmp(name, "PlayAudioStream")) {
    return &web49_api_runtime_PlayAudioStream;
  }
  if (!strcmp(name, "PauseAudioStream")) {
    return &web49_api_runtime_PauseAudioStream;
  }
  if (!strcmp(name, "ResumeAudioStream")) {
    return &web49_api_runtime_ResumeAudioStream;
  }
  if (!strcmp(name, "IsAudioStreamPlaying")) {
    return &web49_api_runtime_IsAudioStreamPlaying;
  }
  if (!strcmp(name, "StopAudioStream")) {
    return &web49_api_runtime_StopAudioStream;
  }
  if (!strcmp(name, "SetAudioStreamVolume")) {
    return &web49_api_runtime_SetAudioStreamVolume;
  }
  if (!strcmp(name, "SetAudioStreamPitch")) {
    return &web49_api_runtime_SetAudioStreamPitch;
  }
  if (!strcmp(name, "SetAudioStreamPan")) {
    return &web49_api_runtime_SetAudioStreamPan;
  }
  if (!strcmp(name, "SetAudioStreamBufferSizeDefault")) {
    return &web49_api_runtime_SetAudioStreamBufferSizeDefault;
  }
  if (!strcmp(name, "rlMatrixMode")) {
    return &web49_api_runtime_rlMatrixMode;
  }
  if (!strcmp(name, "rlPushMatrix")) {
    return &web49_api_runtime_rlPushMatrix;
  }
  if (!strcmp(name, "rlPopMatrix")) {
    return &web49_api_runtime_rlPopMatrix;
  }
  if (!strcmp(name, "rlLoadIdentity")) {
    return &web49_api_runtime_rlLoadIdentity;
  }
  if (!strcmp(name, "rlTranslatef")) {
    return &web49_api_runtime_rlTranslatef;
  }
  if (!strcmp(name, "rlRotatef")) {
    return &web49_api_runtime_rlRotatef;
  }
  if (!strcmp(name, "rlScalef")) {
    return &web49_api_runtime_rlScalef;
  }
  if (!strcmp(name, "rlMultMatrixf")) {
    return &web49_api_runtime_rlMultMatrixf;
  }
  if (!strcmp(name, "rlFrustum")) {
    return &web49_api_runtime_rlFrustum;
  }
  if (!strcmp(name, "rlOrtho")) {
    return &web49_api_runtime_rlOrtho;
  }
  if (!strcmp(name, "rlViewport")) {
    return &web49_api_runtime_rlViewport;
  }
  if (!strcmp(name, "rlBegin")) {
    return &web49_api_runtime_rlBegin;
  }
  if (!strcmp(name, "rlEnd")) {
    return &web49_api_runtime_rlEnd;
  }
  if (!strcmp(name, "rlVertex2i")) {
    return &web49_api_runtime_rlVertex2i;
  }
  if (!strcmp(name, "rlVertex2f")) {
    return &web49_api_runtime_rlVertex2f;
  }
  if (!strcmp(name, "rlVertex3f")) {
    return &web49_api_runtime_rlVertex3f;
  }
  if (!strcmp(name, "rlTexCoord2f")) {
    return &web49_api_runtime_rlTexCoord2f;
  }
  if (!strcmp(name, "rlNormal3f")) {
    return &web49_api_runtime_rlNormal3f;
  }
  if (!strcmp(name, "rlColor4ub")) {
    return &web49_api_runtime_rlColor4ub;
  }
  if (!strcmp(name, "rlColor3f")) {
    return &web49_api_runtime_rlColor3f;
  }
  if (!strcmp(name, "rlColor4f")) {
    return &web49_api_runtime_rlColor4f;
  }
  if (!strcmp(name, "rlEnableVertexArray")) {
    return &web49_api_runtime_rlEnableVertexArray;
  }
  if (!strcmp(name, "rlDisableVertexArray")) {
    return &web49_api_runtime_rlDisableVertexArray;
  }
  if (!strcmp(name, "rlEnableVertexBuffer")) {
    return &web49_api_runtime_rlEnableVertexBuffer;
  }
  if (!strcmp(name, "rlDisableVertexBuffer")) {
    return &web49_api_runtime_rlDisableVertexBuffer;
  }
  if (!strcmp(name, "rlEnableVertexBufferElement")) {
    return &web49_api_runtime_rlEnableVertexBufferElement;
  }
  if (!strcmp(name, "rlDisableVertexBufferElement")) {
    return &web49_api_runtime_rlDisableVertexBufferElement;
  }
  if (!strcmp(name, "rlEnableVertexAttribute")) {
    return &web49_api_runtime_rlEnableVertexAttribute;
  }
  if (!strcmp(name, "rlDisableVertexAttribute")) {
    return &web49_api_runtime_rlDisableVertexAttribute;
  }
  if (!strcmp(name, "rlActiveTextureSlot")) {
    return &web49_api_runtime_rlActiveTextureSlot;
  }
  if (!strcmp(name, "rlEnableTexture")) {
    return &web49_api_runtime_rlEnableTexture;
  }
  if (!strcmp(name, "rlDisableTexture")) {
    return &web49_api_runtime_rlDisableTexture;
  }
  if (!strcmp(name, "rlEnableTextureCubemap")) {
    return &web49_api_runtime_rlEnableTextureCubemap;
  }
  if (!strcmp(name, "rlDisableTextureCubemap")) {
    return &web49_api_runtime_rlDisableTextureCubemap;
  }
  if (!strcmp(name, "rlTextureParameters")) {
    return &web49_api_runtime_rlTextureParameters;
  }
  if (!strcmp(name, "rlEnableShader")) {
    return &web49_api_runtime_rlEnableShader;
  }
  if (!strcmp(name, "rlDisableShader")) {
    return &web49_api_runtime_rlDisableShader;
  }
  if (!strcmp(name, "rlEnableFramebuffer")) {
    return &web49_api_runtime_rlEnableFramebuffer;
  }
  if (!strcmp(name, "rlDisableFramebuffer")) {
    return &web49_api_runtime_rlDisableFramebuffer;
  }
  if (!strcmp(name, "rlActiveDrawBuffers")) {
    return &web49_api_runtime_rlActiveDrawBuffers;
  }
  if (!strcmp(name, "rlEnableColorBlend")) {
    return &web49_api_runtime_rlEnableColorBlend;
  }
  if (!strcmp(name, "rlDisableColorBlend")) {
    return &web49_api_runtime_rlDisableColorBlend;
  }
  if (!strcmp(name, "rlEnableDepthTest")) {
    return &web49_api_runtime_rlEnableDepthTest;
  }
  if (!strcmp(name, "rlDisableDepthTest")) {
    return &web49_api_runtime_rlDisableDepthTest;
  }
  if (!strcmp(name, "rlEnableDepthMask")) {
    return &web49_api_runtime_rlEnableDepthMask;
  }
  if (!strcmp(name, "rlDisableDepthMask")) {
    return &web49_api_runtime_rlDisableDepthMask;
  }
  if (!strcmp(name, "rlEnableBackfaceCulling")) {
    return &web49_api_runtime_rlEnableBackfaceCulling;
  }
  if (!strcmp(name, "rlDisableBackfaceCulling")) {
    return &web49_api_runtime_rlDisableBackfaceCulling;
  }
  if (!strcmp(name, "rlEnableScissorTest")) {
    return &web49_api_runtime_rlEnableScissorTest;
  }
  if (!strcmp(name, "rlDisableScissorTest")) {
    return &web49_api_runtime_rlDisableScissorTest;
  }
  if (!strcmp(name, "rlScissor")) {
    return &web49_api_runtime_rlScissor;
  }
  if (!strcmp(name, "rlEnableWireMode")) {
    return &web49_api_runtime_rlEnableWireMode;
  }
  if (!strcmp(name, "rlDisableWireMode")) {
    return &web49_api_runtime_rlDisableWireMode;
  }
  if (!strcmp(name, "rlSetLineWidth")) {
    return &web49_api_runtime_rlSetLineWidth;
  }
  if (!strcmp(name, "rlGetLineWidth")) {
    return &web49_api_runtime_rlGetLineWidth;
  }
  if (!strcmp(name, "rlEnableSmoothLines")) {
    return &web49_api_runtime_rlEnableSmoothLines;
  }
  if (!strcmp(name, "rlDisableSmoothLines")) {
    return &web49_api_runtime_rlDisableSmoothLines;
  }
  if (!strcmp(name, "rlEnableStereoRender")) {
    return &web49_api_runtime_rlEnableStereoRender;
  }
  if (!strcmp(name, "rlDisableStereoRender")) {
    return &web49_api_runtime_rlDisableStereoRender;
  }
  if (!strcmp(name, "rlIsStereoRenderEnabled")) {
    return &web49_api_runtime_rlIsStereoRenderEnabled;
  }
  if (!strcmp(name, "rlClearColor")) {
    return &web49_api_runtime_rlClearColor;
  }
  if (!strcmp(name, "rlClearScreenBuffers")) {
    return &web49_api_runtime_rlClearScreenBuffers;
  }
  if (!strcmp(name, "rlCheckErrors")) {
    return &web49_api_runtime_rlCheckErrors;
  }
  if (!strcmp(name, "rlSetBlendMode")) {
    return &web49_api_runtime_rlSetBlendMode;
  }
  if (!strcmp(name, "rlSetBlendFactors")) {
    return &web49_api_runtime_rlSetBlendFactors;
  }
  if (!strcmp(name, "rlglInit")) {
    return &web49_api_runtime_rlglInit;
  }
  if (!strcmp(name, "rlglClose")) {
    return &web49_api_runtime_rlglClose;
  }
  if (!strcmp(name, "rlLoadExtensions")) {
    return &web49_api_runtime_rlLoadExtensions;
  }
  if (!strcmp(name, "rlGetVersion")) {
    return &web49_api_runtime_rlGetVersion;
  }
  if (!strcmp(name, "rlSetFramebufferWidth")) {
    return &web49_api_runtime_rlSetFramebufferWidth;
  }
  if (!strcmp(name, "rlGetFramebufferWidth")) {
    return &web49_api_runtime_rlGetFramebufferWidth;
  }
  if (!strcmp(name, "rlSetFramebufferHeight")) {
    return &web49_api_runtime_rlSetFramebufferHeight;
  }
  if (!strcmp(name, "rlGetFramebufferHeight")) {
    return &web49_api_runtime_rlGetFramebufferHeight;
  }
  if (!strcmp(name, "rlGetTextureIdDefault")) {
    return &web49_api_runtime_rlGetTextureIdDefault;
  }
  if (!strcmp(name, "rlGetShaderIdDefault")) {
    return &web49_api_runtime_rlGetShaderIdDefault;
  }
  if (!strcmp(name, "rlLoadRenderBatch")) {
    return &web49_api_runtime_rlLoadRenderBatch;
  }
  if (!strcmp(name, "rlUnloadRenderBatch")) {
    return &web49_api_runtime_rlUnloadRenderBatch;
  }
  if (!strcmp(name, "rlDrawRenderBatch")) {
    return &web49_api_runtime_rlDrawRenderBatch;
  }
  if (!strcmp(name, "rlSetRenderBatchActive")) {
    return &web49_api_runtime_rlSetRenderBatchActive;
  }
  if (!strcmp(name, "rlDrawRenderBatchActive")) {
    return &web49_api_runtime_rlDrawRenderBatchActive;
  }
  if (!strcmp(name, "rlCheckRenderBatchLimit")) {
    return &web49_api_runtime_rlCheckRenderBatchLimit;
  }
  if (!strcmp(name, "rlSetTexture")) {
    return &web49_api_runtime_rlSetTexture;
  }
  if (!strcmp(name, "rlLoadVertexArray")) {
    return &web49_api_runtime_rlLoadVertexArray;
  }
  if (!strcmp(name, "rlLoadVertexBuffer")) {
    return &web49_api_runtime_rlLoadVertexBuffer;
  }
  if (!strcmp(name, "rlLoadVertexBufferElement")) {
    return &web49_api_runtime_rlLoadVertexBufferElement;
  }
  if (!strcmp(name, "rlUpdateVertexBuffer")) {
    return &web49_api_runtime_rlUpdateVertexBuffer;
  }
  if (!strcmp(name, "rlUpdateVertexBufferElements")) {
    return &web49_api_runtime_rlUpdateVertexBufferElements;
  }
  if (!strcmp(name, "rlUnloadVertexArray")) {
    return &web49_api_runtime_rlUnloadVertexArray;
  }
  if (!strcmp(name, "rlUnloadVertexBuffer")) {
    return &web49_api_runtime_rlUnloadVertexBuffer;
  }
  if (!strcmp(name, "rlSetVertexAttribute")) {
    return &web49_api_runtime_rlSetVertexAttribute;
  }
  if (!strcmp(name, "rlSetVertexAttributeDivisor")) {
    return &web49_api_runtime_rlSetVertexAttributeDivisor;
  }
  if (!strcmp(name, "rlSetVertexAttributeDefault")) {
    return &web49_api_runtime_rlSetVertexAttributeDefault;
  }
  if (!strcmp(name, "rlDrawVertexArray")) {
    return &web49_api_runtime_rlDrawVertexArray;
  }
  if (!strcmp(name, "rlDrawVertexArrayElements")) {
    return &web49_api_runtime_rlDrawVertexArrayElements;
  }
  if (!strcmp(name, "rlDrawVertexArrayInstanced")) {
    return &web49_api_runtime_rlDrawVertexArrayInstanced;
  }
  if (!strcmp(name, "rlDrawVertexArrayElementsInstanced")) {
    return &web49_api_runtime_rlDrawVertexArrayElementsInstanced;
  }
  if (!strcmp(name, "rlLoadTexture")) {
    return &web49_api_runtime_rlLoadTexture;
  }
  if (!strcmp(name, "rlLoadTextureDepth")) {
    return &web49_api_runtime_rlLoadTextureDepth;
  }
  if (!strcmp(name, "rlLoadTextureCubemap")) {
    return &web49_api_runtime_rlLoadTextureCubemap;
  }
  if (!strcmp(name, "rlUpdateTexture")) {
    return &web49_api_runtime_rlUpdateTexture;
  }
  if (!strcmp(name, "rlGetGlTextureFormats")) {
    return &web49_api_runtime_rlGetGlTextureFormats;
  }
  if (!strcmp(name, "rlUnloadTexture")) {
    return &web49_api_runtime_rlUnloadTexture;
  }
  if (!strcmp(name, "rlGenTextureMipmaps")) {
    return &web49_api_runtime_rlGenTextureMipmaps;
  }
  if (!strcmp(name, "rlLoadFramebuffer")) {
    return &web49_api_runtime_rlLoadFramebuffer;
  }
  if (!strcmp(name, "rlFramebufferAttach")) {
    return &web49_api_runtime_rlFramebufferAttach;
  }
  if (!strcmp(name, "rlFramebufferComplete")) {
    return &web49_api_runtime_rlFramebufferComplete;
  }
  if (!strcmp(name, "rlUnloadFramebuffer")) {
    return &web49_api_runtime_rlUnloadFramebuffer;
  }
  if (!strcmp(name, "rlLoadShaderCode")) {
    return &web49_api_runtime_rlLoadShaderCode;
  }
  if (!strcmp(name, "rlCompileShader")) {
    return &web49_api_runtime_rlCompileShader;
  }
  if (!strcmp(name, "rlLoadShaderProgram")) {
    return &web49_api_runtime_rlLoadShaderProgram;
  }
  if (!strcmp(name, "rlUnloadShaderProgram")) {
    return &web49_api_runtime_rlUnloadShaderProgram;
  }
  if (!strcmp(name, "rlGetLocationUniform")) {
    return &web49_api_runtime_rlGetLocationUniform;
  }
  if (!strcmp(name, "rlGetLocationAttrib")) {
    return &web49_api_runtime_rlGetLocationAttrib;
  }
  if (!strcmp(name, "rlSetUniform")) {
    return &web49_api_runtime_rlSetUniform;
  }
  if (!strcmp(name, "rlSetUniformMatrix")) {
    return &web49_api_runtime_rlSetUniformMatrix;
  }
  if (!strcmp(name, "rlSetUniformSampler")) {
    return &web49_api_runtime_rlSetUniformSampler;
  }
  if (!strcmp(name, "rlSetShader")) {
    return &web49_api_runtime_rlSetShader;
  }
  if (!strcmp(name, "rlLoadComputeShaderProgram")) {
    return &web49_api_runtime_rlLoadComputeShaderProgram;
  }
  if (!strcmp(name, "rlComputeShaderDispatch")) {
    return &web49_api_runtime_rlComputeShaderDispatch;
  }
  if (!strcmp(name, "rlLoadShaderBuffer")) {
    return &web49_api_runtime_rlLoadShaderBuffer;
  }
  if (!strcmp(name, "rlUnloadShaderBuffer")) {
    return &web49_api_runtime_rlUnloadShaderBuffer;
  }
  if (!strcmp(name, "rlUpdateShaderBufferElements")) {
    return &web49_api_runtime_rlUpdateShaderBufferElements;
  }
  if (!strcmp(name, "rlGetShaderBufferSize")) {
    return &web49_api_runtime_rlGetShaderBufferSize;
  }
  if (!strcmp(name, "rlReadShaderBufferElements")) {
    return &web49_api_runtime_rlReadShaderBufferElements;
  }
  if (!strcmp(name, "rlBindShaderBuffer")) {
    return &web49_api_runtime_rlBindShaderBuffer;
  }
  if (!strcmp(name, "rlCopyBuffersElements")) {
    return &web49_api_runtime_rlCopyBuffersElements;
  }
  if (!strcmp(name, "rlBindImageTexture")) {
    return &web49_api_runtime_rlBindImageTexture;
  }
  if (!strcmp(name, "rlGetMatrixModelview")) {
    return &web49_api_runtime_rlGetMatrixModelview;
  }
  if (!strcmp(name, "rlGetMatrixProjection")) {
    return &web49_api_runtime_rlGetMatrixProjection;
  }
  if (!strcmp(name, "rlGetMatrixTransform")) {
    return &web49_api_runtime_rlGetMatrixTransform;
  }
  if (!strcmp(name, "rlGetMatrixProjectionStereo")) {
    return &web49_api_runtime_rlGetMatrixProjectionStereo;
  }
  if (!strcmp(name, "rlGetMatrixViewOffsetStereo")) {
    return &web49_api_runtime_rlGetMatrixViewOffsetStereo;
  }
  if (!strcmp(name, "rlSetMatrixProjection")) {
    return &web49_api_runtime_rlSetMatrixProjection;
  }
  if (!strcmp(name, "rlSetMatrixModelview")) {
    return &web49_api_runtime_rlSetMatrixModelview;
  }
  if (!strcmp(name, "rlSetMatrixProjectionStereo")) {
    return &web49_api_runtime_rlSetMatrixProjectionStereo;
  }
  if (!strcmp(name, "rlSetMatrixViewOffsetStereo")) {
    return &web49_api_runtime_rlSetMatrixViewOffsetStereo;
  }
  if (!strcmp(name, "rlLoadDrawCube")) {
    return &web49_api_runtime_rlLoadDrawCube;
  }
  if (!strcmp(name, "rlLoadDrawQuad")) {
    return &web49_api_runtime_rlLoadDrawQuad;
  }
  return NULL;
}
