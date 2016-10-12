#include <Data/Card.hpp>

std::string Card::filenameDir;
std::vector<Card> Card::dataCards;

Card::Card():
    lvl(0),
    element(CardElement::None)
{
    memset(this->values,0,sizeof(this->values[0])*4);
}

void Card::loadfromXML(const TiXmlHandle& xmlhCard){
    TiXmlElement* xmlValues = xmlhCard.FirstChild("values").ToElement();
    TiXmlElement* xmlLvL = xmlhCard.FirstChild("lvl").ToElement();
    TiXmlElement* xmlMonster = xmlhCard.FirstChild("monster").ToElement();
    TiXmlElement* xmlElement = xmlhCard.FirstChild("element").ToElement();

    if(xmlValues){
        std::string values = xmlValues->Attribute("value");

        std::vector<std::string> words;
        getStringsSeparatedByLetter(words,values," ");

        for(size_t i = 0;i < words.size() || i < 4;++i){
            int value = atoi(words[i].c_str());
            this->values[i] = value;

        }
    }
    if(xmlLvL){
        int lvl;
        xmlLvL->Attribute("value",&lvl);
        this->lvl = lvl;
    }
    if(xmlMonster){
        this->monsterFilename = Card::filenameDir + xmlMonster->Attribute("filename");
        this->monsterName = xmlMonster->Attribute("name");
    }

    this->element = CardElement::None;
    if(xmlElement){
        std::string readElement = xmlElement->Attribute("value");

        if(readElement == "0" || readElement == "None")
            this->element = CardElement::None;
        else if(readElement == "1" || readElement == "Earth")
            this->element = CardElement::Earth;
        else if (readElement == "2" || readElement == "Fire")
            this->element = CardElement::Fire;
        else if (readElement == "3" || readElement == "Water")
            this->element = CardElement::Water;
        else if (readElement == "4" || readElement == "Poisen")
            this->element = CardElement::Poisen;
        else if (readElement == "5" || readElement == "Holy")
            this->element = CardElement::Holy;
        else if(readElement == "6" || readElement == "Thunder")
            this->element = CardElement::Thunder;
        else if(readElement == "7" || readElement == "Wind")
            this->element = CardElement::Wind;
        else if(readElement == "8" || readElement == "Cold")
            this->element = CardElement::Cold;
    }
}


void Card::loadDatafromXML(std::vector<Card>& getData,std::string filename){
    getData.clear();

    TiXmlDocument doc;
    if(doc.LoadFile(filename.c_str())){
        TiXmlHandle hDoc(dynamic_cast<TiXmlNode*>(&doc));

        TiXmlElement* xmldataCard = hDoc.FirstChildElement( "dataCard" ).ToElement();
        if(xmldataCard){
            TiXmlHandle xmlhDataCard = hDoc.FirstChild( "dataCard" );

            TiXmlHandle xmlhCard = xmlhDataCard.Child( "Card",0 );
            TiXmlElement* xmlCard = xmlhCard.ToElement();

            for(int i = 1; xmlCard; ++i){
                if(xmlCard){
                    Card card;
                    card.loadfromXML(xmlhCard);
                    getData.push_back(card);
                }

                xmlhCard = xmlhDataCard.Child("Card",i);
                xmlCard = xmlhCard.ToElement();
            }
        }
    }else if(doc.Error()){
        std::stringstream strError;
        strError << "Cant load " << filename << std::endl;
        strError << doc.ErrorRow() << ": " << doc.ErrorDesc() << std::endl;
        F2C::LogError::writeString(strError.str());
    }
}
