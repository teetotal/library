//
//  ui_effect.h
//
//  Created by Jung, DaeCheon on 17/07/2019.
//

#ifndef ui_effect_h
#define ui_effect_h

#include "ui.h"
#include "ui_color.h"

class ui_effect : public Layout
{
public:
    static ui_effect * create() {
        ui_effect * ret = new (std::nothrow) ui_effect;
        if (ret)
        {
            ret->autorelease();
        } else {
            CC_SAFE_DELETE(ret);
        }
        
        return ret;
    };
    
    void addBG(Node * parent, COLOR_RGB color, bool isRunRotate = false);
    void runBGRotate(float duration = 10.f);
    void stopRotate();
    
private:
    void drawArc(Node * layer, float radius, float fromDegree, float toDegree, const Color4F color);
    Layout * mBGLayer;
    LayerRadialGradient * mBGGradientLayer;
};
#endif /* ui_effect_h */
