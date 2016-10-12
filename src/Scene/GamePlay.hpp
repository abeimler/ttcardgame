#ifndef GAMEPLAY_HPP_INCLUDED
#define GAMEPLAY_HPP_INCLUDED

#include <GameBasic.h>
#include <Scene/MainTitle.hpp>

class GamePlay : public GameState{
    private:
    F2C::uint players;
    F2C::uint cards;
    std::vector<GameHand> hands;
    GameField field;
    F2C::FontSprite fsprPlayer;
    F2C::FontSprite fsprInfo;
    F2C::FontSprite fsprSwitch;
    F2C::FontSprite fsprPoints;
    std::vector<std::string> strPoints;
    size_t fieldw;
    size_t fieldh;

    public:
    GamePlay();
    GamePlay(F2C::uint players,F2C::uint cards, size_t fieldw, size_t fieldh);

    void Init();
    void Cleanup(){}
    void Update();
    void Render();
};

#endif // GAMEPLAY_HPP_INCLUDED
