//
//  ui_charator_animal.cpp
//
//  Created by Jung, DaeCheon on 27/06/2019.
//

#include "ui_character_animal.h"
#include "ui_ext.h"

#define CREATE_LAYOUT(x) mLayout[x] = Layout::create();\
mLayout[x]->setContentSize(this->getContentSize());\
this->addChild(mLayout[x]);

void ui_character_animal::drawEars(int i) {

    CREATE_LAYOUT(ID_LAYOUT_EARS)
    
    if(mType == TYPE_RECTANGLE) {
        float f = this->getContentSize().height / GRID2.y;
        
        Vec2 posEarLeftT = getPositionOnGrid2(1, 0, ALIGNMENT_RIGHT);
        Vec2 posEarLeftL = getPositionOnGrid2(1, 1, ALIGNMENT_LEFT_BOTTOM);
        Vec2 posEarLeftR = getPositionOnGrid2(2, 1, ALIGNMENT_RIGHT_BOTTOM);
        
        gui::inst()->drawTriangle(mLayout[ID_LAYOUT_EARS], posEarLeftT, posEarLeftL, posEarLeftR, mColorSkin);
        gui::inst()->drawTriangle(mLayout[ID_LAYOUT_EARS]
                                  , Vec2(posEarLeftT.x, posEarLeftT.y - (f / 2.f))
                                  , Vec2(posEarLeftL.x + (f / 2.f), posEarLeftL.y)
                                  , Vec2(posEarLeftR.x - (f / 2.f), posEarLeftR.y)
                                  , mColorFeatures);
        
        Vec2 posEarRightT = getPositionOnGrid2(5, 0, ALIGNMENT_RIGHT);
        Vec2 posEarRightL = getPositionOnGrid2(5, 1, ALIGNMENT_LEFT_BOTTOM);
        Vec2 posEarRightR = getPositionOnGrid2(6, 1, ALIGNMENT_RIGHT_BOTTOM);
        
        gui::inst()->drawTriangle(mLayout[ID_LAYOUT_EARS], posEarRightT, posEarRightL, posEarRightR, mColorSkin);
        gui::inst()->drawTriangle(mLayout[ID_LAYOUT_EARS]
                                  , Vec2(posEarRightT.x, posEarRightT.y - (f / 2.f))
                                  , Vec2(posEarRightL.x + (f / 2.f), posEarRightL.y)
                                  , Vec2(posEarRightR.x - (f / 2.f), posEarRightR.y)
                                  , mColorFeatures);
    }
}

void ui_character_animal::drawFace(int i) {
    
    CREATE_LAYOUT(ID_LAYOUT_FACE)
    
    if(mType == TYPE_RECTANGLE) {
        Vec2 posFace1 = getPositionOnGrid2(0, 1, ALIGNMENT_RIGHT_BOTTOM);
        Vec2 posFace2 = getPositionOnGrid2(6, 1, ALIGNMENT_RIGHT_BOTTOM);
        Vec2 posFace3 = getPositionOnGrid2(6, 7, ALIGNMENT_RIGHT_BOTTOM);
        Vec2 posFace4 = getPositionOnGrid2(0, 7, ALIGNMENT_RIGHT_BOTTOM);
        
        gui::inst()->drawRect(mLayout[ID_LAYOUT_FACE], posFace1, posFace2, posFace3, posFace4, mColorSkin, true);
    }
}

void ui_character_animal::drawEyebrow(int i) {
    
    CREATE_LAYOUT(ID_LAYOUT_EYEBROW)
    
    if(mType == TYPE_RECTANGLE) {
        float f = mLayout[ID_LAYOUT_EYEBROW]->getContentSize().height / GRID2.y;
        gui::inst()->drawRect(mLayout[ID_LAYOUT_EYEBROW], getPositionOnGrid2(2, 3, ALIGNMENT_RIGHT_TOP), Size(f / 2, f / 8), mColorFeatures);
        gui::inst()->drawRect(mLayout[ID_LAYOUT_EYEBROW], getPositionOnGrid2(5, 3, ALIGNMENT_LEFT_TOP), Size(f / 2, f / 8), mColorFeatures);
    }
}

void ui_character_animal::drawEyes(int i) {
    CREATE_LAYOUT(ID_LAYOUT_EYES)
    if(mType == TYPE_RECTANGLE) {
        float f = mLayout[ID_LAYOUT_EYES]->getContentSize().height / GRID2.y;
        gui::inst()->drawCircle(mLayout[ID_LAYOUT_EYES], getPositionOnGrid2(2, 3, ALIGNMENT_RIGHT), f / 4.f, mColorFeatures);
        gui::inst()->drawCircle(mLayout[ID_LAYOUT_EYES], getPositionOnGrid2(5, 3, ALIGNMENT_LEFT), f / 4.f, mColorFeatures);
    }
}

void ui_character_animal::drawMouth(int i) {
    CREATE_LAYOUT(ID_LAYOUT_MOUTH)
    if(mType == TYPE_RECTANGLE) {
        float f = mLayout[ID_LAYOUT_MOUTH]->getContentSize().height / GRID2.y;
        switch(i) {
            case 0: {
                Vec2 t = getPositionOnGrid2(3, 4, ALIGNMENT_RIGHT);
                Vec2 c = getPositionOnGrid2(3, 5, ALIGNMENT_RIGHT_TOP);
                Vec2 l = getPositionOnGrid2(3, 5, ALIGNMENT_CENTER);
                Vec2 r = getPositionOnGrid2(4, 5, ALIGNMENT_CENTER);
                
                //100 : 10 = f: x
                //
                gui::inst()->drawLine(mLayout[ID_LAYOUT_MOUTH], t, c, mColorFeatures, f / 4);
                gui::inst()->drawLine(mLayout[ID_LAYOUT_MOUTH], c, l, mColorFeatures, f / 2);
                gui::inst()->drawLine(mLayout[ID_LAYOUT_MOUTH], c, r, mColorFeatures, f / 2);
                
                break;
            }
            case 1: {
                gui::inst()->drawCircle(mLayout[ID_LAYOUT_MOUTH], getPositionOnGrid(1, 2, ALIGNMENT_RIGHT), f / 16.f, mColorFeatures);
                
                break;
            }
        }
    }
}

void ui_character_animal::drawNose(int i) {
    CREATE_LAYOUT(ID_LAYOUT_NOSE)
    if(mType == TYPE_RECTANGLE) {
        float f = mLayout[ID_LAYOUT_NOSE]->getContentSize().height / GRID2.y;
        gui::inst()->drawCircle(mLayout[ID_LAYOUT_NOSE], getPositionOnGrid2(3, 4, ALIGNMENT_RIGHT), f / 6.f, mColorFeatures);
    }
}

void ui_character_animal::drawPoint(int i) {
    CREATE_LAYOUT(ID_LAYOUT_POINT)
    if(mType == TYPE_RECTANGLE) {
        float f = mLayout[ID_LAYOUT_POINT]->getContentSize().height / GRID2.y;
        float thick = f / 4.f;
        gui::inst()->drawLine(mLayout[ID_LAYOUT_POINT]
                              , getPositionOnGrid2(1, 4, ALIGNMENT_RIGHT)
                              , getPositionOnGrid2(0, 4, ALIGNMENT_CENTER)
                              , mColorPoint
                              , thick
                              );
        gui::inst()->drawLine(mLayout[ID_LAYOUT_POINT]
                              , getPositionOnGrid2(1, 5, ALIGNMENT_RIGHT)
                              , getPositionOnGrid2(0, 5, ALIGNMENT_CENTER)
                              , mColorPoint
                              , thick
                              );
        
        gui::inst()->drawLine(mLayout[ID_LAYOUT_POINT]
                              , getPositionOnGrid2(7, 4, ALIGNMENT_CENTER)
                              , getPositionOnGrid2(6, 4, ALIGNMENT_LEFT)
                              , mColorPoint
                              , thick
                              );
        gui::inst()->drawLine(mLayout[ID_LAYOUT_POINT]
                              , getPositionOnGrid2(7, 5, ALIGNMENT_CENTER)
                              , getPositionOnGrid2(6, 5, ALIGNMENT_LEFT)
                              , mColorPoint
                              , thick
                              );
    }
}

void ui_character_animal::addRectangle(Size parentSize, Color3B colorBG, Color4F colorSkin, Color4F colorFeatures, Color4F colorPoint) {
    this->setContentSize(parentSize);
    
    this->setBackGroundColor(colorBG);
    this->setBackGroundColorType(Layout::BackGroundColorType::SOLID);

    mColorSkin = colorSkin;
    mColorFeatures = colorFeatures;
    mColorPoint = colorPoint;
    
    mType = TYPE_RECTANGLE;
    //ear
    drawEars(0);
    
    //face
    drawFace(0);

    //눈썹
    drawEyebrow(0);
    
    //eyes
    drawEyes(0);

    //mouth
    drawMouth(0);
    
    //nose
    drawNose(0);

    // point
    drawPoint(0);
    
    //drawLine
//    gui::inst()->drawGrid(this, this->getContentSize(), GRID2, Vec2::ZERO, Vec2::ZERO);
}

void ui_character_animal::addCircle(Size parentSize, Color3B colorBG, Color4F colorSkin, Color4F colorFeatures, Color4F colorPoint) {
    float f = fmin(parentSize.width, parentSize.height);
    this->setContentSize(Size(f, f));
    
    this->setBackGroundColor(colorBG);
    this->setBackGroundColorType(Layout::BackGroundColorType::SOLID);

    //ear
    gui::inst()->drawCircle(this, getPositionOnGrid(0, 0), f / 8.f, colorSkin);
    gui::inst()->drawCircle(this, getPositionOnGrid(3, 0), f / 8.f, colorSkin);
    
    gui::inst()->drawCircle(this, getPositionOnGrid(0, 0), f / 12.f, colorFeatures);
    gui::inst()->drawCircle(this, getPositionOnGrid(3, 0), f / 12.f, colorFeatures);
    //face
    gui::inst()->drawCircle(this, gui::inst()->getCenter(this), f / 2.f, colorSkin);
    
    //눈썹
    gui::inst()->drawRect(this, getPositionOnGrid(1, 1, ALIGNMENT_CENTER_TOP), Size(f / 8, f / 32), colorFeatures);
    gui::inst()->drawRect(this, getPositionOnGrid(2, 1, ALIGNMENT_CENTER_TOP), Size(f / 8, f / 32), colorFeatures);
    //eyes
    gui::inst()->drawCircle(this, getPositionOnGrid(1, 1), f / 16.f, colorFeatures);
    gui::inst()->drawCircle(this, getPositionOnGrid(2, 1), f / 16.f, colorFeatures);
    
    
    //mouth
//    gui::inst()->drawCircle(this, getPositionOnGrid(1, 2, ALIGNMENT_RIGHT), f / 16.f, colorMain);
    Vec2 t = getPositionOnGrid(3, 4, ALIGNMENT_RIGHT_TOP, Vec2(8,8));
    Vec2 c = getPositionOnGrid(3, 4, ALIGNMENT_RIGHT, Vec2(8,8));
    Vec2 l = getPositionOnGrid(3, 5, ALIGNMENT_CENTER_TOP, Vec2(8,8));
    Vec2 r = getPositionOnGrid(4, 5, ALIGNMENT_CENTER_TOP, Vec2(8,8));
    
    gui::inst()->drawLine(this, t, c, colorFeatures, f*0.05f);
    gui::inst()->drawLine(this, c, l, colorFeatures, f*0.1f);
    gui::inst()->drawLine(this, c, r, colorFeatures, f*0.1f);
    
    //nose
    gui::inst()->drawCircle(this, getPositionOnGrid(1, 2, ALIGNMENT_RIGHT_TOP), f / 32.f, colorFeatures);
    
    
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
