//
//  ui_icon.h
//
//  Created by Jung, DaeCheon on 19/06/2019.
//

#ifndef ui_icon_h
#define ui_icon_h

#include "ui.h"
#include "ui_color.h"

class ui_icon : public Layout
{
public:
    static ui_icon * create() {
        ui_icon * ret = new (std::nothrow) ui_icon;
        if (ret)
        {
            ret->autorelease();
        } else {
            CC_SAFE_DELETE(ret);
        }
        
        return ret;
    };
    
    void addHeart(Node * p, Size sizePerGrid, Vec2 pos, ALIGNMENT align, const string sz = "", COLOR_RGB color = COLOR_RGB());
    void addCircle(Node * p, Size sizePerGrid, Vec2 pos, ALIGNMENT align, COLOR_RGB color, const string sz, const string szText = "", COLOR_RGB colorText = COLOR_RGB());
    
    inline void setText(const string sz) {
        if(mLabel) {
            mLabel->setString(sz);
        }
    };
    inline void setTextColor(const Color3B& color) {
        if(mLabel) {
            mLabel->setColor(color);
        }
    };
    inline void enableGlow(const Color4B& color) {
        if(mLabel) {
            mLabel->enableGlow(color);
        }
    };
    
private:
    Label * mLabel;
};
#endif /* ui_icon_h */
