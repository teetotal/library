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
    
    static ui_button * create(int id
                              , int target
                              , const string text
                              , Node * p
                              , Vec2 pos
                              , ALIGNMENT align
                              , Size size
                              , TYPE type
                              , std::function<void(int, int)> callback
                              , COLOR_RGB color
                              , COLOR_RGB colorFont
                              , COLOR_RGB colorBack = COLOR_RGB()
                              , const string img = ""
                              , TOUCH_TYPE touchType = TOUCH_TYPE_NORMAL)
    {
        ui_button * ret = ui_button::create();
        ret->init(id
                  , target
                  , text
                  , p
                  , pos
                  , align
                  , size
                  , type
                  , callback
                  , color
                  , colorFont
                  , colorBack
                  , img
                  , touchType);
        return ret;
    }
    
    ui_button() : mEnable(true) {};
    
    void init(int id
              , int target
              , const string text
              , Node * p
              , Vec2 pos
              , ALIGNMENT align
              , Size size
              , TYPE type
              , std::function<void(int, int)> callback
              , COLOR_RGB color
              , COLOR_RGB colorFont
              , COLOR_RGB colorBack = COLOR_RGB()
              , const string img = ""
              , TOUCH_TYPE touchType = TOUCH_TYPE_NORMAL);
    
    inline void setText(const string sz) {
        if(mNodes.menuItem) {
            mNodes.menuItem->setString(sz);
        }
    };
    inline void setTextColor(const Color3B& color) {
        if(mNodes.menuItem) {
            mNodes.menuItem->setColor(color);
        }
    };
    
    inline bool isEnabled() const {
        return mEnable;
    };
    
    inline void setTouchType(TOUCH_TYPE t) {
        mTouchType = t;
    };
    //터치 이벤트 효과
    void runScaleAndDisable();
    
    void setEnabled(bool enable);
    
private:
    struct Nodes {
        
        MenuItemLabel * menuItem;
        MenuItemImage * menuItemImage;
        DrawNode * drawNode;
        Nodes() : drawNode(NULL), menuItem(NULL), menuItemImage(NULL) {};
    } mNodes;
    
    bool mEnable;
    void callbackFn(cocos2d::Ref* pSender);
    void drawRectRoundShadow (COLOR_RGB color);
    void drawRectCircleButton(COLOR_RGB colorFront, COLOR_RGB colorBack);
    int mId, mTarget;
    TOUCH_TYPE mTouchType;
    std::function<void(int, int)> mCallback;
};

class ui_checkbox : public Layout
{
public:
    static ui_checkbox * create() {
        ui_checkbox * ret = new (std::nothrow) ui_checkbox;
        if (ret)
        {
            ret->autorelease();
        } else {
            CC_SAFE_DELETE(ret);
        }
        
        return ret;
    };
    
    static ui_checkbox * create(Node * p
                                , Vec2 pos
                                , ALIGNMENT align
                                , Size sizePerGrid
                                , int sizeDefine
                                , const string text
                                , COLOR_RGB color
                                , COLOR_RGB colorFont)
    {
        ui_checkbox * ret = ui_checkbox::create();
        ret->init(p
                  , pos
                  , align
                  , sizePerGrid
                  , sizeDefine
                  , text
                  , color
                  , colorFont);
        return ret;
    }
    
    ui_checkbox() : mEnable(true), mIsChecked(true) {};
    
    void init(Node * p
              , Vec2 pos
              , ALIGNMENT align
              , Size sizePerGrid
              , int sizeDefine
              , const string text
              , COLOR_RGB color
              , COLOR_RGB colorFont);
    
    void setText(const string sz);
    
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
    
    void setEnabled(bool enable);
    
    inline bool isChecked() const {
        return mIsChecked;
    };
    
    void setChecked(bool isChecked);
    inline void setToggle() {
        setChecked(!mIsChecked);
    };
private:
    struct Nodes {
        Label * label;
        Label * labelChecked;
        DrawNode * drawNode;
        Nodes() : drawNode(NULL), label(NULL), labelChecked(NULL) {};
    } mNodes;
    
    bool mEnable, mIsChecked;
    void drawUnchecked(COLOR_RGB color);
    
    Size mCheckboxSize;
};
#endif /* ui_button_h */
