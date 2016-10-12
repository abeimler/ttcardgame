#include "Scene/GamePlay.hpp"

GamePlay::GamePlay():
    players(0),
    cards(0),
    fieldw(0),
    fieldh(0)
{}
GamePlay::GamePlay(F2C::uint players, F2C::uint cards, size_t fieldw, size_t fieldh):
    players(players),
    cards(cards),
    fieldw(fieldw),
    fieldh(fieldh)
{}

void GamePlay::Init(){
    this->players = (this->players > 4)? 4 : this->players;
    this->hands.resize(this->players);

    for(size_t i = 0;i < this->hands.size();++i){
        this->hands[i].active = false;
        for(size_t j = 0;j < this->cards;++j)
            this->hands[i].cards.push_back(Card::dataCards[random(0,Card::dataCards.size()-1)]);

        switch(i){
            case 0:
                this->hands[0].color.set(0,0,255,255);
                this->hands[0].x = 64;
                this->hands[0].y = 32;
            break;
            case 1:
                this->hands[1].color.set(255,0,0,255);
                this->hands[1].x = Engine::WinApp.getScreenSize().width-64-GameCard::cardSize.width;
                this->hands[1].y = 32;
                this->hands[1].flipSelected = true;
            break;
            case 2:
                this->hands[2].color.set(0,255,0,255);
                this->hands[2].horizontal = true;
                this->hands[2].x = Engine::WinApp.getScreenSize().width/2
                                    - GameHand::selectHorizontalArea.width*this->hands[2].cards.size()/2;
                this->hands[2].y = 32;
            break;
            case 3:
                this->hands[3].color.set(255,255,0,255);
                this->hands[3].horizontal = true;
                this->hands[3].x = Engine::WinApp.getScreenSize().width/2
                                    - GameHand::selectHorizontalArea.width*this->hands[3].cards.size()/2;
                this->hands[3].y = Engine::WinApp.getScreenSize().height-8-GameCard::cardSize.height;
                this->hands[3].flipSelected = true;
            break;
        }
    }
    size_t firstPlayer = random(0,this->hands.size()-1);
    this->hands[firstPlayer].active = true;

    std::vector<F2C::Color> playerColors;
    for(size_t i = 0;i < this->hands.size();++i)
        playerColors.push_back(this->hands[i].color);

    this->strPoints.resize(this->hands.size());

    this->field = GameField(this->fieldw,this->fieldh,firstPlayer,playerColors);
    this->field.x = Engine::WinApp.getScreenSize().width/2 - GameCard::cardSize.width*this->field.getWidth()/2;
    this->field.y = Engine::WinApp.getScreenSize().height/2 - GameCard::cardSize.height*this->field.getHeight()/2;
    this->field.same = true;
    this->field.plus = true;
    this->field.samewall = false;
    this->field.pluswall = false;

    this->field.element = false;
    for(size_t x = 0;x < this->field.getWidth();++x){
        for(size_t y = 0;y < this->field.getHeight();++y){
            this->field.setElement(x,y,static_cast<CardElement::Card_Element>(random(0,static_cast<int>(CardElement::MaxElements-1))));
        }
    }

    F2CLoadBitmapintoSprite(this->fsprSwitch,graphicDir+"Font.png");
    F2CLoadBitmapintoSprite(this->fsprPlayer,graphicDir+"Font.png");
    F2CLoadBitmapintoSprite(this->fsprInfo,graphicDir+"iFont.png");
    F2CLoadBitmapintoSprite(this->fsprPoints,graphicDir+"Font.png");

    this->fsprSwitch.x = Engine::WinApp.getScreenSize().width - 240;
    this->fsprSwitch.y = Engine::WinApp.getScreenSize().height - 148;
}
void GamePlay::Update(){
    if(Engine::InApp.getRepeatKey(F2C::KeyboardEvent::F1))
        this->field.same = !this->field.same;
    if(Engine::InApp.getRepeatKey(F2C::KeyboardEvent::F2))
        this->field.plus = !this->field.plus;
    if(Engine::InApp.getRepeatKey(F2C::KeyboardEvent::F3))
        this->field.samewall = !this->field.samewall;
    if(Engine::InApp.getRepeatKey(F2C::KeyboardEvent::F4))
        this->field.pluswall = !this->field.pluswall;
    if(Engine::InApp.getRepeatKey(F2C::KeyboardEvent::F5))
        this->field.element = !this->field.element;
    if(Engine::InApp.getRepeatKey(F2C::KeyboardEvent::F6))
        this->field.combo = !this->field.combo;

    if(Engine::InApp.getRepeatKey(F2C::KeyboardEvent::Esc)){
        Engine::Game.ChangeState(new MainTitle);
        return;
    }

    std::stringstream ssSwitch;
    ssSwitch << "[F1] Same: " << this->field.same << std::endl
                << "[F2] Plus: " << this->field.plus << std::endl
                << "[F3] SameWall: " << this->field.samewall << std::endl
                << "[F4] PlusWall: " << this->field.pluswall << std::endl
                << "[F5] Element: " << this->field.element << std::endl
                << "[F6] Combo: " << this->field.combo << std::endl;


    this->fsprSwitch.clearTexts();
    this->fsprSwitch.addText(0,0,ssSwitch.str());

    this->field.update();
    for(size_t i = 0;i < this->hands.size();++i){
        this->hands[i].update();

        if(!this->hands[i].active || this->field.isFieldFull())
            continue;

        bool isset = false;
        GameAtk::Game_Atk gameAtk;
        if(this->hands[i].getSelectedIndex() >= 0){
            for(size_t x = 0;x < this->field.getWidth();++x){
                for(size_t y = 0;y < this->field.getHeight();++y){
                    if(this->field.isClicked(x,y)){
                        const GameCard* gameCard = this->hands[i].getGameCard(this->hands[i].getSelectedIndex());
                        bool canset = this->field.canSetCard(x,y);
                        gameAtk = this->field.setCard(x,y,*gameCard);
                        if(gameCard && canset){
                            this->hands[i].removeCard(this->hands[i].getSelectedIndex());
                            this->hands[i].resetSelect();
                            isset = true;
                            break;
                        }
                    }
                }
                if(isset) break;
            }
        }

        if(isset){
            this->hands[i].active = false;
            if(i+1 >= this->hands.size())
                this->hands[0].active = true;
            else
                this->hands[i+1].active = true;
        }

    }
    std::stringstream ssPlayer;
    std::stringstream ssInfo;

    std::vector<int> playerPoints;
    this->field.getPlayerPoints(playerPoints);

    if(this->field.isFieldFull()){
        if(this->field.getWinPlayer() > -1){
            ssPlayer << "Player " << this->field.getWinPlayer()+1 << " Win!";
            this->fsprPlayer.setColor(this->hands[this->field.getWinPlayer()].color);
        }else{
            ssPlayer << "Draw!" << std::endl;
            this->fsprPlayer.setColor(255,255,255,255);
        }
    }else{
        this->fsprPlayer.setColor(255,255,255,255);
        ssPlayer << "Player: ";
        for(size_t i = 0;i < this->hands.size();++i){
            if(this->hands[i].active){
                ssPlayer << i+1;
                if(this->hands[i].getHoverIndex() >= 0){
                    ssInfo << "LvL: " << this->hands[i].cards[this->hands[i].getHoverIndex()].lvl << std::endl;
                    ssInfo << "Name: " << this->hands[i].cards[this->hands[i].getHoverIndex()].monsterName << std::endl;
                }else if(this->hands[i].getSelectedIndex() >= 0){
                    ssInfo << "LvL: " << this->hands[i].cards[this->hands[i].getSelectedIndex()].lvl << std::endl;
                    ssInfo << "Name: " << this->hands[i].cards[this->hands[i].getSelectedIndex()].monsterName << std::endl;
                }
                this->fsprPlayer.setColor(this->hands[i].color);
                break;
            }
        }
    }

    this->strPoints.resize(this->hands.size());
    for(size_t i = 0; i < this->strPoints.size();++i){
        std::stringstream ss;
        ss << this->hands[i].cards.size()+this->field.getPlayerPoints(i) << " Cards";
        this->strPoints[i] = ss.str();
    }

    F2C::Rect playerFontCoord = this->fsprPlayer.getStringSize(ssPlayer.str());
    F2C::Rect infoFontCoord = this->fsprInfo.getStringSize(ssInfo.str());

    infoFontCoord.x = 16;
    infoFontCoord.y = Engine::WinApp.getScreenSize().height-16-infoFontCoord.height;

    playerFontCoord.x = 16;
    playerFontCoord.y = infoFontCoord.y - playerFontCoord.height - 8;

    this->fsprPlayer.clearTexts();
    this->fsprPlayer.addText(0,0,ssPlayer.str());
    this->fsprPlayer.x = playerFontCoord.x;
    this->fsprPlayer.y = playerFontCoord.y;

    this->fsprInfo.clearTexts();
    this->fsprInfo.addText(0,0,ssInfo.str());
    this->fsprInfo.x = infoFontCoord.x;
    this->fsprInfo.y = infoFontCoord.y;

}

void GamePlay::Render(){
    this->field.render();
    for(size_t i = 0;i < this->hands.size();++i){
        this->hands[i].render();

        F2C::Rect fontSize = this->fsprPoints.getStringSize(this->strPoints[i]);
        this->fsprPoints.x = this->hands[i].x;
        this->fsprPoints.y = this->hands[i].y - fontSize.height;
        this->fsprPoints.z = this->hands[i].z;
        //this->fsprPoints.setColor(this->hands[i].color);
        this->fsprPoints.clearTexts();
        this->fsprPoints.addText(0,0,this->strPoints[i]);
        this->fsprPoints.render();
    }

    this->fsprSwitch.render();
    this->fsprInfo.render();
    this->fsprPlayer.render();
}
