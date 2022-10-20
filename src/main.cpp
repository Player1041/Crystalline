
// includes
#include <QuickGame.hpp>
#include <pspctrl.h>
#include <memory>
#include <map>
#include "collision.hpp"
#include "state.hpp"

// any namespaces
using namespace QuickGame;
using namespace QuickGame::Graphics;

std::shared_ptr<Audio::Clip> click; //click
std::shared_ptr<Audio::Clip> startup;//startup noise

namespace StateManagement {
    std::vector<std::shared_ptr<State>> stateStack;
    auto set_state(std::shared_ptr<State> state) {
        stateStack.clear();
        stateStack.push_back(state);
        stateStack.shrink_to_fit();
    }
} // StateManagement

class TitleState final : public State {
    std::shared_ptr<Sprite> title; // title screen sprite

    public:
    TitleState() {
        // title screen sprite
        title = std::make_shared<Sprite>(
            QGVector2{240,140}, 
            QGVector2{480, 288}, 
            QGTexInfo{"screens/title.png", 1, 0}
        );
        title->layer = 1;
    }
    ~TitleState() = default;

    auto update(double dt) -> void override {
        if(Input::button_pressed(PSP_CTRL_CROSS)){
            startup->play(0);
            // set_state(std::make_shared<MenuState>());
        }
    }

    auto draw(double dt) -> void override {
        title->draw();
    }
};

bool isLevelSelect = false;
bool isBasic = false;
bool isCurves = false;
bool isPause = false;
bool stopEnemy = false;
bool isDead = false;
int wave = 1;
int lives = 3;

std::map<int, std::string> enemyRanks = {
    {0, "red"},
    {1, "blue"},
    {2, "green"},
    {3, "purple"},
    {4, "black"}
};

std::shared_ptr<Sprite> enemySprites[5];    

std::shared_ptr<Sprite> basicMap;
std::shared_ptr<Sprite> curveMap; // curves map
std::shared_ptr<Sprite> character; // character sprite
std::shared_ptr<Sprite> levelSelect; // level select screen sprite
std::shared_ptr<Sprite> pauseMenu; // pause menu screen sprite
std::shared_ptr<Sprite> gameOver;


auto update() -> void {
    if(Input::button_held(PSP_CTRL_UP)) 
        character->transform.position.y += 1.5f;
    
    if(Input::button_held(PSP_CTRL_DOWN))
        character->transform.position.y -= 1.5f;
    
    if(Input::button_held(PSP_CTRL_RIGHT))
        character->transform.position.x += 1.5f;
        
    if(Input::button_held(PSP_CTRL_LEFT)) 
        character->transform.position.x -= 1.5f;
    
    if(character->transform.position.y < 10) 
        character->transform.position.y = 10;

    if(character->transform.position.x < 10) 
        character->transform.position.x = 10;
    
    if(character->transform.position.y > 272)
        character->transform.position.y = 272;

    if(character->transform.position.x > 480)
        character->transform.position.x = 480;

    // Logic that should be here, not draw

    //collision for out of bounds
    /*
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
    //if(character->intersects(redEnemy)) {
    //    lives = lives -1;
    //} 

    if(isLevelSelect) {
        if(Input::button_pressed(PSP_CTRL_LTRIGGER)) {
            isLevelSelect = false;
            isBasic = true;
            click->play(0);
        }
        if(Input::button_pressed(PSP_CTRL_RTRIGGER)) {
            isLevelSelect = false;
            isCurves = true;
            click->play(0);
        }
    }

    if(isBasic || isCurves) {
        if(Input::button_pressed(PSP_CTRL_START)) { 
            isPause = true;
            stopEnemy = false;
            click->play(0);
        }
    }

    if(isPause){
        if(Input::button_pressed(PSP_CTRL_CIRCLE)) {
            isPause = false;
            click->play(0);
        }
    }

    if(!isDead) {
        if(lives = 0) {
            isDead = true;
            //pDeath.play(0);
        }
    }

    if(isDead) {
        if(Input::button_pressed(PSP_CTRL_SQUARE)) {
            isLevelSelect = true;
            isBasic = false;
            isCurves = false;
        }
    }    
}

auto draw() -> void {
    
    if(isLevelSelect) {
        levelSelect->draw();
    }
    if(isBasic) {
        basicMap->draw();
    } else if(isCurves) {
        curveMap->draw();
    }
    
    //We're actually playing the game
    character->draw();
    //redEnemy->draw();
    
    if(isPause) {
        pauseMenu->draw();
        //FIXME: Is this draw call necessary?
        character->draw();
    }

    if(isDead) 
        gameOver->draw();
}

auto main() -> int {
    // Initialize
    QuickGame::init();    
    
    // set camera to 2d
    Graphics::set2D();

    // basic map
    // QGTexture mapCollBase = *QuickGame_Texture_Load("maps/pngs/test.png", 0, 0);
    
    basicMap = std::make_shared<Sprite>(
        QGVector2{240,140}, 
        QGVector2{480, 288}, 
        QGTexInfo{"maps/pngs/test.png", 0, 0}
    );
    basicMap->layer = -1;

    // curves map
    curveMap = std::make_shared<Sprite>(
        QGVector2{240,130}, 
        QGVector2{480, 288}, 
        QGTexInfo{"maps/pngs/curves.png", 1, 0}
    );
    curveMap->layer = -1;

    // character sprite
    character = std::make_shared<Sprite>(
        QGVector2{240, 136}, 
        QGVector2{30, 53}, 
        QGTexInfo{"sprites/character/character.png", 1, 0}
    );
    character->transform.scale.x *= 0.5f;
    character->transform.scale.y *= 0.5f;

    // level select screen sprite
    levelSelect = std::make_shared<Sprite>(
        QGVector2{240,140}, 
        QGVector2{480, 288}, 
        QGTexInfo{"screens/level select.png", 1, 0}
    );
    levelSelect->layer = 1;

    // pause menu screen sprite
    pauseMenu = std::make_shared<Sprite>(
        QGVector2{240,140}, 
        QGVector2{480, 288}, 
        QGTexInfo{"screens/pause.png", 1, 0}
    );
    pauseMenu->layer = 4;

    gameOver = std::make_shared<Sprite>(
        QGVector2{240,140}, 
        QGVector2{480, 288}, 
        QGTexInfo{"screens/game over.png", 1, 0}
    );
    gameOver->layer = 4;
    

    for(int i = 0; i < 5; i++) {
        enemySprites[i] = std::make_shared<Sprite>(
            QGVector2{100, 120},
            QGVector2{16, 26},
            QGTexInfo{
                ("sprites/enemies/" + enemyRanks[i] + "/front.png").c_str(), 
                0, 0
            }
        );
    }

    //pDeath = std::make_shared<Audio::Clip>("sounds/death.wav", false, false); //player death
    //eDeath = std::make_shared<Audio::Clip>("sounds/edeath.wav", false, false); //enemy death
    //bDeath = std::make_shared<Audio::Clip>("sounds/bdeath.wav", false, false); //boss death

    // FILE* highScore = fopen("data/highscores.txt", "a+")
    // or you should use std::fstream here

    QGTimer timer;
    QuickGame_Timer_Start(&timer);

    // Audio Loading
    click = std::make_shared<Audio::Clip>("sounds/click.wav", false, false);
    startup = std::make_shared<Audio::Clip>("sounds/startup.wav", false, false);

    StateManagement::set_state(std::shared_ptr<TitleState>());

    while(running()){
        auto dt = QuickGame_Timer_Delta(&timer);

        if (!StateManagement::stateStack.empty()) {
            Input::update();
            StateManagement::stateStack.back()->update(dt);

            Graphics::start_frame();
            Graphics::clear();
            Graphics::set2D();

            StateManagement::stateStack.back()->draw(dt);

            Graphics::end_frame(true);
        }
    }

    // fclose(highScore)

    QuickGame::terminate();
    return 0;
}
