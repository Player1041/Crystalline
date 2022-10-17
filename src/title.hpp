#include <QuickGame.hpp>

using namespace QuickGame;
using namespace QuickGame::Graphics;
using namespace QuickGame::Input;
using namespace QuickGame::Audio;

/*
draw an image, make it swap to level.hpp when PSP_CTRL_CROSS is pressed
play a noise when PSP_CTRL_CROSS is pressed; src/build/sounds/startup.wav
*/

    Sprite title({0,0}, {480, 288}, {"sprites/title.png", 0, 0});
void titleMethod() {
    title.layer = -1;
    title.transform.position.x = 240;
    title.transform.position.y = 140;

    return title.draw();
}