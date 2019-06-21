//
//  ui_button.h
//
//  Created by Jung, DaeCheon on 21/06/2019.
//

#ifndef ui_button_h
#define ui_button_h


#include "ui.h"
#include "ui_color.h"

class ui_button : public Layout
{
public:
    enum TYPE {
        TYPE_ROUND,
        TYPE_CIRCLE,
    };
    
    enum TOUCH_TYPE {
        TOUCH_TYPE_NORMAL,
        TOUCH_TYPE_AUTO_DISABLE,
    };
    
    static ui_button * create() {
        ui_button * ret = new (std::nothrow) ui_button;
        if (ret)
        {
            ret->autorelease();
        } else {
            CC_SAFE_DELETE(ret);
        }
        
        return ret;
    };
    
    ui_button() : mEnable(true) {};
    
    void init(int target
              , const string text
              , Node * p
              , Vec2 pos
              , ALIGNMENT align
              , Size size
              , TYPE type
              , std::function<void(int)> callback
              , COLOR_RGB color
              , COLOR_RGB colorFont
              , COLOR_RGB colorBack = COLOR_RGB()
              , const string img = ""
              , TOUCH_TYPE touchType = TOUCH_TYPE_NORMAL);
    
    inline void setText(const string sz) {
        if(mNodes.label) {
            mNodes.label->setString(sz);
        }
    };
    inline void setTextColor(const Color3B& color) {
        if(mNodes.label) {
            mNodes.label->setColor(color);
        }
    };
    inline void enableGlow(const Color4B& color) {
        if(mNodes.label) {
            mNodes.label->enableGlow(color);
        }
    };
    
    inline bool isEnabled() const {
        return mEnable;
    };
    //터치 이벤트 효과
    void runScaleAndDisable();
    
    void setEnabled(bool enable);
    
private:
    struct Nodes {
        Label * label;
        DrawNode * drawNode;
        Sprite * sprite;
        
        Nodes() : label(NULL), drawNode(NULL), sprite(NULL) {};
    } mNodes;
    
    bool mEnable;
    
    void setTouchEvent(std::function<void(int)> callback);
    void drawRectRoundShadow (COLOR_RGB color);
    void drawRectCircleButton(COLOR_RGB colorFront, COLOR_RGB colorBack);
    int mId;
    TOUCH_TYPE mTouchType;
};

#endif /* ui_button_h */
