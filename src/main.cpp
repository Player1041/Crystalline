#include <QuickGame.hpp>
#include <pspctrl.h>

using namespace QuickGame;
using namespace QuickGame::Graphics;
using namespace QuickGame::Input;
using namespace QuickGame::Audio;





int main(int argc, char** argv){
    QuickGame::init();    

    set2D();

    Sprite testMap({0,0}, {480, 288}, {"maps/pngs/test.png", 0, 0});
    testMap.layer = -1;
    testMap.transform.position.x = 240;
    testMap.transform.position.y = 140;

    Sprite curveMap({0,0}, {480, 288}, {"maps/pngs/curves.png", 1, 0});
    curveMap.layer = -1;
    curveMap.transform.position.x = 240;
    curveMap.transform.position.y = 120;


    Sprite character({240, 136}, {30, 53}, {"sprites/character/char v2 front.png", 1, 0});
    character.transform.scale.x *= 0.5;
    character.transform.scale.y *=0.5;

    Sprite blueEnemy({240, 136}, {20, 20}, {"sprites/enemies/blue/front.png", 0 ,0});
    blueEnemy.transform.position.x = 240;
    blueEnemy.transform.position.y = 120;


    Clip click("audio/click.wav", false, false);


    Sprite bg({0,0}, {384, 384}, {"maps/pngs/bg.png", 0, 0});
    bg.layer = -2;
    bg.transform.scale.x *= 5;
    bg.transform.scale.y *= 5;
    

    QGCamera2D camera = QGCamera2D();
    camera.position.x = 0;
    camera.position.y = 0;
    camera.rotation = 0;


    QuickGame::Graphics::set_camera(camera);

    while(running()){
        update();

        if(button_held(PSP_CTRL_UP)) {
            if(character.transform.position.y > 10) {
                character.transform.position.y += 1.5f;
            //camera.position.y += 2.0f;
            }
        }

        if(button_held(PSP_CTRL_DOWN)) {
            if(character.transform.position.y < 272) {
                character.transform.position.y -= 1.5f;
                //camera.position.y -= 2.0f;
            }
        }

        if(button_held(PSP_CTRL_RIGHT)) {
            if(character.transform.position.x < 480) {
                character.transform.position.x += 1.5f;
            // camera.position.x += 2.0f;
            }
        }

        if(button_held(PSP_CTRL_LEFT)) {
            if(character.transform.position.x > 10) {
                character.transform.position.x -= 1.5f;
                //camera.position.x -= 2.0f;
            }
        }

        if(button_pressed(PSP_CTRL_CROSS)) {
            click.play(0);
        }

        
        start_frame();
        clear();

        testMap.draw();
        
        if(button_pressed(PSP_CTRL_SQUARE)){
            blueEnemy.draw();
        }
        if(button_held(PSP_CTRL_START)) {
            curveMap.draw();
        }
        
        character.draw();

        end_frame(true);
    }

    QuickGame::terminate();
    return 0;
}
