//
//
//  Created by Jung, DaeCheon on 05/18/2019.
//

#ifndef ui_progressbar_h
#define ui_progressbar_h

#include "ui.h"
#include "ui_color.h"

class ui_progressbar : public Node
{
public:
    static ui_progressbar * create() {
        auto ret = new (std::nothrow) ui_progressbar;
        
        if (ret)
        {
            ret->autorelease();
        }
        
        return ret;
    };
    
    static ui_progressbar * create(float value, const Vec2 &position, const Size &size, COLOR_RGB& color, COLOR_RGB& outline, ALIGNMENT align = ALIGNMENT_LEFT) {
        auto p = ui_progressbar::create();
        p->init(position, size, color, outline, align);
        p->setValue(value);
        return p;
    };
    
    void init(const Vec2 &position, const Size &size, COLOR_RGB& color, COLOR_RGB& outline, ALIGNMENT align = ALIGNMENT_LEFT);
    
    void addParent(Node * p) {
        p->addChild(mLayer);
    };
    
    void setValue(float f);
    virtual void setPosition(const Vec2 &position) override {
        mLayer->setPosition(position);
    };
    const Vec2& getPosition() const override {
        return mLayer->getPosition();
    };
    virtual void setOpacity(GLubyte opacity) override {  };
private:
    Node * mLayer;
    DrawNode * mBar;
    float mMargin;
    COLOR_RGB mColor;
    ALIGNMENT mAlign;
};
#endif /* ui_progressbar_h */
