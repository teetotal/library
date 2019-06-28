//
//  ui_charator_animal.cpp
//
//  Created by Jung, DaeCheon on 27/06/2019.
//

#include "ui_character_animal.h"
#include "ui_ext.h"

void ui_character_animal::init(Size parentSize) {
    float f = fmin(parentSize.width, parentSize.height);
    this->setContentSize(Size(f, f));
    
    this->setBackGroundColor(Color3B::MAGENTA);
    this->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    
    Color4F colorFace = Color4F::WHITE;
    Color4F colorMain = Color4F::BLACK;
    Color4F colorPoint = Color4F::ORANGE;
    
    //ear
    gui::inst()->drawCircle(this, getPositionOnGrid(0, 0), f / 8.f, colorFace);
    gui::inst()->drawCircle(this, getPositionOnGrid(3, 0), f / 8.f, colorFace);
    
    gui::inst()->drawCircle(this, getPositionOnGrid(0, 0), f / 9.f, colorMain);
    gui::inst()->drawCircle(this, getPositionOnGrid(3, 0), f / 9.f, colorMain);
    //face
    gui::inst()->drawCircle(this, gui::inst()->getCenter(this), f / 2.f, colorFace);
    
    //눈썹
    gui::inst()->drawRectRound(this, getPositionOnGrid(1, 1, ALIGNMENT_CENTER_TOP), Size(f / 8, f / 32), colorMain);
    gui::inst()->drawRectRound(this, getPositionOnGrid(2, 1, ALIGNMENT_CENTER_TOP), Size(f / 8, f / 32), colorMain);
    //eyes
    gui::inst()->drawCircle(this, getPositionOnGrid(1, 1), f / 16.f, colorMain);
    gui::inst()->drawCircle(this, getPositionOnGrid(2, 1), f / 16.f, colorMain);
    
    
    //mouth
//    gui::inst()->drawCircle(this, getPositionOnGrid(1, 2, ALIGNMENT_RIGHT), f / 16.f, colorMain);
    Vec2 t = getPositionOnGrid(3, 4, ALIGNMENT_RIGHT_TOP, Vec2(8,8));
    Vec2 c = getPositionOnGrid(3, 4, ALIGNMENT_RIGHT, Vec2(8,8));
    Vec2 l = getPositionOnGrid(3, 5, ALIGNMENT_CENTER_TOP, Vec2(8,8));
    Vec2 r = getPositionOnGrid(4, 5, ALIGNMENT_CENTER_TOP, Vec2(8,8));
    
    gui::inst()->drawLine(this, t, c, colorMain, 5);
    gui::inst()->drawLine(this, c, l, colorMain, 5);
    gui::inst()->drawLine(this, c, r, colorMain, 5);
    
    //nose
    gui::inst()->drawCircle(this, getPositionOnGrid(1, 2, ALIGNMENT_RIGHT_TOP), f / 32.f, colorMain);
    
    
    // point
    gui::inst()->drawCircle(this, getPositionOnGrid(0, 2, ALIGNMENT_RIGHT_TOP), f / 16.f, colorPoint);
    gui::inst()->drawCircle(this, getPositionOnGrid(3, 2, ALIGNMENT_LEFT_TOP), f / 16.f, colorPoint);
    
//    gui::inst()->drawGrid(this, this->getContentSize(), Vec2(8,8), Vec2::ZERO, Vec2::ZERO);
}

Vec2 ui_character_animal::getPositionOnGrid(int x, int y, ALIGNMENT align, Vec2 grid) {
    return gui::inst()->getPointVec2(x, y
                              , align
                              , this->getContentSize()
                              , grid
                              , Vec2::ZERO
                              , Vec2::ZERO
                              , Vec2::ZERO
                              , Vec2::ZERO);
}
