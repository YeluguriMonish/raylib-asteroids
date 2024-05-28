#pragma once
#include "entities.h"
#include "components.h"
#include "globals.h"
#include "utils.h"
#include <flecs.h>
#include <raylib.h>
#include <raymath.h>
#include <vector>

flecs::entity player;
flecs::entity is_positioned_relative_to;
std::vector<flecs::entity> destruct_queue;

void init_relationships() { is_positioned_relative_to = ecs.entity(); }

void init_player() {
  player = ecs.entity("player");
  player.set<Velocity>({0, 0});
  player.set<Position>({400, 225});
  player.set<Sprite>({LoadTexture("../resources/player/ship.png")});
  player.set<Rotation>({0});
  player.set<RotationalVelocity>({0});
  player.set<ConditionalRender>(
      {false, LoadTexture("../resources/player/flame.png")});
  player.set<Hitbox>({Rectangle(), {25, 25}, 6}); // defined in system
}

void init_thrust() {
  float horizontal_offset = 15;
  float vertical_offset = 64;

  flecs::entity thrust_left = ecs.entity("thrust_left");
  flecs::entity thrust_right = ecs.entity("thrust_right");
  thrust_left.add(is_positioned_relative_to, player);
  thrust_left.set<Position>({-horizontal_offset, vertical_offset});
  thrust_left.set<Rotation>({0});
  thrust_left.set<Sprite>({LoadTexture("../resources/player/flame.png")});
  destruct_queue.push_back(thrust_left);
  thrust_right.add(is_positioned_relative_to, player);
  thrust_right.set<Position>({horizontal_offset, vertical_offset});
  thrust_right.set<Rotation>({0});
  thrust_right.set<Sprite>({LoadTexture("../resources/player/flame.png")});
  destruct_queue.push_back(thrust_right);
}

void init_laser() {
  flecs::entity laser = ecs.entity();
  laser.set<Velocity>({0, 0});
  laser.set<Position>({400, 225});
  laser.set<Sprite>({LoadTexture("../resources/projecties/laser.png")});
  laser.set<Rotation>({player.get<Rotation>()->value});
}
