//
//
//  Created by Jung, DaeCheon on 05/22/2019.
//

#ifndef ui_roulette_h
#define ui_roulette_h

#include "ui.h"
#include "ui_color.h"

class ui_roulette : public Layout
{
public:
    static ui_roulette * create() {
        ui_roulette * ret = new (std::nothrow) ui_roulette;
        
        if (ret)
        {
            ret->autorelease();
        } else {
             CC_SAFE_DELETE(ret);
        }
        
        return ret;
    };
    
    static ui_roulette * create(Size size
                                , Vec2 center
                                , COLOR_RGB& color
                                , COLOR_RGB& colorBG
                                , const string szStart) {
        auto p = ui_roulette::create();
        p->init(size, center, color, colorBG, szStart);
        return p;
    };
    
    void init(Size size
              , Vec2 center
              , COLOR_RGB& color
              , COLOR_RGB& colorBG
              , const string szStart);
    
    void clear() {
        mItemsIdx = 0;
    };
    
    void addParent(Node * p) {
        p->addChild(this);
    };
    bool setValue(float val, const ccMenuCallback& callback);
    void setValue(float val) {
        mValue = val;
    };
    
    bool run(const ccMenuCallback& callback);
    /*
    virtual void setPosition(const Vec2 &position) override {
        this->setPosition(position);
    };
    const Vec2& getPosition() const override {
        return this->getPosition();
    };
    virtual void setOpacity(GLubyte opacity) override {  };
    */
    bool insertItem(Node * p) {
        if(mItemsIdx >= 8) {
            return false;
        }
        mItems[mItemsIdx] = p;
        mItemsIdx++;
        return true;
    };
    
    int getResultIdx() {
        float f = mLayerSquare->getRotation();
        return ((int)((90 + fmodf(f, 360.f)) / 45)) % 8;
    };
  
    float mValue;
    bool mEnable;
    Node * mLayerSquare;
    ui_roulette * mThis;
    float mRadius;
    
private:
    COLOR_RGB mColor;
    Node * mItems[8];
    int mItemsIdx;
    string mStartString;
    Vec2 mCenter;
    
    void drawArc(float fromDegree, float toDegree, const Color4F color);
    
};
#endif /* ui_roulette_h */
