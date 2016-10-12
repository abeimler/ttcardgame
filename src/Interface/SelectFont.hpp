#ifndef SELECTFONT_HPP_INCLUDED
#define SELECTFONT_HPP_INCLUDED

#include <basic.h>
#include <Interface/SelectObject.hpp>

class SelectString : public SelectObject{
    public:
    int x;
    int y;
    std::string str;

    SelectString():
        x(0),
        y(0)
    {}

    SelectString(int  x,int y,std::string str):
        x(x),
        y(y),
        str(str)
    {}

    bool isClicked(F2C::MouseEvent::Mouse event,int x,int y,const F2C::FontSprite& font) const;
    bool isHover(int x,int y,const F2C::FontSprite& font) const;
    void update(F2C::MouseEvent::Mouse event,int x,int y,const F2C::FontSprite& font);
};

/**
*@class SelectFont
*
*/
class SelectFont{
    private:
    static F2C::FontSprite fspractiveFont;
    static F2C::FontSprite fsprdisableFont;
    static F2C::FontSprite fsprselectFont;
    static F2C::FontSprite fsprhoverFont;
    static F2C::FontSprite fsprclickedFont;
    int index;

    public:
    static F2C::Color activeColor;
    static F2C::Color disableColor;
    static F2C::Color selectColor;
    static F2C::Color hoverColor;
    static F2C::Color clickedColor;

    static void setBitmap(const F2C::Bitmap* bitmap);
    static const F2C::FontSprite& getFontSprite();

    int x;
    int y;
    int z;
    bool active;
    std::vector<SelectString> elements; ///< SelectString elements
    F2C::MouseEvent::Mouse mouseEvent; ///< mouse event for update()

    SelectFont():
        index(-1),
        x(0),
        y(0),
        z(0),
        active(true),
        mouseEvent(F2C::MouseEvent::Left)
    {}

    /**
    *@param x x-Coord.of SelectString
    *@param y y-Coord of SelectString
    *@param str Text of SelectString
    *@brief Add a SelectString into elements
    */
    void addString(int x,int y,std::string str);

    /**
    *
    */
    void addStringList(int x,int y,const std::vector<std::string>& list);

    /**
    *
    */
    void addStringListH(int x,int y,const std::vector<std::string>& list,F2C::uint spaceWidth);

    /**
    *
    */
    F2C::Rect getBiggestElement() const;

    F2C::uint getWidth() const;
    F2C::uint getHeight() const;

    int getIndex() const;

    /**
    *@param event Mouse Event
    *@param id SelectString-element ID
    *@brief is clicked on SelectString
    */
    bool isClicked(F2C::MouseEvent::Mouse event,size_t id) const;

    /**
    *@param id SelectString-element ID
    *@brief is Mouse over SelectString.
    */
    bool isHover(size_t id) const;

    /**
    *@brief update clicked and hover of SelectString
    */
    void update();
    void render();
};

#endif // SELECTFONT_HPP_INCLUDED
