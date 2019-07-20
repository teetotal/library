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

void ui_character_animal::init(Node * parent
          , Size size
          , Vec2 position
          , ALIGNMENT align
          , COLOR_RGB colorSkin
          , COLOR_RGB colorFeatures
          , COLOR_RGB colorPoint
          , COLOR_RGB colorBG)
{
    mParentSize = size;
    if(colorBG.isValidColor && colorBG.getA() > 0) {
        this->setBackGroundColor(colorBG.getColor3B());
        this->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    }
    mColorSkin = colorSkin;
    mColorFeatures = colorFeatures;
    mColorPoint = colorPoint;
    
    
    this->setPosition(position);
    gui::inst()->setAnchorPoint(this, align);
    
    if(parent)
        parent->addChild(this);
}

void ui_character_animal::drawEars(ID_EARS i) {

    CREATE_LAYOUT(ID_LAYOUT_EARS)
    
    if(mType == TYPE_RECTANGLE) {
        float f = this->getContentSize().height / GRID2.y;
        
        Vec2 posEarLeftT = getPositionOnGrid2(1, 0, ALIGNMENT_RIGHT);
        Vec2 posEarLeftL = getPositionOnGrid2(1, 1, ALIGNMENT_LEFT_BOTTOM);
        Vec2 posEarLeftR = getPositionOnGrid2(2, 1, ALIGNMENT_RIGHT_BOTTOM);
        
        gui::inst()->drawTriangle(mLayout[ID_LAYOUT_EARS], posEarLeftT, posEarLeftL, posEarLeftR, mColorSkin.getColor4F());
        gui::inst()->drawTriangle(mLayout[ID_LAYOUT_EARS]
                                  , Vec2(posEarLeftT.x, posEarLeftT.y - (f / 2.f))
                                  , Vec2(posEarLeftL.x + (f / 2.f), posEarLeftL.y)
                                  , Vec2(posEarLeftR.x - (f / 2.f), posEarLeftR.y)
                                  , mColorFeatures.getColor4F());
        
        Vec2 posEarRightT = getPositionOnGrid2(5, 0, ALIGNMENT_RIGHT);
        Vec2 posEarRightL = getPositionOnGrid2(5, 1, ALIGNMENT_LEFT_BOTTOM);
        Vec2 posEarRightR = getPositionOnGrid2(6, 1, ALIGNMENT_RIGHT_BOTTOM);
        
        gui::inst()->drawTriangle(mLayout[ID_LAYOUT_EARS], posEarRightT, posEarRightL, posEarRightR, mColorSkin.getColor4F());
        gui::inst()->drawTriangle(mLayout[ID_LAYOUT_EARS]
                                  , Vec2(posEarRightT.x, posEarRightT.y - (f / 2.f))
                                  , Vec2(posEarRightL.x + (f / 2.f), posEarRightL.y)
                                  , Vec2(posEarRightR.x - (f / 2.f), posEarRightR.y)
                                  , mColorFeatures.getColor4F());
    }
}

void ui_character_animal::drawFace(ID_FACE i) {
    
    CREATE_LAYOUT(ID_LAYOUT_FACE)
    
    if(mType == TYPE_RECTANGLE) {
        
        switch(i) {
            case ID_FACE_1: {
                gui::inst()->drawRect(mLayout[ID_LAYOUT_FACE]
                                      , getPositionOnGrid2(0, 1, ALIGNMENT_RIGHT_BOTTOM)
                                      , getPositionOnGrid2(6, 1, ALIGNMENT_RIGHT_BOTTOM)
                                      , getPositionOnGrid2(6, 6, ALIGNMENT_RIGHT_BOTTOM)
                                      , getPositionOnGrid2(0, 6, ALIGNMENT_RIGHT_BOTTOM)
                                      , mColorSkin.getColor4F()
                                      , true);
                
                gui::inst()->drawRect(mLayout[ID_LAYOUT_FACE]
                                      , getPositionOnGrid2(1, 6, ALIGNMENT_RIGHT_BOTTOM)
                                      , getPositionOnGrid2(5, 6, ALIGNMENT_RIGHT_BOTTOM)
                                      , getPositionOnGrid2(5, 7, ALIGNMENT_RIGHT_BOTTOM)
                                      , getPositionOnGrid2(1, 7, ALIGNMENT_RIGHT_BOTTOM)
                                      , mColorSkin.getColor4F()
                                      , true);
                
                gui::inst()->drawTriangle(mLayout[ID_LAYOUT_FACE]
                                          , getPositionOnGrid2(1, 7, ALIGNMENT_LEFT_TOP)
                                          , getPositionOnGrid2(1, 7, ALIGNMENT_RIGHT_TOP)
                                          , getPositionOnGrid2(1, 7, ALIGNMENT_RIGHT_BOTTOM)
                                          , mColorSkin.getColor4F());
                
                gui::inst()->drawTriangle(mLayout[ID_LAYOUT_FACE]
                                          , getPositionOnGrid2(6, 7, ALIGNMENT_LEFT_TOP)
                                          , getPositionOnGrid2(6, 7, ALIGNMENT_RIGHT_TOP)
                                          , getPositionOnGrid2(6, 7, ALIGNMENT_LEFT_BOTTOM)
                                          , mColorSkin.getColor4F());
                
                break;
            }
            case ID_FACE_2: {
                gui::inst()->drawRect(mLayout[ID_LAYOUT_FACE]
                                      , getPositionOnGrid2(0, 1, ALIGNMENT_RIGHT_BOTTOM)
                                      , getPositionOnGrid2(6, 1, ALIGNMENT_RIGHT_BOTTOM)
                                      , getPositionOnGrid2(6, 7, ALIGNMENT_RIGHT_BOTTOM)
                                      , getPositionOnGrid2(0, 7, ALIGNMENT_RIGHT_BOTTOM)
                                      , mColorSkin.getColor4F()
                                      , true);
                break;
            }
            default:
                break;
        }
    }
}

void ui_character_animal::drawEyes(ID_EYES i) {
    CREATE_LAYOUT(ID_LAYOUT_EYES)
    if(mType == TYPE_RECTANGLE) {
        float f = mLayout[ID_LAYOUT_EYES]->getContentSize().height / GRID2.y;
        switch(i) {
            case ID_EYES_1: {
                gui::inst()->drawCircle(mLayout[ID_LAYOUT_EYES], getPositionOnGrid2(2, 3, ALIGNMENT_RIGHT), f / 2.f, mColorFeatures.getColor4F());
                gui::inst()->drawCircle(mLayout[ID_LAYOUT_EYES], getPositionOnGrid2(5, 3, ALIGNMENT_LEFT), f / 2.f, mColorFeatures.getColor4F());
                break;
            }
            case ID_EYES_2: {
                gui::inst()->drawRect(mLayout[ID_LAYOUT_EYES], getPositionOnGrid2(2, 3, ALIGNMENT_RIGHT_TOP), Size(f / 2, f / 8), mColorFeatures.getColor4F());
                gui::inst()->drawRect(mLayout[ID_LAYOUT_EYES], getPositionOnGrid2(5, 3, ALIGNMENT_LEFT_TOP), Size(f / 2, f / 8), mColorFeatures.getColor4F());
                
                gui::inst()->drawCircle(mLayout[ID_LAYOUT_EYES], getPositionOnGrid2(2, 3, ALIGNMENT_RIGHT), f / 4.f, mColorFeatures.getColor4F());
                gui::inst()->drawCircle(mLayout[ID_LAYOUT_EYES], getPositionOnGrid2(5, 3, ALIGNMENT_LEFT), f / 4.f, mColorFeatures.getColor4F());
                break;
            }
            default:
                break;
        }
    }
}

void ui_character_animal::drawMouth(ID_MOUTH i) {
    CREATE_LAYOUT(ID_LAYOUT_MOUTH)
    if(mType == TYPE_RECTANGLE) {
        float f = mLayout[ID_LAYOUT_MOUTH]->getContentSize().height / GRID2.y;
        switch(i) {
            case ID_MOUTH_1: {
                Vec2 t = getPositionOnGrid2(3, 4, ALIGNMENT_RIGHT);
                Vec2 c = getPositionOnGrid2(3, 5, ALIGNMENT_RIGHT_TOP);
                Vec2 l = getPositionOnGrid2(3, 5, ALIGNMENT_CENTER);
                Vec2 r = getPositionOnGrid2(4, 5, ALIGNMENT_CENTER);
                
                //100 : 10 = f: x
                //
                gui::inst()->drawLine(mLayout[ID_LAYOUT_MOUTH], t, c, mColorFeatures.getColor4F(), f / 4);
                gui::inst()->drawLine(mLayout[ID_LAYOUT_MOUTH], c, l, mColorFeatures.getColor4F(), f / 2);
                gui::inst()->drawLine(mLayout[ID_LAYOUT_MOUTH], c, r, mColorFeatures.getColor4F(), f / 2);
                
                break;
            }
            case ID_MOUTH_2: {
                gui::inst()->drawCircle(mLayout[ID_LAYOUT_MOUTH], getPositionOnGrid(1, 2, ALIGNMENT_RIGHT), f / 16.f, mColorFeatures.getColor4F());
                
                break;
            }
            default:
                break;
        }
    }
}

void ui_character_animal::drawNose(ID_NOSE i) {
    CREATE_LAYOUT(ID_LAYOUT_NOSE)
    if(mType == TYPE_RECTANGLE) {
        float f = mLayout[ID_LAYOUT_NOSE]->getContentSize().height / GRID2.y;
        gui::inst()->drawCircle(mLayout[ID_LAYOUT_NOSE], getPositionOnGrid2(3, 4, ALIGNMENT_RIGHT), f / 6.f, mColorFeatures.getColor4F());
    }
}

void ui_character_animal::drawPoint(ID_POINT i) {
    CREATE_LAYOUT(ID_LAYOUT_POINT)
    if(mType == TYPE_RECTANGLE) {
        float f = mLayout[ID_LAYOUT_POINT]->getContentSize().height / GRID2.y;
        float thick = f / 4.f;
        gui::inst()->drawLine(mLayout[ID_LAYOUT_POINT]
                              , getPositionOnGrid2(1, 4, ALIGNMENT_RIGHT)
                              , getPositionOnGrid2(0, 4, ALIGNMENT_CENTER)
                              , mColorPoint.getColor4F()
                              , thick
                              );
        gui::inst()->drawLine(mLayout[ID_LAYOUT_POINT]
                              , getPositionOnGrid2(1, 5, ALIGNMENT_RIGHT)
                              , getPositionOnGrid2(0, 5, ALIGNMENT_CENTER)
                              , mColorPoint.getColor4F()
                              , thick
                              );
        
        gui::inst()->drawLine(mLayout[ID_LAYOUT_POINT]
                              , getPositionOnGrid2(7, 4, ALIGNMENT_CENTER)
                              , getPositionOnGrid2(6, 4, ALIGNMENT_LEFT)
                              , mColorPoint.getColor4F()
                              , thick
                              );
        gui::inst()->drawLine(mLayout[ID_LAYOUT_POINT]
                              , getPositionOnGrid2(7, 5, ALIGNMENT_CENTER)
                              , getPositionOnGrid2(6, 5, ALIGNMENT_LEFT)
                              , mColorPoint.getColor4F()
                              , thick
                              );
    }
}

void ui_character_animal::addRectangle(ID_EARS nEars
                                       , ID_FACE nFace
                                       , ID_EYES nEyes
                                       , ID_MOUTH nMouth
                                       , ID_NOSE nNose
                                       , ID_POINT nPoint)
{
    mType = TYPE_RECTANGLE;
    setContentSize(mParentSize);
    //ear
    drawEars(nEars);
    
    //face
    drawFace(nFace);

    //eyes
    drawEyes(nEyes);

    //mouth
    drawMouth(nMouth);
    
    //nose
    drawNose(nNose);

    // point
    drawPoint(nPoint);
    
    //drawLine
//    gui::inst()->drawGrid(this, this->getContentSize(), GRID2, Vec2::ZERO, Vec2::ZERO);
}

void ui_character_animal::addCircle() {
    mType = TYPE_CIRCLE;
    
    float f = fmin(mParentSize.width, mParentSize.height);
    setContentSize(Size(f, f));
    //ear
    gui::inst()->drawCircle(this, getPositionOnGrid(0, 0), f / 8.f, mColorSkin.getColor4F());
    gui::inst()->drawCircle(this, getPositionOnGrid(3, 0), f / 8.f, mColorSkin.getColor4F());
    
    gui::inst()->drawCircle(this, getPositionOnGrid(0, 0), f / 12.f, mColorFeatures.getColor4F());
    gui::inst()->drawCircle(this, getPositionOnGrid(3, 0), f / 12.f, mColorFeatures.getColor4F());
    //face
    gui::inst()->drawCircle(this, gui::inst()->getCenter(this), f / 2.f, mColorSkin.getColor4F());
    
    //눈썹
    gui::inst()->drawRect(this, getPositionOnGrid(1, 1, ALIGNMENT_CENTER_TOP), Size(f / 8, f / 32), mColorFeatures.getColor4F());
    gui::inst()->drawRect(this, getPositionOnGrid(2, 1, ALIGNMENT_CENTER_TOP), Size(f / 8, f / 32), mColorFeatures.getColor4F());
    //eyes
    gui::inst()->drawCircle(this, getPositionOnGrid(1, 1), f / 24.f, mColorFeatures.getColor4F());
    gui::inst()->drawCircle(this, getPositionOnGrid(2, 1), f / 24.f, mColorFeatures.getColor4F());
    
    
    //mouth
//    gui::inst()->drawCircle(this, getPositionOnGrid(1, 2, ALIGNMENT_RIGHT), f / 16.f, colorMain);
    Vec2 t = getPositionOnGrid(3, 4, ALIGNMENT_RIGHT_TOP, Vec2(8,8));
    Vec2 c = getPositionOnGrid(3, 4, ALIGNMENT_RIGHT, Vec2(8,8));
    Vec2 l = getPositionOnGrid(3, 5, ALIGNMENT_CENTER_TOP, Vec2(8,8));
    Vec2 r = getPositionOnGrid(4, 5, ALIGNMENT_CENTER_TOP, Vec2(8,8));
    
    gui::inst()->drawLine(this, t, c, mColorFeatures.getColor4F(), f*0.05f);
    gui::inst()->drawLine(this, c, l, mColorFeatures.getColor4F(), f*0.1f);
    gui::inst()->drawLine(this, c, r, mColorFeatures.getColor4F(), f*0.1f);
    
    //nose
    gui::inst()->drawCircle(this, getPositionOnGrid(1, 2, ALIGNMENT_RIGHT_TOP), f / 32.f, mColorFeatures.getColor4F());
    
    
    // point
    gui::inst()->drawCircle(this, getPositionOnGrid(0, 2, ALIGNMENT_RIGHT_TOP), f / 16.f, mColorPoint.getColor4F());
    gui::inst()->drawCircle(this, getPositionOnGrid(3, 2, ALIGNMENT_LEFT_TOP), f / 16.f, mColorPoint.getColor4F());
    
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
