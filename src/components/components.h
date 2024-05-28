#pragma once
#include <raylib.h>

struct Position {
  Vector2 value;
};

struct Velocity {
  Vector2 value;
};

struct Sprite {
  Texture2D value;
};

struct Rotation {
  int value;
};

struct RotationalVelocity {
  int value;
};

struct ConditionalRender {
  bool value;
  Texture2D texture;
};

struct Hitbox {
  Rectangle shape;
  Vector2 offset;
  float scale;
};
