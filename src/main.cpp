#include <QuickGame.h>

int main(int argc, char** argv) {
    if (QuickGame_Init() < 0)
        return 1;

    QuickGame_Graphics_Set2D();

    while(QuickGame_Running())  {

    }

    QuickGame_Terminate();
    return 0;
}