#include <QuickGame.hpp>

using namespace QuickGame;
using namespace QuickGame::Graphics;
using namespace QuickGame::Input;



int main(int argc, char** argv){
    QuickGame::init();    
    set2D();

    Sprite sprite({240, 136}, {18, 16}, {"sprites/character/life.png", 0, 0});

    QGCamera2D camera = {
        {x = 0, y = 0},
        rotation = 0f,
    };

    set_camera(camera)

    while(running()){
        update();
        start_frame();
        clear();

        sprite.draw();

        end_frame(true);
    };

    QuickGame::terminate();
    return 0;
}
