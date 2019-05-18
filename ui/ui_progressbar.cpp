#include "ui_progressbar.h"

void ui_progressbar::init(const Vec2 &zeroPosition, const Size &size, COLOR_RGB& color, COLOR_RGB& outline, ALIGNMENT align) {
    mBar = NULL;
    mAlign = align;
    mColor.set(color);
    
    mLayer = gui::inst()->createLayout(size);
    mLayer->setPosition(zeroPosition);
    
    mMargin = size.height * 0.05f;
    Size s90 = Size(size.width - (mMargin * 2.f), size.height - (mMargin * 2.f));
    
    
    gui::inst()->drawRect(mLayer
                         , Vec2(size.width / 2.f, size.height / 2.f)
                         , size
                         , outline.getColor4F());
    
    Color4F colorBG = color.getColor4F();
    float f = 0.4f;
    colorBG.r = std::fmax(colorBG.r - f, 0.f);
    colorBG.g = std::fmax(colorBG.g - f, 0.f);
    colorBG.b = std::fmax(colorBG.b - f, 0.f);
    
    
    gui::inst()->drawRect(mLayer
                        , Vec2(size.width / 2.f, size.height / 2.f)
                        , s90
                        , colorBG);
}

void ui_progressbar::setValue(float f) {
    Size size = mLayer->getContentSize();
    Size value = Size(size.width * f, size.height - (mMargin * 2.f));
    if(mBar) {
        mLayer->removeChild(mBar);
    }
    mBar = DrawNode::create();
    Vec2 origin, dest;
    if(mAlign == ALIGNMENT_RIGHT) {
        origin = Vec2(size.width - mMargin, mMargin);
        dest = Vec2(origin.x - value.width, mMargin + value.height);
    } else {
        origin = Vec2(mMargin, mMargin);
        dest = Vec2(mMargin + value.width, mMargin + value.height);
    }
    mBar->drawSolidRect(origin, dest, mColor.getColor4F());
    mLayer->addChild(mBar);
}
