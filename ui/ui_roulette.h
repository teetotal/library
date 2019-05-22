//
//
//  Created by Jung, DaeCheon on 05/22/2019.
//

#ifndef ui_roulette_h
#define ui_roulette_h

#include "ui.h"
#include "ui_color.h"

class ui_roulette : public Node
{
public:
    static ui_roulette * create() {
        auto ret = new (std::nothrow) ui_roulette;
        
        if (ret)
        {
            ret->autorelease();
        }
        
        return ret;
    };
    
    static ui_roulette * create(Size size
                                , Vec2 center
                                , COLOR_RGB& colorArrow
                                , COLOR_RGB& colorBG
                                , COLOR_RGB& colorOutCircle) {
        auto p = ui_roulette::create();
        p->init(size, center, colorArrow, colorBG, colorOutCircle);
        return p;
    };
    
    void init(Size size
              , Vec2 center
              , COLOR_RGB& colorArrow
              , COLOR_RGB& colorBG
              , COLOR_RGB& colorOutCircle);
    
    void addParent(Node * p) {
        p->addChild(mLayer);
    };
    
    void run(float f);
    virtual void setPosition(const Vec2 &position) override {
        mLayer->setPosition(position);
    };
    const Vec2& getPosition() const override {
        return mLayer->getPosition();
    };
    virtual void setOpacity(GLubyte opacity) override {  };
private:
    Node * mLayer;
    float mRadius;
    Vec2 mCenter;
    void drawArc(float fromDegree, float toDegree, const Color4F color);
    
};
#endif /* ui_roulette_h */
