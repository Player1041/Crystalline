#include <QuickGame.hpp>

int main(int argc, char** argv){
    QuickGame::init();    
    QuickGame::Graphics::set2D();

    QuickGame::Graphics::Sprite CharSprite({240, 136}, {256, 256}, {"./sprites/character/life.png", 0, 0});

    while(QuickGame::running()){
        QuickGame::Graphics::start_frame();
        QuickGame::Graphics::clear();

        CharSprite.draw();

        QuickGame::Graphics::end_frame(true);
    }

    QuickGame::terminate();
    return 0;
}