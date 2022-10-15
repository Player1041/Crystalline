#include <QuickGame.h>

int main(int argc, char** argv){
    if(QuickGame_Init() < 0)
        return 1;

    QGTexture_t characterTex = QuickGame_Texture_Load("./sprites/character/life.png", 0, 0);
    QGSprite_t characterSprite = QuickGame_Sprite_Create_Alt(240, 136, 256, 256, characterTex);

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