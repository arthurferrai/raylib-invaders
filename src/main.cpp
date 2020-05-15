/*******************************************************************************************
* attempt to make a space invaders
********************************************************************************************/
#include <memory>
#include <cassert>

#include "raylib.h"
#include "scene/first_scene.h"
#include "game/game.h"

int main() {
  Game::Instance().start(std::make_unique<FirstScene>());
}