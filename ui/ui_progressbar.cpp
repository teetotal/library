#include "ui_progressbar.h"

void ui_progressbar::init(const Vec2 &zeroPosition, const Size &size, COLOR_RGB& color, COLOR_RGB& outline, ALIGNMENT align) {
    mBar = NULL;
    mAlign = align;
    mColor.set(color);
    
    mLayer = gui::inst()->createLayout(size);
    mLayer->setPosition(zeroPosition);
    
    //outline
    gui::inst()->drawRect(mLayer
                         , Vec2(size.width / 2.f, size.height / 2.f)
                         , size
                         , outline.getColor4F());
    
    //bg
    Color4F colorBG = color.getColor4F(COLOR_RGB_TYPE_DARK, 50);
    mMargin = size.height * 0.05f;
    Size s90 = Size(size.width - (mMargin * 2.f), size.height - (mMargin * 2.f));
    
    gui::inst()->drawRect(mLayer
                        , Vec2(size.width / 2.f, size.height / 2.f)
                        , s90
                        , colorBG);
}

void ui_progressbar::setValue(float f) {
    Size size = mLayer->getContentSize();
    float margin2 = mMargin + (mMargin * .5f);
    Size value = Size(size.width * f - (margin2 * 2.f), size.height - (margin2 * 2.f));
    if(mBar) {
        mLayer->removeChild(mBar);
    }
    mBar = DrawNode::create();
    Vec2 origin, dest;
    if(mAlign == ALIGNMENT_RIGHT) {
        origin = Vec2(size.width - margin2, margin2);
        dest = Vec2(origin.x - value.width, margin2 + value.height);
    } else {
        origin = Vec2(margin2, margin2);
        dest = Vec2(margin2 + value.width, margin2 + value.height);
    }
    mBar->drawSolidRect(origin, dest, mColor.getColor4F());
    mLayer->addChild(mBar);
}
