#include "ui_progressbar.h"

void ui_progressbar::init(UI_PROGRESSBAR_TYPE type
                          , const Vec2 &zeroPosition
                          , const Size &size
                          , COLOR_RGB& color
                          , COLOR_RGB& outline
                          , ALIGNMENT align) {
    mBar = NULL;
    mType = type;
    mAlign = align;
    mColor.set(color);
    
    this->setContentSize(size);
    this->setPosition(zeroPosition);
    
    //outline
    gui::inst()->drawRect(this
                         , Vec2(size.width / 2.f, size.height / 2.f)
                         , size
                         , outline.getColor4F());
    
    //bg
    Color4F colorBG;
    switch(mType) {
        case UI_PROGRESSBAR_TYPE_2:
            colorBG = Color4F::BLACK;
            break;
        case UI_PROGRESSBAR_TYPE_3:
            colorBG = Color4F::WHITE;
            break;
        default:
            colorBG = color.getColor4F(COLOR_RGB_TYPE_DARK, mDarkBG);
            break;
    }
    
    mMargin = size.height * 0.05f;
    Size s90 = Size(size.width - (mMargin * 2.f), size.height - (mMargin * 2.f));
    
    gui::inst()->drawRect(this
                        , Vec2(size.width / 2.f, size.height / 2.f)
                        , s90
                        , colorBG);
}

void ui_progressbar::setValue(float f) {
    Size size = this->getContentSize();
    float margin2 = mMargin + (mMargin * .5f);
    Size value = Size(size.width * f - (margin2 * 2.f), size.height - (margin2 * 2.f));
    Size value2 = Size(value.width, value.height / 2.f);
    
    if(mBar) {
        this->removeChild(mBar);
    }
    mBar = DrawNode::create();
    switch(mType) {
        case UI_PROGRESSBAR_TYPE_0: {
            Vec2 origin, dest;
            if(mAlign == ALIGNMENT_RIGHT) {
                origin = Vec2(size.width - mMargin, margin2);
                dest = Vec2(origin.x - value.width, origin.y + value.height);
            } else {
                origin = Vec2(mMargin, margin2);
                dest = Vec2(origin.x + value.width, origin.y + value.height);
            }
            mBar->drawSolidRect(origin, dest, mColor.getColor4F());
            
            break;
        }
        default: {
            Vec2 origin1, dest1, origin2, dest2;
            if(mAlign == ALIGNMENT_RIGHT) {
                origin2 = Vec2(size.width - mMargin, margin2);
                dest2 = Vec2(origin2.x - value2.width, origin2.y + value2.height);
                
                origin1 = Vec2(size.width - mMargin, dest2.y);
                dest1 = Vec2(dest2.x, origin1.y + value2.height);
            } else {
                origin2 = Vec2(mMargin, margin2);
                dest2 = Vec2(origin2.x + value2.width, origin2.y + value2.height);
                
                origin1 = Vec2(mMargin, dest2.y);
                dest1 = Vec2(dest2.x, origin1.y + value2.height);
            }
            mBar->drawSolidRect(origin1, dest1, mColor.getColor4F());
            mBar->drawSolidRect(origin2, dest2, mColor.getColor4F(COLOR_RGB_TYPE_DARK, mDarkValue));
            break;
        }
    }
   
    this->addChild(mBar);
}
