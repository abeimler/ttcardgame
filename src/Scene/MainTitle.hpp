#ifndef MAINTITLE_HPP_INCLUDED
#define MAINTITLE_HPP_INCLUDED

#include <GameBasic.h>
#include <Scene/GamePlay.hpp>

class MainTitle : public GameState{
    private:
    SelectFont mainFont;
    F2C::SimpleSprite bgTitle;

    public:
    void Init();
    void Cleanup(){}
    void Update();
    void Render();
};

#endif // MAINTITLE_HPP_INCLUDED
