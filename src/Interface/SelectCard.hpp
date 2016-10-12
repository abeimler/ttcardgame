#ifndef SELECTCARD_HPP_INCLUDED
#define SELECTCARD_HPP_INCLUDED

#include <Interface/SelectObject.hpp>
#include <Game/GameCard.hpp>

class SelectCard : public  SelectObject{
    private:

    public:
    int x;
    int y;
    bool horizontal;

    SelectCard();

    void update();
};

#endif // SELECTCARD_HPP_INCLUDED
