//
//  ui_icon.cpp
//
//  Created by Jung, DaeCheon on 19/06/2019.
//

#include "ui_icon.h"
#include "ui_ext.h"

#define SYSTEM_FONT_NAME "Helvetica"

void ui_icon::addHeart(Node * p, Size sizePerGrid, Vec2 pos, ALIGNMENT align, const string sz, COLOR_RGB color, const float fontSize)
{
    Size size;
//    this->setBackGroundColor(Color3B::MAGENTA);
//    this->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    
    mNodes.ch = Label::createWithSystemFont("♥", SYSTEM_FONT_NAME
                                            , gui::inst()->getFontSizeDefine(sizePerGrid, fontSize));
    
    gui::inst()->setAnchorPoint(mNodes.ch, ALIGNMENT_LEFT_BOTTOM);
    mNodes.ch->setPosition(Vec2::ZERO);
    mNodes.ch->enableGlow(Color4B::BLACK);
    this->addChild(mNodes.ch);
    
    size = mNodes.ch->getContentSize();
    
    if(sz.size() > 0) {
        mNodes.label = Label::createWithTTF(sz, gui::inst()->mDefaultFont
                                            , gui::inst()->getFontSizeDefine(sizePerGrid, fontSize));
        mNodes.label->setColor(color.getColor3B());
        gui::inst()->setAnchorPoint(mNodes.label, ALIGNMENT_LEFT_BOTTOM);
        
        float margin = size.width * 0.1f;
        mNodes.label->setPosition(Vec2(size.width + margin, -1));
        size.width += mNodes.label->getContentSize().width + margin;
        enableGlow(Color4B::BLACK);
    }
    
    
    if(mNodes.label)
        this->addChild(mNodes.label);
    
    this->setPosition(pos);
    gui::inst()->setAnchorPoint(this, align);
    this->setContentSize(size);
    
    p->addChild(this);
}

void ui_icon::addCircle(Node * p
                        , Size sizePerGrid
                        , Vec2 pos
                        , ALIGNMENT align
                        , COLOR_RGB color
                        , const string sz
                        , const string img
                        , const string szText
                        , COLOR_RGB colorText
                        , const float fontSize)
{
    Size size;
//    this->setBackGroundColor(Color3B::MAGENTA);
//    this->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    gui::inst()->setAnchorPoint(this, align);
    
    float min = fmin(sizePerGrid.width, sizePerGrid.height);
    float scale = gui::inst()->getScaleDefine(fontSize);
    if(scale == 0)
        scale = 1;
    min = min * scale;
    
    Size sizeCircle = Size(min, min);
    size = sizeCircle;
    
    float radius = min / 2.f;
    
    Color4F colorOut, colorInner, colorOutline;
    Color3B colorSymbol;
    colorOut = color.getColorDark().getColor4F();
    colorInner = color.getColor4F();
//    colorOutline = Color4F::BLACK;//color.getColorDark().getColorDark().getColor4F();
    colorSymbol = color.getColorDark().getColorDark().getColor3B();
    
    mNodes.drawNode = DrawNode::create();
    Vec2 centerInner = Vec2(sizeCircle.width / 2.f, sizeCircle.height / 2.f);
    
    //outline 적용하면 오히려 지저분해짐
//    draw->drawDot(centerInner, radius, colorOutline);
    
    //outcircle
    mNodes.drawNode->drawDot(centerInner, radius, colorOut);
    
    //inner circle
    float innerCircleRadius = radius * 0.8f;
    mNodes.drawNode->drawDot(centerInner, innerCircleRadius, colorInner);
    this->addChild(mNodes.drawNode);
    
    //img
    if(img.size() > 0) {
        mNodes.sprite = gui::inst()->getSprite(img);
        gui::inst()->setScale(mNodes.sprite, innerCircleRadius * 2 * 0.8f);
        mNodes.sprite->setPosition(centerInner);
        this->addChild(mNodes.sprite);
    }
    
    //circle text
    if(sz.size() > 0) {
        float fontSize = gui::inst()->getFontSizeDefine(sizeCircle, -1);
        mNodes.ch = Label::createWithSystemFont(sz, SYSTEM_FONT_NAME, fontSize);
        mNodes.ch->setColor(colorSymbol);
        gui::inst()->setAnchorPoint(mNodes.ch, ALIGNMENT_CENTER);
        mNodes.ch->setPosition(centerInner);
        this->addChild(mNodes.ch);
    }
    
    //text
    if(szText.size() > 0) {
        mNodes.label = Label::createWithTTF(szText, gui::inst()->mDefaultFont
                                            , gui::inst()->getFontSizeDefine(sizeCircle, 0));
        
        mNodes.label->setColor(colorText.getColor3B());
        gui::inst()->setAnchorPoint(mNodes.label, ALIGNMENT_LEFT_BOTTOM);
        enableGlow(Color4B::BLACK);
        
        float margin = size.width * 0.1f;
        mNodes.label->setPosition(Vec2(sizeCircle.width + margin, -1)); // 1px아래로 해야 위에가 안짤림.
        size.width += mNodes.label->getContentSize().width + margin;
        this->addChild(mNodes.label);
    }
    
    this->setContentSize(size);
    this->setPosition(pos);
    
    p->addChild(this);
}

void ui_icon::setEnabled(bool enable) {
    mEnable = enable;
    
    GLubyte opacity = (enable) ? 255 : 128;
        
    if(mNodes.drawNode)
        mNodes.drawNode->setOpacity(opacity);
    if(mNodes.ch)
        mNodes.ch->setOpacity(opacity);
    if(mNodes.label)
        mNodes.label->setOpacity(opacity);
    if(mNodes.sprite)
        mNodes.sprite->setOpacity(opacity);
}

void ui_icon::runScaleAndDisable() {
    mEnable = false;
    guiExt::runScaleEffect(this, CallFunc::create([=](){ this->setEnabled(false); }));
}

void ui_icon::setText(const string sz) {
    if(mNodes.label) {
        float w1 = mNodes.label->getContentSize().width;
        mNodes.label->setString(sz);
        float w2 = mNodes.label->getContentSize().width;
        float f = w2 - w1;
        Size size = this->getContentSize();
        this->setContentSize(Size(size.width + f, size.height));
    }
};
