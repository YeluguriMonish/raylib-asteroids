#pragma once
#include "systems.h"
#include "components.h"
#include "entities.h"
#include "flecs.h"
#include "globals.h"
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

void update_position(flecs::iter it, Position *p, Velocity *v) {
  for (auto i : it) {
    p[i].value.x += v[i].value.x * it.delta_time();
    p[i].value.y += v[i].value.y * it.delta_time();
  }
}

void update_rotation(flecs::iter it, Rotation *r, RotationalVelocity *rv) {
  for (auto i : it) {
    r[i].value += rv[i].value * it.delta_time();
    if (r[i].value > 360) {
      r[i].value -= 360;
    } else if (r[i].value < 0) {
      r[i].value += 360;
    }
  }
}

void draw_texture(flecs::iter it, Sprite *s, Position *p, Rotation *r) {
  for (auto i : it) {
    if (it.entity(i).has(is_positioned_relative_to, flecs::Wildcard)) {
      flecs::entity related_entity =
          it.entity(i).target(is_positioned_relative_to);
      const Position *related_entity_position = related_entity.get<Position>();
      const Rotation *related_entity_rotation = related_entity.get<Rotation>();
      rlPushMatrix();
      rlTranslatef(related_entity_position->value.x,
                   related_entity_position->value.y, 0);
      rlRotatef(related_entity_rotation->value, 0, 0, 1);
    }
    DrawTexturePro(s[i].value,
                   (Rectangle){0, 0, static_cast<float>(s[i].value.width),
                               static_cast<float>(s[i].value.height)},
                   (Rectangle){p[i].value.x, p[i].value.y,
                               static_cast<float>(s[i].value.width * 10),
                               static_cast<float>(s[i].value.height * 10)},
                   {static_cast<float>((s[i].value.width * 10 / 2)),
                    static_cast<float>((s[i].value.height * 10 / 2))},
                   r[i].value, WHITE);

    if (it.entity(i).has(is_positioned_relative_to, flecs::Wildcard)) {
      rlPopMatrix();
    }
  }
}

void draw_hitbox(flecs::iter it, Sprite *s, Position *p, Rotation *r,
                 Hitbox *h) {
  for (auto i : it) {
    DrawRectanglePro({p[i].value.x, p[i].value.y,
                      static_cast<float>(s[i].value.width) * h[i].scale,
                      static_cast<float>(s[i].value.height) * h[i].scale},
                     {h[i].offset.x, h[i].offset.y}, r[i].value, RED);
  }
}

void init_systems() {
  flecs::system update_position_sys =
      ecs.system<Position, Velocity>().iter(update_position);
  flecs::system update_rotation_sys =
      ecs.system<Rotation, RotationalVelocity>().iter(update_rotation);
  flecs::system draw_hitbox_sys =
      ecs.system<Sprite, Position, Rotation, Hitbox>().iter(draw_hitbox);

  flecs::system draw_texture_sys =
      ecs.system<Sprite, Position, Rotation>().iter(draw_texture);
  draw_texture_sys.add(flecs::PostUpdate);
}

void init_world() {}
