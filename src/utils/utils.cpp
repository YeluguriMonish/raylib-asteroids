#pragma once
#include "utils.h"
#include "components.h"
#include "entities.h"
#include "flecs.h"
#include <cstdlib>
#include <raylib.h>
#include <raymath.h>

UserInput *user_input;

UserInput *init_user_input() {
  user_input = (UserInput *)malloc(sizeof(UserInput));
  return user_input;
}

void read_user_input() {
  user_input->left_axis_x = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
  user_input->right_axis_y = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y);

  if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
    user_input->left_axis_x -= 1;
  }

  if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
    user_input->left_axis_x += 1;
  }

  if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
    user_input->right_axis_y -= 1;
  }
}

void parse_user_input(flecs::world *ecs) {
  int i = 0;
  if (user_input->right_axis_y < 0) {
    i = 1;
  }
  player.set<Velocity>({Vector2Scale(
      Vector2Rotate({0, -1}, (player.get<Rotation>()->value * M_PI) / 180),
      i * 300)});

  if (player.get<Velocity>()->value.x != 0 ||
      player.get<Velocity>()->value.y != 0) {
    init_thrust();
  };

  player.set<RotationalVelocity>(
      {static_cast<int>(user_input->left_axis_x * 300)});
}

void parse_destruct_queue() {
  for (flecs::entity e : destruct_queue) {
    e.destruct();
  }
  destruct_queue.clear();
}

float degrees_to_radians(int degrees) { return degrees * M_PI / 180.0; }
