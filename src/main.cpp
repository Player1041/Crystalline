
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

    // various variables defined
    bool isTitle = true;
    bool isLevelSelect = false;
    bool isBasic = false;
    bool isCurves = false;
    bool isPause = false;
    bool stopEnemy = false;
    bool isDead = false;
    int wave = 1;
    int lives = 3;
    



    // sprite loading

    // basic map
    QGTexture mapCollBase = *QuickGame_Texture_Load("maps/pngs/test.png", 0, 0);
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

    Sprite gameOver({0,0}, {480, 288}, {"screens/game over.png", 1, 0});
    gameOver.layer = 4;
    gameOver.transform.position.x = 240;
    gameOver.transform.position.y = 140;
    
    // red enemy (level 1) sprite
    Sprite redEnemy({100,120}, {16,26}, {"sprites/enemies/red/enemy.png", 0, 0});
    
    // blue enemy (level 2) sprite
    Sprite blueEnemy({100,120}, {16,26}, {"sprites/enemies/blue/enemy.png", 0, 0});

    // green enemy (level 3) sprite
    Sprite greenEnemy({100,120}, {16,26}, {"sprites/enemies/green/enemy.png", 0, 0});
    
    // purple enemy (level 4) sprite
    Sprite purpleEnemy({100,120}, {16,26}, {"sprites/enemies/purple/enemy.png", 0, 0});
    
    // black enemy (level 5) sprite
    Sprite blackEnemy({100,120}, {16,26}, {"sprites/enemies/black/enemy.png", 0, 0});

    // audio loading

    Clip click("sounds/click.wav", false, false); //click

    Clip startup("sounds/startup.wav", false, false); //startup noise

    //Clip pDeath("sounds/death.wav", false, false); //player death

    //Clip eDeath("sounds/edeath.wav", false, false); //enemy death

    //Clip bDeath("sounds/bdeath.wav", false, false); //boss death


    // set camera; may be unneeded but we leave it in
    QGCamera2D camera = QGCamera2D();
    camera.position.x = 0;
    camera.position.y = 0;
    camera.rotation = 0;

    //set camera to this camera
    QuickGame::Graphics::set_camera(camera);
    FILE *file = fopen("data/log.txt", "wr");
    // FILE highScore = fopen("data/highscores.txt", "a+")

    while(running()){
        if(!stopEnemy){
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

        
        start_frame();
        clear();
        set2D();

        if(isTitle){
            title.draw();
            if(button_pressed(PSP_CTRL_CROSS)){
                isTitle = false;
                isLevelSelect = true;
                startup.play(0);
            }
        }

        if(isLevelSelect) {
            levelSelect.draw();
            if(button_pressed(PSP_CTRL_LTRIGGER)) {
                isLevelSelect = false;
                isBasic = true;
                click.play(0);
            }
            if(button_pressed(PSP_CTRL_RTRIGGER)) {
                isLevelSelect = false;
                isCurves = true;
                click.play(0);
            }
        }

        if(isBasic) {
            basicMap.draw();
            character.draw();
            redEnemy.draw();
            if(button_pressed(PSP_CTRL_START)) { 
                isPause = true;
                stopEnemy = false;
                click.play(0);
            }
        }  

        if(isCurves) {
            curveMap.draw();
            character.draw();
            redEnemy.draw();
            if(button_pressed(PSP_CTRL_START)) { 
                isPause = true;
                stopEnemy = false;
                click.play(0);
            }
        }
        
        if(isPause) {
            pauseMenu.draw();
            character.draw();
            if(button_pressed(PSP_CTRL_CIRCLE)) {
                isPause = false;
                click.play(0);
            }
        }

        end_frame(true);
/*
        //collision for out of bounds
        int charx = character.transform.position.x + 2;
        int chary = character.transform.position.y + 2;
        int r = getRed(charx, chary, mapCollBase);
        if(r == -2003365){
            character.transform.position.x = 80;
            character.transform.position.y = 136;
            isPause = true;
        }
*/        
            //fprintf(file, "%d\n", r);

        //life system

        //commented out as pseudocode

        if(character.intersects(redEnemy)) {
            lives = lives -1;
        } 

        if(!isDead) {
            if(lives = 0) {
                isDead = true;
                //pDeath.play(0);
            }
        }

        if(isDead) {
            gameOver.draw();
            if(button_pressed(PSP_CTRL_SQUARE)) {
                isLevelSelect = true;
                isBasic = false;
                isCurves = false;
            }
        }

    }

    QuickGame::terminate();
    return 0;
}
