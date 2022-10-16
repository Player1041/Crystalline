#include <QuickGame.hpp>
#include <pspctrl.h>

using namespace QuickGame;
using namespace QuickGame::Graphics;
using namespace QuickGame::Input;
using namespace QuickGame::Audio;



int main(int argc, char** argv){
    QuickGame::init();    
    set2D();
    Sprite testMap({0,0}, {389, 306}, {"maps/pngs/test.png", 0, 0});
    testMap.layer = -1;
    testMap.transform.scale.x *= 3;
    testMap.transform.scale.y *= 3;
    Sprite character({240, 136}, {16, 18}, {"sprites/character/char v2 front.png", 1, 0});
    Clip click("audio/click.wav", false, false);
    
    QGCamera2D camera = QGCamera2D();
    camera.position.x = 0;
    camera.position.y = 0;
    camera.rotation = 0;

    QuickGame::Graphics::set_camera(camera);

    while(running()){
        update();

        if(button_held(PSP_CTRL_UP)) {
            character.transform.position.y += 2.0f;
            if(character.transform.position.y > 54) {
                camera.position.y += 2.0f;
            }
        }

        if(button_held(PSP_CTRL_DOWN)) {
            character.transform.position.y -= 2.0f;
            if(character.transform.position.y < 222) {
                camera.position.y -= 2.0f;
            }
        }

        if(button_held(PSP_CTRL_RIGHT)) {
            character.transform.position.x += 2.0f;
            if(character.transform.position.x > 384) {
                camera.position.x += 2.0f;
            }
        }

        if(button_held(PSP_CTRL_LEFT)) {
            character.transform.position.x -= 2.0f;
            if(character.transform.position.x <= 96) {
                camera.position.x -= 2.0f;
            }
        }

        if(button_pressed(PSP_CTRL_CROSS)) {
            click.play(0);
        }

        start_frame();
        clear();

        testMap.draw();
        character.draw();

        end_frame(true);
    }

    QuickGame::terminate();
    return 0;
}
