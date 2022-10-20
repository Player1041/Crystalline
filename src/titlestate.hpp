#pragma once
#include "levelstate.hpp"

class TitleState final : public State {
    std::shared_ptr<Sprite> title; // title screen sprite
    std::shared_ptr<Audio::Clip> startup;//startup noise
public:
    TitleState() {
        // title screen sprite
        title = std::make_shared<Sprite>(
            QGVector2{240,140}, 
            QGVector2{480, 288}, 
            QGTexInfo{"screens/title.png", 1, 0}
        );
        title->layer = 1;
    
        startup = std::make_shared<Audio::Clip>("sounds/startup.wav", false, false);

        sceKernelDcacheWritebackInvalidateAll();
    }
    ~TitleState() = default;

    auto update(double dt) -> void override {
        if(Input::button_pressed(PSP_CTRL_CROSS)){
            startup->play(0);
            StateManagement::set_state(std::make_shared<LevelState>());
        }
    }

    auto draw(double dt) -> void override {
        title->draw();
    }
};
