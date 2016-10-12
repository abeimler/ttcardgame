#include <Game/GameField.hpp>

std::vector<GameCard*> GameField::getCards(int x,int y,bool wall){
    std::vector< GameCard* > recards (4);
    for(size_t i = 0;i < 4;++i)
        recards[i] = NULL;

    if(x < 0 || y < 0 || x >= this->width || y >= this->height)
        return recards;

    /**
    *[0]: top
    *[1]: right
    *[2]: down
    *[3]: left
    */
    if(wall){
        if(y > 0)
            recards[0] = (!this->isEmptyCard[x+(y-1)*this->width])? &this->cards[x+(y-1)*this->width] : NULL;
        else
            recards[0] = &GameField::wallCard;

        if(x < this->width-1)
            recards[1] = (!this->isEmptyCard[(x+1)+y*this->width])? &this->cards[(x+1)+y*this->width] :  NULL;
        else
            recards[1] = &GameField::wallCard;

        if(y < this->height-1)
            recards[2] = (!this->isEmptyCard[x+(y+1)*this->width])? &this->cards[x+(y+1)*this->width] : NULL;
        else
            recards[2] = &GameField::wallCard;

        if(x > 0)
            recards[3] = (!this->isEmptyCard[(x-1)+y*this->width])? &this->cards[(x-1)+y*this->width] : NULL;
        else
            recards[3] = &GameField::wallCard;
    }else{
        if(y > 0)
            recards[0] = (!this->isEmptyCard[x+(y-1)*this->width])? &this->cards[x+(y-1)*this->width] : NULL;

        if(x < this->width-1)
            recards[1] = (!this->isEmptyCard[(x+1)+y*this->width])? &this->cards[(x+1)+y*this->width] :  NULL;

        if(y < this->height-1)
            recards[2] = (!this->isEmptyCard[x+(y+1)*this->width])? &this->cards[x+(y+1)*this->width] : NULL;

        if(x > 0)
            recards[3] = (!this->isEmptyCard[(x-1)+y*this->width])? &this->cards[(x-1)+y*this->width] : NULL;
    }

    return recards;
}

std::vector<size_t>GameField::normalAtk(int x,int y){
    std::vector<size_t> re;
    if(x < 0 || y < 0 || x >= this->width || y >= this->height)
        return re;

    /**
    *[0]: top
    *[1]: right
    *[2]: down
    *[3]: left
    */
    std::vector<GameCard*> enemyCards = this->getCards(x,y,false);
    const GameCard& playerCard = this->cards[x+y*this->width];

    for(size_t i = 0;i < 4;++i){ //i = player value = enemyCardIndex
        if(enemyCards[i] && enemyCards[i]->color != playerCard.color){ //is Card not Empty and  have other Color
            size_t mirrori = (i+2) % 4; //index of Mirror Value
            if(playerCard.card.values[i] > enemyCards[i]->card.values[mirrori]){
                enemyCards[i]->color = playerCard.color;
                re.push_back(i);
            }
        }
    }

    return re;
}

std::vector<size_t> GameField::sameAtk(int x,int y,bool wall){
    std::vector<size_t> re;
    if(x < 0 || y < 0 || x >= this->width || y >= this->height)
        return re;

    /**
    *[0]: top
    *[1]: right
    *[2]: down
    *[3]: left
    */
    std::vector<GameCard*> enemyCards = this->getCards(x,y,wall);
    const GameCard& playerCard = this->cards[x+y*this->width];

    size_t nEnemyCards = 0;
    for(size_t i = 0;i < 4;++i){
        //not wall: enemyCard exist
        //wall: enemyCard exist and not a Wall(Card)
        if( (!wall && enemyCards[i] && enemyCards[i]->color != playerCard.color) ||
            (wall && enemyCards[i] && enemyCards[i] != &GameField::wallCard && enemyCards[i]->color != playerCard.color))
                nEnemyCards++;
    }
    if(!((nEnemyCards >= 2 && !wall) || (nEnemyCards >= 1 && wall)))
        return re;

    bool isEqual = false;
    std::vector<bool> hasWin (4,false);
    size_t nWins = 0;
    for(size_t i = 0;i < 4;++i){ //i = player value = enemyCardIndex
        if(enemyCards[i] && enemyCards[i]->color != playerCard.color){ //is Card not Empty
            size_t mirrori = (i+2) % 4; //index of Mirror Value
            //comparable test: Values must be Equal
            //isEqual = oldisEqual && newisEqual, 2 >= monsters must be comparable test successfully
            hasWin[i] = playerCard.card.values[i] == enemyCards[i]->card.values[mirrori];
            isEqual = ((nWins > 0)? isEqual : true) && hasWin[i];
            if(isEqual)
                nWins++; //next card, number of enemy Cards
        }
    }

    //successfull, flip Card
    if(nWins >= 2){
        for(size_t i = 0;i < 4;++i){
            if(enemyCards[i] && enemyCards[i] != &GameField::wallCard && hasWin[i]){ //is exist,not a Wall(Card) and has Win
                enemyCards[i]->color = playerCard.color;
                re.push_back(i);
            }
        }
    }

    return re;
}

std::vector<size_t> GameField::plusAtk(int x,int y,bool wall){
    std::vector<size_t> re;
    if(x < 0 || y < 0 || x >= this->width || y >= this->height)
        return re;

    /**
    *[0]: top
    *[1]: right
    *[2]: down
    *[3]: left
    */
    std::vector<GameCard*> enemyCards = this->getCards(x,y,wall);
    const GameCard& playerCard = this->cards[x+y*this->width];

    size_t nEnemyCards = 0;
    for(size_t i = 0;i < 4;++i){
        //not wall: enemyCard exist
        //wall: enemyCard exist and not a Wall(Card)
        if( (!wall && enemyCards[i] && enemyCards[i]->color != playerCard.color) ||
            (wall && enemyCards[i] && enemyCards[i] != &GameField::wallCard && enemyCards[i]->color != playerCard.color))
            nEnemyCards++;
    }
    if(!((nEnemyCards >= 2 && !wall) || (nEnemyCards >= 1 && wall)))
        return re;

    std::vector<int> sums (4,0);
    std::vector<bool> hasWin (4,false);
    size_t nWins = 0;
    for(size_t i = 0;i < 4;++i){ //i = player value = enemyCardIndex
        if(enemyCards[i] && enemyCards[i]->color != playerCard.color){ //is Card not Empty
            size_t mirrori = (i+2) % 4; //index of Mirror Value
            sums[i] = playerCard.card.values[i] + enemyCards[i]->card.values[mirrori];
        }
    }
    for(size_t i = 0;i < 4;++i){ //i = player value = enemyCardIndex
        if(enemyCards[i] && enemyCards[i]->color != playerCard.color){ //is Card not Empty
            size_t mirrori = (i+2) % 4; //index of Mirror Value
            for(size_t j = 0;j < sums.size();++j){
                if(i == j)
                    continue;

                //comparable test: all Sums must be Equal
                //isSumEqual = oldisSumEqual && newisSumEqual, 2 >= monsters must be comparable test successfully
                bool equalSum = playerCard.card.values[i] + enemyCards[i]->card.values[mirrori] == sums[j];
                if(equalSum){
                    hasWin[i] = true;
                    nWins++;
                }
            }
        }
    }

    //successfull, flip Card
    if(nWins >= 1){
        for(size_t i = 0;i < 4;++i){
            if(enemyCards[i] && enemyCards[i] != &GameField::wallCard && hasWin[i]){
                enemyCards[i]->color = playerCard.color;
                re.push_back(i);
            }
        }
    }

    return re;
}


GameAtk::Game_Atk GameField::setCard(int x,int y,const GameCard& card,std::vector<size_t>* comboEnemy){
    if(!this->canSetCard(x,y))
        return GameAtk::None;

    this->cards[x+y*this->width] = card;
    GameCard& thisCard = this->cards[x+y*this->width];
    CardElement::Card_Element& thisElement = this->elements[x+y*this->width];

    this->isEmptyCard[x+y*this->width] = false;
    thisCard.flipOpen = true;

    if(!comboEnemy)
        thisCard.valueStatus = ValueStatus::Normal;
    if(this->element && !comboEnemy && thisElement != CardElement::None){
        if(thisElement == card.card.element){
            for(size_t i = 0;i < 4;++i)
                thisCard.card.values[i]++;
            thisCard.valueStatus = ValueStatus::Reinforced;
        }else{
            for(size_t i = 0;i < 4;++i)
                thisCard.card.values[i]--;
            thisCard.valueStatus = ValueStatus::Weakened;
        }
    }

    GameAtk::Game_Atk re = GameAtk::None;
    std::vector<size_t> winEnemys;
    if((x < 1 || y < 1 || x >= this->width-1 || y >= this->height-1) && this->pluswall && re == GameAtk::None){
        winEnemys = this->plusAtk(x,y,true);
        if(!winEnemys.empty()){
            re = GameAtk::Pluswall;
        }
    }

    if((x < 1 || y < 1 || x >= this->width-1 || y >= this->height-1) && this->samewall && re == GameAtk::None){
        winEnemys = this->sameAtk(x,y,true);
        if(!winEnemys.empty()){
            re = GameAtk::Samewall;
        }
    }

    if(this->plus && re == GameAtk::None){
        winEnemys = this->plusAtk(x,y,false);
        if(!winEnemys.empty()){
            re = GameAtk::Plus;
        }
    }

    if(this->same && re == GameAtk::None){
        winEnemys = this->sameAtk(x,y,false);
        if(!winEnemys.empty()){
            re = GameAtk::Same;
        }
    }

    if(!this->normalAtk(x,y).empty() && re == GameAtk::None){
        re = GameAtk::Normal;
    }

    if(this->combo && re != GameAtk::None && re != GameAtk::Normal && !winEnemys.empty()){
        int curx = x;
        int cury = y;
        for(size_t i = 0;i < winEnemys.size();++i){
            size_t pos = winEnemys[i];
            int addx = (pos == 1)? +1 : (pos == 3)? -1 : 0;
            int addy = (pos == 0)? -1 : (pos == 2)? +1 : 0;
            if(!this->normalAtk(curx+addx,cury+addy).empty())
                re = GameAtk::Combo;
        }
    }

    if(re != GameAtk::None && re != GameAtk::Normal){
        this->rulesEvent.push_back(GameRuleEvent (re,this->rulesEventTime));
    }

    return re;
}
