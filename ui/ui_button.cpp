//
//  ui_button.cpp
//
//  Created by Jung, DaeCheon on 21/06/2019.
//

#include "ui_button.h"
#include "ui_ext.h"

void ui_button::init(int id
                     , int target
                     , const string text
                     , Node * p
                     , Vec2 pos
                     , ALIGNMENT align
                     , Size size
                     , TYPE type
                     , std::function<void(int, int)> callback
                     , COLOR_RGB color
                     , COLOR_RGB colorFont
                     , COLOR_RGB colorBack
                     , const string img
                     , TOUCH_TYPE touchType) {
    this->mId = id;
    this->mTarget = target;
    this->setContentSize(size);
    this->mTouchType = touchType;
    mCallback = callback;
    
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
    
    //hide
    int fontLength = (int)(size.width / gui::inst()->createLabel(0, 0, "M", gui::inst()->getFontSizeDefine(size, 0), ALIGNMENT_CENTER)->getContentSize().width);
    string szM = "";
    for(int n = 0; n < fontLength; n++) {
        szM += "M";
    }
    gui::inst()->addTextButtonAutoDimension(0
                                            , 0
                                            , szM
                                            , this
                                            , CC_CALLBACK_1(ui_button::callbackFn, this)
                                            , gui::inst()->getFontSizeDefine(size, 0)
                                            , ALIGNMENT_CENTER
                                            , Color3B::WHITE
                                            , Vec2(1, 1)
                                            , Vec2::ZERO
                                            , Vec2::ZERO
                                            , Vec2::ZERO
                                            , Vec2::ZERO
                                            )->setOpacity(0);
    
    if(img.size() > 0)
    {
        mNodes.menuItemImage = gui::inst()->addSpriteButton(0, 0, img, img, this, CC_CALLBACK_1(ui_button::callbackFn, this), ALIGNMENT_CENTER, size, Vec2(1, 1), Vec2::ZERO, Vec2::ZERO, Vec2::ZERO);
        
        gui::inst()->setScaleByHeight(mNodes.menuItemImage, size.height * gui::inst()->getScaleDefine(-1));
        
    } else if(text.size() > 0)
    {
        mNodes.menuItem = gui::inst()->addTextButtonAutoDimension(0, 0, text, this, CC_CALLBACK_1(ui_button::callbackFn, this), -1, ALIGNMENT_CENTER, colorFont.getColor3B(), Vec2(1, 1), Vec2::ZERO, Vec2::ZERO, Vec2::ZERO);
        mNodes.menuItem->setOpacity(colorFont.getA());
        mNodes.menuItem->setPosition(Vec2(mNodes.menuItem->getPosition().x, mNodes.menuItem->getPosition().y-1));
    }
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
    if(mNodes.menuItem)
        mNodes.menuItem->setEnabled(enable);
    if(mNodes.menuItemImage)
        mNodes.menuItemImage->setOpacity(opacity);
}


void ui_button::runScaleAndDisable() {
    mEnable = false;
    guiExt::runScaleEffect(this, CallFunc::create([=](){ this->setEnabled(false); }));
}

void ui_button::callbackFn(cocos2d::Ref* pSender) {
    if(this->mEnable == false)
        return;
    
    switch(this->mTouchType) {
        case TOUCH_TYPE_NORMAL:
            guiExt::runScaleEffect(this, CallFunc::create([=](){ mCallback(mId, mTarget); }));
            break;
        case TOUCH_TYPE_AUTO_DISABLE:
            runScaleAndDisable();
            mCallback(mId, mTarget);
            break;
    }
    
}

//==============================================================================================
void ui_checkbox::init(Node * p
                       , Vec2 pos
                       , ALIGNMENT align
                       , Size sizePerGrid
                       , int sizeDefine
                       , const string text
                       , COLOR_RGB color
                       , COLOR_RGB colorFont)
{
    float scale = gui::inst()->getScaleDefine(sizeDefine);
    Size size = Size(sizePerGrid.height * scale, sizePerGrid.height * scale);
    mCheckboxSize = size;
    
    //checkbox
    drawUnchecked(color);
    
    //check v√٧
    Vec2 center = Vec2(mCheckboxSize.width/2.f, mCheckboxSize.height / 2.f);
    float fontSize = gui::inst()->getFontSizeDefine(mCheckboxSize, -2);
    mNodes.labelChecked = Label::createWithSystemFont("V", SYSTEM_FONT_NAME, fontSize);
//    mNodes.labelChecked = Label::createWithTTF("V", gui::inst()->mDefaultFont, fontSize);
    mNodes.labelChecked->setColor(color.getColor3B());
    mNodes.labelChecked->setPosition(center);
//    mNodes.labelChecked->enableBold();
//    mNodes.labelChecked->enableGlow(Color4B::BLACK);
    this->addChild(mNodes.labelChecked);
    setChecked(mIsChecked);
    
    mNodes.label = Label::createWithTTF(text, gui::inst()->mDefaultFont
                                        , gui::inst()->getFontSizeDefine(size, 0));
    
    mNodes.label->setColor(colorFont.getColor3B());
    gui::inst()->setAnchorPoint(mNodes.label, ALIGNMENT_LEFT_BOTTOM);
    
    float margin = size.width * 0.1f;
    mNodes.label->setPosition(Vec2(size.width + margin, -1));
    size.width += mNodes.label->getContentSize().width + margin;
    this->addChild(mNodes.label);
    
    this->setContentSize(size);
    this->setPosition(pos);
    gui::inst()->setAnchorPoint(this, align);
    
    p->addChild(this);
}

void ui_checkbox::drawUnchecked(COLOR_RGB color) {
    if(mNodes.drawNode)
        this->removeChild(mNodes.drawNode);
    
    Vec2 center = Vec2(mCheckboxSize.width/2.f, mCheckboxSize.height / 2.f);
    Size size = Size(mCheckboxSize.width * 0.75f, mCheckboxSize.height * 0.75);
    
    mNodes.drawNode = gui::inst()->drawRect(this, center, size, color.getColor4F(), false);
    int thick = mCheckboxSize.width * 10 * 0.2;
    for(int n=0; n<thick; n++) {
        float f = ((n+1) * 0.1f);
        Size s = Size(size.width - f, size.height - f);
        gui::inst()->drawRect(NULL, center, s, color.getColor4F(), false, mNodes.drawNode);
    }
}

void ui_checkbox::setChecked(bool isChecked) {
    mIsChecked = isChecked;
    mNodes.labelChecked->setVisible(mIsChecked);
}

void ui_checkbox::setEnabled(bool enable) {
    mEnable = enable;
    
    GLubyte opacity = (enable) ? 255 : 128;
    
    //    if(mNodes.drawNode)
    //        mNodes.drawNode->setOpacity(opacity); 그린 여러 폴리곤이 개별적으로 먹어서 이상한 느낌이 됨.
    if(mNodes.label)
        mNodes.label->setOpacity(opacity);
}

void ui_checkbox::setText(const string sz) {
    if(mNodes.label) {
        float w1 = mNodes.label->getContentSize().width;
        mNodes.label->setString(sz);
        float w2 = mNodes.label->getContentSize().width;
        float f = w2 - w1;
        Size size = this->getContentSize();
        this->setContentSize(Size(size.width + f, size.height));
    }
}
