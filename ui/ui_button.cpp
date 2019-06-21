//
//  ui_button.cpp
//
//  Created by Jung, DaeCheon on 21/06/2019.
//

#include "ui_button.h"
#include "ui_ext.h"

void ui_button::init(int id
                     , const string text
                     , Node * p
                     , Vec2 pos
                     , ALIGNMENT align
                     , Size size
                     , TYPE type
                     , std::function<void(int)> callback
                     , COLOR_RGB color
                     , COLOR_RGB colorFont
                     , COLOR_RGB colorBack
                     , const string img
                     , TOUCH_TYPE touchType) {
    this->mId = id;
    this->setContentSize(size);
    this->mTouchType = touchType;
    
    switch(type) {
        case TYPE_ROUND:
            drawRectRoundShadow(color);
            break;
        case TYPE_CIRCLE:
            drawRectCircleButton(color, colorBack);
            break;
        default:
            break;
    }
    this->setPosition(pos);
    gui::inst()->setAnchorPoint(this, align);
    
    p->addChild(this);
    if(img.size() > 0) {
        mNodes.sprite = gui::inst()->getSprite(img);
        gui::inst()->setScaleByHeight(mNodes.sprite, size.height * gui::inst()->getScaleDefine(-1));
        mNodes.sprite->setPosition(gui::inst()->getCenter(this));
        this->addChild(mNodes.sprite);
    } else if(text.size() > 0) {
        mNodes.label = gui::inst()->addLabelAutoDimension(0, 0, text, this, -1, ALIGNMENT_CENTER, colorFont.getColor3B(), Vec2(1, 1), Vec2::ZERO, Vec2::ZERO, Vec2::ZERO);
        mNodes.label->setOpacity(colorFont.getA());
    }
    setTouchEvent(callback);
}

void ui_button::drawRectRoundShadow(COLOR_RGB color)
{
    Size size = this->getContentSize();
    Vec2 center = Vec2(size.width / 2.f, size.height / 2.f);
    
    Color4F colorShadow = color.getColorLight().getColor4F();
    Color4F colorMain = color.getColor4F();
    
    mNodes.drawNode = gui::inst()->drawRectRound(NULL, center, size, colorShadow);
    mNodes.drawNode = gui::inst()->drawRectRound(this, center, Size(size.width - 2.f, size.height - 2.f), colorMain, mNodes.drawNode);
}


void ui_button::drawRectCircleButton(COLOR_RGB colorFront, COLOR_RGB colorBack)
{
    Size size = this->getContentSize();
    Vec2 center = Vec2(size.width / 2.f, size.height / 2.f);
    Size innerSize;
    
    if(colorBack.isValidColor)
    {
        float innerMargin = size.height * 0.1f;
        innerSize = Size(size.width - innerMargin, size.height - innerMargin);
        
        mNodes.drawNode = gui::inst()->drawRectCircle(NULL, center, size, colorBack.getColor4F());
        mNodes.drawNode = gui::inst()->drawRectCircle(NULL, center, innerSize, colorFront.getColorDark().getColor4F(), mNodes.drawNode);
    } else
    {
        mNodes.drawNode = gui::inst()->drawRectCircle(NULL, center, size, colorFront.getColorDark().getColor4F());
        innerSize = size;
    }
    
    float shadowMargin = innerSize.height * 0.1f;
    mNodes.drawNode = gui::inst()->drawRectCircle(this, Vec2(center.x, center.y + (shadowMargin / 2.f)), Size(innerSize.width, innerSize.height - shadowMargin), colorFront.getColor4F(), mNodes.drawNode);
}


void ui_button::setEnabled(bool enable) {
    mEnable = enable;
    
    GLubyte opacity = (enable) ? 255 : 128;
    
//    if(mNodes.drawNode)
//        mNodes.drawNode->setOpacity(opacity); 그린 여러 폴리곤이 개별적으로 먹어서 이상한 느낌이 됨.
    if(mNodes.label)
        mNodes.label->setOpacity(opacity);
    if(mNodes.sprite)
        mNodes.sprite->setOpacity(opacity);
}


void ui_button::runScaleAndDisable() {
    mEnable = false;
    guiExt::runScaleEffect(this, CallFunc::create([=](){ this->setEnabled(false); }));
}

void ui_button::setTouchEvent(std::function<void(int)> callback) {
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = [=](Touch* touch, Event* event){
        // your code
        return true; // if you are consuming it
    };
    listener1->onTouchMoved = [=](Touch* touch, Event* event){
        // your code
    };
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        if(this->mEnable == false)
            return;
        
        switch(this->mTouchType) {
            case TOUCH_TYPE_NORMAL:
                guiExt::runScaleEffect(this);
                break;
            case TOUCH_TYPE_AUTO_DISABLE:
                runScaleAndDisable();
                break;
        }
        callback(mId);
    };
    
    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}
