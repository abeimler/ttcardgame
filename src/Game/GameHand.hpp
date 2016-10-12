#ifndef GAMEHAND_HPP_INCLUDED
#define GAMEHAND_HPP_INCLUDED

#include <Game/GameCard.hpp>

class GameHand{
    private:
    std::vector<GameCard> gameCards;
    int selectedIndex;
    int hoverIndex;
    bool clickedonCard;

    bool isClicked(F2C::MouseEvent::Mouse event,F2C::Rect obj) const;
    bool isHover(F2C::Rect obj) const;

    F2C::Rect getCardCoord(size_t index) const;
    bool isClicked(size_t index) const;
    bool isHover(size_t index) const;

    public:
    int x;
    int y;
    int z;
    bool active;
    bool horizontal;
    bool flipOpen;
    bool flipSelected;
    F2C::Color color;
    std::vector<Card> cards;

    static F2C::Rect selectArea;
    static F2C::Rect selectHorizontalArea;

    GameHand();

    void resetSelect();

    const GameCard* getGameCard(size_t index);
    bool isClickedonCard() const;
    int getSelectedIndex() const;
    int getHoverIndex() const;
    void removeCard(size_t index);

    void update();
    void render();
};

#endif // GAMEHAND_HPP_INCLUDED
