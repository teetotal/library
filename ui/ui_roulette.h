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
    
    void addParent(Node * p) {
        p->addChild(mLayer);
    };
    bool setValue(float val, const std::function<void()>& callback);
    static void setValue(float val) {
        mValue = val;
    };
    bool run(const std::function<void()>& callback);
    
    virtual void setPosition(const Vec2 &position) override {
        mLayer->setPosition(position);
    };
    const Vec2& getPosition() const override {
        return mLayer->getPosition();
    };
    virtual void setOpacity(GLubyte opacity) override {  };
    
    bool insertItem(Node * p) {
        if(mItems.size() >= 8)
            return false;
        mItems.push_back(p);
        return true;
    };
    
    static int getResultIdx() {
        float f = mLayerSquare->getRotation();
        return ((int)((90 + fmodf(f, 360.f)) / 45)) % 8;
    };
    
    static float mValue;
    static bool mEnable;
    static Node * mLayerSquare;
    
private:
    Node * mLayer;
    float mRadius;
    Vec2 mCenter;
    void drawArc(float fromDegree, float toDegree, const Color4F color);
    vector<Node *> mItems;
    COLOR_RGB mColor;
    string mStartString;
};
#endif /* ui_roulette_h */
