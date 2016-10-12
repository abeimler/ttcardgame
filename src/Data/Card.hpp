#ifndef CARD_HPP_INCLUDED
#define CARD_HPP_INCLUDED

#include <basic.h>
#include <tinyxml.h>

namespace CardElement{
    typedef enum Card_Element {
        None = 0,
        Earth = 1,
        Fire = 2,
        Water = 3,
        Poisen = 4,
        Holy = 5,
        Thunder = 6,
        Wind = 7,
        Cold = 8,
        MaxElements = 9
    } Card_Element;
}

class Card{
    public:
    /**
    *[0]: top
    *[1]: right
    *[2]: down
    *[3]: left
    */
    int values[4];
    F2C::uint lvl;
    CardElement::Card_Element element;
    std::string monsterFilename;
    std::string monsterName;

    static std::string filenameDir;
    static std::vector<Card> dataCards;

    Card();

    static void loadDatafromXML(std::vector<Card>& getData,std::string filename);

    void loadfromXML(const TiXmlHandle& xmlhCard);
};

#endif // CARD_HPP_INCLUDED
