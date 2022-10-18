
// includes
#include <QuickGame.hpp>
#include <pspctrl.h>
#include "collision.hpp"

// any namespaces
using namespace QuickGame;
using namespace QuickGame::Graphics;
using namespace QuickGame::Input;
using namespace QuickGame::Audio;





int main(int argc, char** argv){
    // initalize QG
    QuickGame::init();    
    
    // set camera to 2d
    set2D();

    // various draw functions needed
    bool isTitle = true;
    bool isLevelSelect = false;
    bool isBasic = false;
    bool isCurves = false;
    bool isPause = false;

    // sprite loading

    // basic map
    Sprite basicMap({0,0}, {480, 288}, {"maps/pngs/test.png", 0, 0});
    basicMap.layer = -1;
    basicMap.transform.position.x = 240;
    basicMap.transform.position.y = 140;

    // curves map
    Sprite curveMap({0,0}, {480, 288}, {"maps/pngs/curves.png", 1, 0});
    curveMap.layer = -1;
    curveMap.transform.position.x = 240;
    curveMap.transform.position.y = 130;

    // character sprite
    Sprite character({240, 136}, {30, 53}, {"sprites/character/character.png", 1, 0});
    character.transform.scale.x *= 0.5;
    character.transform.scale.y *=0.5;

    // title screen sprite
    Sprite title({0,0}, {480, 288}, {"screens/title.png", 1, 0});
    title.layer = 1;
    title.transform.position.x = 240;
    title.transform.position.y = 140;

    // level select screen sprite
    Sprite levelSelect({0,0}, {480, 288}, {"screens/level select.png", 1, 0});
    levelSelect.layer = 1;
    levelSelect.transform.position.x = 240;
    levelSelect.transform.position.y = 140;

    // pause menu screen sprite
    Sprite pauseMenu({0,0}, {480, 288}, {"screens/pause.png", 1, 0});
    pauseMenu.layer = 4;
    pauseMenu.transform.position.x = 240;
    pauseMenu.transform.position.y = 140;


    /* not finished / files dont exist yet but will do, commented out for now
    
    // red enemy (level 1) sprite
    Sprite redBasic({0,0}, {16,26}, {"sprites/enemies/red/enemy.png", 0, 0})
    
    // blue enemy (level 2) sprite
    Sprite blueBasic({0,0}, {16,26}, {"sprites/enemies/blue/enemy.png", 0, 0})

    // green enemy (level 3) sprite
    Sprite greenBasic({0,0}, {16,26}, {"sprites/enemies/green/enemy.png", 0, 0})
    
    // purple enemy (level 4) sprite
    Sprite purpleBasic({0,0}, {16,26}, {"sprites/enemies/purple/enemy.png", 0, 0})
    
    // black enemy (level 5) sprite
    Sprite blackBasic({0,0}, {16,26}, {"sprites/enemies/black/enemy.png", 0, 0})
    */

    // simple confirm click
    Clip click("audio/click.wav", false, false);

    // set camera; may be unneeded but we leave it in
    QGCamera2D camera = QGCamera2D();
    camera.position.x = 0;
    camera.position.y = 0;
    camera.rotation = 0;

    //set camera to this camera
    QuickGame::Graphics::set_camera(camera);

    while(running()){
        if(!isPause){
            update();
        }
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
        set2D();

        if(isTitle){
            title.draw();
            if(button_pressed(PSP_CTRL_CROSS)){
                isTitle = false;
                isLevelSelect = true;
            }
        }

        if(isLevelSelect) {
            levelSelect.draw();
            if(button_pressed(PSP_CTRL_LTRIGGER)) {
                isLevelSelect = false;
                isBasic = true;
            }
            if(button_pressed(PSP_CTRL_RTRIGGER)) {
                isLevelSelect = false;
                isCurves = true;
            }
        }

        if(isBasic) {
            basicMap.draw();
            character.draw();
            
            if(button_pressed(PSP_CTRL_START)) { 
                isPause = true;
                
            }
            
        }  
        
        if(isPause) {
            pauseMenu.draw();
            if(button_released(PSP_CTRL_START)) {
                isPause = false;
            }
        }
        
        

        if(isCurves) {
            curveMap.draw();
            character.draw();
            if(button_pressed(PSP_CTRL_START)) { 
                isPause = true;
                isCurves = false;
            }
        }

        end_frame(true);
        
    }

    QuickGame::terminate();
    return 0;
}
