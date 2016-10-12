#include <Game/GameCard.hpp>

F2C::SimpleSprite GameCard::sprBG;
F2C::SimpleSprite GameCard::sprBack;
Platte GameCard::pltBorder;
F2C::FontSprite GameCard::fsprValues;
std::map<CardElement::Card_Element, F2C::SimpleSprite> GameCard::ssprElements;
std::map< ValueStatus::Value_Status, F2C::Color > GameCard::valueStatusColor;
F2C::Rect GameCard::cardSize;

void GameCard::loadBackBitmap(std::string filename){
    F2CLoadBitmapintoSprite(GameCard::sprBack,filename);
}
void GameCard::loadElementBitmap(CardElement::Card_Element element, std::string filename){
    F2CLoadBitmapintoSprite(GameCard::ssprElements[element],filename);
}
void GameCard::loadFontBitmap(std::string filename){
    F2CLoadBitmapintoSprite(GameCard::fsprValues,filename);
}
void GameCard::loadBorderPlatte(std::string filename){
    F2C::Bitmap platte;
    F2CLoadBitmap(platte, filename);

    F2C::uint rectSize = platte.getWidth()/3;
    GameCard::pltBorder.loadFrame(platte,rectSize,rectSize,rectSize,
                                            rectSize,rectSize,rectSize);
}

void GameCard::setValueStatusColor(ValueStatus::Value_Status status, F2C::Color color){
    GameCard::valueStatusColor[status] = color;
}

GameCard::GameCard():
    x(0),
    y(0),
    z(0),
    color(255,255,255,255),
    valueStatus(ValueStatus::Normal)
{}

void GameCard::update(){
    if(this->lastMonsterFilename != this->card.monsterFilename){
       F2CLoadBitmapintoSprite(this->sprMonster,this->card.monsterFilename);
       this->lastMonsterFilename = this->card.monsterFilename;
    }
}

void GameCard::render(){
    if(GameCard::cardSize.width < 1 || GameCard::cardSize.height < 1)
        return;

    if(!this->flipOpen){
        GameCard::sprBack.x = this->x;
        GameCard::sprBack.y = this->y;
        GameCard::sprBack.z = this->z;
        GameCard::sprBack.zoom_x = static_cast<double>(GameCard::sprBack.getTexWidth())/GameCard::cardSize.width;
        GameCard::sprBack.zoom_y = static_cast<double>(GameCard::sprBack.getTexHeight())/GameCard::cardSize.height;

        GameCard::sprBack.render();
    }else{
        GameCard::sprBG.src_rect.width = GameCard::cardSize.width-Platte::addMoveBG*2;
        GameCard::sprBG.src_rect.height = GameCard::cardSize.height-Platte::addMoveBG*2;
        GameCard::pltBorder.width = GameCard::cardSize.width;
        GameCard::pltBorder.height = GameCard::cardSize.height;
        //GameCard::fsprValues.src_rect = GameCard::cardSize;
        this->sprMonster.src_rect = GameCard::sprBG.src_rect;

        //F2C::uint8 grayColor = std::min<int>(255,(this->color.red * 0.2126f + this->color.green * 0.7152f + this->color.blue *0.0722f));
        F2C::uint8 grayColor = 225;

        GameCard::sprBG.vColor[0].set(grayColor,grayColor,grayColor,this->color.alpha);
        GameCard::sprBG.vColor[1].set(grayColor,grayColor,grayColor,this->color.alpha);
        GameCard::sprBG.vColor[2] = this->color;
        GameCard::sprBG.vColor[3] = this->color;

        GameCard::sprBG.x = this->x+Platte::addMoveBG;
        GameCard::sprBG.y = this->y+Platte::addMoveBG;
        GameCard::sprBG.z = this->z;

        this->sprMonster.x = GameCard::sprBG.x + ((this->sprMonster.getTexWidth() < GameCard::sprBG.src_rect.width)? GameCard::sprBG.src_rect.width/2 - this->sprMonster.getTexWidth()/2 : 0);
        this->sprMonster.y = GameCard::sprBG.y + ((this->sprMonster.getTexHeight() < GameCard::sprBG.src_rect.height)? GameCard::sprBG.src_rect.height/2 - this->sprMonster.getTexHeight()/2 : 0);
        this->sprMonster.z = GameCard::sprBG.z;

        GameCard::pltBorder.x = this->x;
        GameCard::pltBorder.y = this->y;
        GameCard::pltBorder.z = this->z;

        GameCard::fsprValues.x = this->x;
        GameCard::fsprValues.y = this->y;
        GameCard::fsprValues.z = this->z;

        std::string strValues[4];
        F2C::Rect strValuesCoord[4];

        for(size_t i = 0;i < 4;++i){
            std::stringstream ss;
            ss << std::hex << this->card.values[i];
            strValues[i] = ss.str();
            std::transform(strValues[i].begin(), strValues[i].end(), strValues[i].begin(), static_cast<int (*)(int)>(std::toupper));
            strValuesCoord[i] = GameCard::fsprValues.getStringSize(strValues[i]);
        }

        strValuesCoord[0].x = GameCard::pltBorder.getEdgesSize().width/4+strValuesCoord[3].width+1;
        strValuesCoord[0].y = GameCard::pltBorder.getEdgesSize().height/5;
        strValuesCoord[1].x = strValuesCoord[0].x+strValuesCoord[0].width-2;
        strValuesCoord[1].y = strValuesCoord[0].y+strValuesCoord[0].height-8;
        strValuesCoord[2].x = strValuesCoord[0].x;
        strValuesCoord[2].y = strValuesCoord[1].y+strValuesCoord[1].height-8;
        strValuesCoord[3].x = strValuesCoord[0].x-strValuesCoord[3].width;
        strValuesCoord[3].y = strValuesCoord[1].y;

        GameCard::fsprValues.setColor(GameCard::valueStatusColor[this->valueStatus]);
        GameCard::fsprValues.clearTexts();
        for(size_t i = 0;i < 4;++i)
            GameCard::fsprValues.addText(strValuesCoord[i],strValues[i]);

        if(this->card.element != CardElement::None){
            GameCard::ssprElements[this->card.element].x = GameCard::sprBG.x + GameCard::sprBG.src_rect.width - GameCard::ssprElements[this->card.element].getTexWidth();
            GameCard::ssprElements[this->card.element].y = GameCard::sprBG.y;
            GameCard::ssprElements[this->card.element].z = this->z;
        }

        GameCard::sprBG.render();
        this->sprMonster.render();
        GameCard::fsprValues.render();
        if(this->card.element != CardElement::None)
            GameCard::ssprElements[this->card.element].render();
        GameCard::pltBorder.render();
    }
}
