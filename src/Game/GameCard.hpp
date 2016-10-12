#ifndef GAMECARD_HPP_INCLUDED
#define GAMECARD_HPP_INCLUDED

#include <basic.h>
#include <Data/Card.hpp>
#include <Interface/Platte.hpp>
#include <Interface/SelectObject.hpp>

namespace ValueStatus{
    typedef enum Value_Status {
        Normal = 0,
        Reinforced = 1,
        Weakened = -1
    } Value_Status;
}

class GameCard{
    private:
    F2C::Sprite sprMonster;
    static F2C::SimpleSprite sprBG;
    static F2C::SimpleSprite sprBack;
    static Platte pltBorder;
    static F2C::FontSprite fsprValues;
    static std::map< CardElement::Card_Element, F2C::SimpleSprite > ssprElements;
    static std::map< ValueStatus::Value_Status, F2C::Color > valueStatusColor;

    std::string lastMonsterFilename;

    public:
    int x;
    int y;
    int z;
    bool flipOpen;
    Card card;
    F2C::Color color;
    ValueStatus::Value_Status valueStatus;

    static F2C::Rect cardSize;

    static void loadElementBitmap(CardElement::Card_Element element, std::string filename);
    static void loadFontBitmap(std::string filename);
    static void loadBorderPlatte(std::string filename);
    static void loadBackBitmap(std::string filename);
    static void setValueStatusColor(ValueStatus::Value_Status status, F2C::Color color);

    GameCard();

    void update();
    void render();
};

#endif // GAMECARD_HPP_INCLUDED
