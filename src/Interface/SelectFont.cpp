#include "SelectFont.hpp"

F2C::FontSprite SelectFont::fspractiveFont;
F2C::FontSprite SelectFont::fsprdisableFont;
F2C::FontSprite SelectFont::fsprselectFont;
F2C::FontSprite SelectFont::fsprhoverFont;
F2C::FontSprite SelectFont::fsprclickedFont;

F2C::Color SelectFont::activeColor (255,255,255,255);
F2C::Color SelectFont::disableColor (128,128,128,196);
F2C::Color SelectFont::selectColor (255,128,128,255);
F2C::Color SelectFont::hoverColor (255,196,128,255);
F2C::Color SelectFont::clickedColor (128,128,255,255);

bool SelectString::isClicked(F2C::MouseEvent::Mouse event,int x,int y,const F2C::FontSprite& font) const {
    F2C::Rect strrect = font.getStringSize(this->str);
    strrect.x = x + this->x;
    strrect.y = y + this->y;

    return this->SelectObject::isClicked(event,strrect);
}
bool SelectString::isHover(int x,int y,const F2C::FontSprite& font) const {
    F2C::Rect strrect = font.getStringSize(this->str);
    strrect.x = x + this->x;
    strrect.y = y + this->y;

    return this->SelectObject::isHover(strrect);
}
void SelectString::update(F2C::MouseEvent::Mouse event,int x,int y,const F2C::FontSprite& font){
    F2C::Rect strrect = font.getStringSize(this->str);
    strrect.x = x + this->x;
    strrect.y = y + this->y;

    this->SelectObject::update(event,strrect);
}

void SelectFont::addString(int x,int y,std::string str){
    this->elements.push_back(SelectString (x,y,str));
}

void SelectFont::addStringList(int x,int y,const std::vector<std::string>& list){
    if(list.empty())
        return;
    const F2C::FontSprite& fspr = SelectFont::getFontSprite();

    F2C::Rect fontCoord (x,y,0,0);
    for(size_t i = 0;i < list.size();++i){
        this->addString(fontCoord.x,fontCoord.y,list[i]);
        F2C::Rect fontSize = fspr.getStringSize(list[i]);
        //fontCoord.x = fontCoord.x;
        fontCoord.y = fontCoord.y+fontSize.height+fontSize.height/2;
    }
}

void SelectFont::addStringListH(int x,int y,const std::vector<std::string>& list,F2C::uint spaceWidth){
    if(list.empty())
        return;
    const F2C::FontSprite& fspr = SelectFont::getFontSprite();

    F2C::Rect fontCoord (x,y,0,0);
    for(size_t i = 0;i < list.size();++i){
        this->addString(fontCoord.x,fontCoord.y,list[i]);
        F2C::Rect fontSize = fspr.getStringSize(list[i]);
        fontCoord.x = fontCoord.x+fontSize.width+spaceWidth;
        //fontCoord.y = fontCoord.y;
    }
}

void SelectFont::setBitmap(const F2C::Bitmap* bitmap){
    SelectFont::fspractiveFont.setBitmap(bitmap);
    SelectFont::fsprdisableFont.setBitmap(bitmap);
    SelectFont::fsprselectFont.setBitmap(bitmap);
    SelectFont::fsprhoverFont.setBitmap(bitmap);
    SelectFont::fsprclickedFont.setBitmap(bitmap);
}

const F2C::FontSprite& SelectFont::getFontSprite(){
    return SelectFont::fspractiveFont;
}

bool SelectFont::isClicked(F2C::MouseEvent::Mouse event,size_t id) const {
    if(this->elements.empty() || id >= this->elements.size())
        return false;

    return this->elements[id].isClicked(event,this->x,this->y,SelectFont::fsprhoverFont);
}

bool SelectFont::isHover(size_t id) const {
    if(this->elements.empty() || id >= this->elements.size())
        return false;

    return this->elements[id].isHover(this->x,this->y,SelectFont::fspractiveFont);
}

void SelectFont::update(){
    this->index = -1;
    if(!this->active)
        return;

    for(size_t i = 0;i < this->elements.size();++i){
        this->elements[i].update(this->mouseEvent,this->x,this->y,SelectFont::fsprhoverFont);
        if(this->isClicked(this->mouseEvent,i))
            this->index = i;
    }
}

int SelectFont::getIndex() const {
    return this->index;
}

F2C::uint SelectFont::getWidth() const {
    const F2C::FontSprite& fspr = SelectFont::getFontSprite();

    F2C::Rect fontSize;
    F2C::uint width = 0;
    for(size_t i = 0;i < this->elements.size();++i){
        fontSize = fspr.getStringSize(this->elements[i].str);
        width = std::max(width,this->elements[i].x+fontSize.width);
    }
    return width;
}
F2C::uint SelectFont::getHeight() const {
    const F2C::FontSprite& fspr = SelectFont::getFontSprite();

    F2C::Rect fontSize;
    F2C::uint height = 0;
    for(size_t i = 0;i < this->elements.size();++i){
        fontSize = fspr.getStringSize(this->elements[i].str);
        height = std::max(height,this->elements[i].y+fontSize.height);
    }
    return height;
}

F2C::Rect SelectFont::getBiggestElement() const {
    const F2C::FontSprite& fspr = SelectFont::getFontSprite();
    F2C::Rect listSize;
    F2C::Rect fontSize;

    for(size_t i = 0;i < this->elements.size();++i){
        fontSize = fspr.getStringSize(this->elements[i].str);
        listSize.height = (fontSize.height > listSize.height)? : listSize.height;
        listSize.width = (fontSize.width > listSize.width)? : listSize.width;
    }

    return listSize;
}

void SelectFont::render(){
    SelectFont::fspractiveFont.x = this->x;
    SelectFont::fsprdisableFont.x = this->x;
    SelectFont::fsprselectFont.x = this->x;
    SelectFont::fsprhoverFont.x = this->x;
    SelectFont::fsprclickedFont.x = this->x;

    SelectFont::fspractiveFont.y = this->y;
    SelectFont::fsprdisableFont.y = this->y;
    SelectFont::fsprselectFont.y = this->y;
    SelectFont::fsprhoverFont.y = this->y;
    SelectFont::fsprclickedFont.y = this->y;

    SelectFont::fspractiveFont.z = this->z;
    SelectFont::fsprdisableFont.z = this->z;
    SelectFont::fsprselectFont.z = this->z;
    SelectFont::fsprhoverFont.z = this->z;
    SelectFont::fsprclickedFont.z = this->z;

    SelectFont::fspractiveFont.setColor(SelectFont::activeColor);
    SelectFont::fsprdisableFont.setColor(SelectFont::disableColor);
    SelectFont::fsprselectFont.setColor(SelectFont::selectColor);
    SelectFont::fsprhoverFont.setColor(SelectFont::hoverColor);
    SelectFont::fsprclickedFont.setColor(SelectFont::clickedColor);

    SelectFont::fspractiveFont.clearTexts();
    SelectFont::fsprdisableFont.clearTexts();
    SelectFont::fsprselectFont.clearTexts();
    SelectFont::fsprhoverFont.clearTexts();
    SelectFont::fsprclickedFont.clearTexts();

    for(size_t i = 0;i < this->elements.size();++i){
        F2C::Rect strrect = SelectFont::fspractiveFont.getStringSize(this->elements[i].str);
        strrect.x = this->elements[i].x;
        strrect.y = this->elements[i].y;

        if(this->elements[i].active){
            if(this->elements[i].select && this->active){
                SelectFont::fsprselectFont.addText(strrect,this->elements[i].str);
            }else if(this->elements[i].clicked && this->active){
                SelectFont::fsprclickedFont.addText(strrect,this->elements[i].str);
            }else if(this->elements[i].hover && this->active){
                SelectFont::fsprhoverFont.addText(strrect,this->elements[i].str);
            }else{
                SelectFont::fspractiveFont.addText(strrect,this->elements[i].str);
            }
        }else{
            SelectFont::fsprdisableFont.addText(strrect,this->elements[i].str);
        }
    }

    SelectFont::fspractiveFont.render();
    SelectFont::fsprdisableFont.render();
    SelectFont::fsprselectFont.render();
    SelectFont::fsprhoverFont.render();
    SelectFont::fsprclickedFont.render();
}
