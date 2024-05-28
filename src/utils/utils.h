#pragma once
#include "flecs.h"

struct UserInput {
  float left_axis_x;
  float right_axis_y;
};

extern UserInput *user_input;

UserInput *init_user_input();

void read_user_input();

void parse_user_input(flecs::world *ecs);

void parse_destruct_queue();

float degrees_to_radians(int degrees);
