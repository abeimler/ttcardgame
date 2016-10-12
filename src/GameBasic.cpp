#include <GameBasic.h>

std::string graphicDir = "./Graphics/";

void initGame(){
    Platte::addMoveBG = 2;

    F2C::Bitmap bitFont;
    F2CLoadBitmap(bitFont,graphicDir+"Font.png");
    SelectFont::setBitmap(&bitFont);

    SelectFont::activeColor.set(255,255,255,255);
    SelectFont::disableColor.set(128,128,128,196);
    SelectFont::selectColor.set(255,128,128,255);
    SelectFont::hoverColor.set(255,196,128,255);
    SelectFont::clickedColor.set(128,128,255,255);

    std::string elementDir = graphicDir+"Element/";
    Card::filenameDir = graphicDir+"Monster/";
    GameCard::loadFontBitmap(graphicDir+"hexFont.png");
    GameCard::loadBorderPlatte(graphicDir+"border.png");
    GameCard::loadBackBitmap(graphicDir+"back.png");
    GameField::loadBGBitmap(graphicDir+"field.png");
    GameField::defaultRulesEventTime = 1.2f;
    GameField::loadRuleEventBitmap(GameAtk::Same,graphicDir+"same.png");
    GameField::loadRuleEventBitmap(GameAtk::Plus,graphicDir+"plus.png");
    GameField::loadRuleEventBitmap(GameAtk::Samewall,graphicDir+"samewall.png");
    GameField::loadRuleEventBitmap(GameAtk::Pluswall,graphicDir+"pluswall.png");
    GameField::loadRuleEventBitmap(GameAtk::Combo,graphicDir+"combo.png");

    GameCard::loadElementBitmap(CardElement::Cold,elementDir+"cold.png");
    GameField::loadElementBitmap(CardElement::Cold,elementDir+"cold.png");
    GameCard::loadElementBitmap(CardElement::Earth,elementDir+"earth.png");
    GameField::loadElementBitmap(CardElement::Earth,elementDir+"earth.png");
    GameCard::loadElementBitmap(CardElement::Holy,elementDir+"holy.png");
    GameField::loadElementBitmap(CardElement::Holy,elementDir+"holy.png");
    GameCard::loadElementBitmap(CardElement::Fire,elementDir+"fire.png");
    GameField::loadElementBitmap(CardElement::Fire,elementDir+"fire.png");
    GameCard::loadElementBitmap(CardElement::Poisen,elementDir+"poisen.png");
    GameField::loadElementBitmap(CardElement::Poisen,elementDir+"poisen.png");
    GameCard::loadElementBitmap(CardElement::Thunder,elementDir+"thunder.png");
    GameField::loadElementBitmap(CardElement::Thunder,elementDir+"thunder.png");
    GameCard::loadElementBitmap(CardElement::Water,elementDir+"water.png");
    GameField::loadElementBitmap(CardElement::Water,elementDir+"water.png");
    GameCard::loadElementBitmap(CardElement::Wind,elementDir+"wind.png");
    GameField::loadElementBitmap(CardElement::Wind,elementDir+"wind.png");

    GameCard::setValueStatusColor(ValueStatus::Normal,F2C::Color (255,255,255,255));
    GameCard::setValueStatusColor(ValueStatus::Reinforced,F2C::Color (250,250,100,255));
    GameCard::setValueStatusColor(ValueStatus::Weakened,F2C::Color (250,100,100,255));

    GameField::wallCard.card.monsterName = "_GameWall_";
    for(size_t i = 0;i < 4;++i)
        GameField::wallCard.card.values[i] = 10;

    GameCard::cardSize.set(0,0,96,104);
    GameHand::selectArea.set(0,0,GameCard::cardSize.width,GameCard::cardSize.height/2);
    GameHand::selectHorizontalArea.set(0,0,GameCard::cardSize.width/2,GameCard::cardSize.height);

    Card::loadDatafromXML(Card::dataCards,"./data/cards.xml");
}
