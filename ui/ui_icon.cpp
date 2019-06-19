//
//  ui_icon.cpp
//
//  Created by Jung, DaeCheon on 19/06/2019.
//

#include "ui_icon.h"
#define SYSTEM_FONT_NAME "Helvetica"

void ui_icon::addHeart(Node * p, Size sizePerGrid, Vec2 pos, ALIGNMENT align, const string sz, COLOR_RGB color)
{
    mLabel = NULL;
    Size size;
//    this->setBackGroundColor(Color3B::MAGENTA);
//    this->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    
    float fontSize = gui::inst()->getFontSizeDefine(sizePerGrid, 0);
    auto labelHeart = Label::createWithSystemFont("♥", SYSTEM_FONT_NAME, fontSize);
    gui::inst()->setAnchorPoint(labelHeart, ALIGNMENT_LEFT_BOTTOM);
    labelHeart->setPosition(Vec2::ZERO);
    labelHeart->enableGlow(Color4B::BLACK);
    
    size = labelHeart->getContentSize();
    
    if(sz.size() > 0) {
        mLabel = Label::createWithTTF(sz, gui::inst()->mDefaultFont, fontSize);
        mLabel->setColor(color.getColor3B());
        gui::inst()->setAnchorPoint(mLabel, ALIGNMENT_LEFT_BOTTOM);
        
        float margin = size.width * 0.1f;
        mLabel->setPosition(Vec2(size.width + margin, 0));
        size.width += mLabel->getContentSize().width + margin;
        enableGlow(Color4B::BLACK);
    }
    
    this->addChild(labelHeart);
    if(mLabel)
        this->addChild(mLabel);
    
    this->setPosition(pos);
    gui::inst()->setAnchorPoint(this, align);
    this->setContentSize(size);
    
    p->addChild(this);
}

void ui_icon::addCircle(Node * p, Size sizePerGrid, Vec2 pos, ALIGNMENT align, COLOR_RGB color, const string sz, const string szText, COLOR_RGB colorText)
{
    mLabel = NULL;
    Size size;
//    this->setBackGroundColor(Color3B::MAGENTA);
//    this->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    gui::inst()->setAnchorPoint(this, align);
    
    float min = fmin(sizePerGrid.width, sizePerGrid.height);
    
    Size sizeCircle = Size(min, min);
    size = sizeCircle;
    
    float radius = min /2.f;
    
    Color4F colorOut, colorInner, colorOutline;
    Color3B colorSymbol;
    colorOut = color.getColorDark().getColor4F();
    colorInner = color.getColor4F();
//    colorOutline = Color4F::BLACK;//color.getColorDark().getColorDark().getColor4F();
    colorSymbol = color.getColorDark().getColorDark().getColor3B();
    
    auto draw = DrawNode::create();
    Vec2 centerInner = Vec2(sizeCircle.width / 2.f, sizeCircle.height / 2.f);
    
    //outline 적용하면 오히려 지저분해짐
//    draw->drawDot(centerInner, radius, colorOutline);
    
    //outcircle
    draw->drawDot(centerInner, radius, colorOut);
    
    //inner circle
    draw->drawDot(centerInner, radius * 0.8f, colorInner);
    
    //circle text
    float fontSize = gui::inst()->getFontSizeDefine(sizeCircle, -1);
    auto label = Label::createWithSystemFont(sz, SYSTEM_FONT_NAME, fontSize);
    label->setColor(colorSymbol);
    gui::inst()->setAnchorPoint(label, ALIGNMENT_CENTER);
    label->setPosition(centerInner);
    
    //text
    if(szText.size() > 0) {
        float fontSizeText = gui::inst()->getFontSizeDefine(sizeCircle, 0);
        mLabel = Label::createWithTTF(szText, gui::inst()->mDefaultFont, fontSizeText);
        mLabel->setColor(colorText.getColor3B());
        gui::inst()->setAnchorPoint(mLabel, ALIGNMENT_LEFT_BOTTOM);
        enableGlow(Color4B::BLACK);
        
        float margin = size.width * 0.1f;
        mLabel->setPosition(Vec2(sizeCircle.width + margin, 0));
        size.width += mLabel->getContentSize().width + margin;
    }
    
    this->addChild(draw);
    this->addChild(label);
    
    if(mLabel)
        this->addChild(mLabel);
    
    this->setContentSize(size);
    this->setPosition(pos);
    
    p->addChild(this);
}
