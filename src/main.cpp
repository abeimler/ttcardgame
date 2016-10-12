#include <GameBasic.h>
#include <Scene/MainTitle.hpp>

int main(int argc,const char** argv){
    //Windowd Size
    int wndWidth = 1024;
    int wndHeight = 728;

    //Title, fullscreen and color depth
    std::string title = "Fantasy2C: Final Fantasy Triple Traid Card Game";
    bool fullscreen = false;
    F2C::uint wndBits = 32;

    //Create Window App
    Engine::Game.Init(title,wndWidth,wndHeight,wndBits,fullscreen);

    //Settings
    Engine::Game.framerate = 60.0f;
    Engine::Game.renderingWholeStack = true;
    Engine::Game.showFPS = true;
    Engine::Game.MaxFramerateON = true;
    Engine::Game.useESC = false;

    initGame();

    Engine::Game.PushState(new MainTitle);

    //Game Loop
    while(Engine::Game.Running()){
        #ifdef _DEBUG
        F2C::Timer timer;
        #endif
        //update State
        Engine::Game.UpdateState();

        //Windows Handle
        Engine::Game.HandleEvents();

        //Game update
        Engine::Game.Update();
        #ifdef _DEBUG
        printf("Update Time: %6.4f milisec\n",timer.getTimeMilisec());
        timer.reset();
        #endif

        //Game Rendering
        Engine::Game.Render();
        #ifdef _DEBUG
        printf("Render Time: %6.4f milisec\n\n",timer.getTimeMilisec());
        #endif
    }

    //Clean Window App
    Engine::Game.Cleanup();

    return 0;
}
