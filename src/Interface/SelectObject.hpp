#ifndef SELECTOBJECT_HPP_INCLUDED
#define SELECTOBJECT_HPP_INCLUDED

#include <basic.h>
#include <GameStates.hpp>

class SelectObject{
    protected:
    /**
    *@param event Mouse Event
    *@param obj Object
    *@brief is clicked on Object
    */
    bool isClicked(F2C::MouseEvent::Mouse event,F2C::Rect obj) const;

    /**
    *@param obj Object
    *@brief is Mouse over Object
    */
    bool isHover(F2C::Rect obj) const;

    /**
    *@brief update clicked and hover of SelectObject
    */
    void update(F2C::MouseEvent::Mouse event,F2C::Rect obj);

    public:
    bool active;
    bool select;
    bool hover;
    bool clicked;
    bool selectbyclick;

    SelectObject();
};

#endif // SELECTOBJECT_HPP_INCLUDED
