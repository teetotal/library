//
//
//  Created by Jung, DaeCheon on 05/18/2019.
//

#ifndef ui_progressbar_h
#define ui_progressbar_h

#include "ui.h"
#include "ui_color.h"

enum UI_PROGRESSBAR_TYPE {
    UI_PROGRESSBAR_TYPE_0 = 0,  // 평면
    UI_PROGRESSBAR_TYPE_1,      // 입체
};

class ui_progressbar : public Layout
{
public:
    static ui_progressbar * create() {
        ui_progressbar * ret = new (std::nothrow) ui_progressbar;
        if (ret)
        {
            ret->autorelease();
        } else {
             CC_SAFE_DELETE(ret);
        }
        
        return ret;
    };
    
    static ui_progressbar * create(UI_PROGRESSBAR_TYPE type
                                   , float value
                                   , const Vec2 &position
                                   , const Size &size
                                   , COLOR_RGB& color
                                   , COLOR_RGB& outline
                                   , ALIGNMENT align = ALIGNMENT_LEFT) {
        auto p = ui_progressbar::create();
        p->init(type, position, size, color, outline, align);
        p->setValue(value);
        return p;
    };
    
    void init(UI_PROGRESSBAR_TYPE type
              , const Vec2 &position
              , const Size &size
              , COLOR_RGB& color
              , COLOR_RGB& bgColor
              , ALIGNMENT align = ALIGNMENT_LEFT);
    
    void addParent(Node * p) {
        p->addChild(this);
    };
    const float getValue() {
        return mValue;
    };
    const float setValue(float f);
    const float setValueIncrese(float f) {
        if(mValue >= 1.f)
            return 1.f;
        return setValue(mValue + f);
    };
    const float setValueDecrese(float f) {
        if(mValue <= 0.f)
            return 0.f;
        return setValue(mValue - f);
    };
    void blink(float duration = 0.5f, int blinks = 2);
    void setText(const string sz);
private:
    DrawNode * mBar;
    float mMargin;
    COLOR_RGB mColor;
    ALIGNMENT mAlign;
    UI_PROGRESSBAR_TYPE mType;
    
    const int mDarkValue = 20;
    const int mDarkBG = 50;
    
    float mValue;
    Label * mLabel;
    
    bool mLockBlink; //blink효과에 대한 lock
    
    enum ZORDER {
        ZORDER_BG = 0,
        ZORDER_VALUE = 1,
        ZORDER_TEXT,
        ZORDER_PERCENTAGE
    };
};
#endif /* ui_progressbar_h */
