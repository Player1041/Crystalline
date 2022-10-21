
// includes
#include <QuickGame.hpp>
#include <pspctrl.h>
#include <memory>
#include <map>
#include "collision.hpp"
#include "titlestate.hpp"
#include <pspkernel.h>

// any namespaces
using namespace QuickGame;
using namespace QuickGame::Graphics;

std::shared_ptr<Audio::Clip> click; //click
std::shared_ptr<Audio::Clip> pause; // pause

/**
 * @brief Defines a basic enemy to draw on screen
 * Enemy has a specific type (color)
 * Enemy update makes it chase players in a range
 * Transform is its current position
 *
 */
class Enemy {
    public:
    /**
     * @brief Construct a new Enemy object
     * 
     * @param type Enemy color type based on enemyRank
     */
    Enemy(int type) : m_Type(type) {}
    virtual ~Enemy() = default;

    /**
     * @brief Chase the player
     * 
     * @param playerPosition Player position
     * @param dt Delta Time
     */
    auto update(QGVector2 playerPosition, double dt) -> void {
        // Calculate difference between our positions
        auto diff = QGVector2{playerPosition.x - transform.position.x, playerPosition.y - transform.position.y};
        // Get length via distance formula = sqrtf(x^2 + y^2 + ...)
        auto len = sqrtf(diff.x * diff.x + diff.y * diff.y);

        // Do not attempt normalization below length of 1
        if(len > 1.0f){
            diff.x /= len;
            diff.y /= len;
        }

        // If we're within a certain range, chase it
        if(len < 200){
            transform.position.x += diff.x * 0.8f;
            transform.position.y += diff.y * 0.8f;
        }
    }

    QGTransform2D transform;
    int m_Type;
};

/**
 * @brief Manages Enemy Spawns
 * enemies Map contains a list of existing enemies
 * ecount Is the enemy count
 * add_enemy() method Creates new enemies
 * update() method Updates all enemies
 * draw() method Draws all enemies
 */
class EnemyManager final {
    public:
    std::map<int, std::shared_ptr<Enemy>> enemies;
    int ecount;



    EnemyManager() {
        enemies.clear();
    }

    /**
     * @brief Create an enemy at a position with a set type
     * 
     * @param position Position
     * @param type Type
     */
    auto add_enemy(QGVector2 position, int type) -> void {
        enemies.emplace(
            ecount, 
            std::make_shared<Enemy>(type)
        );
        enemies[ecount]->transform.position = position;
        enemies[ecount]->transform.rotation = 0;
        enemies[ecount]->transform.scale = {16, 26};

        ecount++;
    }

    /**
     * @brief Create a random enemy type at a position
     * 
     * @param position Position
     */
    auto add_enemy_random(QGVector2 position) -> void {
        add_enemy(position, rand() % 5);
    }

    /**
     * @brief Updates all enemies
     * 
     * @param pos Player pos / pos to track
     * @param dt Delta Time
     */
    auto update(QGVector2 pos, double dt) -> void {
        //TODO: If you kill an enemy, add it to the ids list
        // What conditions result in the enemy dying?
        std::vector<int> ids;

        for(auto& [id, e] : enemies) {
            e->update(pos, dt);
        }

        for(auto& id : ids) {
            enemies.erase(id);
        }
    }

    /**
     * @brief Draws all enemies onto the screen
     * 
     * @param eArray Enemy Sprite Array
     */
    auto draw(std::array<std::shared_ptr<Sprite>, 5>& eArray) -> void {
        for(auto& [id, e] : enemies) {
            eArray[e->m_Type]->transform = e->transform;
            eArray[e->m_Type]->draw();
        }
    }
};

/**
 * @brief Main game state
 * 
 */
class GameState final : public State {
    /**
     * @brief Enemy Ranks based on previous comment
     * 
     */
    std::map<int, std::string> enemyRanks = {
        {0, "red"},
        {1, "blue"},
        {2, "green"},
        {3, "purple"},
        {4, "black"}
    };

    std::array<std::shared_ptr<Sprite>, 5> enemySprites;    

    std::shared_ptr<Sprite> basicMap;
    std::shared_ptr<Sprite> curveMap; // curves map
    std::shared_ptr<Sprite> character; // character sprite
    std::shared_ptr<Sprite> pauseMenu; // pause menu screen sprite
    std::shared_ptr<Sprite> gameOver;

    int m_LevelNumber;

    bool isPause = false;
    bool isDead = false;
    int wave = 1;
    int lives = 3;

    EnemyManager eman;
public:
    /**
     * @brief Construct a new Game State object
     * 
     * @param level_number Level to load (0 = basic, 1 = curves)
     */
    
    GameState(int level_number): m_LevelNumber(level_number) {
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
                    ("sprites/enemies/" + enemyRanks[i] + "/enemy.png").c_str(), 
                    1, 0
                }
            );
        }

        for(int i = 0; i < 5; i++) {
            eman.add_enemy_random({
                static_cast<float>(rand() % 480), 
                static_cast<float>(rand() % 272)
            });
        }
    }
    ~GameState() = default;

    /**
     * @brief Update the game state
     * 
     * @param dt Delta Time
     */

    float damageTimeout = 0.0f;

    auto update(double dt) -> void override {
        // Move character
        if(Input::button_held(PSP_CTRL_UP)) 
            character->transform.position.y += 1.5f;
        
        if(Input::button_held(PSP_CTRL_DOWN))
            character->transform.position.y -= 1.5f;

        if(Input::button_held(PSP_CTRL_RIGHT))
            character->transform.position.x += 1.5f;

        if(Input::button_held(PSP_CTRL_LEFT)) 
            character->transform.position.x -= 1.5f;

        // Character bounds check
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

        if(character->intersects(enemySprites)) {
            isDead = true;
        }
        // Check to pause
        if(Input::button_pressed(PSP_CTRL_START)) { 
            isPause = !isPause;
            pause->play(0);
        }

        if(isDead) {
            gameOver->draw();
        }

        if(isDead && Input::button_pressed(PSP_CTRL_SQUARE)) {
            // Go back to level state on death
            StateManagement::set_state(std::make_shared<LevelState>()); //Go back to level select
        }

        // If Not Paused, Update Enemies
        if(!isPause){
            eman.update(character->transform.position, dt);
        }
    }

    auto draw(double dt) -> void override {
        // Draw map
        if(m_LevelNumber == 0) {
            basicMap->draw();
        } else if(m_LevelNumber == 1) {
            curveMap->draw();
        }

        // Draw Enemies
        eman.draw(enemySprites);
        
        // Draw Pause Menu
        if(isPause) 
            pauseMenu->draw();
        
        // Draw Character (above pause if necessary)
        character->draw();
        
        // Draw Game Over
        if(isDead) 
            gameOver->draw();
    }
};

LevelState::LevelState() {
    // level select screen sprite
    levelSelect = std::make_shared<Sprite>(
        QGVector2{240,140}, 
        QGVector2{480, 288}, 
        QGTexInfo{"screens/level select.png", 1, 0}
    );
    levelSelect->layer = 1;
    sceKernelDcacheWritebackInvalidateAll();
}

/**
 * @brief Update -- choose basic or curved state
 * 
 * @param dt Unused
 */
auto LevelState::update(double dt) -> void {
    if(Input::button_pressed(PSP_CTRL_LTRIGGER)) {
        click->play(0);
        //Set State Basic
        StateManagement::set_state(std::make_shared<GameState>(0));
    }
    if(Input::button_pressed(PSP_CTRL_RTRIGGER)) {
        click->play(0);
        //Set State Curves
        StateManagement::set_state(std::make_shared<GameState>(1));
    }
}

/**
 * @brief Draw Level Selection Menu
 * 
 * @param dt Unused
 */
auto LevelState::draw(double dt) -> void {
    levelSelect->draw();
}

/**
 * @brief Entry point!
 * 
 */
auto main() -> int {
    // Initialize
    QuickGame::init();    
    
    // set camera to 2d
    Graphics::set2D();
    
    // FILE* highScore = fopen("data/highscores.txt", "a+")
    // or you should use std::fstream here
    // fclose(highScore)

    QGTimer timer;
    QuickGame_Timer_Start(&timer);

    // Audio Loading
    click = std::make_shared<Audio::Clip>("sounds/click.wav", false, false);
    pause = std::make_shared<Audio::Clip>("sounds/pause.wav",false, false);
    //pDeath = std::make_shared<Audio::Clip>("sounds/death.wav", false, false); //player death
    //eDeath = std::make_shared<Audio::Clip>("sounds/edeath.wav", false, false); //enemy death
    //bDeath = std::make_shared<Audio::Clip>("sounds/bdeath.wav", false, false); //boss death

    // Set base state
    StateManagement::set_state(std::make_shared<TitleState>());

    // While running
    while(running()){
        auto dt = QuickGame_Timer_Delta(&timer);

        // Make sure we have a state to use
        if (StateManagement::stateStack.empty())
            continue;

        // Update Sequence
        Input::update();
        StateManagement::stateStack.back()->update(dt);

        // Draw Sequence
        Graphics::start_frame();
        Graphics::clear();
        Graphics::set2D();
        StateManagement::stateStack.back()->draw(dt);
        Graphics::end_frame(true);   
    }

    // Terminate
    QuickGame::terminate();
    return 0;
}
