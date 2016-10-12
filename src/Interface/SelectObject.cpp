#include "SelectObject.hpp"

SelectObject::SelectObject():
    active(true),
    select(false),
    hover(false),
    clicked(false),
    selectbyclick(false)
{}

bool SelectObject::isClicked(F2C::MouseEvent::Mouse event,F2C::Rect obj) const {
    if(this->isHover(obj)){
        return Engine::InApp.getRepeatMouse(event);
    }

    return false;
}


bool SelectObject::isHover(F2C::Rect obj) const {
    F2C::Rect mouserect (0,0,8,8);
    Engine::InApp.getMousePos(&mouserect.x,&mouserect.y);

    return obj.collision(mouserect);
}

void SelectObject::update(F2C::MouseEvent::Mouse event,F2C::Rect obj){
    if(this->active){
        this->hover = this->isHover(obj);
        this->clicked = this->isClicked(event,obj);
        if(this->selectbyclick && this->clicked){
            this->select = true;
        }
    }
}
