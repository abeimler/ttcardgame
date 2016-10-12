#ifndef GAMEFIELD_HPP_INCLUDED
#define GAMEFIELD_HPP_INCLUDED

#include <Game/GameCard.hpp>
#include <Game/GameHand.hpp>

namespace GameAtk{
    typedef enum Game_Atk{
        None = 0,
        Normal = 1,
        Same = 2,
        Plus = 3,
        Samewall = 4,
        Pluswall = 5,
        Combo = 6
    } Game_Atk;
}

class GameRuleEvent{
    private:
    F2C::Timer timer;

    public:
    GameAtk::Game_Atk atk;
    double eraseTime;

    GameRuleEvent():
        atk(GameAtk::Normal),
        eraseTime(0.0f)
    {}

    GameRuleEvent(GameAtk::Game_Atk atk,double eraseTime):
        atk(atk),
        eraseTime(eraseTime)
    {}

    bool canErase(){
        return this->timer.getTime() >= this->eraseTime;
    }
};

class GameField{
    private:
    static F2C::Plane plnBG;
    static std::map<GameAtk::Game_Atk,F2C::SimpleSprite> sprRulesEvent;
    static std::map< CardElement::Card_Element, F2C::SimpleSprite > ssprElements;
    std::vector<GameCard> cards;
    std::vector<bool> isEmptyCard;
    size_t width;
    size_t height;
    size_t firstPlayer;
    std::vector<F2C::Color> playerColor;
    std::vector<GameRuleEvent> rulesEvent;
    std::vector<CardElement::Card_Element> elements;

    /**
    *[0]: top
    *[1]: right
    *[2]: down
    *[3]: left
    */
    std::vector<GameCard*> getCards(int x,int y,bool wall);
    std::vector<size_t> normalAtk(int x,int y);
    std::vector<size_t> sameAtk(int x,int y,bool wall);
    std::vector<size_t> plusAtk(int x,int y,bool wall);

    public:
    int x;
    int y;
    int z;
    bool same;
    bool plus;
    bool samewall;
    bool pluswall;
    bool combo;
    bool element;
    double rulesEventTime;

    static GameCard wallCard;
    static double defaultRulesEventTime;
    static void loadRuleEventBitmap(GameAtk::Game_Atk atk,std::string filename);
    static void loadElementBitmap(CardElement::Card_Element element, std::string filename);
    static void loadBGBitmap(std::string filename);

    GameField();
    GameField(size_t width, size_t height , size_t firstPlayer,const std::vector<F2C::Color>& playerColor);

    size_t getWidth() const;
    size_t getHeight() const;
    const std::vector<GameCard>& getCards()  const;

    size_t getPlayerSize() const;
    F2C::Color getPlayerColor(size_t index) const;

    bool canSetCard(int x,int y) const;
    GameAtk::Game_Atk setCard(int x,int y,const GameCard& card,std::vector<size_t>* comboEnemy = NULL);
    GameAtk::Game_Atk resetCard(int x,int y,const GameCard& card,std::vector<size_t>* comboEnemy = NULL);
    void removeCard(int x,int y);

    bool isClicked(int x,int y) const;

    bool isFieldFull() const;
    bool isFieldEmpty() const;
    int getWinPlayer() const;
    void getPlayerPoints(std::vector<int>& nPoints) const;
    int getPlayerPoints(size_t index) const;

    void setElement(int x,int y,CardElement::Card_Element element);
    CardElement::Card_Element getElement(int x,int y) const;

    void update();
    void render();
};

#endif // GAMEFIELD_HPP_INCLUDED
