//
//
//  Created by Jung, DaeCheon on 05/18/2019.
//

#ifndef ui_progressbar_h
#define ui_progressbar_h

#include "ui.h"
#include "ui_color.h"

enum UI_PROGRESSBAR_TYPE {
    UI_PROGRESSBAR_TYPE_0 = 0,  // 평면, dark 배경
    UI_PROGRESSBAR_TYPE_1,      // 입체, dark 배경
    UI_PROGRESSBAR_TYPE_2,      // 입체, black 배경
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
              , COLOR_RGB& outline
              , ALIGNMENT align = ALIGNMENT_LEFT);
    
    void addParent(Node * p) {
        p->addChild(this);
    };
    
    void setValue(float f);
    
private:
    DrawNode * mBar;
    float mMargin;
    COLOR_RGB mColor;
    ALIGNMENT mAlign;
    UI_PROGRESSBAR_TYPE mType;
    
    const int mDarkValue = 20;
    const int mDarkBG = 50;
};
#endif /* ui_progressbar_h */
