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
    static ui_icon * create(bool isGlow = true, const Color4B& color = Color4B::BLACK) {
        ui_icon * ret = new (std::nothrow) ui_icon;
        if (ret)
        {
            ret->setGlow(isGlow, color);
            ret->autorelease();
        } else {
            CC_SAFE_DELETE(ret);
        }
        
        return ret;
    };
    ui_icon() : mEnable(true), mEnableGlow(true), mColorGlow(Color4B::BLACK) {};
    
    void addHeart(Node * p
                  , Size sizePerGrid
                  , Vec2 pos
                  , ALIGNMENT align
                  , const string sz = ""
                  , COLOR_RGB color = COLOR_RGB()
                  , const float fontSize = 0);
    
    void addCircle(Node * p
                   , Size sizePerGrid
                   , Vec2 pos
                   , ALIGNMENT align
                   , COLOR_RGB color
                   , const string sz
                   , const string img = ""
                   , const string szText = ""
                   , COLOR_RGB colorText = COLOR_RGB()
                   , const float fontSize = 0);
    
    void setText(const string sz);
    
    inline void setTextColor(const Color3B& color) {
        if(mNodes.label) {
            mNodes.label->setColor(color);
        }
    };
    
    inline void setGlow(bool isGlow, const Color4B& color = Color4B::BLACK) {
        mEnableGlow = isGlow;
        mColorGlow = color;
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
        Label * ch;
        Sprite * sprite;
        
        Nodes() : label(NULL), drawNode(NULL), ch(NULL), sprite(NULL) {};
    } mNodes;
    
    bool mEnable;
    bool mEnableGlow;
    Color4B mColorGlow;
};
#endif /* ui_icon_h */
