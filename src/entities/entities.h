#pragma once
#include "flecs.h"
#include <vector>

extern flecs::entity player;
extern flecs::entity is_positioned_relative_to;
extern std::vector<flecs::entity> destruct_queue;

void init_relationships(flecs::world *ecs);

void init_player();

void init_thrust();

void init_laser();

void init_relationships();
