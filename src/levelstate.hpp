#pragma once
#include <QuickGame.hpp>
#include <pspctrl.h>
#include <memory>
#include <map>
#include "collision.hpp"
#include "state.hpp"
#include <pspkernel.h>
#include "state.hpp"

using namespace QuickGame;
using namespace QuickGame::Graphics;

class LevelState final : public State {
    std::shared_ptr<Sprite> levelSelect; // level select screen sprite

public:
    LevelState();
    ~LevelState() = default;

    auto update(double dt) -> void override;
    auto draw(double dt) -> void override;
};
