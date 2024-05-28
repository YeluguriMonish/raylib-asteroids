#pragma once
#include "components.h"
#include "entities.h"
#include "flecs.h"
#include "globals.h"
#include "raylib.h"
#include "systems.h"
#include "utils.h"

int main(void) {
  init_systems();

  InitWindow(800, 450, "raylib");
  init_player(); // textures must be loaded after window is initialized
  init_relationships();
  SetTargetFPS(60);

  user_input = init_user_input();

  while (!WindowShouldClose()) {
    read_user_input();
    parse_user_input(&ecs);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    ecs.progress();
    EndDrawing();
    parse_destruct_queue();
  }

  free(user_input);
  CloseWindow();

  return 0;
}
