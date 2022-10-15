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

int main(int argc, char** argv){
    QuickGame::init();    
    QuickGame::Graphics::set2D();

    QuickGame::Graphics::Sprite sprite({240, 136}, {256, 256}, {"./sprites/character/life.png", 0, 0});

    while(QuickGame::running()){
        QuickGame::Graphics::start_frame();
        QuickGame::Graphics::clear();

        sprite.draw();

        QuickGame::Graphics::end_frame(true);
    }

    QuickGame::terminate();
    return 0;
}