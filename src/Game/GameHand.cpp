#include <Game/GameHand.hpp>

F2C::Rect GameHand::selectArea;
F2C::Rect GameHand::selectHorizontalArea;

GameHand::GameHand():
    selectedIndex(-1),
    hoverIndex(-1),
    clickedonCard(false),
    x(0),
    y(0),
    z(0),
    active(true),
    horizontal(false),
    flipOpen(true),
    flipSelected(false),
    color(255,255,255,255)
{}

int GameHand::getSelectedIndex() const{
    return this->selectedIndex;
}
int GameHand::getHoverIndex() const{
    return this->hoverIndex;
}
void GameHand::removeCard(size_t index){
    if(index >= this->cards.size())
        return;

    this->cards.erase(this->cards.begin()+index);
}

bool GameHand::isClickedonCard() const{
    return this->clickedonCard;
}

void GameHand::resetSelect(){
     this->selectedIndex = -1;
}

bool GameHand::isClicked(F2C::MouseEvent::Mouse event,F2C::Rect obj) const {
    if(this->isHover(obj)){
        return Engine::InApp.getRepeatMouse(event);
    }

    return false;
}


bool GameHand::isHover(F2C::Rect obj) const {
    F2C::Rect mouserect (0,0,8,8);
    Engine::InApp.getMousePos(&mouserect.x,&mouserect.y);

    return obj.collision(mouserect);
}

F2C::Rect GameHand::getCardCoord(size_t index) const {
    F2C::Rect coord;
    if(this->horizontal){
        coord = GameHand::selectHorizontalArea;
        coord.x += this->x + index*GameHand::selectHorizontalArea.width;
        coord.y += this->y;
    }else{
        coord = GameHand::selectArea;
        coord.x += this->x;
        coord.y += this->y + index*GameHand::selectArea.height;
    }
    return coord;
}

bool GameHand::isClicked(size_t index) const{
    return this->isClicked(F2C::MouseEvent::Left,this->getCardCoord(index));
}
bool GameHand::isHover(size_t index) const{
    return this->isHover(this->getCardCoord(index));
}

const GameCard* GameHand::getGameCard(size_t index){
    if(index >= this->gameCards.size())
        return NULL;

    return &this->gameCards[index];
}

void GameHand::update(){
    if(this->gameCards.size() != this->cards.size())
        this->gameCards.resize(this->cards.size());

    if(this->active){
        this->clickedonCard = false;
        this->hoverIndex = -1;
    }

    bool isSelected = false;
    bool isHover = false;
    for(size_t i = 0;i < this->gameCards.size();++i){
        this->gameCards[i].card = this->cards[i];

        this->gameCards[i].update();
        if(this->active){
            bool clicked = this->isClicked(i);
            bool hover = this->isHover(i);
            if(clicked && !isSelected){
                this->selectedIndex = i;
                isSelected = true;
            }
            if(hover && !isHover){
                this->hoverIndex = i;
                isHover = true;
            }

            this->clickedonCard = (i > 0)? this->clickedonCard && clicked : clicked;
        }
    }
}

void GameHand::render(){
    for(size_t i = 0;i < this->gameCards.size();++i){
        this->gameCards[i].x = this->getCardCoord(i).x;
        this->gameCards[i].y = this->getCardCoord(i).y;
        if(this->horizontal && (this->selectedIndex == i || this->hoverIndex == i)){
            if(this->flipSelected)
                this->gameCards[i].y -= GameCard::cardSize.height/3;
            else
                this->gameCards[i].y += GameCard::cardSize.height/3;
        }else if(this->selectedIndex == i || this->hoverIndex == i){
            if(this->flipSelected)
                this->gameCards[i].x -= GameCard::cardSize.width/3;
            else
                this->gameCards[i].x += GameCard::cardSize.width/3;
        }

        this->gameCards[i].z = this->z;
        this->gameCards[i].color = this->color;
        this->gameCards[i].flipOpen = this->flipOpen;
        this->gameCards[i].render();
    }
}
