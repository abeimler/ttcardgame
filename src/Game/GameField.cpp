#include "GameField.hpp"

double GameField::defaultRulesEventTime = 0.8f;
F2C::Plane GameField::plnBG;
std::map<GameAtk::Game_Atk,F2C::SimpleSprite> GameField::sprRulesEvent;
std::map< CardElement::Card_Element, F2C::SimpleSprite > GameField::ssprElements;
GameCard GameField::wallCard;

void GameField::loadBGBitmap(std::string filename){
    F2CLoadBitmapintoSprite(GameField::plnBG,filename)
}

void GameField::loadRuleEventBitmap(GameAtk::Game_Atk atk,std::string filename){
    F2CLoadBitmapintoSprite(GameField::sprRulesEvent[atk],filename);
}

void GameField::loadElementBitmap(CardElement::Card_Element element, std::string filename){
    F2CLoadBitmapintoSprite(GameField::ssprElements[element],filename);
}

GameField::GameField():
    width(0),
    height(0),
    firstPlayer(0),
    x(0),
    y(0),
    z(0),
    same(false),
    plus(false),
    samewall(false),
    pluswall(false),
    combo(false),
    element(false),
    rulesEventTime(GameField::defaultRulesEventTime)
{}

GameField::GameField(size_t width, size_t height, size_t firstPlayer,const std::vector<F2C::Color>& playerColor):
    width(width),
    height(height),
    firstPlayer(firstPlayer),
    x(0),
    y(0),
    z(0),
    same(false),
    plus(false),
    samewall(false),
    pluswall(false),
    combo(false),
    element(false),
    rulesEventTime(GameField::defaultRulesEventTime)
{
    this->cards.resize(width*height);
    this->isEmptyCard.resize(width*height,true);
    this->elements.resize(width*height,CardElement::None);
    this->playerColor = playerColor;
}

size_t GameField::getWidth() const {return this->width;}
size_t GameField::getHeight() const {return this->height;}
const std::vector<GameCard>& GameField::getCards() const {return this->cards;}

size_t GameField::getPlayerSize() const {
    return this->playerColor.size();
}
F2C::Color GameField::getPlayerColor(size_t index) const {
    if(index >= this->playerColor.size())
        return F2C::Color (0,0,0,0);

    return this->playerColor[index];
}

void GameField::setElement(int x,int y,CardElement::Card_Element element){
    if(x < 0 || y < 0 || x >= this->width || y >= this->height)
        return;

    this->elements[x+y*this->width] = element;
}
CardElement::Card_Element GameField::getElement(int x,int y) const {
    if(x < 0 || y < 0 || x >= this->width || y >= this->height)
        return CardElement::None;

    return this->elements[x+y*this->width];
}

void GameField::removeCard(int x,int y){
    if(x < 0 || y < 0 || x >= this->width || y >= this->height || !this->rulesEvent.empty())
        return;

    this->cards[x+y*this->width] = GameCard();
    this->isEmptyCard[x+y*this->width] = true;
    this->cards[x+y*this->width].flipOpen = false;
}

GameAtk::Game_Atk GameField::resetCard(int x,int y,const GameCard& card,std::vector<size_t>* comboEnemy){
    this->removeCard(x,y);
    return this->setCard(x,y,card,comboEnemy);
}

bool GameField::canSetCard(int x,int y) const{
    if(x < 0 || y < 0 || x >= this->width || y >= this->height || !this->rulesEvent.empty())
        return false;

    return this->isEmptyCard[x+y*this->width];
}

bool GameField::isClicked(int x,int y) const {
    if(x < 0 || y < 0 || x >= this->width || y >= this->height)
        return false;

    F2C::Rect cardObj = GameCard::cardSize;
    cardObj.x = this->x + x*GameCard::cardSize.width;
    cardObj.y = this->y + y*GameCard::cardSize.height;

    F2C::Rect mouserect (0,0,8,8);
    Engine::InApp.getMousePos(&mouserect.x,&mouserect.y);

    if(cardObj.collision(mouserect)){
        return Engine::InApp.getRepeatMouse(F2C::MouseEvent::Left);
    }

    return false;
}

void GameField::update(){
    std::vector<GameRuleEvent> cpyRulesEvent;
    for(size_t i = 0;i < this->rulesEvent.size();++i){
        if(!this->rulesEvent[i].canErase())
            cpyRulesEvent.push_back(this->rulesEvent[i]);
    }

    this->rulesEvent = cpyRulesEvent;
}

bool GameField::isFieldFull() const {
    bool re = false;
    for(size_t i = 0;i < this->isEmptyCard.size();++i)
        re = ((i > 0)? re : true) && !this->isEmptyCard[i];

    return re;
}

bool GameField::isFieldEmpty() const {
    bool re = false;
    for(size_t i = 0;i < this->isEmptyCard.size();++i)
        re = ((i > 0)? re : true) && this->isEmptyCard[i];

    return re;
}

int GameField::getPlayerPoints(size_t index) const{
    if(index >= this->playerColor.size())
        return 0;

    int points = 0;
    for(size_t i = 0;i < this->cards.size();++i){
        if(!this->isEmptyCard[i] && this->cards[i].color == this->playerColor[index])
            points++;
    }
    //if(this->firstPlayer == index && !this->isFieldEmpty() && points > 0)
    //    points--;

    return points;
}

void GameField::getPlayerPoints(std::vector<int>& nPoints) const{
    std::vector<int> nCards (this->playerColor.size(),0);
    for(size_t i = 0;i < this->playerColor.size();++i)
        nCards[i] = this->getPlayerPoints(i);

    nPoints = nCards;
}

int GameField::getWinPlayer() const {
    if(!this->isFieldFull())
        return -1;

    std::vector<int> nCards;
    this->getPlayerPoints(nCards);

    int winPlayer = -1;
    for(size_t i = 0;i < nCards.size();++i){
        int k = 0;
        bool win = false;
        for(size_t j = 0;j < nCards.size();++j){
            if(i != j){
                win = ((k > 0)? win : true) && nCards[i] > nCards[j];
                k++;
            }
        }

        if(win){
            winPlayer = i;
            break;
        }
    }

    bool isDraw = false;
    for(size_t i = 0;i < nCards.size() && winPlayer > -1;++i){
        if(winPlayer != i && nCards[winPlayer] == nCards[i]){
            isDraw = true;
            break;
        }
    }
    if(isDraw)
        winPlayer = -1;

    return winPlayer;
}

void GameField::render(){
    GameField::plnBG.x = this->x;
    GameField::plnBG.y = this->y;
    GameField::plnBG.z = this->z;
    GameField::plnBG.src_rect.set(0,0,this->width*GameCard::cardSize.width,
                                        this->height*GameCard::cardSize.height);
    GameField::plnBG.render();

    for(size_t x = 0;x < this->width;++x){
        for(size_t y = 0;y < this->height;++y){
            if(this->element && this->elements[x+y*this->width] != CardElement::None){
                GameField::ssprElements[this->elements[x+y*this->width]].x = this->x + x*GameCard::cardSize.width +
                    (GameCard::cardSize.width/2 - GameField::ssprElements[this->elements[x+y*this->width]].getTexWidth()/2);
                GameField::ssprElements[this->elements[x+y*this->width]].y = this->y + y*GameCard::cardSize.height +
                    (GameCard::cardSize.height/2 - GameField::ssprElements[this->elements[x+y*this->width]].getTexHeight()/2);
                GameField::ssprElements[this->elements[x+y*this->width]].z = this->z;

                GameField::ssprElements[this->elements[x+y*this->width]].render();
            }

            if(this->isEmptyCard[x+y*this->width])
                continue;

            GameCard& card = this->cards[x+y*this->width];
            card.x = this->x + x*GameCard::cardSize.width;
            card.y = this->y + y*GameCard::cardSize.height;
            card.z = this->z;

            card.render();
        }
    }

    for(size_t i = 0;i < this->rulesEvent.size();++i){
        F2C::SimpleSprite& ssprEvent = GameField::sprRulesEvent[this->rulesEvent[i].atk];
        ssprEvent.x = this->x + GameField::plnBG.src_rect.width/2 - ssprEvent.getTexWidth()/2;
        ssprEvent.y = this->y + GameField::plnBG.src_rect.height/2 - ssprEvent.getTexHeight()/2 - i*ssprEvent.getTexHeight();
        ssprEvent.z = this->z;

        ssprEvent.render();
    }
}
