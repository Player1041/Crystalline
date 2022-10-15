/*#include <QuickGame.hpp>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGTexture_t characterTex = QuickGame_Texture_Load("./sprites/character/life.png", 0, 0);
    QGSprite_t characterSprite = QuickGame_Sprite_Create_Alt(240, 136, 18, 16, characterTex);

    QuickGame_Graphics_Set2D();

    while(QuickGame_Running()){
        QuickGame_Graphics_Start_Frame();

        QuickGame_Graphics_Clear();

        QuickGame_Sprite_Draw(characterSprite);

        QuickGame_Graphics_End_Frame(true);
    }

    QuickGame_Sprite_Destroy(&characterSprite);
    QuickGame_Texture_Destroy(&characterTex);

    QuickGame_Terminate();
    return 0;
}
*/

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
        rotation = 0f
    }

    set_camera(camera)

    while(running()){
        update();
        start_frame();
        clear();

        sprite.draw();

        end_frame(true);
    }

    QuickGame::terminate();
    return 0;
}
